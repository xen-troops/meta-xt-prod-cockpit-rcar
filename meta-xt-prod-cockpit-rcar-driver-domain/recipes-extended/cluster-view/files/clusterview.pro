CONFIG += c++17
QT += quick websockets

DEFINES -= QT_NO_SSL

SOURCES += \
    Consumers.cpp \
    QtVisSocket.cpp \
    VisSocket.cpp \
    commandline.cpp \
    main.cpp \
    visclient.cpp \
    ActivatedEvent.cpp 

RESOURCES += \
    qml.qrc

OTHER_FILES += \
    doc/src/*.*

HEADERS += \
    Consumers.h \
    QtVisSocket.h \
    VisSocket.h \
    commandline.h \
    visclient.h \
    ActivatedEvent.h



