#ifndef CALCULATIONBASE_H
#define CALCULATIONBASE_H

#include <QObject>
#include "../../datatypes.h"

class CalculationBase : public QObject
{
    Q_OBJECT
public:
    explicit CalculationBase(Column& column, std::shared_ptr<Section> section, QObject *parent = nullptr) : QObject(parent) {}
    virtual ~CalculationBase() {};

    virtual std::vector<std::shared_ptr<CalculationResults>> fetchResults() { return results; }
    virtual std::vector<std::vector<std::pair<int, QString>>> fetchMessages() { return messages; }

protected:
    virtual void nullData() = 0;
    virtual void newInitData() = 0;
    virtual bool checkInitData() = 0;

    std::vector <std::shared_ptr<CalculationResults>> results;
    std::vector <std::vector <std::pair<int, QString>>> messages;
    std::vector <std::pair <int, QString>> message;

    QString weirName;

    virtual void handleError (const QString& errorMessage, int errorLevel)
    {
        message.push_back({errorLevel, weirName + " - " + errorMessage});
    }
};

#endif // CALCULATIONBASE_H
