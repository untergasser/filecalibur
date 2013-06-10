#-------------------------------------------------
#
# Project created by QtCreator 2012-10-30T12:21:53
#
#-------------------------------------------------

QT       += widgets

TARGET = Filecalibur
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogcalchash.cpp \
    dialogposmatch.cpp \
    dialogerrormessage.cpp \
    filedatamodel.cpp \
    dialognegmatch.cpp \
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
    dialogdelemptdir.cpp

HEADERS  += mainwindow.h \
    dialogcalchash.h \
    dialogposmatch.h \
    dialogerrormessage.h \
    filedatamodel.h \
    dialognegmatch.h \
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
    dialogdelemptdir.h

FORMS    += mainwindow.ui \
    dialogcalchash.ui \
    dialogposmatch.ui \
    dialogerrormessage.ui \
    dialognegmatch.ui \
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
    dialogdelemptdir.ui

TRANSLATIONS    = spreadsheet_de.ts

RESOURCES += \
    translations.qrc
