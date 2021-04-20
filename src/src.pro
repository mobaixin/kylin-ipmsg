QT       += core gui
QT       += svg
QT       += dbus
QT       += x11extras KWindowSystem
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
# 适配窗口管理器圆角阴影
LIBS +=-lpthread
LIBS +=-lX11
TARGET = kylin-photo-viewer
TEMPLATE = app

CONFIG += link_pkgconfig
PKGCONFIG += gsettings-qt

DEFINES += QT_DEPRECATED_WARNINGS

#stb
LIBS += -lstb \

#gif
LIBS += -lgif \

target.path = /usr/bin
target.source +=$$TARGET
INSTALLS += target

SOURCES += main.cpp \

HEADERS += \

RESOURCES += \
