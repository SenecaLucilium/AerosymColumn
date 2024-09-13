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

// #include "resultstab.h"

// AdditionalResultsWidget::AdditionalResultsWidget(QWidget *parent) : QDialog(parent)
// {
//     setWindowTitle(QString("Подробные результаты по тарелке"));
//     QStringList headerLabels = {"Название", "Значение"};

//     firstContainer = new QWidget(this);
//     {
//         columnDiameterLabel = new QLabel("Диаметр колонны", firstContainer);
//         columnDiameterLabel->setStyleSheet("font-weight: bold;");

//         columnDiameterTable = new QTableWidget(15, 2, firstContainer);
//         QStringList columnDiameterRowNames = {"Фактор нагрузки", "Коэффициент нагрузки", "Плотность вспененной жидкости по отношению к исходной",
//                                               "Максимально допустимая скорость газа (м/с)", "Расчётная рабочая площадь тарелки (м^2)", "Периметр слива (м)",
//                                               "Периметр, округлённый по табл. (м)", "Ширина перелива (мм)", "Сечение перелива (м^2)",
//                                               "Расчётное свободное сечение колонны (м^2)", "Расчётный диаметр колонны (м)", "Расчётный диаметр колонны по табл. (м)",
//                                               "Принятый периметр слива (м)", "Принятая ширина перелива (мм)", "Принятое сечение перелива (м^2)"};
//         setupTable(columnDiameterTable, headerLabels, columnDiameterRowNames);

//         columnDiameterTable->setFixedHeight(480); columnDiameterTable->setFixedWidth(460);
//         columnDiameterTable->setColumnWidth(0, 350); columnDiameterTable->setColumnWidth(1, 80);

//         firstVLayout = new QVBoxLayout();
//         firstVLayout->addWidget(columnDiameterLabel);
//         firstVLayout->addWidget(columnDiameterTable);
//         firstVLayout->addStretch();
//         firstContainer->setLayout(firstVLayout);
//     }

//     secondContainer = new QWidget(this);
//     {
//         columnSectionLabel = new QLabel("Свободное сечение колонны", secondContainer);
//         columnSectionLabel->setStyleSheet("font-weight: bold;");

//         columnSectionTable = new QTableWidget(12, 2, secondContainer);
//         QStringList columnSectionRowNames = {"Рабочая площадь тарелки (м^2)", "Рабочая скорость газа в колонне (м/с)", "Расход жидкости на единицу длины сливной планки (м*ч)",
//                                              "Диапазон устойчивой работы тарелки", "Относительное свободное сечение тарелки (%)", "Площадь колонны (м^2)",
//                                              "Скорость газа в сечении колонны (м/с)", "Расчётное относительное свободное сечение колонны (%)", "Площадь отверстий тарелки (м^2)",
//                                              "Принятое относительное сечение колонны (%)", "Скорость жидкости в отверстиях тарелки (м/с)", "Расчётная минимальная скорость газа в отверстиях тарелки (м/с)"};
//         setupTable(columnSectionTable, headerLabels, columnSectionRowNames);

//         columnSectionTable->setFixedHeight(390); columnSectionTable->setFixedWidth(485);
//         columnSectionTable->setColumnWidth(0, 375); columnSectionTable->setColumnWidth(1, 80);

//         secondVLayout = new QVBoxLayout();
//         secondVLayout->addWidget(columnSectionLabel);
//         secondVLayout->addWidget(columnSectionTable);
//         secondVLayout->addStretch();
//         secondContainer->setLayout(secondVLayout);
//     }

//     thirdContainer = new QWidget(this);
//     {
//         weirHydrResistLabel = new QLabel("Гидравлическое сопротивление тарелки", thirdContainer);
//         weirHydrResistLabel->setStyleSheet("font-weight: bold;");
//         overflowDeviceLabel = new QLabel("Переливное устройство", thirdContainer);
//         overflowDeviceLabel->setStyleSheet("font-weight: bold;");

//         weirHydrResistTable = new QTableWidget(9, 2, thirdContainer);
//         QStringList weirHydrResistRowNames = {"Подпор жидкости над сливной планкой (для опр. скорости) (мм)", "Скорость газа в отверстиях тарелки (м/с)", "Подпор жидкости над сливной планкой (мм)",
//                                               "Минимально допустимая скорость газа в отверстиях (м/с)", "Сопротивление сухой тарелки (мм вод. ст.)", "Потеря напора газового потока в слое жидкости на тарелке (мм вод. ст.)",
//                                               "Общий перепад давления тарелки (мм вод. ст.)", "Высота вспененного слоя жидкости на тарелке (мм)", "Высота светлого слоя невспененной жидкости на тарелке (мм)"};
//         setupTable(weirHydrResistTable, headerLabels, weirHydrResistRowNames);

//         weirHydrResistTable->setFixedHeight(300); weirHydrResistTable->setFixedWidth(510);
//         weirHydrResistTable->setColumnWidth(0, 410); weirHydrResistTable->setColumnWidth(1, 80);

//         overflowDeviceTable = new QTableWidget(6, 2, thirdContainer);
//         QStringList overflowDeviceRowNames = {"Сопротивление движению жидкости в переливе (мм вод. ст.)", "Коэффициент, зависящий от числа потоков на тарелке", "Подпор жидкости над затворной планкой (мм)",
//                                               "Высота слоя светлой жидкости в переливном устройстве (мм)", "Высота вспененного слоя жидкости в переливном устройстве (мм)", "Высота переливного устройства (мм)"};
//         setupTable(overflowDeviceTable, headerLabels, overflowDeviceRowNames);

//         overflowDeviceTable->setFixedHeight(210); overflowDeviceTable->setFixedWidth(510);
//         overflowDeviceTable->setColumnWidth(0, 410); overflowDeviceTable->setColumnWidth(1, 80);

//         thirdVLayout = new QVBoxLayout();
//         thirdVLayout->addWidget(weirHydrResistLabel);
//         thirdVLayout->addWidget(weirHydrResistTable);
//         thirdVLayout->addWidget(overflowDeviceLabel);
//         thirdVLayout->addWidget(overflowDeviceTable);
//         thirdVLayout->addStretch();
//         thirdContainer->setLayout(thirdVLayout);
//     }

//     mainHLayout = new QHBoxLayout();
//     mainHLayout->addWidget(firstContainer);
//     mainHLayout->addWidget(secondContainer);
//     mainHLayout->addWidget(thirdContainer);
//     setLayout(mainHLayout);
// }

// void AdditionalResultsWidget::updateInformation(CalculationResults results)
// {
//     // if (results.loadFactor != std::numeric_limits<double>::lowest())
//     //     updateCell(columnDiameterTable, 0, 1, QString::number(results.loadFactor));
//     // if (results.loadCoeff != std::numeric_limits<double>::lowest())
//     //     updateCell(columnDiameterTable, 1, 1, QString::number(results.loadCoeff));
//     // if (results.foamedRelativeDensity != std::numeric_limits<double>::lowest())
//     //     updateCell(columnDiameterTable, 2, 1, QString::number(results.foamedRelativeDensity));
//     // if (results.maxGasSpeed != std::numeric_limits<double>::lowest())
//     //     updateCell(columnDiameterTable, 3, 1, QString::number(results.maxGasSpeed));
//     // if (results.workingPlateArea_diameter != std::numeric_limits<double>::lowest())
//     //     updateCell(columnDiameterTable, 4, 1, QString::number(results.workingPlateArea_diameter));
//     // if (results.perimeter != std::numeric_limits<double>::lowest())
//     //     updateCell(columnDiameterTable, 5, 1, QString::number(results.perimeter));
//     // if (results.perimeterTable != std::numeric_limits<double>::lowest())
//     //     updateCell(columnDiameterTable, 6, 1, QString::number(results.perimeterTable));
//     // if (results.width != std::numeric_limits<double>::lowest())
//     //     updateCell(columnDiameterTable, 7, 1, QString::number(results.width));
//     // if (results.crossSection != std::numeric_limits<double>::lowest())
//     //     updateCell(columnDiameterTable, 8, 1, QString::number(results.crossSection));
//     // if (results.freeColumnSection != std::numeric_limits<double>::lowest())
//     //     updateCell(columnDiameterTable, 9, 1, QString::number(results.freeColumnSection));
//     // if (results.columnDiameter != std::numeric_limits<double>::lowest())
//     //     updateCell(columnDiameterTable, 10, 1, QString::number(results.columnDiameter));
//     // if (results.columnDiameterTable != std::numeric_limits<double>::lowest())
//     //     updateCell(columnDiameterTable, 11, 1, QString::number(results.columnDiameterTable));
//     // if (results.acceptedPerimeter != std::numeric_limits<double>::lowest())
//     //     updateCell(columnDiameterTable, 12, 1, QString::number(results.acceptedPerimeter));
//     // if (results.acceptedWidth != std::numeric_limits<double>::lowest())
//     //     updateCell(columnDiameterTable, 13, 1, QString::number(results.acceptedWidth));
//     // if (results.acceptedCrossSection != std::numeric_limits<double>::lowest())
//     //     updateCell(columnDiameterTable, 14, 1, QString::number(results.acceptedCrossSection));

//     // if (results.workingPlateArea_section != std::numeric_limits<double>::lowest())
//     //     updateCell(columnSectionTable, 0, 1, QString::number(results.workingPlateArea_section));
//     // if (results.workingGasSpeed != std::numeric_limits<double>::lowest())
//     //     updateCell(columnSectionTable, 1, 1, QString::number(results.workingGasSpeed));
//     // if (results.liquidConsumptionPerUnit != std::numeric_limits<double>::lowest())
//     //     updateCell(columnSectionTable, 2, 1, QString::number(results.liquidConsumptionPerUnit));
//     // if (results.stableRangeOperation != std::numeric_limits<double>::lowest())
//     //     updateCell(columnSectionTable, 3, 1, QString::number(results.stableRangeOperation));
//     // if (results.relativeFreePlateSection != std::numeric_limits<double>::lowest())
//     //     updateCell(columnSectionTable, 4, 1, QString::number(results.relativeFreePlateSection));
//     // if (results.areaColumn != std::numeric_limits<double>::lowest())
//     //     updateCell(columnSectionTable, 5, 1, QString::number(results.areaColumn));
//     // if (results.columnSectionGasSpeed != std::numeric_limits<double>::lowest())
//     //     updateCell(columnSectionTable, 6, 1, QString::number(results.columnSectionGasSpeed));
//     // if (results.calcRelativeFreeSection != std::numeric_limits<double>::lowest())
//     //     updateCell(columnSectionTable, 7, 1, QString::number(results.calcRelativeFreeSection));
//     // if (results.weirHoleArea != std::numeric_limits<double>::lowest())
//     //     updateCell(columnSectionTable, 8, 1, QString::number(results.weirHoleArea));
//     // if (results.acceptedRelativeColumnSection != std::numeric_limits<double>::lowest())
//     //     updateCell(columnSectionTable, 9, 1, QString::number(results.acceptedRelativeColumnSection));
//     // if (results.liquidHoleSpeed != std::numeric_limits<double>::lowest())
//     //     updateCell(columnSectionTable, 10, 1, QString::number(results.liquidHoleSpeed));
//     // if (results.minSteamHoleSpeed != std::numeric_limits<double>::lowest())
//     //     updateCell(columnSectionTable, 11, 1, QString::number(results.minSteamHoleSpeed));

//     // if (results.liquidDrainPlate_speed != std::numeric_limits<double>::lowest())
//     //     updateCell(weirHydrResistTable, 0, 1, QString::number(results.liquidDrainPlate_speed));
//     // if (results.steamHoleSpeed != std::numeric_limits<double>::lowest())
//     //     updateCell(weirHydrResistTable, 1, 1, QString::number(results.steamHoleSpeed));
//     // if (results.liquidDrainPlate != std::numeric_limits<double>::lowest())
//     //     updateCell(weirHydrResistTable, 2, 1, QString::number(results.liquidDrainPlate));
//     // if (results.minGasHoleSpeed != std::numeric_limits<double>::lowest())
//     //     updateCell(weirHydrResistTable, 3, 1, QString::number(results.minGasHoleSpeed));
//     // if (results.dryPlateResist != std::numeric_limits<double>::lowest())
//     //     updateCell(weirHydrResistTable, 4, 1, QString::number(results.dryPlateResist));
//     // if (results.gasFlowLoss != std::numeric_limits<double>::lowest())
//     //     updateCell(weirHydrResistTable, 5, 1, QString::number(results.gasFlowLoss));
//     // if (results.totalPressureDrop != std::numeric_limits<double>::lowest())
//     //     updateCell(weirHydrResistTable, 6, 1, QString::number(results.totalPressureDrop));
//     // if (results.foamedLayerHeight_weir != std::numeric_limits<double>::lowest())
//     //     updateCell(weirHydrResistTable, 7, 1, QString::number(results.foamedLayerHeight_weir));
//     // if (results.nonFoamedLayerHeight != std::numeric_limits<double>::lowest())
//     //     updateCell(weirHydrResistTable, 8, 1, QString::number(results.nonFoamedLayerHeight));

//     // if (results.fluidMovementResist != std::numeric_limits<double>::lowest())
//     //     updateCell(overflowDeviceTable, 0, 1, QString::number(results.fluidMovementResist));
//     // if (results.passesNumberCoeff != std::numeric_limits<double>::lowest())
//     //     updateCell(overflowDeviceTable, 1, 1, QString::number(results.passesNumberCoeff));
//     // if (results.liquidAboveDrainPlate != std::numeric_limits<double>::lowest())
//     //     updateCell(overflowDeviceTable, 2, 1, QString::number(results.liquidAboveDrainPlate));
//     // if (results.lightLiquidHeight != std::numeric_limits<double>::lowest())
//     //     updateCell(overflowDeviceTable, 3, 1, QString::number(results.lightLiquidHeight));
//     // if (results.foamedLayerHeight_device != std::numeric_limits<double>::lowest())
//     //     updateCell(overflowDeviceTable, 4, 1, QString::number(results.foamedLayerHeight_device));
//     // if (results.overflowDeviceHeight != std::numeric_limits<double>::lowest())
//     //     updateCell(overflowDeviceTable, 5, 1, QString::number(results.overflowDeviceHeight));
// }

// void AdditionalResultsWidget::updateCell(QTableWidget* table, int row, int col, QString newValue)
// {
//     QTableWidgetItem* item = table->item(row, col);
//     item->setText(newValue);
// }

// void AdditionalResultsWidget::setupTable(QTableWidget* table, QStringList headerLabels, QStringList rowNames)
// {
//     table->setHorizontalHeaderLabels(headerLabels);
//     for (int row = 0; row < rowNames.size(); ++row)
//     {
//         QTableWidgetItem* nameItem = new QTableWidgetItem(rowNames[row]);
//         QTableWidgetItem* valueItem = new QTableWidgetItem("-");

//         nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
//         nameItem->setToolTip(nameItem->text());
//         valueItem->setFlags(valueItem->flags() & ~Qt::ItemIsEditable);

//         table->setItem(row, 0, nameItem);
//         table->setItem(row, 1, valueItem);
//     }
// }

// AdditionalResultsWidget::~AdditionalResultsWidget() {}

// ResultsTab::ResultsTab(QWidget *parent)
//     : QWidget{parent}
// {
//     QStringList headerLabels = {"Название проверки"};

//     mainResultsContainer = new QWidget(this);
//     {
//         mainResultsLabel = new QLabel("Основные проверки", mainResultsContainer);
//         mainResultsLabel->setStyleSheet("font-weight: bold;");

//         mainResultsTable = new QTableWidget(10, 1, mainResultsContainer);
//         QStringList mainRowNames = {"Условие высоты вспененного слоя", "Условие высоты переливного устройства", "Условие нормальной работы",
//                                     "Условие работы переливного устройства", "Условие нормальной работы тарелки", "Условие расстояния между тарелками",
//                                     "Проверка скорости газа в колонне", "Проверка расхода жидкости", "Проверка скорости газа в отверстиях тарелки",
//                                     "Показать дополнительные результаты"};
//         setupTable(mainResultsTable, headerLabels, mainRowNames);
//         mainResultsTable->setColumnWidth(0, 280);
//         mainResultsTable->setFixedHeight(330);

//         mainResultsVLayout = new QVBoxLayout();
//         mainResultsVLayout->addWidget(mainResultsLabel);
//         mainResultsVLayout->addWidget(mainResultsTable);
//         mainResultsContainer->setLayout(mainResultsVLayout);
//     }

//     verificationResultsContainer = new QWidget(this);
//     {
//         verificationResultsLabel = new QLabel("Основные проверки", verificationResultsContainer);
//         verificationResultsLabel->setStyleSheet("font-weight: bold;");

//         verificationResultsTable = new QTableWidget(5, 1, verificationResultsContainer);
//         QStringList verificationRowNames = {"Диаметр", "Периметр слива", "Сечение перелива",
//                                             "Рабочая площадь тарелки", "Относительное свободное сечение колонны"};
//         setupTable(verificationResultsTable, headerLabels, verificationRowNames);
//         verificationResultsTable->setColumnWidth(0, 280);
//         verificationResultsTable->setFixedHeight(180);

//         verificationResultsVLayout = new QVBoxLayout();
//         verificationResultsVLayout->addWidget(verificationResultsLabel);
//         verificationResultsVLayout->addWidget(verificationResultsTable);
//         verificationResultsContainer->setLayout(verificationResultsVLayout);
//     }

//     mainVLayout = new QVBoxLayout();
//     mainVLayout->addWidget(mainResultsContainer);
//     mainVLayout->addWidget(verificationResultsContainer);
//     mainVLayout->addStretch();
//     setLayout(mainVLayout);
// }

// void ResultsTab::updateInformation(std::vector<CalculationResults>& results)
// {
//     // for (auto& weirRes : results)
//     // {
//     //     int newColumnIndex = mainResultsTable->columnCount();
//     //     mainResultsTable->insertColumn(newColumnIndex);
//     //     mainResultsTable->setHorizontalHeaderItem(newColumnIndex, new QTableWidgetItem(weirRes.weirName));

//     //     auto setTableItem = [&](QTableWidget* table, int row, bool condition) {
//     //         QTableWidgetItem* item = new QTableWidgetItem(condition ? "OK" : "Ошибка");
//     //         item->setFlags(item->flags() & ~Qt::ItemIsEditable);

//     //         if (condition) {
//     //             item->setBackground(QColor(144, 238, 144));
//     //         } else {
//     //             item->setBackground(QColor(255, 99, 71));
//     //         }

//     //         table->setItem(row, newColumnIndex, item);
//     //     };

//     //     setTableItem(mainResultsTable, 0, weirRes.condition_foamedHeight);
//     //     setTableItem(mainResultsTable, 1, weirRes.condition_deviceHeight);
//     //     setTableItem(mainResultsTable, 2, weirRes.condition_normalWork);
//     //     setTableItem(mainResultsTable, 3, weirRes.condition_overflowDevice);
//     //     setTableItem(mainResultsTable, 4, weirRes.condition_weirWork);
//     //     setTableItem(mainResultsTable, 5, weirRes.condition_weirDistance);
//     //     setTableItem(mainResultsTable, 6, weirRes.condition_gasSpeed);
//     //     setTableItem(mainResultsTable, 7, weirRes.condition_liquidFlow);
//     //     setTableItem(mainResultsTable, 8, weirRes.condition_gasHoleSpeed);

//     //     QPushButton* additionalResultsButton = new QPushButton("Подробнее", mainResultsTable);
//     //     mainResultsTable->setCellWidget(9, newColumnIndex, additionalResultsButton);

//     //     connect(additionalResultsButton, &QPushButton::clicked, this, [this, weirRes](){
//     //         AdditionalResultsWidget* additionalWidget = new AdditionalResultsWidget(this);
//     //         additionalWidget->updateInformation(weirRes);
//     //         additionalWidget->show();
//     //     });

//     //     if (weirRes.active) {
//     //         verificationResultsTable->insertColumn(newColumnIndex);
//     //         verificationResultsTable->setHorizontalHeaderItem(newColumnIndex, new QTableWidgetItem(weirRes.weirName));

//     //         setTableItem(verificationResultsTable, 0, weirRes.verification_columnDiameter);
//     //         setTableItem(verificationResultsTable, 1, weirRes.verification_perimeter);
//     //         setTableItem(verificationResultsTable, 2, weirRes.verification_crossSection);
//     //         setTableItem(verificationResultsTable, 3, weirRes.verification_workingPlateArea);
//     //         setTableItem(verificationResultsTable, 4, weirRes.verification_relativeColumnSection);
//     //     }
//     // }
// }

// void ResultsTab::setupTable(QTableWidget* table, QStringList headerLabels, QStringList rowNames)
// {
//     table->setHorizontalHeaderLabels(headerLabels);
//     for (int row = 0; row < rowNames.size(); ++row)
//     {
//         QTableWidgetItem* nameItem = new QTableWidgetItem(rowNames[row]);
//         nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
//         nameItem->setToolTip(nameItem->text());
//         table->setItem(row, 0, nameItem);
//     }
// }


#endif // SIEVERESULTS_H
