#pragma once

#include <QTcpSocket>
#include "tcp_global.h"
class TCP_EXPORT TcpClientSocket : public QTcpSocket
{
    Q_OBJECT

public:
    explicit TcpClientSocket(const QString &ip, const quint16 &port,
                       QObject *parent = 0);
    ~TcpClientSocket();

    void init();

    QString getIP() const;
    void setIp(const QString &ip);

    quint16 getPort() const;
    void setPort(const quint16 &port);

signals:
    void signal_socketDisconnect(
            const QString &, const quint16, QThread *);
    void signal_recvData(QString ip, quint16 port, QByteArray data);

private slots:
    void slot_connectToHost(QString ip, quint16 port);

    void slot_recvData();
    void slot_sendData(QString ip, quint16 port, QByteArray data);
    void slot_disconnected();
    void slot_socketClose(QString ip, quint16 port);

private:
    QString m_ip;
    quint16 m_port;

    QByteArray encode(const QByteArray &data);
    void decode(QByteArray &data);
};
