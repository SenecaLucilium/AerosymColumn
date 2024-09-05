#include "sectiondatamodule.h"

SectionDataModule::SectionDataModule(Column& column, int sectionIndex, QWidget *parent)
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

// void SectionDataModule::receiveResults(std::vector<CalculationResults>& results)
// {
//     // resultsTab->updateInformation(results);
// }

// void SectionDataModule::receiveMessages(std::vector<std::vector<std::pair<int, QString>>>& messages)
// {
//     // messagesTab->updateInformation(messages);
// }

SectionDataModule::~SectionDataModule() {}
