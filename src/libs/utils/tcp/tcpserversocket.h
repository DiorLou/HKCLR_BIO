#pragma once

#include <QTcpSocket>
#include "tcp_global.h"
class TCP_EXPORT TcpServerSocket : public QTcpSocket
{
    Q_OBJECT

public:
    explicit TcpServerSocket(QObject *parent = 0);
    ~TcpServerSocket();

    void init();

    QObject *getParentObj() const;

    QThread *getThread() const;
    void setThread(QThread *thread);

signals:
    void signal_socketDisConnect(
            const QObject *, const QString &, QThread *);
    void signal_recvData(const TcpServerSocket *,
                         QString ip, QByteArray data);

private slots:
    void slot_recvData();
    void slot_sendData(QString ip, QByteArray data);
    void slot_disconnected();

private:
    QObject *m_parentObj;

    QThread *m_thread;

    QByteArray encode(const QByteArray &data);
    void decode(QByteArray &data);
};
