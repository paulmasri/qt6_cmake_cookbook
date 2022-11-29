list(APPEND MODULE_SOURCE_FILES
    MyCommonHeaders.h
    IMyInterface.h
)

qt_add_library(CommonHeadersLib STATIC ${MODULE_SOURCE_FILES})

target_include_directories(CommonHeadersLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(CommonHeadersLib PRIVATE Qt6::Core)
