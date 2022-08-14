QT       += core gui multimedia multimediawidgets quick quickwidgets positioning location

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    collection_display.cpp \
    leftside.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    metadata.cpp \
    playeroverlay.cpp \
    prompt.cpp \
    rightside.cpp \
    searchbox.cpp \
    the_button.cpp \
    the_player.cpp \
    video.cpp \
    videobutton.cpp

HEADERS += \
    collection_display.h \
    custommenu.h \
    custommenu.h \
    leftside.h \
    mainwindow.h \
    map.h \
    metadata.h \
    playeroverlay.h \
    prompt.h \
    rightside.h \
    searchbox.h \
    the_button.h \
    the_player.h \
    timer.h \
    video.h \
    videobutton.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc \
    Resources.qrc

DISTFILES += \
    Player.pro.user \
    load_test.txt \
    map.qml


HEADERS += \
    collection_display.h \
    custommenu.h \
    leftside.h \
    mainwindow.h \
    map.h \
    metadata.h \
    playeroverlay.h \
    prompt.h \
    rightside.h \
    searchbox.h \
    the_button.h \
    the_player.h \
    timer.h \
    video.h \
    videobutton.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc \
    Resources.qrc

DISTFILES += \
    Player.pro.user \
    load_test.txt \
    map.qml
