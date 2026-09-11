#pragma once

#include <QWidget>
#include <QSet>
#include <QStringList>
#include <QVector>

#include <array>

class QLineEdit;
class QComboBox;
class QPushButton;
class QTextBrowser;
class QVBoxLayout;

class RobotControlForm : public QWidget
{
public:
    explicit RobotControlForm(QWidget *parent = nullptr);

private:
    QWidget *createLeftPanel();
    QWidget *createRightPanel();
    void addPoseEditor(QVBoxLayout *layout, const QString &title,
                       const QString &prefix, const QString &buttonText);
    void updateRealtimeStatus();
    void capturePoint(const QString &prefix, const QString &toolName);
    void savePointData();
    void loadPointData();
    void requestAlarmHistory();
    void startFineTuneProbe();
    void finishFineTuneProbeSwitch(bool success, int toolId);
    void finishFineTuneProbeSave(bool success);
    void setFineTuneProbeActive(bool active);
    void updateFineTuneProbeAvailability();

    std::array<QLineEdit *, 6> m_jointValueEdits{};
    std::array<QLineEdit *, 6> m_tcpValueEdits{};
    std::array<QLineEdit *, 6> m_targetToolEdits{};
    std::array<QLineEdit *, 6> m_currentToolEdits{};
    std::array<QLineEdit *, 3> m_aPointEdits{};
    std::array<QLineEdit *, 3> m_oPointEdits{};
    std::array<QLineEdit *, 3> m_ePointEdits{};
    QComboBox *m_aHistoryCombo = nullptr;
    QTextBrowser *m_alarmHistoryView = nullptr;
    QStringList m_alarmHistory;
    QSet<QString> m_alarmBaseline;
    bool m_alarmBaselineCaptured = false;
    QVector<std::array<double, 3>> m_aPointHistory;
    int m_confirmedActiveToolId = -1;
    QPushButton *m_fineTuneProbeButton = nullptr;
    QVector<QPushButton *> m_toolJogButtons;
    int m_fineTuneStep = 0;
    bool m_fineTuneProbeActive = false;
};
