#pragma once

#include <QAbstractListModel>

#include "ToDoObjects.h"
//Q_MOC_INCLUDE("todolist.h")

class ToDoModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ToDoList *list READ list WRITE setList)

public:
    explicit ToDoModel(QObject *parent = nullptr);

    enum {
        DoneRole = Qt::UserRole,
        DescriptionRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    ToDoList *list() const;
    void setList(ToDoList *list);

private:
    ToDoList *mList;
};
