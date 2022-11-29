#pragma once

#include "ToDoListModel.h"

#include <QtQml>
#include "ToDoObjects.h"

class CountableToDoModel : public ToDoModel
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    explicit CountableToDoModel(QObject *parent = nullptr);

    int count() const;

    void setList(ToDoList *list) override;

signals:
    void countChanged();

private:
    void makeConnections() override;

    int mCount;
};
