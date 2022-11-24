cmake_minimum_required(VERSION 3.16)

project(tests VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 6.2 COMPONENTS Core Test REQUIRED)

set(APP_DIRECTORY ${CMAKE_SOURCE_DIR}/app)
include_directories(${APP_DIRECTORY})
