#pragma once

#include <QObject>
#include <QHash>
#include <QMap>
#include "tcp_global.h"
class TcpClientSocket;
class QMutex;

class TCP_EXPORT TcpClientEngine : public QObject
{
    Q_OBJECT

public:
    static TcpClientEngine *instance();

    explicit TcpClientEngine(const int &maxThreads, QObject *parent = 0);
    ~TcpClientEngine();

    Q_INVOKABLE void connect2Host(const QString &ip, const quint16 &port);
    Q_INVOKABLE void disconnectToHost(const QString &ip, const quint16 &port);
    void close();

    Q_INVOKABLE bool isConnected(const QString &ip, const quint16 &port);

    Q_INVOKABLE void sendData(
        const QString &ip, const quint16 &port, const QByteArray &data);

    QByteArray recvData(const QString &ip, const quint16 &port);

    Q_INVOKABLE void connectCompleted(
        TcpClientSocket *socket,
        const QString &ip, const quint16 &port);

signals:
    void signal_connectToHost(QString ip, quint16 port);
    void signal_sendData(QString ip, quint16 port, QByteArray data);
    void signal_socketClose(QString ip, quint16 port);

private slots:
    void slot_socketDisconnect(
        const QString &ip, quint16 port, QThread *th);

    void slot_recvData(QString ip, quint16 port, QByteArray data);

private:
    int m_maxThreads;

    QThread *getThread();

    QHash<QThread *, unsigned int> threadSize;  // 线程池，保存每个线程的连接数

    QMap<QString, QByteArray> m_mapIpPortAndRecvData;

    QMap<QString, TcpClientSocket *> m_mapIpPortAndTcpSocket;

    QMutex *m_mutex;
};
