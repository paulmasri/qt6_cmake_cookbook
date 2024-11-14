#pragma once

#include <QObject>

class IMyInterface
{
public:
    virtual ~IMyInterface() {}

signals:
    virtual void countChanged() = 0;
};

Q_DECLARE_INTERFACE(IMyInterface, "special_IMyInterface")
