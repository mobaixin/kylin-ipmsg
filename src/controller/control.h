#ifndef __CONTROL_H__
#define __CONTROL_H__

#include <QObject>

#include "global/utils/global_data.h"
#include "network/tcp_server.h"
#include "network/tcp_client.h"
#include "network/udp_socket.h"

class Control : public QObject
{
    Q_OBJECT

public:
    Control();
    ~Control();

    void init(void);
    void establishInterrupt(void);

private:
    TcpServer *m_server;
    TcpClient *m_client;
    UdpSocket *m_udpSocket;

private slots:
    void slotSend(g_send send);
    void slotRecvMsgSuccess(g_recv recv);
    void slotSendMsgSuccess(g_send send);
};


#endif
