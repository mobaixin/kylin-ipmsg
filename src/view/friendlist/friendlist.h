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

#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <QStringListModel>
#include <QStringList>
#include <QListView>
#include <QScrollBar>
#include <QDebug>
#include <QMetaType>

// #include "../../model/friendlistmodel.h"
#include "friendItemDelegate.h"

typedef struct {
    QString iconPath;
    QString singer;
    QString songsNb;
} MuItemData;

Q_DECLARE_METATYPE(MuItemData)

class FriendListView : public QListView
{

public:
    FriendListView(QListView *parent = nullptr);
    ~FriendListView();

private:
    /* data */
};




#endif // FRIENDLIST_H