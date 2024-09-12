#ifndef SIEVERESULTS_H
#define SIEVERESULTS_H

#include <QWidget>
#include <QDialog>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>

#include <QLabel>
#include <QTableWidget>
#include <QPushButton>

#include "../../../datatypes.h"

class AdditionalSieveResultsWidget : public QDialog
{
    Q_OBJECT
public:
    explicit AdditionalSieveResultsWidget(QWidget *parent = nullptr);
    ~AdditionalSieveResultsWidget();

    void updateInformation(std::shared_ptr<SieveCalculationResults> results);
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

class SieveResults : public QWidget
{
    Q_OBJECT
public:
    explicit SieveResults(QWidget *parent = nullptr);
    ~SieveResults();

    void updateInformation(std::vector<std::shared_ptr<SieveCalculationResults>>& results);
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

#endif // SIEVERESULTS_H
