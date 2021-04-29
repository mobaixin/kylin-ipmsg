#include "global/utils/global_data.h"
#include "tcp_module.h"

#include <QDebug>
#include <QHostAddress>

/* 用于tcp server */
TcpModule::TcpModule(QTcpSocket *socket)
{
    if (socket == NULL) {
        qDebug() << "Error : TcpModule , call server , socket point is NULL";
    }

    this->m_flag = false;
    this->m_uuid = "";
    this->m_socket = socket;

    establishInterrupt();
}

/* 重载构造 ， 用于tcp client */
TcpModule::TcpModule(QTcpSocket *socket , g_send send)
{
    if (socket == NULL) {
        qDebug() << "Error : TcpModule , call client , socket point is NULL";
    }

    this->m_flag = true;
    this->m_uuid = send.uuid;
    this->m_socket = socket;

    establishInterrupt();

    if (send.type == QString("msg")) {
        tranMsg(send);
    } else if (send.type == QString("file")) {
        tranFile(send);
    }
}

TcpModule::~TcpModule()
{
    if (this->m_socket != NULL) {
        delete m_socket;
    }
}

void TcpModule::establishInterrupt(void)
{
    connect(this->m_socket , &QTcpSocket::readyRead , this , &TcpModule::slotReadSocket);
    connect(this->m_socket , &QTcpSocket::disconnected , this , &TcpModule::slotSocketDisconnect);

    return;
}

void TcpModule::tranMsg(g_send send)
{
    /* 协议封装 */
    QMap<QString , QString> map;
    map.clear();
    map.insert(QString("uuid") , this->m_uuid);
    map.insert(QString("type") , QString("msg"));
    map.insert(QString("body") , send.msgData);

    QString encapsulationtData = moduleProtocolAnalysis.encapsulationHeadBody(map);

    /* 发送 */
    this->m_socket->write(encapsulationtData.toStdString().c_str());
    this->m_socket->flush();

    qDebug() << "Info : TcpModule , tranMsg , success ---> " << send.msgData;

    /* 发送消息发送成功信号 */
    emit sigSendMsgSuccess(send);

    return;
}

int TcpModule::tranFile(g_send send)
{

}

void TcpModule::slotReadSocket(void)
{
    qDebug() << "Info : TcpModule , slotReadSocket , uuid ---> " << this->m_uuid;

    /* 接收数据包 */
    QByteArray recvData = this->m_socket->readAll();

    /* 解析协议 */
    QMap<QString , QString> map = moduleProtocolAnalysis.analysisHeadBody(QString(recvData));

    /* 判断tcp module 是否可用 */
    if (m_flag == false) {
        this->m_uuid = map.value(QString("uuid"));
        if (this->m_uuid.isEmpty()) {
            qDebug() << "Error : TcpModule , slotReadSocket , recvData uuid is empty , recv data discard";
            return;
        }

        /* 维护tcp链接表 */
        g_tcpItem item;
        item.uuid = this->m_uuid;
        item.selfIp = GlobalData::getInstance()->m_tcpListenIP;
        item.selfPort = GlobalData::getInstance()->m_tcpListenPort;
        item.peerIp = this->m_socket->peerAddress().toString();
        item.peerPort = QString::number(this->m_socket->peerPort());
        item.module = this;

        /* 同步调用槽 , 接收返回值 */
        emit sigMaintainTcpLinkAdd(item);

        this->m_flag = true;
    }

    /* 判断数据包是否对应 */
    if (map.value(QString("uuid")) != this->m_uuid) {
        qDebug() << "Error : TcpModule , slotReadSocket , recv uuid differ save uuid , recv data discard";
        return;
    }

    /* 判断数据包种类 */
    if (map.value(QString("type")) == QString("msg")) {
        /* 接收信息 */
        g_recv recv;
        recv.uuid = this->m_uuid;
        recv.type = QString("msg");
        recv.msgData = map.value(QString("body"));

        /* ---临时打印--- */
        qDebug() << "Info : TcpModule , slotReadSocket , recv msg ---> " << recv.msgData;

        emit sigRecvMsgSuccess(recv);

    } else if (map.value(QString("type")) == QString("file")) {
        /* 接收文件 */

    }

    return;
}

void TcpModule::slotSocketDisconnect(void)
{
    /* 释放socket */
    if (this->m_socket != NULL) {
        delete this->m_socket;
        this->m_socket = NULL;
    }

    /* 维护tcp链接表 */
    emit sigMaintainTcpLinkDelete(this->m_uuid);

    return;
}
