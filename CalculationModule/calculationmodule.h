#ifndef CALCULATIONMODULE_H
#define CALCULATIONMODULE_H

#include <QObject>
#include "../datatypes.h"

#include "WeirTypes/sievecalculation.h"

class CalculationModule : public QObject
{
    Q_OBJECT
public:
    explicit CalculationModule(QObject *parent = nullptr) {};
    ~CalculationModule() {};

    std::pair<std::vector<std::shared_ptr<CalculationResults>>, std::vector<std::vector<std::pair<int, QString>>>> performCalculations(Column& column)
    {
        std::vector<std::shared_ptr<CalculationResults>> results;
        std::vector<std::vector<std::pair<int, QString>>> messages;

        for (const auto& section : column.sections)
        {
            CalculationBase* calcModule;

            if (auto sieveSection = std::dynamic_pointer_cast<SieveSection>(section)) {
                calcModule = new SieveCalculations();
                calcModule->performCalculations(column, sieveSection);
            }

            std::vector<std::shared_ptr<CalculationResults>> newResults = calcModule->fetchResults();
            std::vector<std::vector<std::pair<int, QString>>> newMessages = calcModule->fetchMessages();

            results.insert(results.end(), newResults.begin(), newResults.end());
            messages.insert(messages.end(), newMessages.begin(), newMessages.end());
        }

        return std::make_pair(results, messages);
    }
};

#endif // CALCULATIONMODULE_H
