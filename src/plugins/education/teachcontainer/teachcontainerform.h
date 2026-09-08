#pragma once

#include "teachcontainer_global.h"

#include <QList>
#include <QObject>
#include <QVariant>

class RobotControlForm;
class QWidget;

// Compatibility shell for the TeachContainer plugin interface. The legacy
// Teaching page is gone; this object now only installs Robot Control.
class TEACHCONTAINER_EXPORT TeachContainerForm : public QObject
{
    Q_OBJECT

public:
    static TeachContainerForm *instance();

    explicit TeachContainerForm(QWidget *parent = nullptr);
    ~TeachContainerForm() override = default;

    void initialize();
    void delayInitialized();
    void getFunctionEnabledList(QList<QVariant> &retList);
    void setFunctionEnabledList(const QVariant &params);

    Q_INVOKABLE int getPtFileCount();

private:
    int m_robotControlTabIndex = -1;
    RobotControlForm *m_robotControlForm = nullptr;
};
