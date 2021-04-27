#include "protocol_analysis.h"

#include <QDebug>

ProtocolAnalysis::ProtocolAnalysis()
{

}

ProtocolAnalysis::~ProtocolAnalysis()
{

}

QMap<QString , QString> ProtocolAnalysis::analysisHeadBody(QString str)
{
    QMap<QString , QString> dst;
    QString key;
    QString value;
    dst.clear();
    key.clear();
    value.clear();

    char *first = NULL;
    char *separator = NULL;
    char *end = NULL;
    char *data = NULL;
    char *tmp = NULL;

    if (str.isEmpty()) {
        qDebug() << "Waring : ProtocolAnalysis , analysisHeadBody , orignal str is empty!!!";
        return dst;
    }

    QByteArray originalStrTmp = str.toLatin1();
    char *originalStr = originalStrTmp.data();

    /* 获取指向数据第一个字符的指针 */
    data = strstr(originalStr , "\r\n\r\n");
    if (data == NULL) {
        qDebug() << "Error : ProtocolAnalysis , analysisHeadBody , package head error";
        return dst;
    }
    data = data + 4;

    /* 解析包头key */
    first = originalStr;

    while (first + 2 != data) {
        separator = strchr(first , ':');
        end = strstr(first , "\r\n");

        int size = separator - first + 1;
        tmp = (char *)malloc(size);
        memset(tmp , 0x00 , size);

        strncpy(tmp , first , separator - first);

        /* 保存key */
        key = QString(tmp);

        /* 解析value */
        size = end - separator;
        tmp = (char *)realloc(tmp , size);
        memset(tmp , 0x00 , size);

        strncpy(tmp , separator + 1 , end - separator - 1);

        /* 保存value */
        value = QString(tmp);

        /* 保存key , value */
        dst.insert(key , value);

        /* 释放堆内存 */
        free(tmp);
        tmp = NULL;

        /* 重置first指针 */
        first = end + 2;
    }

    /* 解析包体 */
    key = QString("body");
    value = QString(data);

    dst.insert(key , value);

    return dst;
}

QString ProtocolAnalysis::encapsulationHeadBody(QMap<QString, QString> map)
{

    QString dst;
    QString data;

    dst.clear();
    data.clear();

    if (map.isEmpty()) {
        qDebug() << "Waring : ProtocolAnalysis , encapsulationHeadBody , map is empty!!!";
        return dst;
    }


    data = map.value("body" , "");

    /* 遍历map , 拼接包头 */
    QMap<QString , QString>::iterator begin = map.begin();
    QMap<QString , QString>::iterator end = map.end();

    while (begin != end) {
        QString key = begin.key();
        QString value = begin.value();

        if (key != "body") {
            dst.append(key);
            dst.append(":");
            dst.append(value);
            dst.append("\r\n");
        }
        begin++;
    }

    dst.append("\r\n");

    if (!data.isEmpty()) {
        dst.append(data);
    }

    return dst;
}
