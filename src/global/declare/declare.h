#ifndef __DECLARE_H__
#define __DECLARE_H__

#include <QString>

class TcpModule;

/* 代表tcp链接表的一条数据 */
typedef struct TcpMaintain
{
    QString uuid;
    QString selfIp;
    QString selfPort;
    QString peerIp;
    QString peerPort;
    QString peerListenIp;
    QString peerListenPort;
    TcpModule *module;
} g_tcpMaintain;

/* tcp维护tcp链接表 */
typedef struct TcpItem
{
    QString uuid;
    QString selfIp;
    QString selfPort;
    QString peerIp;
    QString peerPort;
    TcpModule *module;
} g_tcpItem;

/* udp维护tcp链接表 */
typedef struct UdpItem
{
    QString uuid;
    QString peerListenIp;
    QString peerListenPort;
} g_udpItem;

/* 发送数据结构 */
typedef struct Send
{
    QString uuid;
    QString type;
    QString msgData;
    QString fileName;
    QString filePath;
} g_send;

/* 接受数据结构 */
typedef struct Recv
{
    QString uuid;
    QString type;
    QString msgData;
    QString fileName;
    QString filePath;
} g_recv;

#endif
