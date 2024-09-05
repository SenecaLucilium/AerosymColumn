#include "resultsviewmodule.h"

ResultsViewModule::ResultsViewModule(std::vector <CalculationResults>& _results, QWidget *parent)
    : QWidget{parent}, results{_results}
{
    this->setWindowTitle("Графические результаты");

    int widgetWidth = 1280;
    int widgetHeight = 720;
    this->setFixedSize(widgetWidth, widgetHeight);

    mainWidget = new QWidget(this);

    chooseContainer = new QWidget(mainWidget);
    {
        mainLabel = new QLabel("Этап расчета:", chooseContainer);
        mainComboBox = new QComboBox(chooseContainer);
        mainComboBox->addItems({"Диаметр колонны", "Свободное сечение колонны", "Гидравлическое сопротивление тарелки", "Переливное устройство"});
        connect(mainComboBox, &QComboBox::currentIndexChanged, this, &ResultsViewModule::onStageChanged);

        paramsLabel = new QLabel("Параметр:", chooseContainer);
        paramsComboBox = new QComboBox(chooseContainer);
        paramsComboBox->setFixedWidth(400);

        chooseHLayout = new QHBoxLayout();
        chooseHLayout->addWidget(mainLabel);
        chooseHLayout->addWidget(mainComboBox);
        chooseHLayout->addSpacing(30);
        chooseHLayout->addWidget(paramsLabel);
        chooseHLayout->addWidget(paramsComboBox);
        chooseHLayout->addStretch();

        chooseContainer->setLayout(chooseHLayout);
    }

    plotter = new JKQTPlotter(mainWidget);
    plotter->setFixedSize(1260, 660);
    connect(paramsComboBox, &QComboBox::currentTextChanged, this, &ResultsViewModule::onParamChanged);

    mainVLayout = new QVBoxLayout();
    mainVLayout->addWidget(chooseContainer, 1);
    mainVLayout->addWidget(plotter, 9);
    mainWidget->setLayout(mainVLayout);

    emit mainComboBox->currentIndexChanged(0);
}

void ResultsViewModule::onStageChanged()
{
    paramsComboBox->clear();

    switch(mainComboBox->currentIndex())
    {
    case(0):
        paramsComboBox->addItems({"Фактор нагрузки", "Коэффициент нагрузки", "Плотность вспененной жидкости по отношению к исходной",
                                  "Максимально допустимая скорость газа (м/с)", "Расчетная рабочая площадь тарелки (м^2)", "Периметр слива (м)",
                                  "Периметр, округлённый по табл. (м)", "Ширина перелива (мм)", "Сечение перелива (м^2)",
                                  "Расчетное свободное сечение колонны (м^2)", "Расчетный диаметр колонны (м)", "Расчетный диаметр колонны по табл. (м)",
                                  "Принятый периметр слива (м)", "Принятая ширина перелива (мм)", "Принятое сечение перелива (м^2)"});
        break;
    case(1):
        paramsComboBox->addItems({"Рабочая площадь тарелки (м^2)", "Рабочая скорость газа в колонне (м/с)", "Расход жидкости на единицу длины сливной планки (м*ч)",
                                  "Диапазон устойчивой работы тарелки", "Относительное свободное сечение тарелки (%)", "Площадь колонны (м^2)",
                                  "Скорость газа в сечении колонны (м/с)", "Расчетное относительное свободное сечение колонны (%)", "Площадь отверстий тарелки (м^2)",
                                  "Принятое относительное сечение колонны (%)", "Скорость жидкости в отверстиях тарелки (м/с)", "Расчетная минимальная скорость газа в отверстиях тарелки (м/с)"});
        break;
    case(2):
        paramsComboBox->addItems({"Подпор жидкости над сливной планкой (для опр. скорости) (мм)", "Скорость газа в отверстиях тарелки (м/с)", "Подпор жидкости над сливной планкой (мм)",
                                  "Минимально допустимая скорость газа в отверстиях (м/с)", "Сопротивление сухой тарелки (мм вод. ст.)", "Потеря напора газового потока в слое жидкости на тарелке (мм вод. ст.)",
                                  "Общий перепад давления тарелки (мм вод. ст.)", "Высота вспененного слоя жидкости на тарелке (мм)", "Высота светлого слоя невспененной жидкости на тарелке (мм)"});
        break;
    case(3):
        paramsComboBox->addItems({"Сопротивление движению жидкости в переливе (мм вод. ст.)", "Коэффициент, зависящий от числа потоков на тарелке", "Подпор жидкости над затворной планкой (мм)",
                                  "Высота слоя светлой жидкости в переливном устройстве (мм)", "Высота вспененного слоя жидкости в переливном устройстве (мм)", "Высота переливного устройства (мм)"});
        break;
    default:
        return;
    }
}

void ResultsViewModule::onParamChanged()
{
    QString currParam = paramsComboBox->currentText();
    if (currParam == "") return;

    QVector<double> xValues, yValues, yZeroedValues;
    bool zeroed = false;

    int iter = 0;
    for (const auto& weir : results)
    {
        xValues.append(iter + 1);
        double yValue = 0.0;

        if (currParam == "Фактор нагрузки") yValue = weir.loadFactor;
        else if (currParam == "Коэффициент нагрузки") yValue = weir.loadCoeff;
        else if (currParam == "Плотность вспененной жидкости по отношению к исходной") yValue = weir.foamedRelativeDensity;
        else if (currParam == "Максимально допустимая скорость газа (м/с)") yValue = weir.maxGasSpeed;
        else if (currParam == "Расчетная рабочая площадь тарелки (м^2)") yValue = weir.workingPlateArea_diameter;
        else if (currParam == "Периметр слива (м)") yValue = weir.perimeter;
        else if (currParam == "Периметр, округлённый по табл. (м)") yValue = weir.perimeterTable;
        else if (currParam == "Ширина перелива (мм)") yValue = weir.width;
        else if (currParam == "Сечение перелива (м^2)") yValue = weir.crossSection;
        else if (currParam == "Расчетное свободное сечение колонны (м^2)") yValue = weir.freeColumnSection;
        else if (currParam == "Расчетный диаметр колонны (м)") yValue = weir.columnDiameter;
        else if (currParam == "Расчетный диаметр колонны по табл. (м)") yValue = weir.columnDiameterTable;
        else if (currParam == "Принятый периметр слива (м)") yValue = weir.acceptedPerimeter;
        else if (currParam == "Принятая ширина перелива (мм)") yValue = weir.acceptedWidth;
        else if (currParam == "Принятое сечение перелива (м^2)") yValue = weir.acceptedCrossSection;
        else if (currParam == "Рабочая площадь тарелки (м^2)") yValue = weir.workingPlateArea_section;
        else if (currParam == "Рабочая скорость газа в колонне (м/с)") yValue = weir.workingGasSpeed;
        else if (currParam == "Расход жидкости на единицу длины сливной планки (м*ч)") yValue = weir.liquidConsumptionPerUnit;
        else if (currParam == "Диапазон устойчивой работы тарелки") yValue = weir.stableRangeOperation;
        else if (currParam == "Относительное свободное сечение тарелки (%)") yValue = weir.relativeFreePlateSection;
        else if (currParam == "Площадь колонны (м^2)") yValue = weir.areaColumn;
        else if (currParam == "Скорость газа в сечении колонны (м/с)") yValue = weir.columnSectionGasSpeed;
        else if (currParam == "Расчетное относительное свободное сечение колонны (%)") yValue = weir.calcRelativeFreeSection;
        else if (currParam == "Площадь отверстий тарелки (м^2)") yValue = weir.weirHoleArea;
        else if (currParam == "Принятое относительное сечение колонны (%)") yValue = weir.acceptedRelativeColumnSection;
        else if (currParam == "Скорость жидкости в отверстиях тарелки (м/с)") yValue = weir.liquidHoleSpeed;
        else if (currParam == "Расчетная минимальная скорость газа в отверстиях тарелки (м/с)") yValue = weir.minSteamHoleSpeed;
        else if (currParam == "Подпор жидкости над сливной планкой (для опр. скорости) (мм)") yValue = weir.liquidDrainPlate_speed;
        else if (currParam == "Скорость газа в отверстиях тарелки (м/с)") yValue = weir.steamHoleSpeed;
        else if (currParam == "Подпор жидкости над сливной планкой (мм)") yValue = weir.liquidDrainPlate;
        else if (currParam == "Минимально допустимая скорость газа в отверстиях (м/с)") yValue = weir.minGasHoleSpeed;
        else if (currParam == "Сопротивление сухой тарелки (мм вод. ст.)") yValue = weir.dryPlateResist;
        else if (currParam == "Потеря напора газового потока в слое жидкости на тарелке (мм вод. ст.)") yValue = weir.gasFlowLoss;
        else if (currParam == "Общий перепад давления тарелки (мм вод. ст.)") yValue = weir.totalPressureDrop;
        else if (currParam == "Высота вспененного слоя жидкости на тарелке (мм)") yValue = weir.foamedLayerHeight_weir;
        else if (currParam == "Высота светлого слоя невспененной жидкости на тарелке (мм)") yValue = weir.nonFoamedLayerHeight;
        else if (currParam == "Сопротивление движению жидкости в переливе (мм вод. ст.)") yValue = weir.fluidMovementResist;
        else if (currParam == "Коэффициент, зависящий от числа потоков на тарелке") yValue = weir.passesNumberCoeff;
        else if (currParam == "Подпор жидкости над затворной планкой (мм)") yValue = weir.liquidAboveDrainPlate;
        else if (currParam == "Высота слоя светлой жидкости в переливном устройстве (мм)") yValue = weir.lightLiquidHeight;
        else if (currParam == "Высота вспененного слоя жидкости в переливном устройстве (мм)") yValue = weir.foamedLayerHeight_device;
        else if (currParam == "Высота переливного устройства (мм)") yValue = weir.overflowDeviceHeight;

        if (yValue == std::numeric_limits<double>::lowest()) {
            zeroed = true;
            yValues.append(0.0);
            yZeroedValues.append(0.0);
        }
        else {
            yValues.append(yValue);
            yZeroedValues.append(std::numeric_limits<double>::quiet_NaN());
        }
        iter++;
    }

    plotter->clearGraphs();

    JKQTPDatastore* datastore = plotter->getDatastore();
    int xColumnSize = datastore->addCopiedColumn(xValues);
    int yColumnSize = datastore->addCopiedColumn(yValues);
    int yZeroedColumnSize = datastore->addCopiedColumn(yZeroedValues);

    JKQTPXYLineGraph* lineGraph = new JKQTPXYLineGraph(plotter);
    lineGraph->setXColumn(xColumnSize);
    lineGraph->setYColumn(yColumnSize);
    lineGraph->setTitle(currParam);
    plotter->addGraph(lineGraph);

    if (zeroed) {
        JKQTPXYScatterGraph* zeroedGraph = new JKQTPXYScatterGraph(plotter);
        zeroedGraph->setXColumn(xColumnSize);
        zeroedGraph->setYColumn(yZeroedColumnSize);
        zeroedGraph->setTitle("Ошибочные значения (занулены)");
        zeroedGraph->setSymbolSize(20.0);
        plotter->addGraph(zeroedGraph);
    }

    plotter->redrawPlot();

    auto yMin_iter = std::min_element(yValues.begin(), yValues.end());
    auto yMax_iter = std::max_element(yValues.begin(), yValues.end());

    double yMin = (*yMin_iter > 0) ? 0 : *yMin_iter * 1.25;
    double yMax = *yMax_iter * 1.25;

    plotter->zoom(xValues.first() - 1, xValues.last() + 1, yMin, yMax);
}

ResultsViewModule::~ResultsViewModule() {}
