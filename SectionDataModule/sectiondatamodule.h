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
    explicit SectionDataModule(Column& column, int sectionIndex, QWidget *parent = nullptr);
    ~SectionDataModule();

    // void receiveResults(std::vector<CalculationResults>& results);
    // void receiveMessages(std::vector<std::vector<std::pair<int, QString>>>& messages);

private:
    InitialDataTab* initialDataTab;
    ResultsTab* resultsTab;
    MessagesTab* messagesTab;

    QTabWidget* tabWidget;
};

#endif // SECTIONDATAMODULE_H
