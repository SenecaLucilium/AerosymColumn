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

//     QString weirName;
//     std::unordered_map<QString, QString> typeData;
//     std::unordered_map<QString, double> geometryData;
//     std::unordered_map<QString, double> fluidsData;
//     std::unordered_map<QString, double> constantsData;
//     std::unordered_map<QString, double> weirData;
//     void newInitData(ColumnData& column, SectionData& section, WeirData& weir);
//     void nullData();
//     void handleError (const QString& errorMessage, int errorLevel);

//     bool checkInitData();

//     std::unordered_map<QString, double> columnDiameterResults;
//     bool calculateColumnDiameterData();
//     std::unordered_map<QString, double> columnSectionResults;
//     bool calculateColumnSectionData();
//     std::unordered_map<QString, double> weirHydrResistResults;
//     bool calculateWeirHydrResistData();
//     std::unordered_map<QString, double> overflowDeviceResults;
//     bool calculateOverflowDeviceData();
//     std::unordered_map<QString, bool> checkFlags;
//     void calculateCheckFlags();
//     std::unordered_map<QString, bool> verificationFlags;
//     void calculateVerificationFlags();

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

// bool CalculationModule::calculateColumnDiameterData()
// {
//     double L_max = weirData["liquidLoad"];
//     double G_max = weirData["steamLoad"];
//     double rho_liquid = weirData["liquidDensity"];
//     double rho_vapor = weirData["steamDensity"];
//     double H = geometryData["platesDistance"];
//     double K_foam = fluidsData["foamingCoeff"];
//     double K_r = constantsData["reliabilityCoeff"];
//     double L1_v = fluidsData["liquidFlow"];
//     double K2 = constantsData["occupiedAreaCoeff"];
//     double N = geometryData["passesNumber"];

//     double C = L_max / G_max * std::sqrt(rho_vapor / rho_liquid); // Фактор нагрузки
//     columnDiameterResults["loadFactor"] = C;
//     if (C < 0.001 || C > 4.0) {
//         handleError ("Ошибка при вычислении фактора нагрузки.", 1);
//         handleError ("Проверьте корректность входных данных по максимальным нагрузкам и плотностям жидкости и пара.", 0);
//         return false;
//     }

//     double K1 = get_K1(H, C); // Коэффициент нагрузки
//     columnDiameterResults["loadCoeff"] = K1;
//     if (K1 <= 0) {
//         handleError ("Ошибка при вычислении коэффициента нагрузки.", 1);
//         handleError ("Проверьте корректность значения расстояния между тарелками и фактора нагрузки.", 0);
//         return false;
//     }

//     double rho1_vapor = get_rho1_vapor(K_foam); // Плотность вспененной жидкости по отношению к исходной
//     columnDiameterResults["foamedRelativeDensity"] = rho1_vapor;
//     if (rho1_vapor <= 0) {
//         handleError ("Ошибка при вычислении плотности вспененной жидкости по отношению к исходной.", 1);
//         handleError ("Проверьте корректность значения коэффициента вспенивания.", 0);
//         return false;
//     }

//     double W_p_max = K_r * K1 * K_foam * std::sqrt((rho_liquid - rho_vapor) / rho_vapor); // Максимально-допустимая скорость газа
//     columnDiameterResults["maxGasSpeed"] = W_p_max;
//     if (W_p_max <= 0) {
//         handleError ("Ошибка при вычислении максимальной допустимой скорости газа.", 1);
//         return false;
//     }
//     double F1_w = G_max / 3600.0 / W_p_max / rho_vapor; // Расчетная рабочая площадь тарелки
//     columnDiameterResults["workingPlateArea"] = F1_w;

//     double b1 = L_max / L1_v / rho_liquid; // Периметр слива
//     columnDiameterResults["perimeter"] = b1;
//     if (b1 <= 0 || b1 > 24.70) {
//         handleError ("Ошибка при вычислении расчетного периметра слива.", 1);
//         handleError ("Проверьте входные данные по максимальной нагрузке жидкости, плотности жидкости и расхода жидкости на единицу длины сливной планки.", 0);
//         return false;
//     }
//     double b1r = get_table_b_from_calculated_b(b1); // округленный до ближайшего значения по таблице
//     columnDiameterResults["perimeterTable"] = b1r;
//     double S1 = get_S_from_table_b(b1r); // Ширина перелива
//     columnDiameterResults["width"] = S1;
//     if (S1 <= 0) {
//         handleError ("Ошибка при вычислении расчетной ширины перелива.", 1);
//         return false;
//     }
//     double F1_of = b1r * S1 / 2.0E3; // Сечение перелива
//     columnDiameterResults["crossSection"] = F1_of;

//     double F1_col = K2 * (F1_w + F1_of); // Расчетное свободное сечение колонны
//     columnDiameterResults["freeColumnSection"] = F1_col;
//     double D1 = 1.13 * std::sqrt(F1_col); // Расчетный диаметр колонны
//     columnDiameterResults["columnDiameter"] = D1;
//     if (D1 <= 0 || D1 > 3.6) {
//         handleError ("Ошибка при вычислении расчетного диаметра колонны.", 1);
//         handleError ("Проверьте расчетное свободное сечение колонны.", 0);
//         return false;
//     }
//     double D = get_table_D_from_calculated_D(D1); // по таблице
//     columnDiameterResults["columnDiameterTable"] = D;

//     double b = get_b_from_D_and_N(D, N); // Принятый периметр слива
//     double S = get_S_from_table_D(D); // Принятая ширина перелива
//     double F_of = b * S / 2.0E3; // Принятое сечение перелива
//     columnDiameterResults["acceptedPerimeter"] = b;
//     columnDiameterResults["acceptedWidth"] = S;
//     columnDiameterResults["acceptedCrossSection"] = F_of;

//     return true;
// }

// bool CalculationModule::calculateColumnSectionData()
// {
//     double D = columnDiameterResults["columnDiameterTable"];
//     double b = columnDiameterResults["acceptedPerimeter"];
//     double d = geometryData["holeDiameter"];
//     double G_max = weirData["steamLoad"];
//     double G_min = weirData["steamLoad"];
//     double L_max = weirData["liquidLoad"];
//     double L_min = weirData["liquidLoad"];
//     double rho_vapor = weirData["steamDensity"];
//     double rho_liquid = weirData["liquidDensity"];
//     double sigma = weirData["liquidSurfaceTension"];
//     double h_p = constantsData["overflowBarHeight"];
//     double K_h = constantsData["reserveCoeff"];
//     double mu = constantsData["flowCoeff"];
//     double xi = constantsData["dryResistCoeff_speed"];
//     double g = 9.81;

//     double F_w = get_F_w_from_D_b_and_d(D, b, d); // Рабочая площадь тарелки
//     columnSectionResults["workingPlateArea"] = F_w;
//     if (F_w <= 0) {
//         handleError ("Ошибка при вычислении рабочей площади тарелки.", 1);
//         handleError ("Проверьте диаметр колонны, принятый периметр слива и диаметр отверстия.", 0);
//         return false;
//     }
//     double W_w = G_max / 3600.0 / rho_vapor / F_w; // Рабочая скорость газа в колонне
//     columnSectionResults["workingGasSpeed"] = W_w;

//     // Посмотреть на сноску у обнулений результатов ниже - ВАЖНО
//     double L_v = L_max / rho_liquid / b; // Расход жидкости на единицу длины сливной планки
//     columnSectionResults["liquidConsumptionPerUnit"] = L_v;

//     double L_v_max = L_max / rho_liquid / b;
//     columnSectionResults["liquidConsumptionPerUnit"] = L_v_max;
//     if (L_v_max > 50) {
//         handleError ("Предупреждение - слишком высокое значение расхода жидкости на единицу длины сливной планки.", 0);
//     }
//     double L_v_min = L_min / rho_liquid / b;
//     columnSectionResults["LiquidConsumptionPerUnit"] = L_v_min;
//     if (L_v_min < 2) {
//         handleError ("Предупреждение - слишком низкое значение расхода жидкости на единицу длины сливной планки.", 0);
//     }

//     double n = G_max / G_min; // Диапазон устойчивой работы тарелки
//     columnSectionResults["stableRangeOperation"] = n;
//     double F_fr = 1.6 * W_w / n * std::sqrt(rho_vapor) / (1.0 - std::sqrt(1.0 - 3.2E-3 * (h_p * 1000.0 * rho_liquid / 1000.0 + 3.2 * std::pow(L_v / n, 2.0 / 3.0) + 4.0 * sigma / d + 63.0))); // Относительное свободное сечение тарелки
//     columnSectionResults["relativeFreePlateSection"] = F_fr;
//     if (F_fr <= 0) {
//         handleError ("Ошибка при вычислении относительного свободного сечения тарелки.", 1);
//         return false;
//     }

//     double F_col = 0.785 * D * D; // Площадь колонны
//     columnSectionResults["areaColumn"] = F_col;
//     double W1_w = G_max / 3600.0 / rho_vapor / F_col; // Скорость газа в сечении колонны
//     columnSectionResults["columnSectionGasSpeed"] = W1_w;
//     double F1_col_fr = F_w * F_fr / F_col; // Расчетное относительное свободное сечение колонны
//     columnSectionResults["calcRelativeFreeSection"] = F1_col_fr;

//     double dh_vel = 3.1 * std::pow(L_min / rho_liquid / b, 2.0 / 3.0); // Подпор жидкости над сливной планкой (для опр скор)
//     if (dh_vel <= 0) {
//         handleError ("Ошибка при вычислении подпора жидкости над сливной планкой.", 1);
//         return false;
//     }
//     weirHydrResistResults["liquidDrainPlate_speed"] = dh_vel;

//     double t1 = G_min / (3600.0 * rho_vapor);
//     double t2 = L_min / (3600.0 * rho_liquid * mu * std::sqrt(2.0 * g * (h_p * 1000.0 + dh_vel) * 1.0E-3));
//     double t3 = std::sqrt(2.0 * rho_liquid * g * (h_p * 1000.0 + dh_vel) * 1.0E-3 / ((2.0 * xi + 1.0) * rho_vapor));
//     double F_h_max = t1 / t3 + t2;
//     double F_h = K_h * F_h_max; // Площадь отверстий тарелки
//     columnSectionResults["weirHoleArea"] = F_h;
//     if (F_h <= 0) {
//         handleError ("Ошибка при вычислении площади отверстий тарелки.", 1);
//         return false;
//     }

//     double F_col_fr = F_h / (F_col * 1.0E-2); // Принятое относительное сечение колонны
//     columnSectionResults["acceptedRelativeColumnSection"] = F_col_fr;

//     double W_h_liquid;
//     double W1_h_min;

//     if (typeData["calcType"] == "Поверочный")
//     {
//         double F_h_in = geometryData["summaryArea"];
//         W_h_liquid = L_min / 3600.0 / rho_liquid / F_h_in; // Скорость жидкости в отверстиях тарелки
//         W1_h_min = G_min / 3600.0 / rho_vapor / F_h_in; // Расчетная минимальная скорость газа в отверстиях тарелки
//     }
//     else {
//         W_h_liquid = L_min / 3600.0 / rho_liquid / F_h; // Скорость жидкости в отверстиях тарелки
//         W1_h_min = G_min / 3600.0 / rho_vapor / F_h; // Расчетная минимальная скорость газа в отверстиях тарелки
//     }
//     columnSectionResults["liquidHoleSpeed"] = W_h_liquid;
//     columnSectionResults["minSteamHoleSpeed"] = W1_h_min;

//     return true;
// }

// bool CalculationModule::calculateWeirHydrResistData()
// {
//     double mu = constantsData["flowCoeff"];
//     double xi_speed = constantsData["dryResistCoeff_speed"];
//     double xi_resist = constantsData["dryResistCoeff_resist"];
//     double g = 9.81;
//     double K_foam = fluidsData["foamingCoeff"];
//     double G_max = weirData["steamLoad"];
//     double rho_liquid = weirData["liquidDensity"];
//     double rho_vapor = weirData["steamDensity"];
//     double F_h = columnSectionResults["weirHoleArea"];
//     double L_v = columnSectionResults["liquidConsumptionPerUnit"];
//     double W_h_liquid = columnSectionResults["liquidHoleSpeed"];
//     double h_p = constantsData["overflowBarHeight"];
//     double dh_vel = weirHydrResistResults["liquidDrainPlate_speed"];

//     double W_h;

//     if (typeData["calcType"] == "Поверочный")
//     {
//         double F_h_in = geometryData["summaryArea"];
//         W_h = G_max / 3600.0 / rho_vapor / F_h_in; // Скорость газа в отверстиях тарелки
//     }
//     else {
//         W_h = G_max / 3600.0 / rho_vapor / F_h; // Скорость газа в отверстиях тарелки
//     }
//     weirHydrResistResults["steamHoleSpeed"] = W_h;

//     double dh = 3.1 * std::pow(L_v, 2.0 / 3.0); // Подпор жидкости над сливной планкой
//     weirHydrResistResults["liquidDrainPlate"] = dh;
//     double W_h_min = (1.0 - W_h_liquid / mu / std::sqrt(2.0 * g * (h_p * 1000.0 + dh_vel) * 1.0E-3)) * std::sqrt(2.0 * rho_liquid * g * (h_p * 1000.0 + dh_vel) * 1.0E-3 / (2.0 * xi_speed + 1.0) / rho_vapor); // Минимально допустимая скорость газа в отверстиях
//     weirHydrResistResults["minGasHoleSpeed"] = W_h_min;
//     if (W_h_min <= 0) {
//         handleError ("Ошибка при вычислении минимально допустимой скорости газа в отверстиях.", 1);
//         return false;
//     }

//     double dP_dry = xi_resist * W_h * W_h * rho_vapor / 2.0 / g; // Сопротивление сухой тарелки
//     weirHydrResistResults["dryPlateResist"] = dP_dry;
//     double dP_liquid = (h_p * 1000.0 + dh) * rho_liquid / 1000.0; // Потеря напора газового потока в слое жидкости на тарелке
//     weirHydrResistResults["gasFlowLoss"] = dP_liquid;
//     double dP = dP_dry + dP_liquid; // Общий перепад давления тарелки
//     weirHydrResistResults["totalPressureDrop"] = dP;

//     double H_f = 3.0 * dP_liquid / K_foam / (rho_liquid / 1000.0); // Высота вспененного слоя жидкости на тарелке
//     weirHydrResistResults["foamedLayerHeight"] = H_f;
//     double H_liquid = h_p * 1000.0 + dh; // Высота светлого слоя невспененной жидкости на тарелке
//     weirHydrResistResults["nonFoamedLayerHeight"] = H_liquid;

//     return true;
// }

// bool CalculationModule::calculateOverflowDeviceData()
// {
//     double D = columnDiameterResults["columnDiameterTable"];
//     double H = geometryData["platesDistance"];
//     double N = geometryData["passesNumber"];
//     double h_cp = constantsData["boltHeight"];
//     double rho_liquid = weirData["liquidDensity"];
//     double rho1_vapor = columnDiameterResults["foamedRelativeDensity"];
//     double xi_of = constantsData["overflowResistCoeff"];
//     double L_v = columnSectionResults["liquidConsumptionPerUnit"];
//     double dP = weirHydrResistResults["totalPressureDrop"];
//     double g = 9.81;
//     double a = 0.06;

//     double K = xi_of * rho_liquid / 2.0 / g;
//     double dP_liquid_of = K * std::pow(L_v / 3600.0 / a, 2.0); // Сопротивление движению жидкости в переливе
//     overflowDeviceResults["fluidMovementResist"] = dP_liquid_of;

//     double K3 = get_K3(N); // Коэффициент, зависящий от числа потоков на тарелке
//     overflowDeviceResults["passesNumberCoeff"] = K3;
//     double dh_cp = 3.1 * std::pow(L_v / K3, 2.0 / 3.0); // Подпор жидкости над затворной планкой
//     overflowDeviceResults["liquidAboveDrainPlate"] = dh_cp;

//     double h1 = dP_liquid_of / (rho_liquid / 1000.0) + h_cp + dh_cp + dP / (rho_liquid / 1000.0); // Высота слоя светлой жидкости в переливном устройстве
//     overflowDeviceResults["lightLiquidHeight"] = h1;
//     if (h1 < 0) {
//         handleError ("Ошибка при вычислении высоты слоя светлой жидкости в переливном устройстве.", 1);
//         return false;
//     }

//     double H1_of = 0.8 * h1 / rho1_vapor; // Высота вспененного слоя жидкости в переливном устройстве
//     overflowDeviceResults["foamedLayerHeight"] = H1_of;

//     double h = get_h(D, H); // Высота переливного устройства
//     overflowDeviceResults["overflowDeviceHeight"] = h;
//     if (h <= 0) {
//         handleError ("Ошибка при вычислении высоты переливного устройства.", 1);
//         handleError ("Проверьте корректность принятого диаметра колонны и расстояния между тарелками.", 0);
//         return false;
//     }

//     return true;
// }

// void CalculationModule::calculateCheckFlags()
// {
//     double H_f = weirHydrResistResults["foamedLayerHeight"];
//     double H = geometryData["platesDistance"];
//     if (H_f >= 0.9 * H) {
//         handleError ("Нужно принять большее расстояние между тарелками и повторить расчет.", 1);
//     }
//     else checkFlags["foamedHeight"] = true;

//     double h1 = overflowDeviceResults["lightLiquidHeight"];
//     double h = overflowDeviceResults["overflowDeviceHeight"];
//     if (h1 > h) {
//         handleError ("Необходимо увеличить диаметр колонны или уменьшить нагрузку на единицу длины слива и повторить расчет.", 1);
//     }
//     else checkFlags["deviceHeight"] = true;

//     double rho1_vapor = columnDiameterResults["foamedRelativeDensity"];
//     double H1_of = overflowDeviceResults["foamedLayerHeight"];
//     if (rho1_vapor > 0 && H_f + H1_of > 0.9 * (H + h)) {
//         handleError ("Нужно выбрать следующий больший размер расстояния между тарелками и повторить расчет.", 1);
//     }
//     else checkFlags["normalWork"] = true;

//     if (H1_of > h) {
//         handleError ("Провалена проверка условия нормальной работы переливного устройста.", 1);
//     }
//     else checkFlags["overflowDevice"] = true;

//     if (H - h < H_f) {
//         handleError ("Рекомендуется принять большее расстояние между тарелками.", 1);
//     }
//     else checkFlags["weirWork"] = true;

//     if (H - (H_f + h1) <= 50) {
//         handleError ("Провалена проверка на расстояние между тарелками.", 1);
//     }
//     else checkFlags["weirDistance"] = true;

//     double W_w = columnSectionResults["workingGasSpeed"];
//     double W_p_max = columnDiameterResults["maxGasSpeed"];
//     if (W_w >= W_p_max) {
//         handleError ("Провалена провервка условия на скорость газа.", 1);
//     }
//     else checkFlags["gasSpeed"] = true;

//     double L_v = columnSectionResults["liquidConsumptionPerUnit"];
//     double L1_v = fluidsData["liquidFlow"];
//     if (L_v >= L1_v) {
//         handleError ("Провалена проверка расхода жидкости.", 1);
//     }
//     else checkFlags["liquidFlow"] = true;

//     double W1_h_min = columnSectionResults["minSteamHoleSpeed"];
//     double W_h_min = weirHydrResistResults["minGasHoleSpeed"];
//     if (W1_h_min < W_h_min) {
//         handleError ("Провалена проверка скорости газа в отверстиях тарелки.", 1);
//     }
//     else checkFlags["gasHoleSpeed"] = true;
// }

// void CalculationModule::calculateVerificationFlags()
// {
//     verificationFlags["active"] = true;

//     double D1 = columnDiameterResults["columnDiameter"];
//     double D_in = geometryData["columnDiameter"];
//     if (D1 > D_in) {
//         handleError ("Ошибка. Фактический диаметр меньше рекомендуемого.", 1);
//     }
//     else verificationFlags["columnDiameter"] = true;

//     double b = columnDiameterResults["acceptedPerimeter"];
//     double b_in = geometryData["perimeter"];
//     if (b > b_in) {
//         handleError ("Ошибка. Фактический периметр слива меньше рекомендуемого.", 1);
//     }
//     else verificationFlags["perimeter"] = true;

//     double F_of = columnDiameterResults["acceptedCrossSection"];
//     // double F_of_in = columnDiameterData["crossSectionOverflow"]; ???
//     double S_in = geometryData["widthOverflow"];
//     double F_of_in = b_in * S_in / 2000.0;
//     if (F_of > F_of_in) {
//         handleError ("Ошибка. Фактическое сечение перелива меньше рекомендуемого.", 1);
//     }
//     else verificationFlags["crossSection"] = true;

//     double F_w = columnSectionResults["workingPlateArea"];
//     double F_w_in = geometryData["workingArea"];
//     if (F_w > F_w_in) {
//         handleError ("Ошибка. Фактическая рабочая площадь тарелки меньше рекомендуемой.", 1);
//     }
//     else verificationFlags["workingPlateArea"] = true;

//     double F_col_fr = columnSectionResults["acceptedRelativeColumnSection"];
//     double F_col_fr_in = geometryData["percentArea"];
//     if (F_col_fr < F_col_fr_in) {
//         handleError ("Ошибка. Фактическое относительное свободное сечение колонны больше рекомендуемого.", 1);
//     }
//     else verificationFlags["relativeColumnSection"] = true;
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
