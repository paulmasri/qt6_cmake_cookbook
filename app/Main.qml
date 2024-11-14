import QtQuick
import CountableModels
import ObjectTypes

Window { id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Person { id: kate
        name: "Bob"
        age: 27
    }

    Animal {
        id: panther
        species: "panther"
        name: "Jerry"
        age: 2
    }

    CountableToDoModel { id: toDoListModel
    }
}
