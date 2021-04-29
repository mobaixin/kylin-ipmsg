#include <QHostAddress>
#include <QThread>

#include "tcp_client.h"
#include "tcp_module.h"
#include "global/utils/global_data.h"

TcpClient::TcpClient()
{

}

TcpClient::~TcpClient()
{


}

int TcpClient::tran(g_send send)
{
    this->m_send = send;

    /* 检测链接是否建立 */
    g_tcpMaintain item = GlobalData::getInstance()->m_tcpLink.select(send.uuid);

    /* 链接已经建立 */
    if (item.module != NULL) {
        if (send.type == QString("msg")) {
            item.module->tranMsg(send);

        } else if (send.type == QString("file")) {

        }

        return 0;
    }

    /* 链接未建立 */
    QString ip = item.peerListenIp;
    QString port = item.peerListenPort;

    qDebug() << "Info : TcpClient , tran , connect peer ip ---> " << ip << "port ---> " << port;

    this->m_socket = new QTcpSocket;
    connect(this->m_socket , &QTcpSocket::connected , this , &TcpClient::slotLinkSuccess);
    this->m_socket->connectToHost(QHostAddress(ip) , port.toUShort() , QTcpSocket::ReadWrite);

    return 0;
}

void TcpClient::slotLinkSuccess(void)
{
    qDebug() << "Info : TcpClient , slotLinkSuccess , client link success!!!";

    /* 加载功能模块 */
    TcpModule *module = new TcpModule(this->m_socket , this->m_send);

    connect(module , &TcpModule::sigSendMsgSuccess , this , &TcpClient::slotSendMsgSuccess);
    connect(module , &TcpModule::sigRecvMsgSuccess , this , &TcpClient::slotRecvMsgSuccess);

    /* 维护tcp链接表 */
    g_tcpItem item;
    item.uuid = this->m_send.uuid;
    item.selfIp = this->m_socket->localAddress().toString();
    item.selfPort = QString::number(this->m_socket->localPort());
    item.peerIp = this->m_socket->peerAddress().toString();
    item.peerPort = QString::number(this->m_socket->peerPort());
    item.module = module;

    if (GlobalData::getInstance()->m_tcpLink.tcpMaintainAdd(item)) {
        qDebug() << "Error : TcpClient , slotLinkSuccess , maintain tcp link fail";
    }

    /* 移至线程中 */
    QThread *thread = new QThread;
    module->moveToThread(thread);
    thread->start();

    return;
}

void TcpClient::slotSendMsgSuccess(g_send send)
{
    emit sigTcpClientSendMsgSuccess(send);
}

void TcpClient::slotRecvMsgSuccess(g_recv recv)
{
    emit sigTcpClientRecvMsgSuccess(recv);
}
