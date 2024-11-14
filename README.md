# qt6_cmake_cookbook

A cookbook and instruction manual for writing CMake for Qt6 for cross-platform apps.

My own production app is a Qt Quick app, so my architecture matches this use case.

## Start with the root-level CMake file

The root level CMake file `CMakeLists.txt`
- sets up the project,
- adds in code modules as 'libraries',
- adds in the app itself, as an executable target that is also a QML module,
- adds in test modules that may make use of the libraries.

### Project setup

Qt provides a number of [its own CMake commands](https://doc.qt.io/qt-6/cmake-command-reference.html). These have evolved and changed considerably since Qt 6.2 and the versions supported here are based on Qt 6.5. This repo has been tested against Qt 6.8.0.

I use [`qt_standard_project_setup`](https://doc.qt.io/qt-6/qt-standard-project-setup.html) provided in `Qt6::Core` to set up the project, which avoids the need to manually ensure auto-moc or auto-rcc, for example.

### Adding libraries/modules

Each library, module, and even the executable target, sits in its own subdirectory in the filespace, has its own CMake file, and is added with the command `add_subdirectory`. By structuring it this way, the libraries can be made available to both the app and the tests.

Although a flatter structure would technically be possible, you would still need a separate library for each QML module, because of how Qt creates them. More on that below.

## How to create a library

See `CommonHeaders/CMakeLists.txt`, which creates a C++ library that does not have a QML counterpart. These are the simplest libraries and contain all the elements needed for all libraries.

1. We use [`qt_add_library`](https://doc.qt.io/qt-6/qt-add-library.html) to define the library and specify its source files (which can include header files, e.g. `.h`, as well as source files, e.g. `.cpp`).

   By convention, the name of the library is the name of the directory with `Lib` appended. e.g. `CommonHeadersLib` for the library in the `CommonHeaders` directory.

2. Source files in this directory need to be able to `#include` one another without any path, so we have `target_include_directories` for this directory. (`${CMAKE_CURRENT_SOURCE_DIR}` is the path of the directory of this CMake file.)

3. Any libraries that are `#include`d by the source files are linked using `target_link_libraries`. In the `CommonHeaders` example, we don't reference any of our other libraries, just Qt's Core module.

### PUBLIC vs PRIVATE linking

In the previous example, `target_link_libraries` only used the `PUBLIC` keyword. In general you will use `PRIVATE` and `PUBLIC` and their usage is important.

Any libraries following the `PRIVATE` keyword are only available to this library whereas any libraries following the `PUBLIC` keyword become available to a library that links to this one.

A simple rule of thumb is:

- **`Use PRIVATE`**, where you `#include` a library's header in source file(s) and **not in any of the header files**.
- **`Use PUBLIC`**, for any other libraries you `#include`.

So in the case of `ToDoListModel/CMakeLists.txt`,
- `CommonHeadersLib` is privately linked because `MyCommonHeaders.h` is included in the `.cpp` file and not the `.h` file, and so any libraries that use `ToDoModel` do not need to know about this link.
- `Qt Quick` is publicly linked because the header file has `#include <QAbstractListModel>` and any library using this one will need to understand the `QAbstractListModel` class.
- `ToDoObjects` is publicly linked because the header file has `#include "ToDoObjects.h"` and `ToDoList` is the return type of `list()`, so any library that uses this one will also need to understand `ToDoList`.

## How to create a QML module library

A QML module is a special kind of library. Since Qt 6.2, Qt has made it easy to create a QML module using `qt_add_qml_module`.

If you're migrating from Qmake or you've been used to creating QML modules before Qt 6.2, you'll be familiar with having to register each module in your `main.cpp` and ensuring you've created a `qmldir`. Fortunately `qt_add_qml_module` does all of this for you. But it doesn't come without its own idiosyncracies.

Let's consider a C++ class that extends QML. See `ToDoListModel/CMakeLists.txt`.

1. We use `qt_add_library` to define the library, but we do not specify any source files here.
2. We use `qt_add_qml_module` to generate a QML module associated with the library, and this is where we specify the source files.
   1. We need to set a `URI`, in this case `ToDoListModel`. After building, this will enable you to use `import ToDoListModel` in your QML files.
   2. As of Qt 6.5, it is necessary to specify `RESOURCE_PREFIX`. My personal choice is to set it to `/`. If you were to set it to `RESOURCE_PREFIX /my/custom/path` then you'd have to use `import my/custom/path/ToDoListModel` in QML.
   3. Set the `VERSION`. By default I always set this to `1.0`. Note that as of Qt 6 (6.2?), [QML `import` statements no longer need to specify the version](https://doc.qt.io/qt-6/qtqml-syntax-imports.html), to use the latest version, so I see this as boilerplate code.
3. Now look at the C++. To make an item available to QML engine, you also need to declare it using one of the [QQmlEngine macros](https://doc.qt.io/qt-6/qqmlengine.html#macros) in your C++.
   1. `#include <QtQml>` to make those macros available.
   2. The most common macro is `QML_ELEMENT` which you apply to a `QObject` derived class, alongside `Q_OBJECT`. By doing this, its properties and `Q_INVOKABLE` functions become available in QML. See `ToDoListModel/ToDoListModel.h`.
4. Finally, when we link the main app target to this library (see `app/CMakeLists.txt`), because we want it to have the QML module, not a C++ library, within `target_link_libraries` we link to `ToDoListModelLibplugin` instead of linking to `ToDoListModelLib`. This gets generated for us by `qt_add_qml_module`. Note that the suffix is `plugin`, all lowercase.

See `ObjectTypes/CMakeLists.txt` for a more complex example of a QML module that contains a QML file as well as a C++ class.
