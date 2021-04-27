#include "tcp_server.h"
#include "global/utils/global_data.h"
#include "tcp_module.h"

#include <QHostAddress>
#include <QTcpSocket>
#include <QThread>

TcpServer::TcpServer()
{
    qDebug() << "Info : TcpServer , tcp server start up ...";
    establishInterrupt();
    startListen();
}

TcpServer::~TcpServer()
{

}

void TcpServer::establishInterrupt(void)
{
    connect(this , &TcpServer::newConnection , this , &TcpServer::slotEstablishNewLink);

    return;
}

int TcpServer::startListen(void)
{
    /* 获取需要监听的ip和port */
    QString ip = GlobalData::getInstance()->m_tcpListenIP;
    QString port = GlobalData::getInstance()->m_tcpListenPort;

    if (ip.isEmpty() || port.isEmpty()) {
        qDebug() << "Error : TcpServer , startListen , ip or port is empty";
        return -1;
    }

    if (this->listen(QHostAddress(ip) , port.toUShort()) == false) {
        qDebug() << "Error : TcpServer , startListen , listen fail";
        return -1;
    }

    qDebug() << "Info : TcpServer , startListen , listen success , ip --- > " << ip << "port ---> " << port;

    return 0;
}

void TcpServer::slotEstablishNewLink(void)
{
    qDebug() << "Info : TcpServer , slotEstablishNewLink , new link coming in ...";

    /* 获取新链接 */
    QTcpSocket *socket = this->nextPendingConnection();

    /* 加载功能模块 */
    TcpModule *tcpModule = new TcpModule(socket);

    connect(tcpModule , &TcpModule::sigMaintainTcpLinkAdd , this , &TcpServer::slotMaintainTcpLinkAdd , Qt::BlockingQueuedConnection);
    connect(tcpModule , &TcpModule::sigMaintainTcpLinkDelete , this , &TcpServer::slotMaintainTcpLinkDelete , Qt::BlockingQueuedConnection);
    connect(tcpModule , &TcpModule::sigRecvMsgSuccess , this , &TcpServer::slotRecvMsgSuccess , Qt::BlockingQueuedConnection);
    connect(tcpModule , &TcpModule::sigSendMsgSuccess , this , &TcpServer::slotSendMsgSuccess , Qt::BlockingQueuedConnection);

    /* 移至线程 */
    QThread *thread = new QThread;
    tcpModule->moveToThread(thread);
    thread->start();

    return;
}

void TcpServer::slotMaintainTcpLinkAdd(g_tcpItem item)
{
    qDebug() << "Info : TcpServer , slotMaintainTcpLinkAdd , uuid ---> " << item.uuid;

    if (GlobalData::getInstance()->m_tcpLink.tcpMaintainAdd(item)) {
        qDebug() << "Waring , TcpServer , slotMaintainTcpLinkadd , maintain tcp link fail";
    }
}

void TcpServer::slotMaintainTcpLinkDelete(QString uuid)
{
    qDebug() << "Info : TcpServer , slotMaintainTcpLinkDelete , uuid ---> " << uuid;

    if (GlobalData::getInstance()->m_tcpLink.tcpMaintainDelete(uuid)) {
        qDebug() << "Waring , TcpServer , slotMaintainTcpLinkDelete , maintain tcp link fail";
    }
}

void TcpServer::slotRecvMsgSuccess(g_recv recv)
{
    qDebug() << "Info : TcpServer , slotRecvMsgSuccess , uuid ---> " << recv.uuid << "msgData ---> " << recv.msgData;

    emit sigTcpServerRecvMsgSuccess(recv);
}

void TcpServer::slotSendMsgSuccess(g_send send)
{
    qDebug() << "Info : TcpServer , slotSendMsgSuccess , uuid ---> " << send.uuid << "msgData ---> " << send.msgData;

    emit sigTcpServerSendMsgSuccess(send);
}
