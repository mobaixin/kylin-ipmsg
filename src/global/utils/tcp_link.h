#ifndef __TCP_LINK_H__
#define __TCP_LINK_H__

#include <QList>
#include <pthread.h>

#include "global/declare/declare.h"

class TcpLink
{
public:
    TcpLink();
    ~TcpLink();

    int init();
    void ergodic(void);
    int tcpMaintainAdd(g_tcpItem);
    int tcpMaintainDelete(QString uuid);
    int udpMaintainAdd(g_udpItem);
    int udpMaintainDelete(QString uuid);

private:
    pthread_rwlock_t m_rwLock;
    QList<g_tcpMaintain *> m_tcpMaintain;
};

#endif
