TEMPLATE = subdirs
SUBDIRS = \
    plugins \
    src \
    
# translations
TRANSLATIONS += \
    data/translations/kylin-wechat_zh_CN.ts
!system($$PWD/data/translations/generate_translations_pm.sh): error("Failed to generate pm")
qm_files.files = data/translations/*.qm
qm_files.path = /usr/share/kylin-wechat/data/translations/

# gsettings
schemes.files += \
    $$PWD/data/schemas/org.kylin-wechat-data.gschema.xml \
    $$PWD/data/schemas/org.ukui.log4qt.kylin-wechat.gschema.xml
schemes.path = /usr/share/glib-2.0/schemas/

desktop.files = data/kylin-wechat.desktop
desktop.path = /usr/share/applications/

INSTALLS += \
    desktop \
    schemes \
    qm_files

# V10Pro使用自定义用户手册
greaterThan(QT_MAJOR_VERSION, 5) | greaterThan(QT_MINOR_VERSION, 9) {
    # message("QT_VERSION ("$$QT_VERSION")")
    DEFINES   += __V10Pro__
    guide.path = /usr/share/kylin-user-guide/data/guide/
    guide.files = data/guide/kylin-wechat/

    INSTALLS += guide
}