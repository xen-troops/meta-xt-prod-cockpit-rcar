QT += quick websockets

DEFINES -= QT_NO_SSL

SOURCES += \
    main.cpp \
    visclient.cpp

RESOURCES += \
    qml.qrc

OTHER_FILES += \
    doc/src/*.*

HEADERS += \
    visclient.h



