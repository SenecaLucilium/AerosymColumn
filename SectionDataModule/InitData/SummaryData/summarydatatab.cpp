#include "summarydatatab.h"

SummaryDataTab::SummaryDataTab(QWidget *parent)
    : QWidget{parent}
{
    mainVLayout = new QVBoxLayout();
    setLayout(mainVLayout);
}

SummaryDataTab::~SummaryDataTab() {}

void SummaryDataTab::updateInformation(Column& column, int sectionIndex)
{
    QLayoutItem* item;
    while ((item = mainVLayout->takeAt(0))) {
        if (item->widget()) delete item->widget();
        delete item;
    }

    if (auto sieveSection = std::dynamic_pointer_cast<SieveSection>(column.sections[sectionIndex])) {
        SieveSummary* sieveSummary = new SieveSummary(this);
        mainVLayout->addWidget(sieveSummary);
        sieveSummary->updateInformation(column, sectionIndex);
    }
}
