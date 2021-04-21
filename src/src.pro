QT += core gui network dbus
QT += x11extras KWindowSystem

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# 适配窗口管理器圆角阴影
LIBS +=-lpthread
LIBS +=-lX11

# 配置gsettings
CONFIG += link_pkgconfig
PKGCONFIG += gsettings-qt

# for nullptr
CONFIG += c++11

# 配置gsettings
PKGCONFIG += gsettings-qt

# 统一日志输出
LIBS += -L/usr/lib/libukui-log4qt.so.1.0.0 -lukui-log4qt

TARGET = kylin-wechat
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

target.path = /usr/bin
target.source += $$TARGET

INSTALLS += target

# V10Pro使用自定义用户手册
greaterThan(QT_MAJOR_VERSION, 5) | greaterThan(QT_MINOR_VERSION, 9) {
    # message("QT_VERSION ("$$QT_VERSION")")
    DEFINES   += __V10Pro__
}

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/view/kyview.cpp \
    $$PWD/view/common/xatom-helper.cpp  \
    $$PWD/view/common/daemondbus.cpp    \
    $$PWD/view/common/dbusadaptor.cpp   \
    $$PWD

HEADERS += \
    $$PWD/view/kyview.h \
    $$PWD/view/common/xatom-helper.h    \
    $$PWD/view/common/daemondbus.h      \
    $$PWD/view/common/dbusadaptor.h     \

RESOURCES += \
