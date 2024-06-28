CONFIG += c++17
QT += quick websockets

DEFINES -= QT_NO_SSL

SOURCES += \
    Consumers.cpp \
    QtVisSocket.cpp \
    VisSocket.cpp \
    main.cpp \
    ActivatedEvent.cpp  \
    Model.cpp

RESOURCES += \
    qml.qrc

OTHER_FILES += \
    doc/src/*.*

HEADERS += \
    Consumers.h \
    QtVisSocket.h \
    VisSocket.h \
    ActivatedEvent.h \
    Model.h



