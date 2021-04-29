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

    newItem = new QStandardItem();
    newItem->setData("Z", FriendListModel::Avatar);
    newItem->setData("Zhangsan", FriendListModel::Nickname);
    newItem->setData("listview", FriendListModel::RecentMsgContent);
    newItem->setData("10:22", FriendListModel::RecentMsgTime);
    newItem->setData("5", FriendListModel::UnreadMsgNum);
    newItem->setData(true, FriendListModel::OnlineState);

    appendRow(newItem);
}
void FriendListModel::updateFriend()
{
    this->item(0)->setData("Zhaoyun", FriendListModel::Nickname);
}

void removeFriend(QString uuid)
{

}