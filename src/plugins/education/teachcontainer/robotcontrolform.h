#pragma once

#include <QWidget>

#include <array>

class QLineEdit;
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

    std::array<QLineEdit *, 6> m_jointValueEdits{};
    std::array<QLineEdit *, 6> m_tcpValueEdits{};
};
