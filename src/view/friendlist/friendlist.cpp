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

#include <QDateTime>
#include <QThread>

#include "friendlist.h"


FriendListView::FriendListView(QListView *parent) :
    QListView(parent)
{
    QStringListModel *strListModel = new QStringListModel(this);
    QStringList *strList = new QStringList();
    
    strList->append("aaaaaaaaaaa");
    strList->append("bbbbbbbbbbb");
    strList->append("ccccccccccc");

    strListModel->setStringList(*strList);

    FriendListModel *friendListModel = new FriendListModel();
    friendListModel->addFriend();
    friendListModel->addFriend();
    friendListModel->addFriend();

    FriendItemDelegate *myItemDelegate = new FriendItemDelegate();
    this->setItemDelegate(myItemDelegate);

    // this->setModel(strListModel);
    this->setModel(friendListModel);
    this->setSpacing(0);
    this->setDragEnabled(false);
    this->setFrameShape(QListView::NoFrame);

    // QThread::sleep(5);

    friendListModel->updateFriend();

    delete strList;
}

FriendListView::~FriendListView()
{

}