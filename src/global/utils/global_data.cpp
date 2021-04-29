#include "global_data.h"

#include <QHostAddress>
#include <QNetworkInterface>
#include <QList>
#include <QDebug>

#define TCP_LISTEN_PORT "6066"
#define UDP_LISTEN_PORT "6067"

GlobalData::GlobalData()
{
    init();
}

GlobalData::~GlobalData()
{

}

GlobalData *GlobalData::getInstance(void)
{
    static GlobalData *s_globalData;
    if (s_globalData == NULL) {
        s_globalData = new GlobalData;
    }

    return s_globalData;
}

void GlobalData::init(void)
{
    getTcpListenIp();
    getTcpListenPort();
    getUdpListenPort();
    getUuid();

    return;
}

/* 取第一个ipv4地址 , 进行监听 */
void GlobalData::getTcpListenIp(void)
{
    QList<QHostAddress> ipList = QNetworkInterface::allAddresses();

    for (int i = 0 ; i < ipList.count() ; i++) {
        if (ipList.at(i) != QHostAddress::LocalHost && ipList.at(i).toIPv4Address()) {
            this->m_tcpListenIP = ipList.at(i).toString();
            break;
        }
    }
    return;
}

void GlobalData::getTcpListenPort(void)
{
    this->m_tcpListenPort = QString(TCP_LISTEN_PORT);
    return;
}

void GlobalData::getUdpListenPort(void)
{
    this->m_udpListenPort = QString(UDP_LISTEN_PORT);
    return;
}

void GlobalData::getUuid(void)
{
    this->m_uuid = QString("0x7777777");

    return;
}
