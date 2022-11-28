# qt6_cmake_subdirectories

A test project combining CMake for Qt6 with subdirectories

## Subdirectories

### Purpose
Use a subdirectory to create a _library_. Within this subdirectory, you can include various files (source, QML & JS, resources) and compile them as a self-contained unit.

The subdirectory has its own CMakeLists.txt file that defines the library, what it contains and what it links against.

This library can then be linked against by other targets that need to use its classes or components. In QML it is imported using its URI.

### Implementation
1. Create a subdirectory; e.g. NewDirectory
1. In the parent directory CMakeLists.txt
	```
	add_subdirectory(NewDirectory)
	```
1. Add a CMakeLists.txt in the subdirectory that contains the following calls
	```
	qt_add_library(LibraryName [STATIC|SHARED])

	qt_add_qml_module(LibraryName
		URI LibraryURI
		VERSION 1.0
		SOURCES ...
		QML_FILES ...
		RESOURCES ...
	)

	target_link_libraries(ObjectTypesLib PRIVATE [e.g. Qt6::Qml Qt6::Quick])
	```

## Static vs Shared libraries

A static library is compiled into the executable, so it gets bundled as part of that file. A shared library is compiled as a standalone library that can be dynamically loaded (.dll for Windows, .dylib for MacOS).

If in doubt, go for a static library.

### Creating and linking a static library

1. Within the subdirectory CMakeLists.txt, set the library to be static
	```
	qt_add_library(LibraryName STATIC)
	```
1. Within the parent CMakeLists.txt, link to the _plugin for the library_ that qt_add_qml_module() creates. This always has the same name as the library with `plugin` appended.
	```
	target_link_libraries(appMyApp
		PRIVATE [e.g. Qt6::Qml Qt6::Quick]
		LibraryNameplugin
	)
	```

### Creating and linking a shared library

1. Within the subdirectory CMakeLists.txt, set the library to be shared
	```
	qt_add_library(LibraryName SHARED)
	```
1. Within the parent CMakeLists.txt, link to the library itself
	```
	target_link_libraries(appMyApp
		PRIVATE [e.g. Qt6::Qml Qt6::Quick]
		LibraryName
	)
	```

## C++ classes that extend QML

### Purpose

Where a C++ class derives from `QObject` and contains `QML_ELEMENT` (as well as `Q_OBJECT` of course), it extends QML and can be instantiated as a QML component.

### Implementation

1. Place the class source files in the subdirectory and list them as `SOURCES` in the library CMake file.
1. In QML
	```
	import QtQuick
	import LibraryURI

	...
	ClassDefinedInLibrary {
		...
	}
	```

## QML components

### Purpose

It may also be useful to have QML files in a library. Perhaps it makes logical sense to group certain components in their own module. Perhaps they relate to C++ classes in the library. Or perhaps they use other QML files that should remain private to the library. (See the Widgets library [in the example by Lukas Kosiński of Scythe Studio](https://github.com/scytheStudio/qt_add_qml_module_example).)

### Implementation

There are a few tricky things to get right for this to work.
1. The subdirectory must have the same name as the library for qmllint to work. i.e. put the `LibraryName` library in the `LibraryName` subdirectory.
1. The import path must match. There are two options:
	1. You can define a custom path
		- Within every CMakeLists.txt that contains QML use the same `RESOURCE_PREFIX`
			```
			qt_add_qml_module(
				...
				RESOURCE_PREFIX /my/custom/imports
				...
			)
			```
		- In main.cpp, add the import path and specify main.qml within that path too
			```
			QQmlApplicationEngine engine;

			engine.addImportPath("qrc:/my/custom/imports");

			const QUrl url(u"qrc:/my/custom/imports/MyApp/main.qml"_qs);

			QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
							&app, [url](QObject *obj, const QUrl &objUrl) {
				if (!obj && url == objUrl)
					QCoreApplication::exit(-1);
			}, Qt::QueuedConnection);
			engine.load(url);

			```
	2. You can define an empty import path in main.cpp and skip using `RESOURCE_PREFIX` in any CMake file.
		```
		QQmlApplicationEngine engine;

		engine.addImportPath("qrc:/");

		const QUrl url(u"qrc:/MyApp/main.qml"_qs);

		QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
						&app, [url](QObject *obj, const QUrl &objUrl) {
			if (!obj && url == objUrl)
				QCoreApplication::exit(-1);
		}, Qt::QueuedConnection);
		engine.load(url);

		```
1. Within the library CMakeLists.txt you need to include the following
	```
	set_target_properties(LibraryName PROPERTIES AUTOMOC ON)
	```
    _(I'm unclear whether this is needed if the root CMakeLists.txt has `set(CMAKE_AUTOMOC ON)`)_
