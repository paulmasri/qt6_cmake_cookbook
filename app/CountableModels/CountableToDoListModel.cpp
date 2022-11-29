#include "CountableToDoListModel.h"

CountableToDoModel::CountableToDoModel(QObject *parent)
    : ToDoModel(parent)
{
}

int CountableToDoModel::count() const
{
    return mCount;
}

void CountableToDoModel::setList(ToDoList *list)
{
    ToDoModel::setList(list);

    mCount = list->items().size();
    emit countChanged();
}

void CountableToDoModel::makeConnections()
{
    if (mList) {
        connect(mList, &ToDoList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &ToDoList::postItemAppended, this, [=]() {
            endInsertRows();
            ++mCount;
            emit countChanged();
        });

        connect(mList, &ToDoList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &ToDoList::postItemRemoved, this, [=]() {
            endRemoveRows();
            --mCount;
            emit countChanged();
        });
    }
}
