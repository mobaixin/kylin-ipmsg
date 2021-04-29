#ifndef __TCP_CLIENT_H__
#define __TCP_CLIENT_H__

#include <QObject>
#include <QTcpSocket>

#include "global/declare/declare.h"

class TcpClient : public QObject
{
    Q_OBJECT

public:
    TcpClient();
    ~TcpClient();

    int tran(g_send send);

private:
    QTcpSocket *m_socket;
    g_send m_send;

signals:
    void sigTcpClientSendMsgSuccess(g_send send);
    void sigTcpClientRecvMsgSuccess(g_recv recv);

private slots:
    void slotLinkSuccess(void);
    void slotSendMsgSuccess(g_send send);
    void slotRecvMsgSuccess(g_recv recv);
};

#endif
