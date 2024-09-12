cmake_minimum_required(VERSION 3.16)
project(clusterapp LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Quick3D)

qt_add_executable(clusterapp
    main.cpp
)

set_target_properties(clusterapp PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(clusterapp PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Quick
    Qt::Quick3D
)

qt_add_qml_module(clusterapp
    URI Example
    VERSION 1.0
    QML_FILES main.qml
    RESOURCES cluster-bkg.png
    NO_RESOURCE_TARGET_PATH
)

install(TARGETS clusterapp
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
