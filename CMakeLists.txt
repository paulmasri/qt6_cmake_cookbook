cmake_minimum_required(VERSION 3.25)

project(MyApp VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

# Assets/resources
# add_subdirectory(AppAssets)

# C++ (only) libraries
add_subdirectory(CommonHeaders)

find_package(Qt6 6.5 REQUIRED COMPONENTS Qml)

# add_subdirectory(FolderTypes)

# C++/QML module libraries
find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

add_subdirectory(ToDoObjects)
add_subdirectory(ToDoListModel)
add_subdirectory(CountableModels)
add_subdirectory(ObjectTypes)

# The app
add_subdirectory(app)

# Tests
include(CTest)
enable_testing()
add_subdirectory(tests)

# Other files: for inclusion (easy access in Qt Creator) but not for compiling
add_custom_target(non-compiled-files SOURCES
    .gitignore
    README.md
)
