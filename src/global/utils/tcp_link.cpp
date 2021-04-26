#include "tcp_link.h"

TcpLink::TcpLink()
{
    if (init()) {
        qDebug() << "Error : TcpLink , init fail\n";
    }
}

TcpLink::~TcpLink()
{
    for (int i = 0 ; i < this->m_tcpMaintain.count() ; i++) {
        g_tcpMaintain *tmp = this->m_tcpMaintain.at(i);

        if (tmp->module != NULL) {
            delete tmp->module;
        }

        delete tmp;
    }
}

int TcpLink::init()
{
    /* 初始化读写锁 */
    if (pthread_rwlock_init(&(this->m_rwLock) , NULL)) {
        qDebug() << "Error : TcpLink , init , init rwLock fail";
        return -1;
    }

    return 0;
}

int TcpLink::tcpMaintainAdd(g_tcpItem item)
{
    int flag = -1;

    if (pthread_rwlock_wrlock(&(this->m_rwLock))) {
        qDebug() << "Error : TcpLink , tcpMaintainAdd , lock rwLock fail";
        return -1;
    }

    for (int i = 0 ; i < this->m_tcpMaintain.count() ; i++) {
        g_tcpMaintain *tmp = this->m_tcpMaintain.at(i);

        if (tmp->uuid == item.uuid) {
            tmp->selfIp = item.selfIp;
            tmp->selfPort = item.selfPort;
            tmp->peerIp = item.peerIp;
            tmp->peerPort = item.peerPort;
            tmp->module = item.module;

            flag = 0;
            break;
        }
    }

    if (pthread_rwlock_unlock(&(this->m_rwLock))) {
        qDebug() << "Error : TcpLink , tcpMaintainAdd , unlock rwLock fail";
        return -1;
    }

    if (flag) {
        qDebug() << "Waring : TcpLink , tcpMaintainAdd , uuid dont find!!!";
    }

    return 0;
}


/* 此函数并没有释放tcp module实例 , 释放的话函数返回会造成崩溃 , 不释放会造成内存泄露 , 有待优化 */
int TcpLink::tcpMaintainDelete(QString uuid)
{
    int flag = -1;

    if (pthread_rwlock_wrlock(&(this->m_rwLock))) {
        qDebug() << "Error : TcpLink , tcpMaintainDelete , lock rwLock fail";
        return -1;
    }

    for (int i = 0 ; i < this->m_tcpMaintain.count() ; i++) {
        g_tcpMaintain *tmp = this->m_tcpMaintain.at(i);

        if (tmp->uuid == uuid) {
            tmp->selfIp.clear();
            tmp->selfPort.clear();
            tmp->peerIp.clear();
            tmp->peerPort.clear();
            tmp->module = NULL;

            flag = 0;

            break;
        }
    }

    if (pthread_rwlock_unlock(&(this->m_rwLock))) {
        qDebug() << "Error : TcpLink , tcpMaintainDelete , unlock rwLock fail";
        return -1;
    }

    if (flag) {
        qDebug() << "Waring : TcpLink , tcpMaintainDelete , uuid dont find!!!";
    }

    return 0;
}

int TcpLink::udpMaintainAdd(g_udpItem item)
{
    /* 变量没被改变 -> 不存在 , 新添 */
    /* 变量被置0 -> 存在 , 覆盖 */
    int flag = -1;

    if (pthread_rwlock_wrlock(&(this->m_rwLock))) {
        qDebug() << "Error : TcpLink , udpMaintainAdd , lock rwLock fail";
        return -1;
    }

    for (int i = 0 ; i < this->m_tcpMaintain.count() ; i++) {
        g_tcpMaintain *tmp = this->m_tcpMaintain.at(i);

        if (tmp->uuid == item.uuid) {
            tmp->uuid = item.uuid;
            tmp->peerListenIp = item.peerListenIp;
            tmp->peerListenPort = item.peerListenPort;

            flag = 0;
            goto FLAG;
        }
    }

    /* 不存在相同uuid , 新增一条 */
    g_tcpMaintain *newItem = new g_tcpMaintain;
    newItem->module = NULL;

    newItem->uuid = item.uuid;
    newItem->peerListenIp = item.peerListenIp;
    newItem->peerListenPort = item.peerListenPort;

    this->m_tcpMaintain.push_back(newItem);

FLAG:
    if (pthread_rwlock_unlock(&(this->m_rwLock))) {
        qDebug() << "Error : TcpLink , udpMaintainAdd , unlock rwLock fail";
        return -1;
    }

    if (flag == -1) {
        return 1;
    } else {
        return 0;
    }
}

int TcpLink::udpMaintainDelete(QString uuid)
{
    int flag = -1;

    if (pthread_rwlock_wrlock(&(this->m_rwLock))) {
        qDebug() << "Error : TcpLink , udpMaintainDelete , lock rwLock fail";
        return -1;
    }

    for (int i = 0 ; i < this->m_tcpMaintain.count() ; i++) {
        g_tcpMaintain *tmp = this->m_tcpMaintain.at(i);
        if (tmp->uuid == uuid) {
            if (tmp->module != NULL) {
                /* 释放tcp module */
                delete tmp->module;
            }

            /* 释放该条记录 */
            delete tmp;

            /* 从list中移除记录 */
            this->m_tcpMaintain.removeAt(i);
            flag = 0;

            break;
        }
    }

    if (pthread_rwlock_unlock(&(this->m_rwLock))) {
        qDebug() << "Error : TcpLink , udpMaintainDelete , unlock rwLock fail";
        return -1;
    }

    if (flag) {
        qDebug() << "Waring : TcpLink , udpMaintainDelete , uuid dont find!!!";
    }

    return 0;
}

void TcpLink::ergodic()
{
    if (pthread_rwlock_rdlock(&(this->m_rwLock))) {
        qDebug() << "Error : TcpLink , ergodic , lock rwLock fail";
        return;
    }

    qDebug() << "Info : tcpMaintain ergodic ......";
    qDebug() << "uuid      selfIp      selfPort      peerIp      peerPort      peerListenIp      peerListenPort      module";

    for (int i = 0 ; i < this->m_tcpMaintain ; i++) {
        g_tcpMaintain *tmp = this->m_tcpMaintain.at(i);

        std::string stdUuid = tmp->uuid.toStdString();
        const char *uuid = stdUuid.c_str();

        std::string stdSelfIp = tmp->selfIp.toStdString();
        const char *selfIp = stdSelfIp.c_str();

        std::string stdSelfPort = tmp->selfPort.toStdString();
        const char *selfPort = stdSelfPort.c_str();

        std::string stdPeerIP = tmp->peerIp.toStdString();
        const char *peerIp = stdPeerIP.c_str();

        std::string stdPeerPort = tmp->peerPort.toStdString();
        const char *peerPort = stdPeerPort.c_str();

        std::string stdPeerListenIp = tmp->peerListenIp.toStdString();
        const char *peerListenIp = stdPeerListenIp.c_str();

        std::string stdPeerListenPort = tmp->peerListenPort.toStdString();
        const char *peerListenPort = stdPeerListenPort.c_str();

        printf("[%s]      [%s]      [%s]      [%s]      [%s]      [%s]      [%s]      [%x]\n" , uuid , selfIp , selfPort , peerIp , peerPort , peerListenIp , peerListenPort , tmp->module);
    }

    if (pthread_rwlock_unlock(&(this->m_rwLock))) {
        qDebug() << "Error : TcpLink , ergodic , unlock rwLock fail";
        return ;
    }

    return ;
}
