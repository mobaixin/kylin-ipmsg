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

#ifndef DBUSADAPTOR_H
#define DBUSADAPTOR_H

#define KYLIN_MESSAGES_PATH "/"
#define KYLIN_MESSAGES_SERVICE "com.kylin.messages"
#define KYLIN_MESSAGES_INTERFACE "com.kylin.messages"

#include <QObject>
#include <QApplication>
#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusError>
#include <QDebug>

#include "../kyview.h"

class DbusAdaptor: public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", KYLIN_MESSAGES_SERVICE)

public:
    DbusAdaptor(QObject *parent = 0);
    virtual ~DbusAdaptor();

public slots:
    // 显示应用主界面
    void showMainWindow();
};

#endif
