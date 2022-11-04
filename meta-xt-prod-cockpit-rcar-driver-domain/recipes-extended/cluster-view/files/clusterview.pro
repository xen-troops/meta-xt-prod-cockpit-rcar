QT += quick websockets

DEFINES -= QT_NO_SSL

SOURCES += \
    commandline.cpp \
    main.cpp \
    visclient.cpp

RESOURCES += \
    qml.qrc

OTHER_FILES += \
    doc/src/*.*

HEADERS += \
    commandline.h \
    visclient.h



