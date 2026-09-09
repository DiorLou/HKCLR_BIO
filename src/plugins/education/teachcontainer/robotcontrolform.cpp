#include "robotcontrolform.h"
#include "communication.h"
#include "communicationengine.h"

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHash>
#include <QFile>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollArea>
#include <QSlider>
#include <QTimer>
#include <QVBoxLayout>

namespace {
QLineEdit *valueEdit(const QString &text = QStringLiteral("0.00"), bool readOnly = false)
{
    auto *edit = new QLineEdit(text);
    edit->setAlignment(Qt::AlignCenter);
    edit->setReadOnly(readOnly);
    if (readOnly)
        edit->setProperty("displayValue", true);
    return edit;
}

QPushButton *button(const QString &text)
{
    auto *result = new QPushButton(text);
    result->setMinimumHeight(26);
    return result;
}

QGroupBox *group(const QString &title, QLayout *layout)
{
    auto *result = new QGroupBox(title);
    result->setLayout(layout);
    return result;
}
}

RobotControlForm::RobotControlForm(QWidget *parent) : QWidget(parent)
{
    setObjectName(QStringLiteral("robotControlForm"));
    setStyleSheet(QStringLiteral(
        "#robotControlForm { background:#f2f4f7; }"
        "#robotControlForm QGroupBox { background:white; border:1px solid #d9dee7;"
        " border-radius:5px; margin-top:9px; padding-top:7px; font-weight:600; }"
        "#robotControlForm QGroupBox::title { subcontrol-origin:margin; left:10px; padding:0 4px; }"
        "#robotControlForm QLineEdit[displayValue='true'], #robotControlForm QTextEdit {"
        " background:#eceff3; color:#333; }"
        "#robotControlForm QPushButton { padding:4px 8px; }"
        "#emergencyStop { background:#d9363e; color:white; font-weight:700; }"));

    auto *columns = new QHBoxLayout(this);
    columns->setContentsMargins(5, 5, 5, 5);
    columns->setSpacing(6);
    for (QWidget *panel : {createLeftPanel(), createRightPanel()}) {
        auto *scroll = new QScrollArea;
        scroll->setWidgetResizable(true);
        scroll->setFrameShape(QFrame::NoFrame);
        scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll->setWidget(panel);
        columns->addWidget(scroll, 1);
    }

    auto *realtimeTimer = new QTimer(this);
    realtimeTimer->setInterval(100);
    connect(realtimeTimer, &QTimer::timeout,
            this, &RobotControlForm::updateRealtimeStatus);
    realtimeTimer->start();
}

QWidget *RobotControlForm::createLeftPanel()
{
    auto *panel = new QWidget;
    auto *layout = new QVBoxLayout(panel);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(4);

    auto *top = new QHBoxLayout;
    auto *jointLayout = new QVBoxLayout;
    const auto connectJogButton = [this](QPushButton *jogButton, int axisId,
                                         bool isPositive, RobotCoordType coordType) {
        connect(jogButton, &QPushButton::pressed, this,
                [this, axisId, isPositive, coordType] {
            if (!Communication::instance()->isConnected())
                return;

            if (Communication::instance()->GetCurCoodType() != coordType) {
                CommunicationEngine::instance()->enqueueCmd_setData(
                    this, AbstractCmd::CmdType_Control_SetCoordType, coordType);
            }
            CommunicationEngine::instance()->enqueueCmd_axisMove(
                this, axisId, isPositive, true);
        });
        connect(jogButton, &QPushButton::released, this,
                [this, axisId, isPositive] {
            if (!Communication::instance()->isConnected())
                return;

            CommunicationEngine::instance()->enqueueCmd_axisMove(
                this, axisId, isPositive, false);
        });
    };
    for (int i = 0; i < 6; ++i) {
        auto *row = new QHBoxLayout;
        row->addWidget(new QLabel(tr("Joint %1 (q%1):").arg(i + 1)));
        auto *edit = valueEdit(QStringLiteral("0.00"), true);
        m_jointValueEdits[i] = edit;
        edit->setMaximumWidth(75);
        row->addWidget(edit);
        row->addStretch();
        auto *minus = button(QStringLiteral("−"));
        auto *plus = button(QStringLiteral("+"));
        minus->setFixedWidth(34); plus->setFixedWidth(34);
        connectJogButton(minus, i, false, RobotCoordType_Joint);
        connectJogButton(plus, i, true, RobotCoordType_Joint);
        row->addWidget(minus); row->addWidget(plus);
        jointLayout->addLayout(row);
    }
    auto *initializeJointPosition = button(tr("Initialize Joint Position"));
    initializeJointPosition->setToolTip(
        tr("Move the robot to the initial posture stored in the controller"));
    connect(initializeJointPosition, &QPushButton::clicked, this, [this] {
        if (!Communication::instance()->isConnected())
            return;

        CommunicationEngine::instance()->enqueueCmd(
            this, AbstractCmd::CmdType_RobotMoveJointToInitPosture);
    });
    jointLayout->addWidget(initializeJointPosition, 0, Qt::AlignCenter);
    top->addWidget(group(tr("Motor Fine-tuning Module (Forward Kinematics)"), jointLayout), 4);

    auto *speedLayout = new QVBoxLayout;
    auto *speed = new QSlider(Qt::Vertical);
    speed->setRange(1, 100); speed->setValue(1);
    speed->setTickPosition(QSlider::TicksBothSides);
    speed->setTickInterval(10);
    speed->setToolTip(tr("Controller speed override: 1% to 100%"));
    auto *speedLabel = new QLabel(tr("Motion Speed: 0.01"));
    speedLayout->addWidget(speedLabel, 0, Qt::AlignCenter);
    speedLayout->addWidget(speed, 1, Qt::AlignCenter);
    speedLayout->addWidget(new QLabel(tr("Current Motion Speed:")), 0, Qt::AlignCenter);
    auto *currentSpeed = valueEdit(QStringLiteral("0.00"), true);
    currentSpeed->setFixedWidth(75);
    speedLayout->addWidget(currentSpeed, 0, Qt::AlignCenter);

    // The Python UI represents the override as 0.01 ... 1.00, while the
    // controller SetSpeed API expects the exactly equivalent 1 ... 100 percent.
    const auto updateSpeedDisplay = [speedLabel](int percent) {
        speedLabel->setText(
            QObject::tr("Motion Speed: %1").arg(percent / 100.0, 0, 'f', 2));
    };
    const auto updateCurrentSpeed = [speed, currentSpeed](int percent) {
        const int boundedPercent = qBound(speed->minimum(), percent, speed->maximum());
        speed->setValue(boundedPercent);
        currentSpeed->setText(QString::number(boundedPercent / 100.0, 'f', 2));
    };

    connect(speed, &QSlider::valueChanged, this, updateSpeedDisplay);
    connect(speed, &QSlider::sliderReleased, this, [this, speed] {
        if (!Communication::instance()->isConnected())
            return;

        CommunicationEngine::instance()->enqueueCmd_setData(
            this, AbstractCmd::CmdType_Control_SetSpeed, speed->value());
    });
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_setspeed_result,
            this, [updateCurrentSpeed](bool isSuccess, int percent) {
                if (isSuccess)
                    updateCurrentSpeed(percent);
            });
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_speed_changed,
            this, [updateCurrentSpeed](quint16 percent) {
                updateCurrentSpeed(static_cast<int>(percent));
            });
    top->addWidget(group(tr("Motion Speed"), speedLayout), 1);
    layout->addLayout(top);

    auto *toolGrid = new QGridLayout;
    const QStringList poses{QStringLiteral("Tcp_X"), QStringLiteral("Tcp_Y"), QStringLiteral("Tcp_Z"),
                            QStringLiteral("Tcp_Rx\n(Roll)"), QStringLiteral("Tcp_Ry\n(Pitch)"),
                            QStringLiteral("Tcp_Rz\n(Yaw)")};
    for (int i = 0; i < poses.size(); ++i) {
        const int col = (i % 3) * 2;
        const int row = (i / 3) * 2;
        toolGrid->addWidget(new QLabel(poses[i]), row, col);
        auto *edit = valueEdit(QStringLiteral("0.00"), true);
        m_tcpValueEdits[i] = edit;
        toolGrid->addWidget(edit, row, col + 1);
        auto *controls = new QHBoxLayout;
        auto *minus = button(QStringLiteral("−"));
        auto *plus = button(QStringLiteral("+"));
        connectJogButton(minus, i, false, RobotCoordType_Tool);
        connectJogButton(plus, i, true, RobotCoordType_Tool);
        controls->addWidget(minus);
        controls->addWidget(plus);
        toolGrid->addLayout(controls, row + 1, col, 1, 2);
    }
    auto *fineTuneProbe = button(tr("Fine tune probe"));
    fineTuneProbe->setEnabled(false);
    fineTuneProbe->setToolTip(tr(
        "Requires the ultrasound alignment and navigation calculation module"));
    toolGrid->addWidget(fineTuneProbe, 4, 0, 1, 6, Qt::AlignCenter);
    layout->addWidget(group(tr("Robot Tool Real-time Status"), toolGrid));

    auto *points = new QVBoxLayout;
    addPoseEditor(points, tr("A Point"), QStringLiteral("A"), tr("Get A Point Position"));
    addPoseEditor(points, tr("O Point"), QStringLiteral("O"), tr("Get O Point Position"));
    addPoseEditor(points, tr("End-Effect"), QStringLiteral("E"), tr("Get End-Effect Position"));
    auto *rotateToPuncture = button(
        tr("Rotate the ultrasound plane to pass through the puncture point"));
    rotateToPuncture->setEnabled(false);
    rotateToPuncture->setToolTip(tr(
        "Requires the Python ultrasound alignment and navigation calculation module"));
    points->addWidget(rotateToPuncture);
    layout->addWidget(group(tr("Robot A, O, and End-Effect Positions"), points));

    auto *lesion = new QVBoxLayout;
    auto *bRow = new QHBoxLayout;
    for (const QString &axis : {QStringLiteral("x"), QStringLiteral("y"), QStringLiteral("z")}) {
        bRow->addWidget(new QLabel(QStringLiteral("B_%1:").arg(axis)));
        bRow->addWidget(valueEdit());
    }
    auto *bPoints = new QComboBox;
    bPoints->addItem(tr("Please read TXT file first"));
    bPoints->setEnabled(false);
    bRow->addWidget(bPoints);
    lesion->addLayout(bRow);
    auto *loadRow = new QHBoxLayout;
    auto *readReplanA = button(tr("Read A Points (Volume) from Replan File"));
    auto *readReplanB = button(tr("Read B Points (Volume) from Replan File"));
    readReplanA->setEnabled(false);
    readReplanB->setEnabled(false);
    readReplanA->setToolTip(tr("Replan coordinate conversion is not implemented yet"));
    readReplanB->setToolTip(tr("Replan coordinate conversion is not implemented yet"));
    loadRow->addWidget(readReplanA);
    loadRow->addWidget(readReplanB);
    lesion->addLayout(loadRow);
    auto *rotateToBiopsy = button(
        tr("Rotate the ultrasound plane to pass through the biopsy point"));
    rotateToBiopsy->setEnabled(false);
    rotateToBiopsy->setToolTip(tr(
        "Requires the biopsy planning and navigation calculation module"));
    lesion->addWidget(rotateToBiopsy);
    layout->addWidget(group(tr("Lesion B Point Localization"), lesion));

    auto *save = new QHBoxLayout;
    auto *saveButton = button(tr("Save"));
    auto *loadButton = button(tr("Load"));
    connect(saveButton, &QPushButton::clicked,
            this, &RobotControlForm::savePointData);
    connect(loadButton, &QPushButton::clicked,
            this, &RobotControlForm::loadPointData);
    save->addStretch(); save->addWidget(saveButton); save->addWidget(loadButton); save->addStretch();
    layout->addWidget(group(tr("Save Current Data"), save));
    layout->addStretch();
    return panel;
}

void RobotControlForm::updateRealtimeStatus()
{
    if (!Communication::instance()->isConnected())
        return;

    const RoadPoint point = Communication::instance()->GetRealTimePt();
    for (int i = 0; i < static_cast<int>(m_jointValueEdits.size()); ++i)
        m_jointValueEdits[i]->setText(QString::number(point.m_jointAngle[i], 'f', 3));

    const std::array<double, 6> tcpValues{
        point.m_position.m_x,
        point.m_position.m_y,
        point.m_position.m_z,
        point.m_orientation.m_rx,
        point.m_orientation.m_ry,
        point.m_orientation.m_rz
    };
    for (int i = 0; i < static_cast<int>(m_tcpValueEdits.size()); ++i)
        m_tcpValueEdits[i]->setText(QString::number(tcpValues[i], 'f', 3));
}

void RobotControlForm::addPoseEditor(QVBoxLayout *layout, const QString &title,
                                     const QString &prefix, const QString &buttonText)
{
    auto *row = new QHBoxLayout;
    std::array<QLineEdit *, 3> *pointEdits = nullptr;
    if (prefix == QStringLiteral("A"))
        pointEdits = &m_aPointEdits;
    else if (prefix == QStringLiteral("O"))
        pointEdits = &m_oPointEdits;
    else if (prefix == QStringLiteral("E"))
        pointEdits = &m_ePointEdits;

    int axisIndex = 0;
    for (const QString &axis : {QStringLiteral("x"), QStringLiteral("y"), QStringLiteral("z")}) {
        row->addWidget(new QLabel(QStringLiteral("%1_%2:").arg(prefix, axis)));
        auto *edit = valueEdit();
        if (pointEdits)
            (*pointEdits)[axisIndex++] = edit;
        row->addWidget(edit);
    }
    auto *capture = button(buttonText);
    const QString toolName = prefix == QStringLiteral("E")
        ? QStringLiteral("TCP_E") : QStringLiteral("TCP_tip");
    connect(capture, &QPushButton::clicked, this,
            [this, prefix, toolName] { capturePoint(prefix, toolName); });
    if (prefix == QStringLiteral("A")) {
        row->addWidget(capture);
        m_aHistoryCombo = new QComboBox;
        m_aHistoryCombo->setPlaceholderText(tr("History (Empty)"));
        connect(m_aHistoryCombo, &QComboBox::currentIndexChanged,
                this, [this](int index) {
            if (index < 0 || index >= m_aPointHistory.size())
                return;
            const auto &point = m_aPointHistory[index];
            for (int i = 0; i < static_cast<int>(point.size()); ++i)
                m_aPointEdits[i]->setText(QString::number(point[i], 'f', 3));
        });
        row->addWidget(m_aHistoryCombo);
    } else {
        row->addWidget(capture);
    }
    layout->addWidget(group(title, row));
}

void RobotControlForm::capturePoint(const QString &prefix, const QString &toolName)
{
    if (!Communication::instance()->isConnected())
        return;

    const QStringList toolNames = Communication::instance()->getCurToolNames();
    int toolId = -1;
    for (int i = 0; i < toolNames.size(); ++i) {
        if (toolNames[i].compare(toolName, Qt::CaseInsensitive) == 0) {
            toolId = i;
            break;
        }
    }
    if (toolId < 0) {
        QMessageBox::warning(
            this, tr("Point Capture"),
            tr("Tool '%1' does not exist in the controller.").arg(toolName));
        return;
    }

    const RoadPoint point
        = Communication::instance()->GetCurRoadPoint(static_cast<quint16>(toolId), true);
    const std::array<double, 3> position{
        point.m_position.m_x, point.m_position.m_y, point.m_position.m_z
    };
    std::array<QLineEdit *, 3> *edits = prefix == QStringLiteral("A")
        ? &m_aPointEdits
        : prefix == QStringLiteral("O") ? &m_oPointEdits : &m_ePointEdits;
    for (int i = 0; i < static_cast<int>(position.size()); ++i)
        (*edits)[i]->setText(QString::number(position[i], 'f', 3));

    if (prefix == QStringLiteral("A") && m_aHistoryCombo) {
        m_aPointHistory.append(position);
        m_aHistoryCombo->addItem(
            tr("A%1: (%2, %3, %4)")
                .arg(m_aPointHistory.size())
                .arg(position[0], 0, 'f', 2)
                .arg(position[1], 0, 'f', 2)
                .arg(position[2], 0, 'f', 2));
        m_aHistoryCombo->setCurrentIndex(m_aPointHistory.size() - 1);
    }
}

void RobotControlForm::savePointData()
{
    const QString fileName = QFileDialog::getSaveFileName(
        this, tr("Save Robot Control Data"), QStringLiteral("robot_control_data.json"),
        tr("JSON files (*.json)"));
    if (fileName.isEmpty())
        return;

    const auto editsToArray = [](const auto &edits) {
        QJsonArray values;
        for (QLineEdit *edit : edits)
            values.append(edit->text().toDouble());
        return values;
    };
    QJsonArray history;
    for (const auto &point : m_aPointHistory) {
        QJsonArray value;
        for (double coordinate : point)
            value.append(coordinate);
        history.append(value);
    }

    QJsonObject data{
        {QStringLiteral("formatVersion"), 1},
        {QStringLiteral("aPoint"), editsToArray(m_aPointEdits)},
        {QStringLiteral("oPoint"), editsToArray(m_oPointEdits)},
        {QStringLiteral("endEffectPoint"), editsToArray(m_ePointEdits)},
        {QStringLiteral("aPointHistory"), history},
        {QStringLiteral("targetToolTcp"), editsToArray(m_targetToolEdits)}
    };
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)
        || file.write(QJsonDocument(data).toJson(QJsonDocument::Indented)) < 0) {
        QMessageBox::critical(this, tr("Save Data"), tr("Failed to write the data file."));
        return;
    }
    QMessageBox::information(this, tr("Save Data"), tr("Robot control data saved."));
}

void RobotControlForm::loadPointData()
{
    const QString fileName = QFileDialog::getOpenFileName(
        this, tr("Load Robot Control Data"), QString(), tr("JSON files (*.json)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, tr("Load Data"), tr("Failed to open the data file."));
        return;
    }
    QJsonParseError error;
    const QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &error);
    if (error.error != QJsonParseError::NoError || !document.isObject()) {
        QMessageBox::critical(this, tr("Load Data"), tr("The selected JSON file is invalid."));
        return;
    }

    const QJsonObject data = document.object();
    const auto restoreEdits = [](const QJsonValue &value, const auto &edits) {
        const QJsonArray values = value.toArray();
        if (values.size() != static_cast<int>(edits.size()))
            return false;
        for (int i = 0; i < values.size(); ++i) {
            if (!values[i].isDouble())
                return false;
            edits[i]->setText(QString::number(values[i].toDouble(), 'f', 3));
        }
        return true;
    };
    if (!restoreEdits(data.value(QStringLiteral("aPoint")), m_aPointEdits)
        || !restoreEdits(data.value(QStringLiteral("oPoint")), m_oPointEdits)
        || !restoreEdits(data.value(QStringLiteral("endEffectPoint")), m_ePointEdits)
        || !restoreEdits(data.value(QStringLiteral("targetToolTcp")), m_targetToolEdits)) {
        QMessageBox::critical(this, tr("Load Data"), tr("The data file has an unsupported format."));
        return;
    }

    m_aPointHistory.clear();
    m_aHistoryCombo->clear();
    const QJsonArray history = data.value(QStringLiteral("aPointHistory")).toArray();
    for (const QJsonValue &entry : history) {
        const QJsonArray values = entry.toArray();
        if (values.size() != 3)
            continue;
        const std::array<double, 3> point{
            values[0].toDouble(), values[1].toDouble(), values[2].toDouble()
        };
        m_aPointHistory.append(point);
        m_aHistoryCombo->addItem(
            tr("A%1: (%2, %3, %4)")
                .arg(m_aPointHistory.size())
                .arg(point[0], 0, 'f', 2)
                .arg(point[1], 0, 'f', 2)
                .arg(point[2], 0, 'f', 2));
    }
    QMessageBox::information(this, tr("Load Data"), tr("Robot control data loaded."));
}

QWidget *RobotControlForm::createRightPanel()
{
    auto *panel = new QWidget;
    auto *layout = new QVBoxLayout(panel);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(4);

    auto *device = new QGridLayout;
    auto *power = button(tr("Power On"));
    auto *enable = button(tr("Enable"));
    auto *initialize = button(tr("Initialize Controller"));
    auto *reset = button(tr("Reset Alarm"));
    auto *pause = button(tr("Pause Program"));
    auto *resume = button(tr("Continue Program"));
    auto *stopProgram = button(tr("Stop Program"));
    auto *emergencyStop = button(tr("Emergency Stop"));

    power->setCheckable(true);
    power->setEnabled(false);
    power->setToolTip(tr(
        "Robot body power is managed by the robot platform. This control is display-only."));
    enable->setCheckable(true);
    emergencyStop->setCheckable(true);
    emergencyStop->setObjectName(QStringLiteral("emergencyStop"));
    initialize->setEnabled(false);
    initialize->setToolTip(tr(
        "The Python StartMaster command has no equivalent public Communication API"));

    device->addWidget(power, 0, 0);
    device->addWidget(enable, 0, 1);
    device->addWidget(initialize, 1, 0);
    device->addWidget(reset, 1, 1);
    device->addWidget(pause, 2, 0);
    device->addWidget(resume, 2, 1);
    device->addWidget(stopProgram, 3, 0, 1, 2);
    device->addWidget(emergencyStop, 4, 0, 1, 2);
    layout->addWidget(group(tr("E05-L Pro Device Control"), device));

    const QList<QPushButton *> controllerButtons{
        reset, pause, resume, stopProgram, emergencyStop
    };
    const auto setControllerButtonsEnabled = [controllerButtons](bool connected) {
        for (QPushButton *control : controllerButtons)
            control->setEnabled(connected);
    };
    setControllerButtonsEnabled(Communication::instance()->isConnected());

    const auto updatePowerUi = [power, enable](InoCoRobotBodyPowerState state) {
        power->setProperty("robotBodyPowerState", static_cast<int>(state));
        const bool powered = state == ROBOT_BODY_POWER_ON;
        power->setChecked(powered);
        power->setEnabled(false);
        power->setText(
            state == ROBOT_BODY_POWERING_ON_IN_PROCESS
                ? QObject::tr("Powering On...")
                : state == ROBOT_BODY_POWER_OFF_IN_PROCESS
                    ? QObject::tr("Powering Off...")
                    : powered ? QObject::tr("Power Off")
                              : QObject::tr("Power On"));
        // Some controller versions do not report ROBOT_BODY_POWER_ON even
        // though the cabinet is powered.  Keep Enable available while
        // connected and let the controller API validate the request.
        enable->setEnabled(Communication::instance()->isConnected());
    };
    const auto updateEnableUi = [power, enable](bool enabled) {
        enable->setChecked(enabled);
        enable->setText(enabled ? QObject::tr("Disable")
                                : QObject::tr("Enable"));
        enable->setEnabled(Communication::instance()->isConnected());
        power->setEnabled(false);
    };

    connect(power, &QPushButton::clicked, this, [this, power](bool) {
        const auto currentState = static_cast<InoCoRobotBodyPowerState>(
            power->property("robotBodyPowerState").toInt());
        const bool requestPowerOn = currentState != ROBOT_BODY_POWER_ON;
        // A click is only a request. Keep showing the controller's actual state
        // until its monitoring signal confirms that the state has changed.
        power->setChecked(currentState == ROBOT_BODY_POWER_ON);
        const QString question = requestPowerOn
            ? tr("Are you sure you want to power on the robot?")
            : tr("Are you sure you want to power off the robot?");
        if (QMessageBox::question(this, tr("Robot Power"), question)
            != QMessageBox::Yes) {
            return;
        }

        CommunicationEngine::instance()->enqueueCmd_setData(
            this, AbstractCmd::CmdType_SetRobotBodyPowerState,
            requestPowerOn ? ROBOT_BODY_POWER_ON : ROBOT_BODY_POWER_OFF);
    });
    connect(enable, &QPushButton::clicked, this,
            [this, power, enable, updatePowerUi, updateEnableUi](bool) {
        if (!Communication::instance()->isConnected()) {
            updatePowerUi(ROBOT_BODY_DISCONNECTED_STATE);
            updateEnableUi(false);
            QMessageBox::warning(
                this, tr("Enable Robot"), tr("Controller not connected!"));
            return;
        }

        const auto powerState = Communication::instance()->getRobotBodyPowerState();
        const bool actualEnabled = Communication::instance()->IsEnable();
        const bool requestedEnabled = !actualEnabled;
        updatePowerUi(powerState);
        updateEnableUi(actualEnabled);

        CommunicationEngine::instance()->enqueueCmd_enableRobot(
            this, requestedEnabled);
    });
    connect(reset, &QPushButton::clicked, this, [this] {
        CommunicationEngine::instance()->enqueueCmd(
            this, AbstractCmd::CmdType_ClearAlarm);
    });
    connect(pause, &QPushButton::clicked, this, [this] {
        CommunicationEngine::instance()->enqueueCmd(
            this, AbstractCmd::CmdType_ProgramPause);
    });
    connect(resume, &QPushButton::clicked, this, [this] {
        CommunicationEngine::instance()->enqueueCmd(
            this, AbstractCmd::CmdType_ProgramContinue);
    });
    connect(stopProgram, &QPushButton::clicked, this, [this] {
        CommunicationEngine::instance()->enqueueCmd(
            this, AbstractCmd::CmdType_ProgramStop);
    });
    connect(emergencyStop, &QPushButton::clicked, this, [this](bool checked) {
        const InoCtrlAuthority authority
            = Communication::instance()->GetCurCtrlAuthority();
        const bool releaseForbidden
            = !checked
              && (authority == InoCtrlAuthority_IO
                  || (authority == InoCtrlAuthority_IO_AUTO
                      && Communication::instance()->GetCurDeviceMode()
                             == MetaType::RobotDeviceMode_Auto));
        if (releaseForbidden) {
            auto *stopButton = qobject_cast<QPushButton *>(sender());
            if (stopButton)
                stopButton->setChecked(true);
            QMessageBox::warning(
                this, tr("Emergency Stop"),
                tr("Emergency stop cannot be released in the current remote control mode."));
            return;
        }

        CommunicationEngine::instance()->enqueueCmd_setEmergecy(this, checked);
    });

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_enableStateChanged,
            enable, updateEnableUi);
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_enableRobotInterface_result,
            this,
            [this, updatePowerUi, updateEnableUi](QObject *object, bool success) {
        if (object != this)
            return;

        if (!success) {
            QMessageBox::warning(
                this, tr("Enable Robot"),
                tr("The controller failed to change the robot enable state."));
        }

        if (Communication::instance()->isConnected()) {
            updatePowerUi(Communication::instance()->getRobotBodyPowerState());
            updateEnableUi(Communication::instance()->IsEnable());
        }
    });
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_emergecyStateChanged,
            emergencyStop, [emergencyStop](bool engaged) {
                emergencyStop->setChecked(engaged);
                emergencyStop->setText(engaged
                    ? QObject::tr("Release Emergency Stop")
                    : QObject::tr("Emergency Stop"));
            });
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_robotBodyPowerStateChanged,
            power, updatePowerUi);

    const auto refreshControllerState = [updatePowerUi, updateEnableUi] {
        // The monitor backend is not ready while functional modules are being
        // constructed. Query it only after the controller connection succeeds;
        // an early query can block application startup on the splash screen.
        if (!Communication::instance()->isConnected()) {
            updatePowerUi(ROBOT_BODY_DISCONNECTED_STATE);
            updateEnableUi(false);
            return;
        }
        updatePowerUi(Communication::instance()->getRobotBodyPowerState());
        updateEnableUi(Communication::instance()->IsEnable());
    };
    refreshControllerState();
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_connectSuccess,
            this, refreshControllerState);

    auto *teach = new QHBoxLayout;
    auto *teachMode = new QCheckBox(tr("Teach Mode On"));
    teachMode->setEnabled(false);
    teachMode->setToolTip(tr(
        "The controller exposes drag-teach status, but no matching public set API"));
    teach->addWidget(teachMode);
    teach->addStretch();
    layout->addWidget(group(tr("Teach Mode"), teach));

    auto *tcpSettings = new QVBoxLayout;
    auto *tcpGrid = new QGridLayout;
    const QStringList tcpAxes{QStringLiteral("Tar_Tcp_X"), QStringLiteral("Tar_Tcp_Y"), QStringLiteral("Tar_Tcp_Z"),
                              QStringLiteral("Tar_Tcp_Rx"), QStringLiteral("Tar_Tcp_Ry"), QStringLiteral("Tar_Tcp_Rz")};
    for (int i = 0; i < tcpAxes.size(); ++i) {
        tcpGrid->addWidget(new QLabel(tcpAxes[i] + QStringLiteral(":")), i / 3, (i % 3) * 2);
        m_targetToolEdits[i] = valueEdit();
        tcpGrid->addWidget(m_targetToolEdits[i], i / 3, (i % 3) * 2 + 1);
    }
    tcpSettings->addLayout(tcpGrid);
    auto *switches = new QHBoxLayout;
    const auto findToolId = [](const QString &toolName) {
        const QStringList toolNames = Communication::instance()->getCurToolNames();
        for (int i = 0; i < toolNames.size(); ++i) {
            if (toolNames[i].compare(toolName, Qt::CaseInsensitive) == 0)
                return i;
        }
        return -1;
    };
    const auto requestTool = [this, findToolId](const QString &toolName) {
        if (!Communication::instance()->isConnected())
            return;

        const int toolId = findToolId(toolName);
        if (toolId < 0) {
            QMessageBox::warning(
                this, tr("Tool TCP"),
                tr("Tool '%1' does not exist in the controller.").arg(toolName));
            return;
        }
        CommunicationEngine::instance()->enqueueCmd_setData(
            this, AbstractCmd::CmdType_Control_SetToolId, toolId);
    };
    QHash<QString, QPushButton *> switchToolButtons;
    for (const QString &name : {QStringLiteral("TCP_O"), QStringLiteral("TCP_P"), QStringLiteral("TCP_U"),
                                QStringLiteral("TCP_E"), QStringLiteral("TCP_tip")}) {
        auto *switchTool = button(tr("Switch to %1").arg(name));
        switchTool->setCheckable(true);
        connect(switchTool, &QPushButton::clicked, this,
                [requestTool, name] { requestTool(name); });
        switchToolButtons.insert(name, switchTool);
        switches->addWidget(switchTool);
    }
    tcpSettings->addLayout(switches);
    auto *saveCurrentTool = button(tr("Save Parameters to Active TCP"));
    saveCurrentTool->setToolTip(tr(
        "Save the six values above to the tool currently active in the controller"));
    tcpSettings->addWidget(saveCurrentTool);
    layout->addWidget(group(tr("Tool Coordinate System Settings (TCP)"), tcpSettings));

    auto *current = new QVBoxLayout;
    auto *currentGrid = new QGridLayout;
    for (int i = 0; i < tcpAxes.size(); ++i) {
        QString label = tcpAxes[i];
        label.replace(QStringLiteral("Tar_"), QStringLiteral("Cur_"));
        currentGrid->addWidget(new QLabel(label + QStringLiteral(":")), i / 3, (i % 3) * 2);
        m_currentToolEdits[i] = valueEdit(QStringLiteral("0.00"), true);
        currentGrid->addWidget(m_currentToolEdits[i], i / 3, (i % 3) * 2 + 1);
    }
    current->addLayout(currentGrid);
    auto *reads = new QHBoxLayout;
    const auto requestToolParams = [this, findToolId](const QString &toolName) {
        if (!Communication::instance()->isConnected())
            return;

        const int toolId = toolName.isEmpty()
            ? Communication::instance()->GetCurToolId()
            : findToolId(toolName);
        if (toolId < 0) {
            QMessageBox::warning(
                this, tr("Tool TCP"),
                tr("Tool '%1' does not exist in the controller.").arg(toolName));
            return;
        }
        CommunicationEngine::instance()->enqueueCmd_handleToolCalibrate(
            this, AbstractCmd::CmdType_Tool_Refresh, toolId);
    };
    const QList<QPair<QString, QString>> readTools{
        {tr("Read Active TCP"), QString()},
        {tr("Read TCP_O"), QStringLiteral("TCP_O")},
        {tr("Read TCP_P"), QStringLiteral("TCP_P")},
        {tr("Read TCP_U"), QStringLiteral("TCP_U")},
        {tr("Read TCP_E"), QStringLiteral("TCP_E")},
        {tr("Read TCP_tip"), QStringLiteral("TCP_tip")},
    };
    QPushButton *readActiveTool = nullptr;
    QHash<QString, QPushButton *> readToolButtons;
    for (const auto &readTool : readTools) {
        auto *read = button(readTool.first);
        connect(read, &QPushButton::clicked, this,
                [requestToolParams, toolName = readTool.second] {
                    requestToolParams(toolName);
                });
        if (readTool.second.isEmpty())
            readActiveTool = read;
        else
            readToolButtons.insert(readTool.second, read);
        reads->addWidget(read);
    }
    current->addLayout(reads);
    layout->addWidget(group(tr("Current TCP Settings"), current));

    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_settool_result,
            this, [this](QObject *object, bool success, int toolId) {
                if (object != this)
                    return;
                if (!success) {
                    QMessageBox::warning(
                        this, tr("Tool TCP"), tr("Failed to switch the controller tool."));
                }
            });
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_tool_Refresh_result,
            this, [this](QObject *object, bool success, const ToolParams &params) {
                if (object != this)
                    return;
                if (!success) {
                    QMessageBox::warning(
                        this, tr("Tool TCP"), tr("Failed to read the tool parameters."));
                    return;
                }

                const std::array<double, 6> values{
                    params.pos.m_x, params.pos.m_y, params.pos.m_z,
                    params.ori.m_rx, params.ori.m_ry, params.ori.m_rz
                };
                for (int i = 0; i < static_cast<int>(values.size()); ++i)
                    m_currentToolEdits[i]->setText(QString::number(values[i], 'f', 3));
            });
    connect(saveCurrentTool, &QPushButton::clicked, this, [this] {
        if (!Communication::instance()->isConnected())
            return;

        const int toolId = Communication::instance()->GetCurToolId();
        ToolParams params;
        Communication::instance()->GetCurToolParams(toolId, params);

        std::array<double, 6> values{};
        for (int i = 0; i < static_cast<int>(values.size()); ++i) {
            bool ok = false;
            values[i] = m_targetToolEdits[i]->text().toDouble(&ok);
            if (!ok) {
                QMessageBox::warning(
                    this, tr("Tool TCP"), tr("All TCP parameters must be valid numbers."));
                return;
            }
        }
        params.pos.m_x = values[0];
        params.pos.m_y = values[1];
        params.pos.m_z = values[2];
        params.ori.m_rx = values[3];
        params.ori.m_ry = values[4];
        params.ori.m_rz = values[5];
        CommunicationEngine::instance()->enqueueCmd_ToolSave(
            this, static_cast<quint16>(toolId), params, true);
    });
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_tool_Save_result,
            this, [this, requestTool](QObject *object, bool success) {
                if (object != this)
                    return;
                if (!success) {
                    QMessageBox::warning(
                        this, tr("Tool TCP"), tr("Failed to save the tool parameters."));
                    return;
                }
                requestTool(QStringLiteral("TCP_E"));
            });

    const auto refreshToolButtons = [=] {
        const bool connected = Communication::instance()->isConnected();
        const QStringList names = Communication::instance()->getCurToolNames();
        const int activeToolId = Communication::instance()->GetCurToolId();
        const QString activeToolName
            = activeToolId >= 0 && activeToolId < names.size()
                ? names[activeToolId] : QString();

        for (auto it = switchToolButtons.cbegin(); it != switchToolButtons.cend(); ++it) {
            const bool exists = findToolId(it.key()) >= 0;
            it.value()->setEnabled(connected && exists);
            it.value()->setChecked(
                connected && activeToolName.compare(it.key(), Qt::CaseInsensitive) == 0);
            it.value()->setToolTip(exists
                ? QObject::tr("Activate controller tool '%1'").arg(it.key())
                : QObject::tr("Tool '%1' does not exist in the controller").arg(it.key()));
        }
        for (auto it = readToolButtons.cbegin(); it != readToolButtons.cend(); ++it) {
            const bool exists = findToolId(it.key()) >= 0;
            it.value()->setEnabled(connected && exists);
            it.value()->setToolTip(exists
                ? QObject::tr("Read controller tool '%1'").arg(it.key())
                : QObject::tr("Tool '%1' does not exist in the controller").arg(it.key()));
        }
        readActiveTool->setEnabled(connected && !activeToolName.isEmpty());
        saveCurrentTool->setEnabled(connected && !activeToolName.isEmpty());
    };
    refreshToolButtons();
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_connectSuccess,
            this, refreshToolButtons);
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_ToolChanged,
            this, [refreshToolButtons](int) { refreshToolButtons(); });

    auto *communication = new QVBoxLayout;
    auto *endpoint = new QHBoxLayout;
    endpoint->addWidget(new QLabel(tr("Controller IP:")));
    auto *ip = new QLineEdit(Communication::instance()->getIP());
    endpoint->addWidget(ip);
    endpoint->addWidget(new QLabel(tr("Port:")));
    auto *port = new QLineEdit(QString::number(Communication::instance()->getPort()));
    endpoint->addWidget(port);
    communication->addLayout(endpoint);
    auto *connection = new QHBoxLayout;
    auto *connectController = button(tr("Connect"));
    connection->addWidget(connectController);
    auto *disconnect = button(tr("Disconnect")); disconnect->setEnabled(false);
    connection->addWidget(disconnect);
    communication->addLayout(connection);
    auto *status = new QLabel(tr("Controller Status: Disconnected"));
    status->setStyleSheet(QStringLiteral("color:#2468b4;"));
    communication->addWidget(status);

    const auto updateConnectionUi = [=](ControllerConnectionState state) {
        const bool connected = state == ControllerConnectionState_Connected;
        const bool connecting = state == ControllerConnectionState_Connecting;
        connectController->setEnabled(!connected && !connecting);
        disconnect->setEnabled(connected);
        ip->setEnabled(!connected && !connecting);
        port->setEnabled(!connected && !connecting);
        status->setText(connecting
            ? QObject::tr("Controller Status: Connecting...")
            : connected
                ? QObject::tr("Controller Status: Connected")
                : QObject::tr("Controller Status: Disconnected"));
        setControllerButtonsEnabled(connected);
        if (connected) {
            refreshControllerState();
        } else {
            updatePowerUi(ROBOT_BODY_DISCONNECTED_STATE);
            updateEnableUi(false);
        }
        refreshToolButtons();
    };
    updateConnectionUi(Communication::instance()->isConnected()
        ? ControllerConnectionState_Connected
        : ControllerConnectionState_Closed);

    connect(connectController, &QPushButton::clicked, this, [=] {
        bool portOk = false;
        const int controllerPort = port->text().toInt(&portOk);
        if (ip->text().trimmed().isEmpty() || !portOk || controllerPort <= 0)
            return;

        CommunicationEngine::instance()->enqueueCmd_connectController(
            this, ip->text().trimmed(), controllerPort);
    });
    connect(disconnect, &QPushButton::clicked, this, [this] {
        if (QMessageBox::question(
                this, tr("Disconnect Controller"),
                tr("Are you sure you want to disconnect from the controller?"))
            != QMessageBox::Yes) {
            return;
        }

        CommunicationEngine::instance()->enqueueCmd(
            this, AbstractCmd::CmdType_DisconnectController);
    });
    connect(CommunicationEngine::instance(),
            &CommunicationEngine::signal_controllerConnectionStatusChanged,
            this, updateConnectionUi);

    layout->addWidget(group(tr("Controller Communication"), communication));
    layout->addStretch();
    return panel;
}
