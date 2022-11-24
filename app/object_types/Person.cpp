#include "Person.h"

Person::Person(QObject *parent)
    : QObject{parent}
{

}

QString Person::name() const
{
    return _name;
}

void Person::setName(const QString &newName)
{
    if (_name == newName)
        return;
    _name = newName;
    emit nameChanged();
}

int Person::age() const
{
    return _age;
}

void Person::setAge(int newAge)
{
    if (_age == newAge)
        return;
    _age = newAge;
    emit ageChanged();
}
