/*
 * Copyright (C) 2020, KylinSoft Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "database.h"

FriendInfoData::FriendInfoData(int     m_friendId,
                               QString m_friendUuid,
                               QString m_friendIp,
                               int     m_friendPort,
                               QString m_friendMac,
                               QString m_username,
                               QString m_nickname,
                               QString m_system,
                               QString m_platform,
                               QString m_avatarUrl,
                               QString m_recentMsgCont,
                               QString m_recentMsgTime,
                               int     m_unreadMsgNum,
                               int     m_priority)
{
    this->m_friendId    = m_friendId;
    this->m_friendUuid  = m_friendUuid;
    this->m_friendIp    = m_friendIp;
    this->m_friendPort  = m_friendPort;
    this->m_friendMac   = m_friendMac;
    this->m_username    = m_username;
    this->m_nickname    = m_nickname;
    this->m_system      = m_system;
    this->m_platform    = m_platform;
    this->m_avatarUrl   = m_avatarUrl;
    this->m_recentMsgCont   = m_recentMsgCont;
    this->m_recentMsgTime   = m_recentMsgTime;
    this->m_unreadMsgNum    = m_unreadMsgNum;
    this->m_priority    = m_priority;
}

FriendInfoData::FriendInfoData(QMap<QString, QString> strMap, QMap<QString, int> intMap)
{
    // if (strMap.isEmpty() || intMap.isEmpty()) {
    //     return ;
    // }

    // QString类型变量赋值
    if (strMap.contains("m_friendUuid")) {
        m_friendUuid = strMap["m_friendUuid"];
    }    
    if (strMap.contains("m_friendIp")) {
        m_friendIp = strMap["m_friendIp"];
    }
    if (strMap.contains("m_friendMac")) {
        m_friendMac = strMap["m_friendMac"];
    }
    if (strMap.contains("m_username")) {
        m_username = strMap["m_username"];
    }
    if (strMap.contains("m_nickname")) {
        m_nickname = strMap["m_nickname"];
    }
    if (strMap.contains("m_system")) {
        m_system = strMap["m_system"];
    }
    if (strMap.contains("m_platform")) {
        m_platform = strMap["m_platform"];
    }
    if (strMap.contains("m_avatarUrl")) {
        m_avatarUrl = strMap["m_avatarUrl"];
    }
    if (strMap.contains("m_recentMsgCont")) {
        m_recentMsgCont = strMap["m_recentMsgCont"];
    }
    if (strMap.contains("m_recentMsgTime")) {
        m_recentMsgTime = strMap["m_recentMsgTime"];
    }
    
    // int类型变量赋值
    if (intMap.contains("m_friendId")) {
        m_friendId = intMap["m_friendId"];
    }
    if (intMap.contains("m_friendPort")) {
        m_friendPort = intMap["m_friendPort"];
    }
    if (intMap.contains("m_unreadMsgNum")) {
        m_unreadMsgNum = intMap["m_unreadMsgNum"];
    }
    if (intMap.contains("m_priority")) {
        m_priority = intMap["m_priority"];
    }
}

FriendInfoData::~FriendInfoData()
{
}


FriendInfoDataBase::FriendInfoDataBase(QObject *parent) : QObject(parent)
{
    m_dbName = "kylin-messages.db";
    m_dbTableName = "friend_info";

    // 打开数据库
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(QApplication::applicationDirPath() + "/../../data/database/" + m_dbName); 

    qDebug() << QApplication::applicationDirPath() + "/../../data/database/" + m_dbName;

    if (!m_db.open()) {
        m_dbName = "";
        m_dbTableName = "";
        QMessageBox::warning(0, QObject::tr("Database Error"),
                                     m_db.lastError().text());
    }

    // 使用model
    m_model = new QSqlTableModel(this, m_db);
    m_model->setTable(m_dbTableName);
    // 提交后才修改数据库
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    m_model->select();
}

FriendInfoDataBase::~FriendInfoDataBase()
{
    
}

FriendInfoDataBase* FriendInfoDataBase::getInstance()
{
    static FriendInfoDataBase *instance = nullptr;

    if (instance == nullptr) {
        try {
            instance = new FriendInfoDataBase();
        }
        catch (const std::runtime_error &re)
        {
            qDebug() << "runtime_error:" << re.what();
        }
    }

    return instance;
}

// 插入数据
// TODO 数据加密处理
bool FriendInfoDataBase::insertData(FriendInfoData *friendInfo)
{
    int col = m_model->columnCount();
    int row = m_model->rowCount();
    int index = 0;

    m_model->insertRow(row);
    index++;
    // m_model->setData(m_model->index(row, index++), friendInfo->m_friendId);
    m_model->setData(m_model->index(row, index++), friendInfo->m_friendUuid);
    m_model->setData(m_model->index(row, index++), friendInfo->m_friendIp);
    m_model->setData(m_model->index(row, index++), friendInfo->m_friendPort);
    m_model->setData(m_model->index(row, index++), friendInfo->m_friendMac);
    m_model->setData(m_model->index(row, index++), friendInfo->m_username);
    m_model->setData(m_model->index(row, index++), friendInfo->m_nickname);
    m_model->setData(m_model->index(row, index++), friendInfo->m_system);
    m_model->setData(m_model->index(row, index++), friendInfo->m_platform);
    m_model->setData(m_model->index(row, index++), friendInfo->m_avatarUrl);
    m_model->setData(m_model->index(row, index++), friendInfo->m_recentMsgCont);
    m_model->setData(m_model->index(row, index++), friendInfo->m_recentMsgTime);
    m_model->setData(m_model->index(row, index++), friendInfo->m_unreadMsgNum);
    m_model->setData(m_model->index(row, index++), friendInfo->m_priority);
    
    // 提交修改
    m_model->submitAll();
    m_model->select();

    return true;
}

// 查询数据
bool FriendInfoDataBase::queryData(FriendInfoData *friendInfo)
{
    return m_model->select();
}

// 更新数据
// TODO 获取行号
bool FriendInfoDataBase::updateData(FriendInfoData *friendInfo)
{
    // 示例
    // 使用model必须要获取到行号和列号
    int row = 0;
    int col = 0;
    
    m_model->setData(m_model->index(row, col), friendInfo->m_priority);

    m_model->submitAll();

    // TODO 使用query获取行号
    QString queryIndex = QString("SELECT rowid from %1 where friend_id = %2")
                                 .arg(m_dbTableName).arg(friendInfo->m_friendId);
    query.prepare(queryIndex);
    return query.exec();
}

// 删除数据
bool FriendInfoDataBase::deleteData(FriendInfoData *friendInfo)
{
    // 示例
    int delRow = 0;

    m_model->removeRow(delRow);
    m_model->submitAll();
    return m_model->select();
}

/**************************************************************************
* 函数名称：updatePriority
* 函数功能：修改好友的优先级
* 输入参数：FriendInfoData
* 返回数值：bool
* 创建人员：
* 创建时间：2021-05-06
* 修改人员：
* 修改时间：
**************************************************************************/
bool FriendInfoDataBase::updatePriority(FriendInfoData *friendInfo)
{
    // 使用query
    QString updateSql = QString("update %1 set priority = %2 where friend_id = %3")
                                 .arg(m_dbTableName).arg(friendInfo->m_priority).arg(friendInfo->m_friendId);
    query.prepare(updateSql);
    return query.exec();
}

/**************************************************************************
* 函数名称：updateNickname
* 函数功能：修改好友的备注名
* 输入参数：FriendInfoData
* 返回数值：bool
* 创建人员：
* 创建时间：2021-05-06
* 修改人员：
* 修改时间：
**************************************************************************/
bool FriendInfoDataBase::updateNickname(FriendInfoData *friendInfo)
{
    // 使用query
    QString updateSql = QString("update %1 set nickname = %2 where friend_id = %3")
                                 .arg(m_dbTableName).arg(friendInfo->m_nickname).arg(friendInfo->m_friendId);
    query.prepare(updateSql);
    return query.exec();
}

/**************************************************************************
* 函数名称： queryInfoById
* 函数功能： 根据ID获取好友信息
* 输入参数： friendId
* 返回数值： FriendInfoData
* 创建人员：
* 创建时间： 2021-05-06
* 修改人员：
* 修改时间：
**************************************************************************/
FriendInfoData *FriendInfoDataBase::queryInfoById(int friendId)
{
    // 使用query
    QString querySql = QString("select * from %1 where friend_id = %2")
                                 .arg(m_dbTableName).arg(friendId);
    query.prepare(querySql);
    query.exec();

    FriendInfoData *friendInfo = new FriendInfoData();

    if (query.next()) {
        friendInfo->m_friendId      = query.value("friend_id").toInt();
        friendInfo->m_friendUuid    = query.value("friend_uuid").toString();
        friendInfo->m_friendIp      = query.value("friend_ip").toString();
        friendInfo->m_friendPort    = query.value("friend_port").toInt();
        friendInfo->m_friendMac = query.value("friend_mac").toString();
        friendInfo->m_username  = query.value("user_name").toString();
        friendInfo->m_nickname  = query.value("nickname").toString();
        friendInfo->m_system    = query.value("system").toString();
        friendInfo->m_platform  = query.value("platform").toString();
        friendInfo->m_avatarUrl = query.value("avatar_url").toString();
        friendInfo->m_recentMsgCont = query.value("recent_msg_content").toString();
        friendInfo->m_recentMsgTime = query.value("recent_msg_time").toString();
        friendInfo->m_unreadMsgNum  = query.value("unread_msg_num").toInt();
        friendInfo->m_priority      = query.value("priority").toInt();
    }

    return friendInfo;
}

/**************************************************************************
* 函数名称： queryInfoByUuid
* 函数功能： 根据UUID获取好友信息
* 输入参数： friendUuid
* 返回数值： FriendInfoData
* 创建人员：
* 创建时间： 2021-05-06
* 修改人员：
* 修改时间：
**************************************************************************/
FriendInfoData *FriendInfoDataBase::queryInfoByUuid(QString friendUuid)
{
    // 使用query
    QString querySql = QString("select * from %1 where friend_uuid = %2")
                                 .arg(m_dbTableName).arg(friendUuid);
    query.prepare(querySql);
    query.exec();

    FriendInfoData *friendInfo = new FriendInfoData();

    if (query.next()) {
        friendInfo->m_friendId      = query.value("friend_id").toInt();
        friendInfo->m_friendUuid    = query.value("friend_uuid").toString();
        friendInfo->m_friendIp      = query.value("friend_ip").toString();
        friendInfo->m_friendPort    = query.value("friend_port").toInt();
        friendInfo->m_friendMac = query.value("friend_mac").toString();
        friendInfo->m_username  = query.value("user_name").toString();
        friendInfo->m_nickname  = query.value("nickname").toString();
        friendInfo->m_system    = query.value("system").toString();
        friendInfo->m_platform  = query.value("platform").toString();
        friendInfo->m_avatarUrl = query.value("avatar_url").toString();
        friendInfo->m_recentMsgCont = query.value("recent_msg_content").toString();
        friendInfo->m_recentMsgTime = query.value("recent_msg_time").toString();
        friendInfo->m_unreadMsgNum  = query.value("unread_msg_num").toInt();
        friendInfo->m_priority      = query.value("priority").toInt();
    }

    return friendInfo;
}