QT += core quickcontrols2 websockets dbus
DEFINES -= QT_NO_SSL
HEADERS += VisClient.h \
    Consumers.h
SOURCES += main.cpp VisClient.cpp \
    Consumers.cpp
