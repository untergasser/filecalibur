#-------------------------------------------------
#
# Project created by QtCreator 2012-10-30T12:21:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Filecalibur
TEMPLATE = app

mac {
    ICON = files/Logo_mac.icns
    QMAKE_INFO_PLIST += Info.plist
}

win32 {
    RC_FILE = filecalibur.rc
}

RESOURCES += resource.qrc

SOURCES += main.cpp\
    mainwindow.cpp \
    dialogcalchash.cpp \
    dialogerrormessage.cpp \
    filedatamodel.cpp \
    dialogrunhasdeep.cpp \
    dialogrsync.cpp \
    dialogrunrsync.cpp \
    dialogmodifypath.cpp \
    dialogremovepath.cpp \
    dialogextractpath.cpp \
    dialogjoinfiles.cpp \
    dialogoptionen.cpp \
    dialogpositivehashing.cpp \
    dialognegativehashing.cpp \
    dialogfindduplicates.cpp \
    dialogdifftool.cpp \
    dialogdeletefiles.cpp \
    dialogdelemptdir.cpp \
    dialogabout.cpp \
    dialogmanual.cpp \
    dialogfindlongname.cpp

HEADERS  += mainwindow.h \
    dialogcalchash.h \
    dialogerrormessage.h \
    filedatamodel.h \
    dialogrunhasdeep.h \
    dialogrsync.h \
    dialogrunrsync.h \
    dialogmodifypath.h \
    dialogremovepath.h \
    dialogextractpath.h \
    dialogjoinfiles.h \
    dialogoptionen.h \
    dialogpositivehashing.h \
    dialognegativehashing.h \
    dialogfindduplicates.h \
    dialogdifftool.h \
    dialogdeletefiles.h \
    dialogdelemptdir.h \
    dialogabout.h \
    dialogmanual.h \
    dialogfindlongname.h

FORMS    += mainwindow.ui \
    dialogcalchash.ui \
    dialogerrormessage.ui \
    dialogrunhasdeep.ui \
    dialogrsync.ui \
    dialogrunrsync.ui \
    dialogmodifypath.ui \
    dialogremovepath.ui \
    dialogextractpath.ui \
    dialogjoinfiles.ui \
    dialogoptionen.ui \
    dialogpositivehashing.ui \
    dialognegativehashing.ui \
    dialogfindduplicates.ui \
    dialogdifftool.ui \
    dialogdeletefiles.ui \
    dialogdelemptdir.ui \
    dialogabout.ui \
    dialogmanual.ui \
    dialogfindlongname.ui

TRANSLATIONS    += spreadsheet_de.ts

RESOURCES += \
    translations.qrc
