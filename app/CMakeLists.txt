set(APP_TARGET MyApp)
set(APP_NAME "My app")

find_package(Qt6 6.5 REQUIRED COMPONENTS Qml Quick)

qt_add_executable(${APP_TARGET} main.cpp)

qt_add_qml_module(${APP_TARGET}
    URI Primary
    RESOURCE_PREFIX /
    VERSION 1.0
    QML_FILES
        Main.qml
)

set_target_properties(${APP_TARGET} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(${APP_TARGET}
    PRIVATE $<$<CONFIG:Debug>:QT_QML_DEBUG>)

target_link_libraries(${APP_TARGET}
    PRIVATE Qt6::Qml Qt6::Quick

    CountableModelsLibplugin
    ObjectTypesLibplugin
)

install(TARGETS ${APP_TARGET}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)
