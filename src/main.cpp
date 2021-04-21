/* 
 * Copyright (C) 2011 Emanuele Colombo
 *               2020 KylinSoft Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QStandardPaths>
#include <QLibraryInfo>
#include <QDir>
#include <fcntl.h>
#include <syslog.h>
#include <QDebug>

#include <ukui-log4qt.h>

#include <QFile>
#include <QMutex>
#include <QDateTime>
#include <sys/inotify.h>

#include "view/kyview.h"
#include "view/common/xatom-helper.h"
#include "view/common/dbusadaptor.h"

int main(int argc, char *argv[])
{
    // 统一日志输出
    initUkuiLog4qt("kylin-ipmsg");

    // 适配4K屏以及分数缩放
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 12, 0))
        QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    #endif
    
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
        QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    #endif

    QApplication app(argc, argv);
    app.setApplicationVersion("2.1.1");

    // 设置不使用gtk3平台文件对话框
    app.setProperty("useFileDialog", false);

    // 连接DBus服务
    QDBusInterface interface(KYLIN_MESSAGES_SERVICE, 
                             KYLIN_MESSAGES_PATH,
                             KYLIN_MESSAGES_INTERFACE,
                             QDBusConnection::sessionBus());
    if (interface.isValid()) {
        // 调用拉起主界面的method
        interface.call("showMainWindow");
        interface.call("showMainWindow");
    }

    // 文件锁实现VNC单例
    QStringList homePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
    // 需要给文件锁加一个DISPLAY标识
    int fd = open(QString(homePath.at(0) + "/.config/kylin-messages%1.lock").arg(getenv("DISPLAY")).toUtf8().data(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0)
    {
        exit(1);
    }
    if (lockf(fd, F_TLOCK, 0))
    {
        syslog(LOG_ERR, "Can't lock single file, kylin-messages is already running!");
        exit(0);
    }

    // 国际化
    QString qtTransPath;
    // /usr/share/qt5/translations
    qtTransPath = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
    QString kylinMessagesTransPath;

#ifdef QT_NO_DEBUG
    if (QDir("/usr/share/kylin-messages/translations").exists()) {
        kylinMessagesTransPath = "/usr/share/kylin-messages/translations";
    }
    else {
        kylinMessagesTransPath = qApp->applicationDirPath() + "/.qm";
    }
#else
    kylinMessagesTransPath = "translations";
#endif

    QString locale = QLocale::system().name();
    QTranslator trans_global, trans_qt;
    if (locale == "zh_CN") {
        if(!trans_global.load(QLocale(), "kylin-messages", "_", kylinMessagesTransPath))
            qDebug() << "Load translations file" <<QLocale() << "failed!";
        else
            app.installTranslator(&trans_global);

        if(!trans_qt.load(QLocale(), "qt", "_", qtTransPath))
            qDebug() << "Load translations file" <<QLocale() << "failed!";
        else
            app.installTranslator(&trans_qt);
    }

    KyView::getInstance();

#ifdef __V10Pro__
    // 添加窗管协议
    MotifWmHints hints;
    hints.flags = MWM_HINTS_FUNCTIONS | MWM_HINTS_DECORATIONS;
    hints.functions = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_BORDER;
    XAtomHelper::getInstance()->setWindowMotifHint(KyView::getInstance()->winId(), hints);
#endif

    KyView::getInstance()->show();

    // 创建DBus服务
    DbusAdaptor adaptor;
    Q_UNUSED(adaptor);

    return app.exec();
}
