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

#ifndef FRIENDLISTMODEL_H
#define FRIENDLISTMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <QDebug>
#include <QUuid>

#include "../global/database/database.h"

class FriendListModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit FriendListModel();
    ~FriendListModel();

    // 添加好友
    void addFriend();

    // 更新好友信息
    void updateFriend();

    // 更新好友状态
    // void updateFriendState(QString uuid， bool isOnline);

    // 删除好友
    void removeFriend(QString uuid);

    QStandardItem *friendById(QString id);
    QStandardItem *friendByUuid(QString uuid);

    enum FriendRoles {
        Id = Qt::UserRole + 1,
        Uuid,
        Ip,
        Port,
        Mac,
        Username,
        Nickname,
        System,
        Platform,
        Avatar,
        RecentMsgContent,
        RecentMsgTime,
        UnreadMsgNum,
        OnlineState,
        Priority,
    };

    /*<"uuid" , QStandardItem *>*/
    QHash<QString, QStandardItem*> m_ItemsMap;

private:

};

#endif // FRIENDLISTMODEL_H