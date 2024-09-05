#include "initialdatatab.h"

InitialDataTab::InitialDataTab(Column& column, int sectionIndex, QWidget *parent)
    : QWidget{parent}
{
    verticalTabWidget = new QTabWidget(this);
    verticalTabWidget->setTabPosition(QTabWidget::West);
    verticalTabWidget->setTabShape(QTabWidget::Rounded);
    verticalTabWidget->tabBar()->setStyle(new CustomTabStyle);

    geometryDataTab = new GeometryDataTab(column, sectionIndex, verticalTabWidget);
    paramsDataTab = new ParamsDataTab(column, verticalTabWidget);
    summaryDataTab = new SummaryDataTab(verticalTabWidget);

    connect(verticalTabWidget, &QTabWidget::currentChanged, this, [this, &column, sectionIndex]() {
        if (verticalTabWidget->currentIndex() == 2) summaryDataTab->updateInformation(column, sectionIndex);
    });
    // connect(verticalTabWidget, &QTabWidget::currentChanged, this, [&column, &section, this]() {
    //     if (verticalTabWidget->currentIndex() == 2) summaryDataTab->updateInformation(column, section);
    // });

    verticalTabWidget->addTab(geometryDataTab, "Геометрия");
    verticalTabWidget->addTab(paramsDataTab, "Доп. Параметры");
    verticalTabWidget->addTab(summaryDataTab, "Сводка данных");
}

InitialDataTab::~InitialDataTab() {}
