#ifndef RESULTSTAB_H
#define RESULTSTAB_H

#include <QWidget>
#include <QDialog>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>

#include <QLabel>
#include <QTableWidget>
#include <QPushButton>

#include "../../datatypes.h"

class AdditionalResultsWidget : public QDialog
{
    Q_OBJECT
public:
    explicit AdditionalResultsWidget(QWidget *parent = nullptr);
    ~AdditionalResultsWidget();

    void updateInformation(CalculationResults results);

private:
    static void updateCell(QTableWidget* table, int row, int col, QString newValue);
    static void setupTable(QTableWidget* table, QStringList headerLabels, QStringList rowNames);

    QHBoxLayout* mainHLayout;

    QWidget* firstContainer;
    QVBoxLayout* firstVLayout;
    QLabel* columnDiameterLabel;
    QTableWidget* columnDiameterTable;

    QWidget* secondContainer;
    QVBoxLayout* secondVLayout;
    QLabel* columnSectionLabel;
    QTableWidget* columnSectionTable;

    QWidget* thirdContainer;
    QVBoxLayout* thirdVLayout;
    QLabel* weirHydrResistLabel;
    QLabel* overflowDeviceLabel;
    QTableWidget* weirHydrResistTable;
    QTableWidget* overflowDeviceTable;
};

class ResultsTab : public QWidget
{
    Q_OBJECT
public:
    explicit ResultsTab(QWidget *parent = nullptr);
    ~ResultsTab();

    void updateInformation(std::vector<CalculationResults>& results);
private:
    static void setupTable(QTableWidget* table, QStringList headerLabels, QStringList rowNames);

    QVBoxLayout* mainVLayout;

    QWidget* mainResultsContainer;
    QVBoxLayout* mainResultsVLayout;
    QLabel* mainResultsLabel;
    QTableWidget* mainResultsTable;

    QWidget* verificationResultsContainer;
    QVBoxLayout* verificationResultsVLayout;
    QLabel* verificationResultsLabel;
    QTableWidget* verificationResultsTable;
};

#endif // RESULTSTAB_H
