#ifndef __TCP_MODULE_H__
#define __TCP_MODULE_H__

#include "global/declare/declare.h"
#include "protocol_analysis.h"

#include <QObject>
#include <QTcpSocket>

class TcpModule : public QObject
{
    Q_OBJECT

public:
    TcpModule(QTcpSocket *socket);
    TcpModule(QTcpSocket *socket , g_send send);
    ~TcpModule();

    int tranFile(g_send send);
    void tranMsg(g_send send);

public:
    ProtocolAnalysis moduleProtocolAnalysis;

private:
    void establishInterrupt(void);

private:
    bool m_flag;
    QString m_uuid;
    QTcpSocket *m_socket;

signals:
    void sigMaintainTcpLinkAdd(g_tcpMaintain item);
    void sigMaintainTcpLinkDelete(QString uuid);
    void sigSendMsgSuccess(g_send send);
    void sigRecvMsgSuccess(g_recv recv);

private slots:
    void slotReadSocket(void);
    void slotSocketDisconnect(void);

};

#endif
