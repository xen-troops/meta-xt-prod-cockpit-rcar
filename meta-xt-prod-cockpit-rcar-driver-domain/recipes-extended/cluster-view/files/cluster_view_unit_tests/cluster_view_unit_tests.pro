QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

DEFINES += CLUSTER_UNIT_TEST=1

TEMPLATE = app

SOURCES +=  \
    tst_cluster_view_input.cpp \
    ../VisSocket.cpp \
    ../visclient.cpp \
    ../Consumers.cpp

HEADERS += \
    ../visclient.h \
    ../VisSocket.h \
    ../Consumers.h
