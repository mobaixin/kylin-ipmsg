#include "udp_socket.h"
#include "global/utils/global_data.h"

#include <QNetworkInterface>

UdpSocket::UdpSocket()
{
    init();
    //slotOnline();
}

UdpSocket::~UdpSocket()
{
    if (this->m_timer != NULL) {
        delete this->m_timer;
    }

    if (this->m_udpSocket != NULL) {
        delete this->m_udpSocket;
    }

    slotOffline();
}

void UdpSocket::init(void)
{
    /* 实例udpsocket */
    this->m_udpSocket = new QUdpSocket;

    /* 获取udp监听端口 */
    QString port = GlobalData::getInstance()->m_udpListenPort;

    if (this->m_udpSocket->bind(QHostAddress::AnyIPv4 , port.toUShort() , QUdpSocket::ReuseAddressHint) == true) {
        qDebug() << "Info : UdpSocket , bind success";
    }

    connect(this->m_udpSocket , &QUdpSocket::readyRead , this , &UdpSocket::slotSocketRead);

    /* 启动定时器 */
    this->m_timer = new QTimer;
    connect(this->m_timer , &QTimer::timeout , this , &UdpSocket::slotOnline);
    this->m_timer->start(10000);

    return;
}

void UdpSocket::slotSocketRead(void)
{
    qDebug() << "Info  , UdpSocket , slotSocketRead , recv udp package";

    while (this->m_udpSocket->hasPendingDatagrams()) {
        QByteArray package;
        package.resize(65536);
        QHostAddress peerIp;
        int size = this->m_udpSocket->readDatagram(package.data() , package.size() , &peerIp);
        package.resize(size);

        /* udp包接收完毕 , 解析udp包 */
        QString data = QString::fromUtf8(package);
        QStringList dataList = data.split(" ");
        if (dataList.at(0) == "true") {
            /* 上线广播 */
            QString uuid = dataList.at(1);
            QString peerListenIp = dataList.at(2);
            QString peerListenPort = dataList.at(3);

            /* 维护tcp链接表 */
            g_udpItem tmp;
            tmp.uuid = uuid;
            tmp.peerListenIp = peerListenIp;
            tmp.peerListenPort = peerListenPort;

            GlobalData::getInstance()->m_tcpLink.udpMaintainAdd(tmp);

            /* 测试输出 */
            qDebug() << "Info : UdpSocket , slotUdpSocketRead , recv udp data";
            qDebug() << "uuid = " << uuid << "peerListenIp = " << peerListenIp << "peerListenPort = " << peerListenPort;
            GlobalData::getInstance()->m_tcpLink.ergodic();
        } else if (dataList.at(0) == "false") {
            QString uuid = dataList.at(1);

            /* 维护tcp链接表 */
            GlobalData::getInstance()->m_tcpLink.udpMaintainDelete(uuid);
            GlobalData::getInstance()->m_tcpLink.ergodic();

            qDebug() << "Info : UdpSocket , slotUdpSocketRead , recv udp offline";
        }
    }

    return;
}

void UdpSocket::udpSocketBroadcast(bool flag)
{
    QByteArray package;
    QString udpListenPort = GlobalData::getInstance()->m_udpListenPort;

    /* 组装数据包 */
    QString uuid = GlobalData::getInstance()->m_uuid;
    QString tcpListenIp = GlobalData::getInstance()->m_tcpListenIP;
    QString tcpListenPort = GlobalData::getInstance()->m_tcpListenPort;

    if (flag == true) {
        package.append(QString("true"));
        package.append(QString(" "));
        package.append(uuid);
        package.append(QString(" "));
        package.append(tcpListenIp);
        package.append(QString(" "));
        package.append(tcpListenPort);
    } else {
        package.append(QString("false"));
        package.append(QString(" "));
        package.append(QString(uuid));
    }

    /* 广播发送 */
    QList<QNetworkInterface> interface = QNetworkInterface::allInterfaces();
    for (int i = 0 ; i < interface.count() ; i++) {
        QList<QNetworkAddressEntry> addrs = interface.at(i).addressEntries();

        for (int j = 0 ; j < addrs.count() ; j++) {
            if (addrs.at(j).ip().protocol() == QAbstractSocket::IPv4Protocol && (addrs.at(j).broadcast().toString() != "")) {
                this->m_udpSocket->writeDatagram(package.data() , package.length() , addrs.at(j).broadcast() , udpListenPort.toUShort());

                qDebug() << "Debug : UdpSocket , udpSocketBroadcast , broadcast addr ---> " << addrs.at(j).broadcast();

                this->m_udpSocket->flush();
            }
        }
    }

    qDebug() << "Info : UdpSocket , udpSocketBroadcast , udp pkg ---> " << package;

    return;
}

void UdpSocket::slotOnline(void)
{
    udpSocketBroadcast(true);

    return;
}

void UdpSocket::slotOffline(void)
{
    udpSocketBroadcast(false);

    return;
}
