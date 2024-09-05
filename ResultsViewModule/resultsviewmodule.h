#ifndef RESULTSVIEWMODULE_H
#define RESULTSVIEWMODULE_H

#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLabel>
#include <QComboBox>

#include <jkqtplotter/jkqtplotter.h>
#include <jkqtplotter/graphs/jkqtpscatter.h>
#include <jkqtplotter/graphs/jkqtplines.h>

#include <QDebug>
#include <limits>

#include "../datatypes.h"

class ResultsViewModule : public QWidget
{
    Q_OBJECT
public:
    explicit ResultsViewModule(std::vector <CalculationResults>& _results, QWidget *parent = nullptr);
    ~ResultsViewModule();

private slots:
    void onStageChanged();
    void onParamChanged();

private:
    std::vector <CalculationResults> results;

    QWidget* mainWidget;
    QVBoxLayout* mainVLayout;

    QWidget* chooseContainer;
    QHBoxLayout* chooseHLayout;
    QLabel* mainLabel;
    QComboBox* mainComboBox;
    QLabel* paramsLabel;
    QComboBox* paramsComboBox;

    JKQTPlotter* plotter;
};

#endif // RESULTSVIEWMODULE_H
