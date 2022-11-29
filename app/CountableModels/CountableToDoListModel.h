#pragma once

#include "ToDoListModel.h"

#include <QtQml>
#include "IMyInterface.h"
#include "ToDoObjects.h"

class CountableToDoModel : public ToDoModel, public IMyInterface
{
    Q_OBJECT
    QML_ELEMENT
    Q_INTERFACES(IMyInterface)
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    explicit CountableToDoModel(QObject *parent = nullptr);

    int count() const;

    void setList(ToDoList *list) override;

signals:
    void countChanged() override; // implements IMyInterface

private:
    void makeConnections() override;

    int mCount;
};
