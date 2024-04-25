#include "control.h"

Control::Control()
{
    init();
    establishInterrupt();

    /* 模拟客户端 */
    g_udpItem item;
    item.uuid = QString("0x7777777");
    item.peerListenIp = QString("172.20.3.250");
    item.peerListenPort = QString("6066");
    GlobalData::getInstance()->m_tcpLink.udpMaintainAdd(item);

    g_send send;
    send.uuid = QString("0x7777777");
    send.type = QString("msg");
    send.msgData = QString("阿萨德；放假啊商店里；放假啊搜到放假哦啊配送积分大设计费");

    slotSend(send);

}

Control::~Control()
{
    if (this->m_client != NULL) {
        delete this->m_client;
    }

    if (this->m_server != NULL) {
        delete this->m_server;
    }

    if (this->m_udpSocket != NULL) {
        delete this->m_udpSocket;
    }

}

void Control::init(void)
{
    /* 实例全局数据模块 */
    GlobalData::getInstance();

    this->m_server = new TcpServer;
    this->m_client = new TcpClient;
    this->m_udpSocket = new UdpSocket;

    return;
}

void Control::establishInterrupt(void)
{
    connect(this->m_server , &TcpServer::sigTcpServerRecvMsgSuccess , this , &Control::slotRecvMsgSuccess);
    connect(this->m_server , &TcpServer::sigTcpServerSendMsgSuccess , this , &Control::slotSendMsgSuccess);
    connect(this->m_client , &TcpClient::sigTcpClientRecvMsgSuccess , this , &Control::slotRecvMsgSuccess);
    connect(this->m_client , &TcpClient::sigTcpClientSendMsgSuccess , this , &Control::slotSendMsgSuccess);


    return;
}

void Control::slotSend(g_send send)
{
    this->m_client->tran(send);
}

void Control::slotRecvMsgSuccess(g_recv recv)
{
    qDebug() << "Debug : Control , slotRecvMsgSuccess , recv msg ---> " << recv.msgData;

    return;
}

void Control::slotSendMsgSuccess(g_send send)
{
    qDebug() << "Debug , Control , slotSendMsgSuccess , send msg ---> " << send.msgData;

    return;
}
