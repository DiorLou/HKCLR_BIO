#pragma once

#include <QWidget>
#include <QVector>

#include <array>

class QLineEdit;
class QComboBox;
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

    std::array<QLineEdit *, 6> m_jointValueEdits{};
    std::array<QLineEdit *, 6> m_tcpValueEdits{};
    std::array<QLineEdit *, 6> m_targetToolEdits{};
    std::array<QLineEdit *, 6> m_currentToolEdits{};
    std::array<QLineEdit *, 3> m_aPointEdits{};
    std::array<QLineEdit *, 3> m_oPointEdits{};
    std::array<QLineEdit *, 3> m_ePointEdits{};
    QComboBox *m_aHistoryCombo = nullptr;
    QVector<std::array<double, 3>> m_aPointHistory;
    int m_selectedToolId = -1;
    int m_requestedToolId = -1;
};
