#ifndef GRAPHVIEWMODULE_H
#define GRAPHVIEWMODULE_H

#include <QWidget>

#include <QHBoxLayout>
#include <QDebug>

#include "jkqtplotter/jkqtplotter.h"
#include "jkqtplotter/graphs/jkqtpscatter.h"
#include "jkqtplotter/graphs/jkqtplines.h"

#include "../datatypes.h"
#include "graphsectiondiagram.h"

class GraphViewModule : public QWidget
{
    Q_OBJECT
public:
    explicit GraphViewModule(std::vector <CalculationResults>& _results, ColumnData& _column, QWidget *parent = nullptr);
    ~GraphViewModule();

private slots:
    void onWeirChanged(int weirIndex);

private:
    std::vector <CalculationResults> results;
    ColumnData column;

    QWidget* mainWidget;
    QHBoxLayout* mainLayout;

    GraphSectionDiagram* diagram;
    JKQTPlotter* plotter;
};

#endif // GRAPHVIEWMODULE_H
