qt_add_library(ToDoListModelLib STATIC)

list(APPEND MODULE_SOURCE_FILES
    ToDoListModel.h ToDoListModel.cpp
)

qt_add_qml_module(ToDoListModelLib
    URI ToDoListModel
    VERSION 1.0
    SOURCES
    ${MODULE_SOURCE_FILES}
)

target_include_directories(ToDoListModelLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ToDoListModelLib
    PRIVATE Qt6::Quick
    PUBLIC ToDoObjectsLib
)
