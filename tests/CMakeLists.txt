project(tests VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Test)

set(APP_DIRECTORY ${CMAKE_SOURCE_DIR}/app)
include_directories(${APP_DIRECTORY})
