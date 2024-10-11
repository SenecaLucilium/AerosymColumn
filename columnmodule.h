#ifndef COLUMNMODULE_H
#define COLUMNMODULE_H

#include <QMainWindow>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>

#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

#include "sectionscheme.h"
#include "datatypes.h"
#include "CalculationModule/calculationmodule.h"
// #include "ResultsViewModule/resultsviewmodule.h"
// #include "GraphViewModule/graphviewmodule.h"

class ColumnModule : public QMainWindow
{
    Q_OBJECT

public:
    ColumnModule(Column& initialData, QWidget *parent = nullptr);
    ~ColumnModule();

private slots:
    void onTableChanged(int row, int col);
    void onCalculationButtonClicked();

private:
    Column& column;
    QStringList weirNamesList;
    std::vector<std::shared_ptr<Weir>> weirsList;
    std::vector<std::shared_ptr<CalculationResults>> results;
    std::vector<std::vector<std::pair<int, QString>>> messages;

    CalculationModule* calcModule;

    bool ignoreSignals;
    bool activeError;
    bool sectionsError;

    void addNewRow(Section& newSection);
    void addEmptyRow();
    void setupColumn();
    void rearrangeWeirs();
    bool checkSections();
    void setStatusLabel(bool errorFlag, QString message);

    //Дебаг функций
    void printFullColumn();

    QWidget* mainWidget;
    QVBoxLayout* mainLayout;

    QWidget* sectionsContainer;
    QHBoxLayout* sectionsLayout;
    QWidget* tableContainer;
    QVBoxLayout* tableContainerLayout;
    QLineEdit* sectionsStatusLineEdit;
    QTableWidget* sectionsTable;
    SectionsDiagram* sectionsDiagram;

    QWidget* calculationContainer;
    QHBoxLayout* calculationLayout;
    QPushButton* calculationButton;
    QPushButton* resultsButton;
    QPushButton* eraseButton;
    QPushButton* graphButton;
    QLineEdit* statusLineEdit;
};

#endif // COLUMNMODULE_H
