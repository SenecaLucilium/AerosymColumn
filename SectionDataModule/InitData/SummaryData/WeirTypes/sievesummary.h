#ifndef SIEVESUMMARY_H
#define SIEVESUMMARY_H

#include <QWidget>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QLabel>
#include <QTableWidget>

#include "../../../../datatypes.h"

class SieveSummary : public QWidget
{
    Q_OBJECT
public:
    explicit SieveSummary(QWidget *parent = nullptr)
    {
        mainContainer = new QWidget(this);
        {
            groupContainer = new QWidget(mainContainer);
            {
                paramsLabel = new QLabel("Параметры расчёта", groupContainer);
                paramsLabel->setStyleSheet("font-weight: bold;");
                geometryLabel = new QLabel("Геометрия", groupContainer);
                geometryLabel->setStyleSheet("font-weight: bold;");
                fluidLabel = new QLabel("Жидкость и Газ", groupContainer);
                fluidLabel->setStyleSheet("font-weight: bold;");

                paramsTable = new QTableWidget(2, 2, groupContainer);
                QStringList paramsRowNames = {"Тип расчёта", "Тип тарелки"};
                setupTable(paramsTable, paramsRowNames);
                paramsTable->setColumnWidth(0, 100); paramsTable->setColumnWidth(1, 100);
                paramsTable->setFixedHeight(90); paramsTable->setFixedWidth(220);

                geometryTable = new QTableWidget(3, 2, groupContainer);
                QStringList geometryRowNames = {"Число потоков на тарелке", "Диаметр отверстий (м)", "Толщина тарелки (мм)"};
                setupTable(geometryTable, geometryRowNames);
                geometryTable->setColumnWidth(0, 160); geometryTable->setColumnWidth(1, 100);
                geometryTable->setFixedHeight(120); geometryTable->setFixedWidth(280);

                fluidTable = new QTableWidget(2, 2, groupContainer);
                QStringList fluidRowNames = {"Расход жидкости на единицу длины сливной планки (м^3/м*ч)", "Коэффициент вспениваемости жидкости"};
                setupTable(fluidTable, fluidRowNames);
                fluidTable->setColumnWidth(0, 240); fluidTable->setColumnWidth(1, 100);
                fluidTable->setFixedHeight(90); fluidTable->setFixedWidth(360);

                groupVLayout = new QVBoxLayout();
                groupVLayout->addWidget(paramsLabel);
                groupVLayout->addWidget(paramsTable);
                groupVLayout->addWidget(geometryLabel);
                groupVLayout->addWidget(geometryTable);
                groupVLayout->addWidget(fluidLabel);
                groupVLayout->addWidget(fluidTable);
                groupVLayout->addStretch();

                groupContainer->setLayout(groupVLayout);
            }

            constantsContainer = new QWidget(mainContainer);
            {
                constantsLabel = new QLabel("Константы", constantsContainer);
                constantsLabel->setStyleSheet("font-weight: bold;");

                constantsTable = new QTableWidget(10, 2, constantsContainer);
                QStringList constantsRowNames = {"Высота переливной планки (м)", "Высота затворной планки (мм)", "Коэффициент расхода",
                                                 "Коэффициент сопротивления сухой тарелки", "Коэффициент сопротивления перелива",
                                                 "Коэффициент площади опорных конструкций тарелки", "Коэффициент надежности", "Коэффициент нагрузки",
                                                 "Коэффициент числа потоков", "Коэффициент запаса для относительного свободного сечения колонны"};
                setupTable(constantsTable, constantsRowNames);
                constantsTable->setColumnWidth(0, 260); constantsTable->setColumnWidth(1, 100);
                constantsTable->setFixedHeight(330); constantsTable->setFixedWidth(385);

                constantsVLayout = new QVBoxLayout();
                constantsVLayout->addWidget(constantsLabel);
                constantsVLayout->addWidget(constantsTable);
                constantsVLayout->addStretch();

                constantsContainer->setLayout(constantsVLayout);
            }

            verificationContainer = new QWidget(mainContainer);
            {
                verificationLabel = new QLabel("Параметры поверочного расчета", verificationContainer);
                verificationLabel->setStyleSheet("font-weight: bold;");

                verificationTable = new QTableWidget(7, 2, verificationContainer);
                QStringList verificationRowNames = {"Диаметр колонны (м)", "Рабочая площадь тарелки (м^2)",
                                                    "Общая площадь отверстий тарелки (м^2)", "Относительное свободное сечение колонны (%)",
                                                    "Периметр слива (м)", "Ширина перелива (мм)", "Принятое сечение перелива (м^2)"};
                setupTable(verificationTable, verificationRowNames);
                verificationTable->setColumnWidth(0, 280); verificationTable->setColumnWidth(1, 100);
                verificationTable->setFixedHeight(240); verificationTable->setFixedWidth(400);

                verificationVLayout = new QVBoxLayout();
                verificationVLayout->addWidget(verificationLabel);
                verificationVLayout->addWidget(verificationTable);
                verificationVLayout->addStretch();

                verificationContainer->setLayout(verificationVLayout);
                verificationContainer->setDisabled(true);
            }

            mainHLayout = new QHBoxLayout();
            mainHLayout->addWidget(groupContainer);
            mainHLayout->addWidget(constantsContainer);
            mainHLayout->addWidget(verificationContainer);
            mainHLayout->addStretch();
            mainContainer->setLayout(mainHLayout);
        }

        weirsContainer = new QWidget(this);
        {
            weirsLabel = new QLabel("Параметры тарелок", weirsContainer);
            weirsLabel->setStyleSheet("font-weight: bold;");

            weirsTable = new QTableWidget(5, 1, weirsContainer);
            QStringList weirsRowNames = {"Мин./Макс. нагрузка по жидкости (кг/ч)", "Мин./Макс. нагрузка по пару (кг/ч)",
                                         "Плотность жидкости (кг/м^3)", "Плотность пара (кг/м^3)", "Поверхностное натяжение жидкости (Н/м)"};
            setupTable(weirsTable, weirsRowNames);
            weirsTable->setColumnWidth(0, 260);
            weirsTable->setFixedHeight(180);

            weirsVLayout = new QVBoxLayout();
            weirsVLayout->addWidget(weirsLabel);
            weirsVLayout->addWidget(weirsTable);

            weirsContainer->setLayout(weirsVLayout);
        }

        mainVLayout = new QVBoxLayout();
        mainVLayout->addWidget(mainContainer);
        mainVLayout->addWidget(weirsContainer);
        mainVLayout->addStretch();
        setLayout(mainVLayout);
    }

    ~SieveSummary(){};

    void updateInformation(Column& column, int sectionIndex)
    {
        std::shared_ptr<SieveSection> sieveSection = std::dynamic_pointer_cast<SieveSection>(column.sections[sectionIndex]);

        paramsTable->item(0, 1)->setText(sieveSection->calcType);
        paramsTable->item(1, 1)->setText(sieveSection->weirType);

        geometryTable->item(0, 1)->setText(QString::number(sieveSection->passesNumber));
        geometryTable->item(1, 1)->setText(QString::number(sieveSection->holeDiameter));
        if (sieveSection->holeDiameter < 0.005 || sieveSection->holeDiameter > 0.025) setCellInfo(geometryTable->item(1, 1), true, "Поддерживаемые значения диаметра отверстия от 0.005м до 0.025м.");
        else setCellInfo(geometryTable->item(1, 1), false);
        geometryTable->item(2, 1)->setText(QString::number(sieveSection->weirs[0]->weirWidth * 1000));

        fluidTable->item(0, 1)->setText(QString::number(column.liquidFlow));
        if (column.liquidFlow < 10 || column.liquidFlow > 50) setCellInfo(fluidTable->item(0, 1), true, "Значение не может быть ниже 10 и больше 50.");
        else setCellInfo(fluidTable->item(0, 1), false);
        fluidTable->item(1, 1)->setText(QString::number(column.foamingCoeff));
        if (column.foamingCoeff < 0.0 || column.foamingCoeff > 1.0) setCellInfo(fluidTable->item(1, 1), true, "Значение не может быть ниже нуля и больше единицы.");
        else setCellInfo(fluidTable->item(1, 1), false);

        constantsTable->item(0, 1)->setText(QString::number(column.overflowBarHeight));
        if (column.overflowBarHeight < 0.0) setCellInfo(constantsTable->item(0, 1), true, "Значение не может быть ниже нуля.");
        else setCellInfo(constantsTable->item(0, 1), false);
        constantsTable->item(1, 1)->setText(QString::number(column.boltHeight));
        if (column.boltHeight < 0.0) setCellInfo(constantsTable->item(1, 1), true, "Значение не может быть ниже нуля.");
        else setCellInfo(constantsTable->item(1, 1), false);
        constantsTable->item(2, 1)->setText(QString::number(column.flowCoeff));
        if (column.flowCoeff < 0.0) setCellInfo(constantsTable->item(2, 1), true, "Значение не может быть ниже нуля.");
        else setCellInfo(constantsTable->item(2, 1), false);
        constantsTable->item(3, 1)->setText(QString::number(column.dryResistCoeff));
        if (column.dryResistCoeff < 0.0) setCellInfo(constantsTable->item(3, 1), true, "Значение не может быть ниже нуля.");
        else setCellInfo(constantsTable->item(3, 1), false);
        constantsTable->item(4, 1)->setText(QString::number(column.overflowResistCoeff));
        if (column.overflowResistCoeff < 0.0) setCellInfo(constantsTable->item(4, 1), true, "Значение не может быть ниже нуля.");
        else setCellInfo(constantsTable->item(4, 1), false);
        constantsTable->item(5, 1)->setText(QString::number(column.occupiedAreaCoeff));
        if (column.occupiedAreaCoeff < 0.0) setCellInfo(constantsTable->item(5, 1), true, "Значение не может быть ниже нуля.");
        else setCellInfo(constantsTable->item(5, 1), false);
        constantsTable->item(6, 1)->setText(QString::number(column.reliabilityCoeff));
        if (column.reliabilityCoeff < 0.5 || column.reliabilityCoeff > 1.0) setCellInfo(constantsTable->item(6, 1), true, "Значение не может быть ниже нуля или больше единицы.");
        else setCellInfo(constantsTable->item(6, 1), false);
        constantsTable->item(7, 1)->setText(QString::number(column.loadCoeff));
        if (column.loadCoeff < 0.0 || column.loadCoeff > 1.0) setCellInfo(constantsTable->item(7, 1), true, "Значение не может быть ниже нуля или больше единицы.");
        else setCellInfo(constantsTable->item(7, 1), false);
        constantsTable->item(8, 1)->setText(QString::number(sieveSection->flowNumberCoeff));
        if (sieveSection->flowNumberCoeff < 0.0 || sieveSection->flowNumberCoeff > 1.0) setCellInfo(constantsTable->item(8, 1), true, "Значение не может быть ниже нуля или больше единицы.");
        else setCellInfo(constantsTable->item(8, 1), false);
        constantsTable->item(9, 1)->setText(QString::number(column.reserveCoeff));
        if (column.reserveCoeff < 0.0 || column.reserveCoeff > 1.0) setCellInfo(constantsTable->item(9, 1), true, "Значение не может быть ниже нуля или больше единицы.");
        else setCellInfo(constantsTable->item(9, 1), false);

        if (auto sieveSectionVerification = std::dynamic_pointer_cast<SieveSectionVerification>(sieveSection)) {
            verificationContainer->setEnabled(true);

            verificationTable->item(0, 1)->setText(QString::number(sieveSectionVerification->columnDiameter));
            verificationTable->item(1, 1)->setText(QString::number(sieveSectionVerification->workingArea));
            if (sieveSectionVerification->workingArea < 0.0) setCellInfo(verificationTable->item(1, 1), true, "Значение не может быть ниже нуля.");
            else setCellInfo(verificationTable->item(1, 1), false);
            verificationTable->item(2, 1)->setText(QString::number(sieveSectionVerification->summaryArea));
            if (sieveSectionVerification->summaryArea < 0.0) setCellInfo(verificationTable->item(2, 1), true, "Значение не может быть ниже нуля.");
            else setCellInfo(verificationTable->item(2, 1), false);
            verificationTable->item(3, 1)->setText(QString::number(sieveSectionVerification->percentArea));
            if (sieveSectionVerification->percentArea < 0.0 || sieveSectionVerification->percentArea > 100.0) setCellInfo(verificationTable->item(3, 1), true, "Значение не может быть ниже нуля и больше 100.");
            else setCellInfo(verificationTable->item(3, 1), false);
            verificationTable->item(4, 1)->setText(QString::number(sieveSectionVerification->perimeter));
            if (sieveSectionVerification->perimeter < 0.0) setCellInfo(verificationTable->item(4, 1), true, "Значение не может быть ниже нуля.");
            else setCellInfo(verificationTable->item(4, 1), false);
            verificationTable->item(5, 1)->setText(QString::number(sieveSectionVerification->widthOverflow));
            if (sieveSectionVerification->widthOverflow < 0.0) setCellInfo(verificationTable->item(5, 1), true, "Значение не может быть ниже нуля.");
            else setCellInfo(verificationTable->item(5, 1), false);
            verificationTable->item(6, 1)->setText(QString::number(sieveSectionVerification->crossSectionOverflow));
            if (sieveSectionVerification->crossSectionOverflow < 0.0) setCellInfo(verificationTable->item(6, 1), true, "Значение не может быть ниже нуля.");
            else setCellInfo(verificationTable->item(6, 1), false);
        }

        int columnCount = weirsTable->columnCount();
        for (int col = columnCount - 1; col > 0; --col) weirsTable->removeColumn(col);
        for (auto& weir : sieveSection->weirs) {
            int newColumnIndex = weirsTable->columnCount();
            weirsTable->insertColumn(newColumnIndex);

            weirsTable->setHorizontalHeaderItem(newColumnIndex, new QTableWidgetItem(weir->name));

            addWeirDataToTable(weirsTable, newColumnIndex, 0, weir->liquidLoad);
            addWeirDataToTable(weirsTable, newColumnIndex, 1, weir->steamLoad);
            addWeirDataToTable(weirsTable, newColumnIndex, 2, weir->liquidDensity);
            addWeirDataToTable(weirsTable, newColumnIndex, 3, weir->steamDensity);
            addWeirDataToTable(weirsTable, newColumnIndex, 4, weir->liquidSurfaceTension);
        }
    }

private:
    static void setupTable(QTableWidget* table, QStringList rowNames)
    {
        table->setHorizontalHeaderLabels({"Название", "Значение"});
        for (int row = 0; row < rowNames.size(); ++row) {
            QTableWidgetItem* nameItem = new QTableWidgetItem(rowNames[row]);
            QTableWidgetItem* valueItem = new QTableWidgetItem("-");

            nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
            nameItem->setToolTip(nameItem->text());
            valueItem->setFlags(valueItem->flags() & ~Qt::ItemIsEditable);

            table->setItem(row, 0, nameItem);
            table->setItem(row, 1, valueItem);
        }
    }

    static void setCellInfo(QTableWidgetItem* item, bool errorFlag, QString errorMessage = "")
    {
        if (errorFlag) item->setBackground(Qt::red);
        else item->setBackground(Qt::white);
        item->setToolTip(errorMessage);
    }

    static void addWeirDataToTable(QTableWidget* table, int columnIndex, int rowIndex, double value)
    {
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(value));
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        table->setItem(rowIndex, columnIndex, item);
    }

    QVBoxLayout* mainVLayout;

    QWidget* mainContainer;
    QHBoxLayout* mainHLayout;

    QWidget* groupContainer;
    QVBoxLayout* groupVLayout;
    QLabel* paramsLabel;
    QTableWidget* paramsTable;
    QLabel* geometryLabel;
    QTableWidget* geometryTable;
    QLabel* fluidLabel;
    QTableWidget* fluidTable;

    QWidget* constantsContainer;
    QVBoxLayout* constantsVLayout;
    QLabel* constantsLabel;
    QTableWidget* constantsTable;

    QWidget* verificationContainer;
    QVBoxLayout* verificationVLayout;
    QLabel* verificationLabel;
    QTableWidget* verificationTable;

    QWidget* weirsContainer;
    QVBoxLayout* weirsVLayout;
    QLabel* weirsLabel;
    QTableWidget* weirsTable;
};

#endif // SIEVESUMMARY_H
