#include "robotcontrolform.h"

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QSlider>
#include <QTextEdit>
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
    result->setMinimumHeight(30);
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
        " border-radius:5px; margin-top:12px; padding-top:10px; font-weight:600; }"
        "#robotControlForm QGroupBox::title { subcontrol-origin:margin; left:10px; padding:0 4px; }"
        "#robotControlForm QLineEdit[displayValue='true'], #robotControlForm QTextEdit {"
        " background:#eceff3; color:#333; }"
        "#robotControlForm QPushButton { padding:4px 8px; }"
        "#emergencyStop { background:#d9363e; color:white; font-weight:700; }"));

    auto *columns = new QHBoxLayout(this);
    columns->setContentsMargins(8, 8, 8, 8);
    columns->setSpacing(8);
    for (QWidget *panel : {createLeftPanel(), createRightPanel()}) {
        auto *scroll = new QScrollArea;
        scroll->setWidgetResizable(true);
        scroll->setFrameShape(QFrame::NoFrame);
        scroll->setWidget(panel);
        columns->addWidget(scroll, 1);
    }
}

QWidget *RobotControlForm::createLeftPanel()
{
    auto *panel = new QWidget;
    auto *layout = new QVBoxLayout(panel);

    auto *top = new QHBoxLayout;
    auto *jointLayout = new QVBoxLayout;
    for (int i = 0; i < 6; ++i) {
        auto *row = new QHBoxLayout;
        row->addWidget(new QLabel(tr("Joint %1 (q%1):").arg(i + 1)));
        auto *edit = valueEdit(QStringLiteral("0.00"), true);
        edit->setMaximumWidth(75);
        row->addWidget(edit);
        row->addStretch();
        auto *minus = button(QStringLiteral("−"));
        auto *plus = button(QStringLiteral("+"));
        minus->setFixedWidth(34); plus->setFixedWidth(34);
        row->addWidget(minus); row->addWidget(plus);
        jointLayout->addLayout(row);
    }
    jointLayout->addWidget(button(tr("Initialize Joint Position")), 0, Qt::AlignCenter);
    top->addWidget(group(tr("Motor Fine-tuning Module (Forward Kinematics)"), jointLayout), 4);

    auto *speedLayout = new QVBoxLayout;
    auto *speed = new QSlider(Qt::Vertical);
    speed->setRange(1, 100); speed->setValue(1);
    speed->setTickPosition(QSlider::TicksBothSides);
    speedLayout->addWidget(new QLabel(tr("Motion Speed: 0.01")), 0, Qt::AlignCenter);
    speedLayout->addWidget(speed, 1, Qt::AlignCenter);
    speedLayout->addWidget(new QLabel(tr("Current Motion Speed:")), 0, Qt::AlignCenter);
    speedLayout->addWidget(valueEdit(QStringLiteral("0.00"), true), 0, Qt::AlignCenter);
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
        toolGrid->addWidget(valueEdit(QStringLiteral("0.00"), true), row, col + 1);
        auto *controls = new QHBoxLayout;
        controls->addWidget(button(QStringLiteral("−")));
        controls->addWidget(button(QStringLiteral("+")));
        toolGrid->addLayout(controls, row + 1, col, 1, 2);
    }
    toolGrid->addWidget(button(tr("Fine tune probe")), 4, 0, 1, 6, Qt::AlignCenter);
    layout->addWidget(group(tr("Robot Tool Real-time Status"), toolGrid));

    auto *points = new QVBoxLayout;
    addPoseEditor(points, tr("A Point"), QStringLiteral("A"), tr("History (Empty)"));
    addPoseEditor(points, tr("O Point"), QStringLiteral("O"), tr("Get O Point Position"));
    addPoseEditor(points, tr("End-Effect"), QStringLiteral("E"), tr("Get End-Effect Position"));
    points->addWidget(button(tr("Rotate the ultrasound plane to pass through the puncture point")));
    layout->addWidget(group(tr("Robot A, O, and End-Effect Positions"), points));

    auto *lesion = new QVBoxLayout;
    auto *bRow = new QHBoxLayout;
    for (const QString &axis : {QStringLiteral("x"), QStringLiteral("y"), QStringLiteral("z")}) {
        bRow->addWidget(new QLabel(QStringLiteral("B_%1:").arg(axis)));
        bRow->addWidget(valueEdit());
    }
    auto *bPoints = new QComboBox;
    bPoints->addItem(tr("Please read TXT file first"));
    bRow->addWidget(bPoints);
    lesion->addLayout(bRow);
    auto *loadRow = new QHBoxLayout;
    loadRow->addWidget(button(tr("Read A Points (Volume) from Replan File")));
    loadRow->addWidget(button(tr("Read B Points (Volume) from Replan File")));
    lesion->addLayout(loadRow);
    lesion->addWidget(button(tr("Rotate the ultrasound plane to pass through the biopsy point")));
    layout->addWidget(group(tr("Lesion B Point Localization"), lesion));

    auto *save = new QHBoxLayout;
    save->addStretch(); save->addWidget(button(tr("Save"))); save->addWidget(button(tr("Load"))); save->addStretch();
    layout->addWidget(group(tr("Save Current Data"), save));
    layout->addStretch();
    return panel;
}

void RobotControlForm::addPoseEditor(QVBoxLayout *layout, const QString &title,
                                     const QString &prefix, const QString &buttonText)
{
    auto *row = new QHBoxLayout;
    for (const QString &axis : {QStringLiteral("x"), QStringLiteral("y"), QStringLiteral("z")}) {
        row->addWidget(new QLabel(QStringLiteral("%1_%2:").arg(prefix, axis)));
        row->addWidget(valueEdit());
    }
    if (prefix == QStringLiteral("A")) {
        auto *history = new QComboBox;
        history->addItem(buttonText);
        row->addWidget(history);
    } else {
        row->addWidget(button(buttonText));
    }
    layout->addWidget(group(title, row));
}

QWidget *RobotControlForm::createRightPanel()
{
    auto *panel = new QWidget;
    auto *layout = new QVBoxLayout(panel);

    auto *device = new QGridLayout;
    const QStringList controls{tr("Power On"), tr("Enable"), tr("Initialize Controller"), tr("Reset"),
                               tr("Pause"), tr("Continue")};
    for (int i = 0; i < controls.size(); ++i)
        device->addWidget(button(controls[i]), i / 2, i % 2);
    auto *stop = button(tr("Emergency Stop"));
    stop->setObjectName(QStringLiteral("emergencyStop"));
    stop->setEnabled(false);
    device->addWidget(stop, 3, 0, 1, 2);
    layout->addWidget(group(tr("E05-L Pro Device Control"), device));

    auto *teach = new QHBoxLayout;
    teach->addWidget(new QCheckBox(tr("Teach Mode On")));
    teach->addStretch();
    layout->addWidget(group(tr("Teach Mode"), teach));

    auto *tcpSettings = new QVBoxLayout;
    auto *tcpGrid = new QGridLayout;
    const QStringList tcpAxes{QStringLiteral("Tar_Tcp_X"), QStringLiteral("Tar_Tcp_Y"), QStringLiteral("Tar_Tcp_Z"),
                              QStringLiteral("Tar_Tcp_Rx"), QStringLiteral("Tar_Tcp_Ry"), QStringLiteral("Tar_Tcp_Rz")};
    for (int i = 0; i < tcpAxes.size(); ++i) {
        tcpGrid->addWidget(new QLabel(tcpAxes[i] + QStringLiteral(":")), i / 3, (i % 3) * 2);
        tcpGrid->addWidget(valueEdit(), i / 3, (i % 3) * 2 + 1);
    }
    tcpSettings->addLayout(tcpGrid);
    auto *switches = new QHBoxLayout;
    for (const QString &name : {QStringLiteral("TCP_O"), QStringLiteral("TCP_P"), QStringLiteral("TCP_U"),
                                QStringLiteral("TCP_E"), QStringLiteral("TCP_tip")})
        switches->addWidget(button(tr("Switch to %1").arg(name)));
    tcpSettings->addLayout(switches);
    tcpSettings->addWidget(button(tr("Set Cur TCP")));
    layout->addWidget(group(tr("Tool Coordinate System Settings (TCP)"), tcpSettings));

    auto *current = new QVBoxLayout;
    auto *currentGrid = new QGridLayout;
    for (int i = 0; i < tcpAxes.size(); ++i) {
        QString label = tcpAxes[i];
        label.replace(QStringLiteral("Tar_"), QStringLiteral("Cur_"));
        currentGrid->addWidget(new QLabel(label + QStringLiteral(":")), i / 3, (i % 3) * 2);
        currentGrid->addWidget(valueEdit(QStringLiteral("0.00"), true), i / 3, (i % 3) * 2 + 1);
    }
    current->addLayout(currentGrid);
    auto *reads = new QHBoxLayout;
    for (const QString &text : {tr("Read Cur TCP"), tr("Read TCP_O"), tr("Read TCP_tip"), tr("Read TCP_U")})
        reads->addWidget(button(text));
    current->addLayout(reads);
    layout->addWidget(group(tr("Current TCP Settings"), current));

    auto *communication = new QVBoxLayout;
    auto *endpoint = new QHBoxLayout;
    endpoint->addWidget(new QLabel(tr("Remote IP:")));
    endpoint->addWidget(new QLineEdit(QStringLiteral("192.168.10.10")));
    endpoint->addWidget(new QLabel(tr("Port:")));
    endpoint->addWidget(new QLineEdit(QStringLiteral("10003")));
    communication->addLayout(endpoint);
    auto *connection = new QHBoxLayout;
    connection->addWidget(button(tr("Connect")));
    auto *disconnect = button(tr("Disconnect")); disconnect->setEnabled(false);
    connection->addWidget(disconnect);
    communication->addLayout(connection);
    auto *status = new QLabel(tr("TCP Status: Disconnected")); status->setStyleSheet(QStringLiteral("color:#2468b4;"));
    communication->addWidget(status);
    communication->addWidget(new QLabel(tr("Received Messages:")));
    auto *received = new QTextEdit; received->setReadOnly(true); received->setMinimumHeight(90);
    communication->addWidget(received);
    communication->addWidget(new QLabel(tr("Send Message:")));
    auto *sendRow = new QHBoxLayout;
    auto *message = new QLineEdit; message->setEnabled(false);
    auto *send = button(tr("Send")); send->setEnabled(false);
    sendRow->addWidget(message); sendRow->addWidget(send);
    communication->addLayout(sendRow);
    layout->addWidget(group(tr("TCP Communication Module"), communication));
    layout->addStretch();
    return panel;
}
