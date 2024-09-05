#include "columnmodule.h"

ColumnModule::ColumnModule(Column& initialData, QWidget *parent)
    : QMainWindow(parent), column(initialData)
{
    this->setWindowTitle("Модуль Колонны");

    int widgetWidth = 1280;
    int widgetHeight = 720;
    this->setFixedSize(widgetWidth, widgetHeight);

    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    sectionsContainer = new QWidget(mainWidget);
    {
        tableContainer = new QWidget(sectionsContainer);
        {
            sectionsStatusLineEdit = new QLineEdit("", tableContainer);
            sectionsStatusLineEdit->setReadOnly(true);
            sectionsStatusLineEdit->setAlignment(Qt::AlignCenter);
            sectionsStatusLineEdit->setMaximumWidth(400);
            sectionsStatusLineEdit->setStyleSheet("QLineEdit { background-color: red; color: black; }");

            sectionsTable = new QTableWidget(0, 11, tableContainer);
            {
                sectionsTable->setHorizontalHeaderLabels({"Секция", "Начальная", "Последняя", "Режим", "Тип Тарелки",
                                                          "Число потоков", "Коэффициент числа потоков", "Расстояние между тарелками (мм)",
                                                          "Диаметр отверстия (м)", "Подробности", "Удалить"});
                sectionsTable->resizeColumnsToContents();

                sectionsTable->setColumnWidth(0, 100);
                sectionsTable->setColumnWidth(1, 110);
                sectionsTable->setColumnWidth(2, 110);
                sectionsTable->setColumnWidth(3, 100);
                sectionsTable->setColumnWidth(5, 100);
                sectionsTable->setColumnWidth(6, 70);
                sectionsTable->setColumnWidth(7, 70);
                sectionsTable->setColumnWidth(8, 70);

                connect(sectionsTable, qOverload<int, int>(&QTableWidget::cellChanged), this, qOverload<int, int>(&ColumnModule::onTableChanged));
                ignoreSignals = true;
            }

            tableContainerLayout = new QVBoxLayout();
            QSpacerItem* sectionsSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum);

            tableContainerLayout->addWidget(sectionsStatusLineEdit);
            tableContainerLayout->addWidget(sectionsTable);
            tableContainerLayout->addItem(sectionsSpacer);

            tableContainer->setLayout(tableContainerLayout);
        }

        sectionsDiagram = new SectionsDiagram(sectionsContainer);

        sectionsLayout = new QHBoxLayout();

        sectionsLayout->addWidget(tableContainer, 8);
        sectionsLayout->addWidget(sectionsDiagram, 2);

        sectionsContainer->setLayout(sectionsLayout);
    }

    calculationContainer = new QWidget(mainWidget);
    {
        // calcModule = new CalculationModule();

        calculationButton = new QPushButton("Выполнить вычисления", calculationContainer);
        // connect(calculationButton, &QPushButton::clicked, this, &ColumnModule::onCalcButtonPushed);

        resultsButton = new QPushButton("Графические результаты", calculationContainer);
        resultsButton->setDisabled(true);
        // connect(resultsButton, &QPushButton::clicked, this, &ColumnModule::onResultsButtonPushed);

        eraseButton = new QPushButton("Сбросить результаты", calculationContainer);
        eraseButton->setDisabled(true);
        // connect(eraseButton, &QPushButton::clicked, this, &ColumnModule::onEraseButtonPushed);

        graphButton = new QPushButton("Просмотреть гидравлические диаграммы", calculationContainer);
        graphButton->setDisabled(true);
        // connect(graphButton, &QPushButton::clicked, this, &ColumnModule::onGraphButtonPushed);

        statusLineEdit = new QLineEdit("Расчёт не выполнен", calculationContainer);
        statusLineEdit->setReadOnly(true);
        statusLineEdit->setAlignment(Qt::AlignCenter);
        statusLineEdit->setStyleSheet("QLineEdit { background-color: yellow; color: black; }");

        calculationLayout = new QHBoxLayout();

        calculationLayout->addWidget(calculationButton);
        calculationLayout->addWidget(resultsButton);
        calculationLayout->addWidget(eraseButton);
        calculationLayout->addWidget(statusLineEdit);
        calculationLayout->addWidget(graphButton);

        calculationContainer->setLayout(calculationLayout);
    }

    mainLayout = new QVBoxLayout();

    mainLayout->addWidget(sectionsContainer, 9);
    mainLayout->addWidget(calculationContainer, 1);

    mainWidget->setLayout(mainLayout);

    addEmptyRow();
    for (auto& section : column.sections) {
        if (auto sieveSection = std::dynamic_pointer_cast<SieveSection>(section)) {
            for (auto& weir : sieveSection->weirs) {
                weirsList.push_back(weir);
                weirNamesList.push_back(weir->name);
            }
        }
    }
    for (auto& section : column.sections) addNewRow(*section);

    setupColumn();
    setStatusLabel(false, "Секции готовы к расчёту");
    activeError = false;
    sectionsError = false;
    ignoreSignals = false;
}

ColumnModule::~ColumnModule() {}

void ColumnModule::addNewRow(Section& newSection)
{
    ignoreSignals = true;

    int newRowIndex = sectionsTable->rowCount() - 1;
    sectionsTable->removeCellWidget(newRowIndex, 0);

    sectionsTable->setItem(newRowIndex, 0, new QTableWidgetItem(newSection.name));

    QComboBox* startComboBox = new QComboBox(sectionsTable);
    startComboBox->addItems(weirNamesList);
    sectionsTable->setCellWidget(newRowIndex, 1, startComboBox);
    connect(startComboBox, &QComboBox::currentIndexChanged, this, [this, newRowIndex](int){
        onTableChanged(newRowIndex, 1);
    });

    QComboBox* endComboBox = new QComboBox(sectionsTable);
    endComboBox->addItems(weirNamesList);
    sectionsTable->setCellWidget(newRowIndex, 2, endComboBox);
    connect(endComboBox, &QComboBox::currentIndexChanged, this, [this, newRowIndex](int){
        onTableChanged(newRowIndex, 2);
    });

    QComboBox* typeComboBox = new QComboBox(sectionsTable);
    typeComboBox->addItems({"Проектный", "Поверочный"});
    typeComboBox->setCurrentText(newSection.calcType);
    sectionsTable->setCellWidget(newRowIndex, 3, typeComboBox);
    connect(typeComboBox, &QComboBox::currentIndexChanged, this, [this, newRowIndex](int){
        onTableChanged(newRowIndex, 3);
    });

    QComboBox* weirComboBox = new QComboBox(sectionsTable);
    weirComboBox->addItems({"Ситчатая", "Клапанная"});
    typeComboBox->setCurrentText(newSection.weirType);
    sectionsTable->setCellWidget(newRowIndex, 4, weirComboBox);
    connect(weirComboBox, &QComboBox::currentIndexChanged, this, [this, newRowIndex](int){
        onTableChanged(newRowIndex, 4);
    });

    QComboBox* numberComboBox = new QComboBox(sectionsTable);
    numberComboBox->addItems({"2", "4", "6", "8"});
    sectionsTable->setCellWidget(newRowIndex, 5, numberComboBox);
    connect(numberComboBox, &QComboBox::currentIndexChanged, this, [this, newRowIndex](int){
        onTableChanged(newRowIndex, 5);
    });

    if (auto* sieveSection = dynamic_cast<SieveSection*>(&newSection))
    {
        if (sieveSection->weirs.size() == 0) {
            startComboBox->setCurrentText(weirNamesList.front());
            endComboBox->setCurrentText(weirNamesList.back());
        }
        else {
            startComboBox->setCurrentText(sieveSection->weirs.front()->name);
            endComboBox->setCurrentText(sieveSection->weirs.back()->name);
        }

        numberComboBox->setCurrentText(QString::number(sieveSection->passesNumber));
        sectionsTable->setItem(newRowIndex, 6, new QTableWidgetItem(QString::number(sieveSection->flowNumberCoeff)));
        sectionsTable->setItem(newRowIndex, 7, new QTableWidgetItem(QString::number(sieveSection->weirDistance)));
        sectionsTable->setItem(newRowIndex, 8, new QTableWidgetItem(QString::number(sieveSection->holeDiameter)));
    }

    QPushButton* infoButton = new QPushButton("Подробнее", sectionsTable);
    sectionsTable->setCellWidget(newRowIndex, 9, infoButton);
    connect(infoButton, &QPushButton::clicked, this, [this, newRowIndex, startComboBox, endComboBox]() {
        SectionDataModule* module = new SectionDataModule(column, newRowIndex, this);

    //     if (results.size() != 0) {
    //         std::vector <CalculationResults> subResults (results.begin() + startComboBox->currentIndex(), results.begin() + endComboBox->currentIndex() + 1);
    //         module->receiveResults(subResults);
    //     }

    //     if (messages.size() != 0) {
    //         std::vector <std::vector<std::pair<int, QString>>> subMessages (messages.begin() + startComboBox->currentIndex(), messages.begin() + endComboBox->currentIndex() + 1);
    //         module->receiveMessages(subMessages);
    //     }

    //     connect(module, &QDialog::finished, this, [this, newRowIndex](){
    //         this->sectionChanged(newRowIndex);
    //     });

        module->show();
    });

    QPushButton* removeRowButton = new QPushButton("Удалить", sectionsTable);
    sectionsTable->setCellWidget(newRowIndex, 10, removeRowButton);
    connect(removeRowButton, &QPushButton::clicked, this, [this, removeRowButton](){
        int row = sectionsTable->indexAt(removeRowButton->pos()).row();
        sectionsTable->removeRow(row);
        column.sections.erase(column.sections.begin() + row);

        if (sectionsTable->rowCount() == 0) {
            addEmptyRow();
            onTableChanged(0, 0);
        }
        else {
            onTableChanged(0, 1);
        }
    });

    addEmptyRow();
    ignoreSignals = false;
}

void ColumnModule::addEmptyRow() {
    ignoreSignals = true;
    int newRowIndex = sectionsTable->rowCount();
    sectionsTable->insertRow(newRowIndex);

    QPushButton* addNewButton = new QPushButton("Новая", sectionsTable);
    sectionsTable->setCellWidget(newRowIndex, 0, addNewButton);

    for (int col = 1; col < sectionsTable->columnCount(); ++col) {
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setFlags(Qt::NoItemFlags);
        sectionsTable->setItem(newRowIndex, col, item);
    }

    connect(addNewButton, &QPushButton::clicked, this, [this, newRowIndex](){
        auto dummy = std::make_shared<SieveSection>();
        column.sections.push_back(dummy);
        addNewRow(*dummy);
        onTableChanged(newRowIndex, 1);
    });
    ignoreSignals = false;
}

bool ColumnModule::checkSections() {
    sectionsError = false;

    for (int row = 0; row < sectionsTable->rowCount() - 1; ++row)
    {
        QString currentLeft = qobject_cast<QComboBox*>(sectionsTable->cellWidget(row, 1))->currentText();
        QString currentRight = qobject_cast<QComboBox*>(sectionsTable->cellWidget(row, 2))->currentText();

        int currentLeftIndex = weirNamesList.indexOf(currentLeft);
        int currentRightIndex = weirNamesList.indexOf(currentRight);
        if (currentLeftIndex > currentRightIndex) {
            setStatusLabel(true, "Ошибка: в секции нарушен порядок следования тарелок");
            sectionsError = true;
        }

        if (row == 0) {
            if (currentLeft != weirNamesList.front()) {
                setStatusLabel(true, "Ошибка: первая секция должна начинаться с первой тарелки");
                sectionsError = true;
            }
        }
        if (row == sectionsTable->rowCount() - 2) {
            if (currentRight != weirNamesList.back()) {
                setStatusLabel(true, "Ошибка: последняя секция должна заканчиваться с последней тарелки");
                sectionsError = true;
            }
        }

        if (row != 0)
        {
            QString previousRight = qobject_cast<QComboBox*>(sectionsTable->cellWidget(row - 1, 2))->currentText();
            int previousRightIndex = weirNamesList.indexOf(previousRight);
            if (previousRightIndex + 1 != currentLeftIndex) {
                setStatusLabel(true, "Ошибка: секции должны следовать друг за другом, без пробелов");
                sectionsError = true;
            }
        }
    }

    return sectionsError;
}

void ColumnModule::setupColumn()
{
    std::vector<std::pair<int, int>> _sections;
    for (auto& section : column.sections) {
        int leftIndex, rightIndex;

        if (auto sieveSection = std::dynamic_pointer_cast<SieveSection>(section)) {
            leftIndex = weirNamesList.indexOf(sieveSection->weirs.front()->name);
            rightIndex = weirNamesList.indexOf(sieveSection->weirs.back()->name);
        }

        _sections.push_back(std::make_pair(leftIndex, rightIndex));
    }

    sectionsDiagram->updateSection(_sections);
}

void ColumnModule::rearrangeWeirs()
{
    for (int row = 0; row < sectionsTable->rowCount() - 1; ++row)
    {
        QString left = qobject_cast<QComboBox*>(sectionsTable->cellWidget(row, 1))->currentText();
        QString right = qobject_cast<QComboBox*>(sectionsTable->cellWidget(row, 2))->currentText();

        int leftIndex = weirNamesList.indexOf(left);
        int rightIndex = weirNamesList.indexOf(right);

        if (auto sieveSection = std::dynamic_pointer_cast<SieveSection>(column.sections[row])) {
            sieveSection->weirs.clear();
            for (int iter = leftIndex; iter <= rightIndex; iter++) {
                sieveSection->weirs.push_back(std::dynamic_pointer_cast<SieveWeir>(weirsList[iter]));
            }
        }
    }
}

// void ColumnModule::onCalcButtonPushed()
// {
//     results.clear();
//     messages.clear();

//     // calcModule->performCalculations(column);
//     // results = calcModule->fetchResults();
//     // messages = calcModule->fetchMessages();

//     resultsButton->setEnabled(true);
//     eraseButton->setEnabled(true);
//     graphButton->setEnabled(true);
// }

// void ColumnModule::onEraseButtonPushed()
// {
//     resultsButton->setDisabled(true);
//     eraseButton->setDisabled(true);
//     graphButton->setDisabled(true);

//     results.clear();
//     messages.clear();
// }

// void ColumnModule::onResultsButtonPushed()
// {
//     // ResultsViewModule* module = new ResultsViewModule(results);
//     // module->show();
// }

// void ColumnModule::onGraphButtonPushed()
// {
//     // GraphViewModule* graphModule = new GraphViewModule(results, column);
//     // graphModule->show();
// }

void ColumnModule::onTableChanged(int row, int col)
{
    if (ignoreSignals) return;
    activeError = false;

    // Проверка на наличие секций
    if (sectionsTable->rowCount() == 1) {
        setStatusLabel(true, "Секции пустые");
        activeError = true;
    }

    // Проверка на нулевые данные у секций
    for (int row = 0; row < sectionsTable->rowCount() - 1; ++row)
    {
        if(sectionsTable->item(row, 0)->text() == ""
            || sectionsTable->item(row, 6)->text().toDouble() == 0.0
            || sectionsTable->item(row, 7)->text().toDouble() == 0.0
            || sectionsTable->item(row, 8)->text().toDouble() == 0.0)
        {
            setStatusLabel(true, "Ошибка: некоторые поля содержат нулевые данные");
            activeError = true;
            break;
        }
    }

    // Проверка на одинаковые имена секций
    QStringList sectionsNames;
    for (int row = 0; row < sectionsTable->rowCount() - 1; ++row)
    {
        QString currName = sectionsTable->item(row, 0)->text();
        if (sectionsNames.contains(currName)) {
            setStatusLabel(true, "Ошибка: секции имеют одинаковые имена");
            activeError = true;
            break;
        }
        sectionsNames.append(currName);
    }

    switch (col) {
    case 0:
        if (sectionsTable->rowCount() == 1) break;
        column.sections[row]->name = sectionsTable->item(row, col)->text();
        break;
    case 1:
        if (checkSections()) break;
        rearrangeWeirs();
        setupColumn();
        break;
    case 2:
        if (checkSections()) break;
        rearrangeWeirs();
        setupColumn();
        break;
    case 3:
        column.sections[row]->calcType = qobject_cast<QComboBox*>(sectionsTable->cellWidget(row, col))->currentText();

        if (auto sieveSection = std::dynamic_pointer_cast<SieveSection>(column.sections[row])) {
            if (column.sections[row]->calcType == "Поверочный") column.sections[row] = std::make_shared<SieveSectionVerification>(*sieveSection);
            else column.sections[row] = std::make_shared<SieveSection>(*sieveSection);
        }
        break;
    case 4:
        column.sections[row]->weirType = qobject_cast<QComboBox*>(sectionsTable->cellWidget(row, col))->currentText();
        break;
    case 5:
        if (auto sieveSection = std::dynamic_pointer_cast<SieveSection>(column.sections[row])) {
            sieveSection->passesNumber = qobject_cast<QComboBox*>(sectionsTable->cellWidget(row, col))->currentText().toInt();
        }
        break;
    case 6:
        if (auto sieveSection = std::dynamic_pointer_cast<SieveSection>(column.sections[row])) {
            sieveSection->flowNumberCoeff = sectionsTable->item(row, col)->text().toDouble();
        }
        break;
    case 7:
        if (auto sieveSection = std::dynamic_pointer_cast<SieveSection>(column.sections[row])) {
            sieveSection->weirDistance = sectionsTable->item(row, col)->text().toDouble();
        }
        break;
    case 8:
        if (auto sieveSection = std::dynamic_pointer_cast<SieveSection>(column.sections[row])) {
            sieveSection->holeDiameter = sectionsTable->item(row, col)->text().toDouble();
        }
        break;
    }

    if (!activeError && !sectionsError) {
        setStatusLabel(false, "Секции готовы к расчёту");
    }

    printFullColumn();
}

void ColumnModule::setStatusLabel(bool errorFlag, QString message)
{
    sectionsStatusLineEdit->setText(message);
    if (errorFlag) {
        sectionsStatusLineEdit->setStyleSheet("QLineEdit { background-color: red; }");

        for (int row = 0; row < sectionsTable->rowCount() - 1; ++row) {
            qobject_cast<QPushButton*>(sectionsTable->cellWidget(row, 10))->setDisabled(true);
            qobject_cast<QPushButton*>(sectionsTable->cellWidget(row, 9))->setDisabled(true);
        }
        qobject_cast<QPushButton*>(sectionsTable->cellWidget(sectionsTable->rowCount() - 1, 0))->setDisabled(true);
    }
    else {
        sectionsStatusLineEdit->setStyleSheet("QLineEdit { background-color: green; }");

        for (int row = 0; row < sectionsTable->rowCount() - 1; ++row) {
            qobject_cast<QPushButton*>(sectionsTable->cellWidget(row, 10))->setEnabled(true);
            qobject_cast<QPushButton*>(sectionsTable->cellWidget(row, 9))->setEnabled(true);
        }
        qobject_cast<QPushButton*>(sectionsTable->cellWidget(sectionsTable->rowCount() - 1, 0))->setEnabled(true);
    }
}

void ColumnModule::printFullColumn()
{
    qDebug() << column.name;
    for (auto& section : column.sections) {
        qDebug() << section->name << section->calcType << section->weirType;

        if (auto sieveSection = std::dynamic_pointer_cast<SieveSection>(section)) {
            qDebug() << sieveSection->passesNumber << sieveSection->flowNumberCoeff << sieveSection->weirDistance << sieveSection->holeDiameter;
            if (auto sieveVerificationSection = std::dynamic_pointer_cast<SieveSectionVerification>(sieveSection)) {
                qDebug() << sieveVerificationSection->columnDiameter << sieveVerificationSection->workingArea << sieveVerificationSection->summaryArea <<
                    sieveVerificationSection->percentArea << sieveVerificationSection->perimeter << sieveVerificationSection->widthOverflow << sieveVerificationSection->crossSectionOverflow;
            }

            for (auto& weir : sieveSection->weirs) qDebug() << weir->name;
        }
    }
}
