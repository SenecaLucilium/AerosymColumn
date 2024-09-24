#ifndef CALCULATIONMODULE_H
#define CALCULATIONMODULE_H

#include <QObject>
#include "../datatypes.h"

class CalculationModule : public QObject
{
    Q_OBJECT
public:
    explicit CalculationModule(QObject *parent = nullptr);
    ~CalculationModule();

    void performCalculations(Column& column);
};

#endif // CALCULATIONMODULE_H
