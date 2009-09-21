TEMPLATE = app
UI_DIR = uics/client
MOC_DIR = mocs/client
RCC_DIR = rccs/client
OBJECTS_DIR = obj/client
CONFIG += qt
CONFIG += debug \
    \ \
    \ \ # CONFIG += release \
    warn_on
QT += network \
    xml
RESOURCES += src/client/resources/client.qrc
INCLUDEPATH += src/client \
    src/common
DEPENDPATH += src/common

# Input
HEADERS += src/client/gameloop.h \
    src/client/connecttoserverdialog.h \
    src/client/mainwindow.h \
    src/client/serverconnection.h \
    src/client/joingamedialog.h \
    src/client/logwidget.h \
    src/client/chatwidget.h \
    src/client/card.h \
    src/client/opponentwidget.h \
    src/client/game.h \
    src/client/cardwidget.h \
    src/client/creategamedialog.h \
    src/client/playerwidget.h \
    src/client/characterwidget.h \
    src/client/cardpilewidget.h \
    src/client/deckwidget.h \
    src/client/cardpocket.h \
    src/client/localplayerwidget.h \
    src/client/cardlistwidget.h \
    src/client/gameevent.h \
    src/client/gameeventcmd.h \
    src/client/cardmovementevent.h \
    src/client/gameeventqueue.h \
    src/client/gameeventhandler.h \
    src/client/gamecontextchangeevent.h \
    src/client/gamesyncevent.h \
    src/client/lifepointschangeevent.h \
    src/client/gameactionmanager.h \
    src/client/playerdiedevent.h \
    src/client/playerevent.h \
    src/client/graveyardwidget.h \
    src/client/cardzoomwidget.h \
    src/client/newserverdialog.h \
    src/client/selectavatarwidget.h \
    src/client/gamemessageevent.h \
    src/client/cardwidgetsizemanager.h \
    src/client/aboutdialog.h \
    src/client/cardsetmanager.h \
    src/client/cardsetinfo.h \
    src/client/cardbank.h \
    src/client/clienttypes.h \
    src/client/gameeventplayer.h \
    src/client/setplayerscmd.h
FORMS += src/client/connecttoserverdialog.ui \
    src/client/mainwindow.ui \
    src/client/joingamedialog.ui \
    src/client/logwidget.ui \
    src/client/chatwidget.ui \
    src/client/opponentwidget.ui \
    src/client/creategamedialog.ui \
    src/client/localplayerwidget.ui \
    src/client/newserverdialog.ui \
    src/client/aboutdialog.ui
SOURCES += src/client/gameloop.cpp \
    src/client/main.cpp \
    src/client/connecttoserverdialog.cpp \
    src/client/mainwindow.cpp \
    src/client/serverconnection.cpp \
    src/client/joingamedialog.cpp \
    src/client/logwidget.cpp \
    src/client/chatwidget.cpp \
    src/client/card.cpp \
    src/client/opponentwidget.cpp \
    src/client/game.cpp \
    src/client/cardwidget.cpp \
    src/client/creategamedialog.cpp \
    src/client/playerwidget.cpp \
    src/client/characterwidget.cpp \
    src/client/cardpilewidget.cpp \
    src/client/deckwidget.cpp \
    src/client/localplayerwidget.cpp \
    src/client/cardlistwidget.cpp \
    src/client/gameevent.cpp \
    src/client/gameeventcmd.cpp \
    src/client/cardmovementevent.cpp \
    src/client/gameeventqueue.cpp \
    src/client/gameeventhandler.cpp \
    src/client/gamecontextchangeevent.cpp \
    src/client/gamesyncevent.cpp \
    src/client/lifepointschangeevent.cpp \
    src/client/gameactionmanager.cpp \
    src/client/cardpocket.cpp \
    src/client/playerdiedevent.cpp \
    src/client/playerevent.cpp \
    src/client/graveyardwidget.cpp \
    src/client/cardzoomwidget.cpp \
    src/client/newserverdialog.cpp \
    src/client/selectavatarwidget.cpp \
    src/client/gamemessageevent.cpp \
    src/client/cardwidgetsizemanager.cpp \
    src/client/aboutdialog.cpp \
    src/client/cardsetmanager.cpp \
    src/client/cardsetinfo.cpp \
    src/client/cardbank.cpp \
    src/client/gameeventplayer.cpp \
    src/client/setplayerscmd.cpp
TRANSLATIONS = ts/kbang_client_cs.ts
unix { 
    LIBPATH += lib
    TARGETDEPS += lib/libkbang_common.a
}
win32 { 
    RC_FILE = kbang_client.rc
    debug:LIBPATH += debug/lib
    release:LIBPATH += release/lib
}
LIBS += -lkbang_common
TARGET = kbang-client
QMAKE_CXXFLAGS_DEBUG += -Wall
