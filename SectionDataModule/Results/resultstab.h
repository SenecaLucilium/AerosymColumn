#ifndef RESULTSTAB_H
#define RESULTSTAB_H

#include <QWidget>
#include <QLabel>
#include <QFont>
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

        noDataLabel = new QLabel("Расчёт еще не произведен", this);
        noDataLabel->setAlignment(Qt::AlignCenter);

        QFont font = noDataLabel->font();
        font.setPointSize(16);
        font.setBold(true);
        noDataLabel->setFont(font);

        mainVLayout->addWidget(noDataLabel);
    }
    ~ResultsTab() {}

    void updateInformation(std::vector<std::shared_ptr<CalculationResults>>& results) {
        QLayoutItem* item;
        while ((item = mainVLayout->takeAt(0))) {
            if (item->widget()) delete item->widget();
            delete item;
        }

        if (auto sieveResult = std::dynamic_pointer_cast<SieveCalculationResults>(results[0]))
        {
            SieveResults* sieveWidget = new SieveResults(this);
            mainVLayout->addWidget(sieveWidget);
            sieveWidget->updateInformation(results);
        }
    }
private:
    QVBoxLayout* mainVLayout;
    QLabel* noDataLabel;
};

#endif // RESULTSTAB_H
