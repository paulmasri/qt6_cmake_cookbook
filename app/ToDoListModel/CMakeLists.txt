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

target_link_libraries(ToDoListModelLib
    PRIVATE Qt6::Quick
    ToDoObjectsLib
)
