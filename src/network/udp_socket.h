#ifndef __UDP_SOCKET_H__
#define __UDP_SOCKET_H__

#include <QUdpSocket>
#include <QTimer>

class UdpSocket : public QObject
{
public:
    UdpSocket();
    ~UdpSocket();

private:
    QUdpSocket *m_udpSocket;
    QTimer *m_timer;

private:
    void init(void);
    void udpSocketBroadcast(bool flag);

private slots:
    void slotSocketRead(void);
    void slottOnline(void);
    void slotOffline(void);
};

#endif
