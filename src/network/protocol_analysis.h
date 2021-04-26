#ifndef __PROTOCOL_ANALYSIS_H__
#define __PROTOCOL_ANALYSIS_H__

#include <QString>
#include <QMap>

class ProtocolAnalysis
{
public:
    ProtocolAnalysis();
    ~ProtocolAnalysis();

    QMap<QString , QString> analysisHeadBody(QString str);
    QString encapsulationHeadBody(QMap<QString , QStirng> map);

private:
};

#endif

/*
 * 包头 + 包体 协议
 * uuid:xxx\r\n
 * type:msg/file\r\n
 * file_name:xx\r\n
 * file_stat:info/data/end\r\n
 * \r\n
 * body
 */

