#pragma once

#include <QWidget>

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
};
