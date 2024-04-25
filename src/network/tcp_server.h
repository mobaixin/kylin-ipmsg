#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#include <QTcpServer>
#include <QTcpSocket>

#include "global/declare/declare.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT

public:
    TcpServer();
    ~TcpServer();

private:
    void establishInterrupt(void);
    int startListen(void);

/* 对外模块信号 */
signals:
    void sigTcpServerRecvMsgSuccess(g_recv recv);
    void sigTcpServerSendMsgSuccess(g_send send);

private slots:
    void slotEstablishNewLink(void);
    void slotRecvMsgSuccess(g_recv recv);
    void slotSendMsgSuccess(g_send send);
    void slotMaintainTcpLinkAdd(g_tcpItem item);
    void slotMaintainTcpLinkDelete(QString uuid);
};

#endif
