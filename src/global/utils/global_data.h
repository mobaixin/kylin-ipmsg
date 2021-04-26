#ifndef __GLOBAL_DATA_H__
#define __GLOBAL_DATA_H__

#include <QString>

#include "tcp_link.h"

class GlobalData
{
public:
    ~GlobalData();

    /* 本机信息 */
    QString m_uuid;
    QString m_tcpListenIP;
    QString m_tcpListenPort;
    QString m_udpListenPort;

    /* tcp链接表 */
    TcpLink m_tcpLink;

private:
    GlobalData();
public:
    static GlobalData *getInstance();

private:
    void init(void);
    void getTcpListenIp(void);
    void getTcpListenPort(void);
    void getUdpListenPort(void);
    void getUuid(void);
};

#endif

