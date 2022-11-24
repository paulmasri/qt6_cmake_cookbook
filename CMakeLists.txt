cmake_minimum_required(VERSION 3.21)

project(MyApp VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(app)

include(CTest)
add_subdirectory(tests)
enable_testing()

# Other files: for inclusion (easy access in Qt Creator) but not for compiling
add_custom_target(non-compiled-files SOURCES
    README.md
)
