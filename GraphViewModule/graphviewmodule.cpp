#include "graphviewmodule.h"

GraphViewModule::GraphViewModule(std::vector <CalculationResults>& _results, ColumnData& _column, QWidget *parent)
    : QWidget{parent}, results{_results}, column{_column}
{
    this->setWindowTitle("Гидравлические диаграммы");

    int widgetWidth = 1440;
    int widgetHeight = 900;
    this->setFixedSize(widgetWidth, widgetHeight);

    qDebug() << this->size();

    mainWidget = new QWidget(this);

    diagram = new GraphSectionDiagram(mainWidget);
    plotter = new JKQTPlotter(mainWidget);
    connect (diagram, &GraphSectionDiagram::weirChanged, this, &GraphViewModule::onWeirChanged);

    mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(diagram, 2);
    mainLayout->addWidget(plotter, 10);

    diagram->addInformation(results);
}

void GraphViewModule::onWeirChanged(int weirIndex)
{

}

GraphViewModule::~GraphViewModule() {}
