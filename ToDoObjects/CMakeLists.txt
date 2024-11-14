list(APPEND MODULE_SOURCE_FILES
    ToDoObjects.h ToDoObjects.cpp
)

qt_add_library(ToDoObjectsLib STATIC)

qt_add_qml_module(ToDoObjectsLib
    URI ToDoObjects
    RESOURCE_PREFIX /
    VERSION 1.0
    SOURCES ${MODULE_SOURCE_FILES}
)

target_include_directories(ToDoObjectsLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ToDoObjectsLib
    PUBLIC Qt6::Quick
)
