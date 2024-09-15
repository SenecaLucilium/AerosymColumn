#ifndef CALCULATIONMODULE_H
#define CALCULATIONMODULE_H

#include <QObject>
#include "../datatypes.h"

class CalculationModule : public QObject
{
    Q_OBJECT
public:
    explicit CalculationModule(QObject *parent = nullptr);
    ~CalculationModule();

    void performCalculations(Column& column);
};

// class CalculationModule : public QObject
// {
//     Q_OBJECT
// public:
//     explicit CalculationModule(QObject *parent = nullptr);
//     ~CalculationModule();

//     void performCalculations(ColumnData& column);
//     std::vector <CalculationResults> fetchResults();
//     std::vector <std::vector <std::pair<int, QString>>> fetchMessages();

// private:
//     std::vector <CalculationResults> results;
//     std::vector <std::vector <std::pair<int, QString>>> messages;
//     std::vector <std::pair<int, QString>> message;

//     void newInitData(ColumnData& column, SectionData& section, WeirData& weir);
//     void nullData();
//     void handleError (const QString& errorMessage, int errorLevel);

// };

// #include "calculationmodule.h"
// #include <QDebug>

// bool CalculationModule::checkInitData()
// {
//     // geometryData
//     if (geometryData["holeDiameter"] < 0.005 || geometryData["holeDiameter"] > 0.025) {
//         handleError ("Ошибка во входных данных - диаметр отверстия.", 2);
//         handleError ("Поддерживаемые значения диаметра отверстия от 0.005м до 0.025м.", 0);
//         return false;
//     }
//     if (geometryData["platesDistance"] < 500 || geometryData["platesDistance"] > 800) {
//         handleError ("Ошибка во входных данных - расстояние между тарелками.", 2);
//         handleError ("Поддерживаемые значения расстояния между тарелками от 500мм до 800мм.", 0);
//         return false;
//     }

//     if (typeData["calcMode"] == "Поверочный") {
//         // Проверка тех значений, что дает поверочный рассчёт
//         if (geometryData["columnDiameter"] <= 0.0 || geometryData["columnDiameter"] > 3.6) {
//             handleError ("Ошибка во входных данных - диаметр колонны.", 2);
//             handleError ("Поддерживаемые значения диаметра колонны от 1м до 3.6м.", 0);
//             return false;
//         }
//         if (geometryData["perimeter"] <= 0) {
//             handleError ("Ошибка во входных данных - периметр слива.", 2);
//             return false;
//         }
//         if (geometryData["widthOverflow"] <= 0) {
//             handleError ("Ошибка во входных данных - ширина перелива.", 2);
//             return false;
//         }
//         if (geometryData["workingArea"] <= 0) {
//             handleError ("Ошибка во входных данных - рабочая площадь тарелки.", 2);
//             return false;
//         }

//         if (geometryData["percentArea"] <= 0 || geometryData["percentArea"] >= 100) {
//             handleError ("Ошибка во входных данных - относительное свободное сечение колонны.", 2);
//             handleError ("Поддерживаемые значения относительного свободного сечения колонны от 0% до 100%.", 0);
//             return false;
//         }

//         double b_in = geometryData["perimeter"];
//         double S_in = geometryData["widthOverflow"];
//         double F_of_in = b_in * S_in / 2000.0;
//         double F_w_in = geometryData["workingArea"];
//         double D_in = geometryData["columnDiameter"];
//         double F_col_in = 0.785 * D_in * D_in;
//         if (F_of_in + F_w_in >= F_col_in) {
//             handleError ("Ошибка. Сумма сечения перелива и рабочей площади тарелки должна быть меньше полного сечения колонны.", 2);
//             handleError ("Проверьте корректность входных данных - диаметр колонны, периметр слива, ширина перелива, рабочая площадь тарелки.", 0);
//             return false;
//         }
//     }

//     // fluidsData
//     if (weirData["liquidLoad"] <= 0) {
//         handleError ("Ошибка во входных данных - нагрузка по жидкости.", 2);
//         return false;
//     }
//     if (weirData["steamLoad"] <= 0) {
//         handleError ("Ошибка во входных данных - нагрузка по пару.", 2);
//         return false;
//     }

//     if (weirData["liquidDensity"] <= 0) {
//         handleError ("Ошибка во входных данных - плотность жидкости.", 2);
//         return false;
//     }
//     if (weirData["steamDensity"] <= 0) {
//         handleError ("Ошибка во входных данных - плотность пара.", 2);
//         return false;
//     }
//     if (weirData["liquidSurfaceTension"] <= 0) {
//         handleError ("Ошибка во входных данных - поверхностное натяжение жидкости.", 2);
//         return false;
//     }

//     if (fluidsData["liquidFlow"] <= 0) {
//         handleError ("Ошибка во входных данных - расход жидкости на единицу длины сливной планки.", 2);
//         return false;
//     }
//     if (!(fluidsData["foamingCoeff"] == 0.9 || fluidsData["foamingCoeff"] == 0.85 || fluidsData["foamingCoeff"] == 0.75)) {
//         handleError ("Ошибка во входных данных - коэффициент вспениваемости.", 2);
//         handleError ("Поддерживаемые значения коэффициента вспениваемости: 0.9, 0.85, 0.75.", 0);
//         return false;
//     }

//     //constantsData
//     if (constantsData["overflowBarHeight"] <= 0) {
//         handleError ("Ошибка во входных данных - высота переливной планки.", 2);
//         return false;
//     }
//     if (constantsData["boltHeight"] <= 0) {
//         handleError ("Ошибка во входных данных - высота затворной планки.", 2);
//         return false;
//     }
//     if (constantsData["flowCoeff"] <= 0) {
//         handleError ("Ошибка во входных данных - коэффициент расхода.", 2);
//         return false;
//     }
//     // if (constantsData["dryResistCoeff"] <= 0) {
//     //     handleError ("Ошибка во входных данных - коэффициент сопротивления сухой тарелки.", 2);
//     //     return false;
//     // }
//     if (constantsData["overflowResistCoeff"] <= 0) {
//         handleError ("Ошибка во входных данных - коэффициент сопротивления перелива.", 2);
//         return false;
//     }
//     if (constantsData["occupiedAreaCoeff"] <= 0) {
//         handleError ("Ошибка во входных данных - коэффициент площади опорных конструкций тарелки.", 2);
//         return false;
//     }
//     if (constantsData["reliabilityCoeff"] <= 0 || constantsData["reliabilityCoeff"] > 1) {
//         handleError ("Ошибка во входных данных - коэффициент надежности.", 2);
//         return false;
//     }
//     if (constantsData["reserveCoeff"] <= 0 || constantsData["reserveCoeff"] > 1) {
//         handleError ("Ошибка во входных данных - коэффициент запаса для относительного свободного сечения колонны.", 2);
//         return false;
//     }
//     return true;
// }

// void CalculationModule::performCalculations(ColumnData& column)
// {
//     results.clear();
//     messages.clear();

//     for (auto& section : column.sections)
//     {
//         for (auto& weir : section.weirs)
//         {
//             CalculationResults result;
//             nullData();
//             newInitData(column, section, weir);

//             if (calculateColumnDiameterData())
//                 if (calculateColumnSectionData())
//                     if (calculateWeirHydrResistData())
//                         if (calculateOverflowDeviceData()) {
//                             calculateCheckFlags();
//                             if (section.calcType == "Поверочный") calculateVerificationFlags();
//                         }

//             result.weirName = weir.name;
//             {
//                 result.loadFactor = columnDiameterResults["loadFactor"];
//                 result.loadCoeff = columnDiameterResults["loadCoeff"];
//                 result.foamedRelativeDensity = columnDiameterResults["foamedRelativeDensity"];
//                 result.maxGasSpeed = columnDiameterResults["maxGasSpeed"];
//                 result.workingPlateArea_diameter = columnDiameterResults["workingPlateArea"];
//                 result.perimeter = columnDiameterResults["perimeter"];
//                 result.perimeterTable = columnDiameterResults["perimeterTable"];
//                 result.width = columnDiameterResults["width"];
//                 result.crossSection = columnDiameterResults["crossSection"];
//                 result.freeColumnSection = columnDiameterResults["freeColumnSection"];
//                 result.columnDiameter = columnDiameterResults["columnDiameter"];
//                 result.columnDiameterTable = columnDiameterResults["columnDiameterTable"];
//                 result.acceptedPerimeter = columnDiameterResults["acceptedPerimeter"];
//                 result.acceptedWidth = columnDiameterResults["acceptedWidth"];
//                 result.acceptedCrossSection = columnDiameterResults["acceptedCrossSection"];
//             }
//             {
//                 result.workingPlateArea_section = columnSectionResults["workingPlateArea"];
//                 result.workingGasSpeed = columnSectionResults["workingGasSpeed"];
//                 result.liquidConsumptionPerUnit = columnSectionResults["liquidConsumptionPerUnit"];
//                 result.stableRangeOperation = columnSectionResults["stableRangeOperation"];
//                 result.relativeFreePlateSection = columnSectionResults["relativeFreePlateSection"];
//                 result.areaColumn = columnSectionResults["areaColumn"];
//                 result.columnSectionGasSpeed = columnSectionResults["columnSectionGasSpeed"];
//                 result.calcRelativeFreeSection = columnSectionResults["calcRelativeFreeSection"];
//                 result.weirHoleArea = columnSectionResults["weirHoleArea"];
//                 result.acceptedRelativeColumnSection = columnSectionResults["acceptedRelativeColumnSection"];
//                 result.liquidHoleSpeed = columnSectionResults["liquidHoleSpeed"];
//                 result.minSteamHoleSpeed = columnSectionResults["minSteamHoleSpeed"];
//             }
//             {
//                 result.liquidDrainPlate_speed = weirHydrResistResults["liquidDrainPlate_speed"];
//                 result.steamHoleSpeed = weirHydrResistResults["steamHoleSpeed"];
//                 result.liquidDrainPlate = weirHydrResistResults["liquidDrainPlate"];
//                 result.minGasHoleSpeed = weirHydrResistResults["minGasHoleSpeed"];
//                 result.dryPlateResist = weirHydrResistResults["dryPlateResist"];
//                 result.gasFlowLoss = weirHydrResistResults["gasFlowLoss"];
//                 result.totalPressureDrop = weirHydrResistResults["totalPressureDrop"];
//                 result.foamedLayerHeight_weir = weirHydrResistResults["foamedLayerHeight"];
//                 result.nonFoamedLayerHeight = weirHydrResistResults["nonFoamedLayerHeight"];
//             }
//             {
//                 result.fluidMovementResist = overflowDeviceResults["fluidMovementResist"];
//                 result.passesNumberCoeff = overflowDeviceResults["passesNumberCoeff"];
//                 result.liquidAboveDrainPlate = overflowDeviceResults["liquidAboveDrainPlate"];
//                 result.lightLiquidHeight = overflowDeviceResults["lightLiquidHeight"];
//                 result.foamedLayerHeight_device = overflowDeviceResults["foamedLayerHeight"];
//                 result.overflowDeviceHeight = overflowDeviceResults["overflowDeviceHeight"];
//             }
//             {
//                 result.condition_foamedHeight = checkFlags["foamedHeight"];
//                 result.condition_deviceHeight = checkFlags["deviceHeight"];
//                 result.condition_normalWork = checkFlags["normalWork"];
//                 result.condition_overflowDevice = checkFlags["overflowDevice"];
//                 result.condition_weirWork = checkFlags["weirWork"];
//                 result.condition_weirDistance = checkFlags["weirDistance"];
//                 result.condition_gasSpeed = checkFlags["gasSpeed"];
//                 result.condition_liquidFlow = checkFlags["liquidFlow"];
//                 result.condition_gasHoleSpeed = checkFlags["gasHoleSpeed"];
//             }
//             {
//                 result.active = verificationFlags["active"];
//                 result.verification_columnDiameter = verificationFlags["columnDiameter"];
//                 result.verification_perimeter = verificationFlags["perimeter"];
//                 result.verification_crossSection = verificationFlags["crossSection"];
//                 result.verification_workingPlateArea = verificationFlags["workingPlateArea"];
//                 result.verification_relativeColumnSection = verificationFlags["relativeColumnSection"];
//             }
//             if (section.calcType == "Поверочный") result.active = true;

//             results.push_back(result);
//             messages.push_back(message);
//         }
//     }
// }

// std::vector<CalculationResults> CalculationModule::fetchResults()
// {
//     return results;
// }

// std::vector<std::vector<std::pair<int, QString>>> CalculationModule::fetchMessages()
// {
//     return messages;
// }

// void CalculationModule::newInitData(ColumnData& column, SectionData& section, WeirData& weir)
// {
//     weirName = weir.name;
//     weirData["liquidLoad"] = weir.liquidLoad;
//     weirData["steamLoad"] = weir.steamLoad;
//     weirData["liquidDensity"] = weir.liquidDensity;
//     weirData["steamDensity"] = weir.steamDensity;
//     weirData["liquidSurfaceTension"] = weir.liquidSurfaceTension;

//     geometryData["holeDiameter"] = section.holeDiameter;
//     geometryData["platesDistance"] = section.weirDistance;
//     geometryData["passesNumber"] = section.passesNumber;

//     if (section.calcType == "Поверочный")
//     {
//         typeData["calcType"] = "Поверочный";
//         geometryData["summaryArea"] = section.summaryArea;
//         geometryData["columnDiameter"] = section.columnDiameter;
//         geometryData["perimeter"] = section.perimeter;
//         geometryData["widthOverflow"] = section.widthOverflow;
//         geometryData["workingArea"] = section.workingArea;
//         geometryData["percentArea"] = section.percentArea;
//     }
//     else typeData["calcType"] = "Проектный";

//     fluidsData["foamingCoeff"] = column.foamingCoeff;
//     fluidsData["liquidFlow"] = column.liquidFlow;

//     constantsData["reliabilityCoeff"] = column.reliabilityCoeff;
//     constantsData["occupiedAreaCoeff"] = column.occupiedAreaCoeff;
//     constantsData["overflowBarHeight"] = column.overflowBarHeight;
//     constantsData["reserveCoeff"] = column.reserveCoeff;
//     constantsData["flowCoeff"] = column.flowCoeff;

//     constantsData["dryResistCoeff_speed"] = 1.8;
//     if (weir.weirWidth == 0.00635) constantsData["dryResistCoeff_resist"] = 1.81;
//     else if (weir.weirWidth == 0.00635) constantsData["dryResistCoeff_resist"] = 1.80;
//     else if (weir.weirWidth == 0.002642) constantsData["dryResistCoeff_resist"] = 1.79;
//     else constantsData["dryResistCoeff_resist"] = 1.77;

//     constantsData["boltHeight"] = column.boltHeight;
//     constantsData["overflowResistCoeff"] = column.overflowResistCoeff;
// }

// void CalculationModule::nullData()
// {
//     message.clear();
//     {
//         columnDiameterResults["loadFactor"] = std::numeric_limits<double>::lowest();
//         columnDiameterResults["loadCoeff"] = std::numeric_limits<double>::lowest();
//         columnDiameterResults["foamedRelativeDensity"] = std::numeric_limits<double>::lowest();
//         columnDiameterResults["maxGasSpeed"] = std::numeric_limits<double>::lowest();
//         columnDiameterResults["workingPlateArea"] = std::numeric_limits<double>::lowest();
//         columnDiameterResults["perimeter"] = std::numeric_limits<double>::lowest();
//         columnDiameterResults["perimeterTable"] = std::numeric_limits<double>::lowest();
//         columnDiameterResults["width"] = std::numeric_limits<double>::lowest();
//         columnDiameterResults["crossSection"] = std::numeric_limits<double>::lowest();
//         columnDiameterResults["freeColumnSection"] = std::numeric_limits<double>::lowest();
//         columnDiameterResults["columnDiameter"] = std::numeric_limits<double>::lowest();
//         columnDiameterResults["columnDiameterTable"] = std::numeric_limits<double>::lowest();
//         columnDiameterResults["acceptedPerimeter"] = std::numeric_limits<double>::lowest();
//         columnDiameterResults["acceptedWidth"] = std::numeric_limits<double>::lowest();
//         columnDiameterResults["acceptedCrossSection"] = std::numeric_limits<double>::lowest();
//     }
//     {
//         columnSectionResults["workingPlateArea"] = std::numeric_limits<double>::lowest();
//         columnSectionResults["workingGasSpeed"] = std::numeric_limits<double>::lowest();

//         columnSectionResults["liquidConsumptionPerUnit_min"] = std::numeric_limits<double>::lowest();
//         columnSectionResults["liquidConsumptionPerUnit_max"] = std::numeric_limits<double>::lowest();

//         // Существует Лв макс и Лв мин - для целостности кода я пока оставлю только Лв макс
//         columnSectionResults["liquidConsumptionPerUnit"] = std::numeric_limits<double>::lowest();
//         columnSectionResults["stableRangeOperation"] = std::numeric_limits<double>::lowest();
//         columnSectionResults["relativeFreePlateSection"] = std::numeric_limits<double>::lowest();
//         columnSectionResults["areaColumn"] = std::numeric_limits<double>::lowest();
//         columnSectionResults["columnSectionGasSpeed"] = std::numeric_limits<double>::lowest();
//         columnSectionResults["calcRelativeFreeSection"] = std::numeric_limits<double>::lowest();
//         columnSectionResults["weirHoleArea"] = std::numeric_limits<double>::lowest();
//         columnSectionResults["acceptedRelativeColumnSection"] = std::numeric_limits<double>::lowest();
//         columnSectionResults["liquidHoleSpeed"] = std::numeric_limits<double>::lowest();
//         columnSectionResults["minSteamHoleSpeed"] = std::numeric_limits<double>::lowest();
//     }
//     {
//         weirHydrResistResults["liquidDrainPlate_speed"] = std::numeric_limits<double>::lowest();
//         weirHydrResistResults["steamHoleSpeed"] = std::numeric_limits<double>::lowest();
//         weirHydrResistResults["liquidDrainPlate"] = std::numeric_limits<double>::lowest();
//         weirHydrResistResults["minGasHoleSpeed"] = std::numeric_limits<double>::lowest();
//         weirHydrResistResults["dryPlateResist"] = std::numeric_limits<double>::lowest();
//         weirHydrResistResults["gasFlowLoss"] = std::numeric_limits<double>::lowest();
//         weirHydrResistResults["totalPressureDrop"] = std::numeric_limits<double>::lowest();
//         weirHydrResistResults["foamedLayerHeight"] = std::numeric_limits<double>::lowest();
//         weirHydrResistResults["nonFoamedLayerHeight"] = std::numeric_limits<double>::lowest();
//     }
//     {
//         overflowDeviceResults["fluidMovementResist"] = std::numeric_limits<double>::lowest();
//         overflowDeviceResults["passesNumberCoeff"] = std::numeric_limits<double>::lowest();
//         overflowDeviceResults["liquidAboveDrainPlate"] = std::numeric_limits<double>::lowest();
//         overflowDeviceResults["lightLiquidHeight"] = std::numeric_limits<double>::lowest();
//         overflowDeviceResults["foamedLayerHeight"] = std::numeric_limits<double>::lowest();
//         overflowDeviceResults["overflowDeviceHeight"] = std::numeric_limits<double>::lowest();
//     }
//     {
//         checkFlags["foamedHeight"] = false;
//         checkFlags["deviceHeight"] = false;
//         checkFlags["normalWork"] = false;
//         checkFlags["overflowDevice"] = false;
//         checkFlags["weirWork"] = false;
//         checkFlags["weirDistance"] = false;
//         checkFlags["gasSpeed"] = false;
//         checkFlags["liquidFlow"] = false;
//         checkFlags["gasHoleSpeed"] = false;
//     }
//     {
//         verificationFlags["active"] = false;
//         verificationFlags["columnDiameter"] = false;
//         verificationFlags["perimeter"] = false;
//         verificationFlags["crossSection"] = false;
//         verificationFlags["workingPlateArea"] = false;
//         verificationFlags["relativeColumnSection"] = false;
//     }
// }

// void CalculationModule::handleError (const QString& errorMessage, int errorLevel)
// {
//     message.push_back({errorLevel, weirName + " - " + errorMessage});
// }

// CalculationModule::CalculationModule(QObject *parent)
//     : QObject{parent}
// {}

// CalculationModule::~CalculationModule() {}

#endif // CALCULATIONMODULE_H
