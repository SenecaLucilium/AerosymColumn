#ifndef SECTIONDATAMODULE_H
#define SECTIONDATAMODULE_H

#include <QDialog>

#include <QTabWidget>

#include "../datatypes.h"
#include "InitData/initialdatatab.h"
#include "Results/resultstab.h"
#include "Messages/messagestab.h"

class SectionDataModule : public QDialog
{
    Q_OBJECT
public:
    explicit SectionDataModule(Column& column, int sectionIndex, QWidget *parent = nullptr)
        : QDialog(parent)
    {
        int widgetWidth = 1400;
        int widgetHeight = 900;

        this->setWindowTitle(QString("Данные о секции %1").arg(column.sections[sectionIndex]->name));
        this->setFixedSize(widgetWidth, widgetHeight);

        tabWidget = new QTabWidget(this);
        tabWidget->setGeometry(0, 0, widgetWidth, widgetHeight);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);

        initialDataTab = new InitialDataTab(column, sectionIndex, tabWidget);
        resultsTab = new ResultsTab(tabWidget);
        messagesTab = new MessagesTab(tabWidget);

        tabWidget->addTab (initialDataTab, "Исходные данные");
        tabWidget->addTab (resultsTab, "Результаты");
        tabWidget->addTab (messagesTab, "Сообщения");
    }

    ~SectionDataModule() {}

    void receiveResults(std::vector<std::shared_ptr<CalculationResults>>& results) {resultsTab->updateInformation(results);}
    void receiveMessages(std::vector<std::vector<std::pair<int, QString>>>& messages) {messagesTab->updateInformation(messages);}

private:
    InitialDataTab* initialDataTab;
    ResultsTab* resultsTab;
    MessagesTab* messagesTab;

    QTabWidget* tabWidget;
};

#endif // SECTIONDATAMODULE_H
