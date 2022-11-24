find_package(Qt6 6.2 COMPONENTS Qml Quick REQUIRED)

qt_add_executable(appMyApp
    main.cpp
)

qt_add_qml_module(appMyApp
    URI MyApp
    VERSION 1.0
    QML_FILES main.qml
)

add_subdirectory(object_types)

set_target_properties(appMyApp PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appMyApp
    PRIVATE Qt6::Qml Qt6::Quick
    ObjectTypesLibplugin
)

install(TARGETS appMyApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
