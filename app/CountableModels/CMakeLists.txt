qt_add_library(CountableModelsLib STATIC)

list(APPEND MODULE_SOURCE_FILES
    CountableToDoListModel.h CountableToDoListModel.cpp
)

qt_add_qml_module(CountableModelsLib
    URI CountableModels
    VERSION 1.0
    SOURCES
    ${MODULE_SOURCE_FILES}
)

target_include_directories(CountableModelsLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(CountableModelsLib
    PRIVATE Qt6::Quick Qt6::Qml
    CommonHeadersLib
    ToDoListModelLib
)
