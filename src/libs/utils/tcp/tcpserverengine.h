#pragma once

#include <QTcpServer>
#include "tcp_global.h"
class TcpServerSocket;
class QMutex;

class TCP_EXPORT TcpServerEngine : public QTcpServer
{
    Q_OBJECT

public:
    static TcpServerEngine *uiInstance();
    static TcpServerEngine *scriptRuntimeInstance();

    TcpServerEngine(const int &maxThreads, QObject *object = 0);
    ~TcpServerEngine();

    Q_INVOKABLE void listen(const quint16 &port);
    Q_INVOKABLE void close();

    Q_INVOKABLE void sendData(const QString &ip, const QByteArray &data);

    bool isConnected(const QString &ip);

    QByteArray recvData(const QString &ip);

    void broadcastData(const QByteArray &data);

protected:
    virtual void incomingConnection(qintptr socketDescriptor);

signals:
    void signal_sendData(QString ip, QByteArray data);
    void signal_serverClose();

public slots:
    void slot_recvData(const TcpServerSocket *, QString ip, QByteArray data);

private slots:
    void slot_socketDisConnect(
        const QObject *, const QString &ip, QThread *th);

private:
    int m_maxThreads;

    QHash<QThread *, unsigned int> threadSize;

    QThread *getThread();

    QMutex *m_mutex;
    QMap<QString, QByteArray> m_mapIPAndRecvData;
    QMap<QString, TcpServerSocket *> m_mapIPAndTcpSocket;

    quint16 m_port = 0;
};
