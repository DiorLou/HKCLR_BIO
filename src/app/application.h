#pragma once

#include <QApplication>
#include "metatype.h"
#include <QRegularExpression>

class QLocalServer;
class QDir;
class ComboBox;
class QAbstractButton;
class QGroupBox;
class QTableView;
class QSharedMemory;
class Application : public QApplication
{
    Q_OBJECT

public:
    static Application *instance();

    Application(int &argc, char **argv);
    ~Application();
    QTimer *m_lockScreenTimer;

    bool isRunning();

    Q_INVOKABLE void updateLockScreenTime();

protected:
    bool notify(QObject *obj, QEvent *event) override;

private:
    int m_lockScreenTimeoutSec;

    void initLocalConnection();
    bool checkWorkEnv();

    bool m_isRunning;

    void createWorkDir(QDir curDir, const QString &dirName);

    MetaType::RobotType m_robotType;
    void initProfile(const QString &key, const QVariant &value);

    void copyQrcToGenericDataLocation();
    void copyQrcToGenericDataLocation(
        const QString &src, const QString &destTail, int midIdx, bool jumpLanguageFile);

    // ComboBox *m_cmb;
    // QPointer<ComboBox> m_cmb;

    void connectBtnOperationLog(QAbstractButton *btn);
    void connectGropuBoxOperationLog(QGroupBox *);
    void connectTableViewOpeartionLog(QTableView *);
    void getParentInfoFlowMsg(QObject *parent, QString &state);
    QSet<QObject *> m_widgetHasConnectOperation;

    void requestPermission(const QString &permission);

    bool isPureAscill(const QString &str);
    QSharedMemory *m_singleMemory = 0;
    bool m_needDeleteMemory = false;

    bool judgeValidBeforePaste(QObject *obj);
};
