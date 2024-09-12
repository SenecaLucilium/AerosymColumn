#ifndef RESULTSTAB_H
#define RESULTSTAB_H

#include <QWidget>
#include <QVBoxLayout>

#include "WeirTypes/sieveresults.h"
#include "../../datatypes.h"

class ResultsTab : public QWidget
{
    Q_OBJECT
public:
    explicit ResultsTab(QWidget *parent = nullptr) {
        mainVLayout = new QVBoxLayout();
        setLayout(mainVLayout);
    }
    ~ResultsTab() {}

    void updateInformation(std::vector<std::shared_ptr<CalculationResults>>& results) {
        QLayoutItem* item;
        while ((item = mainVLayout->takeAt(0))) {
            if (item->widget()) delete item->widget();
            delete item;
        }

        // if (auto sieveResult = std::dynamic_pointer_cast<SieveCalculationResults>(results)) {
        //     SieveSummary* sieveSummary = new SieveSummary(this);
        //     mainVLayout->addWidget(sieveSummary);
        //     sieveSummary->updateInformation(column, sectionIndex);
        // }
    }
private:
    QVBoxLayout* mainVLayout;
};

#endif // RESULTSTAB_H
