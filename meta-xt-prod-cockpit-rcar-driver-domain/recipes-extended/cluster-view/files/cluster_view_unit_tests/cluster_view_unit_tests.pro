QT += testlib quick websockets
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    tst_cluster_view_input.cpp \
    ../VisSocket.cpp \
    ../visclient.cpp \
    ../QtVisSocket.cpp

HEADERS += \
    ../visclient.h \
    ../VisSocket.h \
    ../QtVisSocket.h
