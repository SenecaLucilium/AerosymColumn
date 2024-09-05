#ifndef SUMMARYDATATAB_H
#define SUMMARYDATATAB_H

#include <QWidget>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QLabel>
#include <QTableWidget>

#include "WeirTypes/sievesummary.h"
#include "../../../datatypes.h"

class SummaryDataTab : public QWidget
{
    Q_OBJECT
public:
    explicit SummaryDataTab(QWidget *parent = nullptr);
    ~SummaryDataTab();
    void updateInformation(Column& column, int sectionIndex);
private:
    // static void addWeirDataToTable(QTableWidget* table, int columnIndex, int rowIndex, double value);
    // static void setCellInfo(QTableWidgetItem* item, bool errorFlag, QString errorMessage = "");
    QVBoxLayout* mainVLayout;
};

#endif // SUMMARYDATATAB_H
