qt_add_library(ObjectTypesLib STATIC)

list(APPEND MODULE_SOURCE_FILES
    Person.h Person.cpp
)
list(APPEND MODULE_QML_FILES
    Animal.qml
)

qt_add_qml_module(ObjectTypesLib
    URI ObjectTypes
    VERSION 1.0
    SOURCES ${MODULE_SOURCE_FILES}
    QML_FILES ${MODULE_QML_FILES}
)

target_link_libraries(ObjectTypesLib PRIVATE Qt6::Qml Qt6::Quick)
