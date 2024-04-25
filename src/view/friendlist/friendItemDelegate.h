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

#ifndef FRIENDITEMDELEGATE_H
#define FRIENDITEMDELEGATE_H

#include <QItemDelegate>
#include <QStyledItemDelegate>
#include <QStyleOption>
#include <QModelIndex>
#include <QEvent>
#include <QAbstractItemModel>
#include <QObject>
#include <QPainter>
#include <QVariant>
#include <QRectF>
#include <QPoint>
#include <QDebug>

#include "../../model/friendlistmodel.h"

class FriendItemDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    FriendItemDelegate();
    ~FriendItemDelegate();

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    // bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

};





#endif // FRIENDITEMDELEGATE_H