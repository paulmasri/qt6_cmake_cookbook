#pragma once

#include <QObject>
#include <QtQml>
#include <QString>

class Person : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)

public:
    explicit Person(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &newName);

    int age() const;
    void setAge(int newAge);

signals:
    void nameChanged();
    void ageChanged();

private:
    QString _name;
    int _age;
};
