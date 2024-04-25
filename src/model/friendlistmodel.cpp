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

#include "friendlistmodel.h"

FriendListModel::FriendListModel() :
    QStandardItemModel(NULL)
{
    QHash<int, QByteArray> roleNames;
    roleNames[Id] = "id";
    roleNames[Uuid] = "uuid";
    roleNames[Ip] = "ip";
    roleNames[Port] = "port";
    roleNames[Mac] = "mac";
    roleNames[Username] = "username";
    roleNames[Username] = "nickname";
    roleNames[System] = "system";
    roleNames[Platform] = "platform";
    roleNames[Avatar] = "avatar";
    roleNames[RecentMsgContent] = "recentMsgContent";
    roleNames[RecentMsgTime] = "recentMsgTime";
    roleNames[UnreadMsgNum] = "unreadMsgNum";
    roleNames[OnlineState] = "onlineState";
    roleNames[Priority] = "priority";
    setItemRoleNames(roleNames);
}

FriendListModel::~FriendListModel()
{
}

void FriendListModel::addFriend()
{
    QStandardItem *newItem = NULL;

    // Check if the same uuid is alreay in the friend list

    QString avatar = "Z";
    QString nickname = "Zhangsan";
    QString msgContent = "listview";
    QString msgTime = "10:22";
    QString msgNum = "5";

    newItem = new QStandardItem();
    newItem->setData(avatar, FriendListModel::Avatar);
    newItem->setData(nickname, FriendListModel::Nickname);
    newItem->setData(msgContent, FriendListModel::RecentMsgContent);
    newItem->setData(msgTime, FriendListModel::RecentMsgTime);
    newItem->setData(msgNum, FriendListModel::UnreadMsgNum);
    newItem->setData(true, FriendListModel::OnlineState);

    appendRow(newItem);

    FriendInfoDataBase::getInstance();

    QMap<QString, QString> strMap;
    QMap<QString, int> intMap;
    strMap.insert("m_friendUuid", QUuid::createUuid().toString());
    strMap.insert("m_avatarUrl",  avatar);
    strMap.insert("m_nickname",   nickname);
    FriendInfoDataBase::getInstance()->insertData(new FriendInfoData(strMap, intMap));
}
void FriendListModel::updateFriend()
{
    this->item(0)->setData("Zhaoyun", FriendListModel::Nickname);
}

void removeFriend(QString uuid)
{

}