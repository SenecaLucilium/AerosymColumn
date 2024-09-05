#include "calculationmodule.h"
#include <QDebug>

bool CalculationModule::checkInitData()
{
    // geometryData
    if (geometryData["holeDiameter"] < 0.005 || geometryData["holeDiameter"] > 0.025) {
        handleError ("Ошибка во входных данных - диаметр отверстия.", 2);
        handleError ("Поддерживаемые значения диаметра отверстия от 0.005м до 0.025м.", 0);
        return false;
    }
    if (geometryData["platesDistance"] < 500 || geometryData["platesDistance"] > 800) {
        handleError ("Ошибка во входных данных - расстояние между тарелками.", 2);
        handleError ("Поддерживаемые значения расстояния между тарелками от 500мм до 800мм.", 0);
        return false;
    }

    if (typeData["calcMode"] == "Поверочный") {
        // Проверка тех значений, что дает поверочный рассчёт
        if (geometryData["columnDiameter"] <= 0.0 || geometryData["columnDiameter"] > 3.6) {
            handleError ("Ошибка во входных данных - диаметр колонны.", 2);
            handleError ("Поддерживаемые значения диаметра колонны от 1м до 3.6м.", 0);
            return false;
        }
        if (geometryData["perimeter"] <= 0) {
            handleError ("Ошибка во входных данных - периметр слива.", 2);
            return false;
        }
        if (geometryData["widthOverflow"] <= 0) {
            handleError ("Ошибка во входных данных - ширина перелива.", 2);
            return false;
        }
        if (geometryData["workingArea"] <= 0) {
            handleError ("Ошибка во входных данных - рабочая площадь тарелки.", 2);
            return false;
        }

        if (geometryData["percentArea"] <= 0 || geometryData["percentArea"] >= 100) {
            handleError ("Ошибка во входных данных - относительное свободное сечение колонны.", 2);
            handleError ("Поддерживаемые значения относительного свободного сечения колонны от 0% до 100%.", 0);
            return false;
        }

        double b_in = geometryData["perimeter"];
        double S_in = geometryData["widthOverflow"];
        double F_of_in = b_in * S_in / 2000.0;
        double F_w_in = geometryData["workingArea"];
        double D_in = geometryData["columnDiameter"];
        double F_col_in = 0.785 * D_in * D_in;
        if (F_of_in + F_w_in >= F_col_in) {
            handleError ("Ошибка. Сумма сечения перелива и рабочей площади тарелки должна быть меньше полного сечения колонны.", 2);
            handleError ("Проверьте корректность входных данных - диаметр колонны, периметр слива, ширина перелива, рабочая площадь тарелки.", 0);
            return false;
        }
    }

    // fluidsData
    if (weirData["liquidLoad"] <= 0) {
        handleError ("Ошибка во входных данных - нагрузка по жидкости.", 2);
        return false;
    }
    if (weirData["steamLoad"] <= 0) {
        handleError ("Ошибка во входных данных - нагрузка по пару.", 2);
        return false;
    }

    if (weirData["liquidDensity"] <= 0) {
        handleError ("Ошибка во входных данных - плотность жидкости.", 2);
        return false;
    }
    if (weirData["steamDensity"] <= 0) {
        handleError ("Ошибка во входных данных - плотность пара.", 2);
        return false;
    }
    if (weirData["liquidSurfaceTension"] <= 0) {
        handleError ("Ошибка во входных данных - поверхностное натяжение жидкости.", 2);
        return false;
    }

    if (fluidsData["liquidFlow"] <= 0) {
        handleError ("Ошибка во входных данных - расход жидкости на единицу длины сливной планки.", 2);
        return false;
    }
    if (!(fluidsData["foamingCoeff"] == 0.9 || fluidsData["foamingCoeff"] == 0.85 || fluidsData["foamingCoeff"] == 0.75)) {
        handleError ("Ошибка во входных данных - коэффициент вспениваемости.", 2);
        handleError ("Поддерживаемые значения коэффициента вспениваемости: 0.9, 0.85, 0.75.", 0);
        return false;
    }

    //constantsData
    if (constantsData["overflowBarHeight"] <= 0) {
        handleError ("Ошибка во входных данных - высота переливной планки.", 2);
        return false;
    }
    if (constantsData["boltHeight"] <= 0) {
        handleError ("Ошибка во входных данных - высота затворной планки.", 2);
        return false;
    }
    if (constantsData["flowCoeff"] <= 0) {
        handleError ("Ошибка во входных данных - коэффициент расхода.", 2);
        return false;
    }
    // if (constantsData["dryResistCoeff"] <= 0) {
    //     handleError ("Ошибка во входных данных - коэффициент сопротивления сухой тарелки.", 2);
    //     return false;
    // }
    if (constantsData["overflowResistCoeff"] <= 0) {
        handleError ("Ошибка во входных данных - коэффициент сопротивления перелива.", 2);
        return false;
    }
    if (constantsData["occupiedAreaCoeff"] <= 0) {
        handleError ("Ошибка во входных данных - коэффициент площади опорных конструкций тарелки.", 2);
        return false;
    }
    if (constantsData["reliabilityCoeff"] <= 0 || constantsData["reliabilityCoeff"] > 1) {
        handleError ("Ошибка во входных данных - коэффициент надежности.", 2);
        return false;
    }
    if (constantsData["reserveCoeff"] <= 0 || constantsData["reserveCoeff"] > 1) {
        handleError ("Ошибка во входных данных - коэффициент запаса для относительного свободного сечения колонны.", 2);
        return false;
    }
    return true;
}

bool CalculationModule::calculateColumnDiameterData()
{
    double L_max = weirData["liquidLoad"];
    double G_max = weirData["steamLoad"];
    double rho_liquid = weirData["liquidDensity"];
    double rho_vapor = weirData["steamDensity"];
    double H = geometryData["platesDistance"];
    double K_foam = fluidsData["foamingCoeff"];
    double K_r = constantsData["reliabilityCoeff"];
    double L1_v = fluidsData["liquidFlow"];
    double K2 = constantsData["occupiedAreaCoeff"];
    double N = geometryData["passesNumber"];

    double C = L_max / G_max * std::sqrt(rho_vapor / rho_liquid); // Фактор нагрузки
    columnDiameterResults["loadFactor"] = C;
    if (C < 0.001 || C > 4.0) {
        handleError ("Ошибка при вычислении фактора нагрузки.", 1);
        handleError ("Проверьте корректность входных данных по максимальным нагрузкам и плотностям жидкости и пара.", 0);
        return false;
    }

    double K1 = get_K1(H, C); // Коэффициент нагрузки
    columnDiameterResults["loadCoeff"] = K1;
    if (K1 <= 0) {
        handleError ("Ошибка при вычислении коэффициента нагрузки.", 1);
        handleError ("Проверьте корректность значения расстояния между тарелками и фактора нагрузки.", 0);
        return false;
    }

    double rho1_vapor = get_rho1_vapor(K_foam); // Плотность вспененной жидкости по отношению к исходной
    columnDiameterResults["foamedRelativeDensity"] = rho1_vapor;
    if (rho1_vapor <= 0) {
        handleError ("Ошибка при вычислении плотности вспененной жидкости по отношению к исходной.", 1);
        handleError ("Проверьте корректность значения коэффициента вспенивания.", 0);
        return false;
    }

    double W_p_max = K_r * K1 * K_foam * std::sqrt((rho_liquid - rho_vapor) / rho_vapor); // Максимально-допустимая скорость газа
    columnDiameterResults["maxGasSpeed"] = W_p_max;
    if (W_p_max <= 0) {
        handleError ("Ошибка при вычислении максимальной допустимой скорости газа.", 1);
        return false;
    }
    double F1_w = G_max / 3600.0 / W_p_max / rho_vapor; // Расчетная рабочая площадь тарелки
    columnDiameterResults["workingPlateArea"] = F1_w;

    double b1 = L_max / L1_v / rho_liquid; // Периметр слива
    columnDiameterResults["perimeter"] = b1;
    if (b1 <= 0 || b1 > 24.70) {
        handleError ("Ошибка при вычислении расчетного периметра слива.", 1);
        handleError ("Проверьте входные данные по максимальной нагрузке жидкости, плотности жидкости и расхода жидкости на единицу длины сливной планки.", 0);
        return false;
    }
    double b1r = get_table_b_from_calculated_b(b1); // округленный до ближайшего значения по таблице
    columnDiameterResults["perimeterTable"] = b1r;
    double S1 = get_S_from_table_b(b1r); // Ширина перелива
    columnDiameterResults["width"] = S1;
    if (S1 <= 0) {
        handleError ("Ошибка при вычислении расчетной ширины перелива.", 1);
        return false;
    }
    double F1_of = b1r * S1 / 2.0E3; // Сечение перелива
    columnDiameterResults["crossSection"] = F1_of;

    double F1_col = K2 * (F1_w + F1_of); // Расчетное свободное сечение колонны
    columnDiameterResults["freeColumnSection"] = F1_col;
    double D1 = 1.13 * std::sqrt(F1_col); // Расчетный диаметр колонны
    columnDiameterResults["columnDiameter"] = D1;
    if (D1 <= 0 || D1 > 3.6) {
        handleError ("Ошибка при вычислении расчетного диаметра колонны.", 1);
        handleError ("Проверьте расчетное свободное сечение колонны.", 0);
        return false;
    }
    double D = get_table_D_from_calculated_D(D1); // по таблице
    columnDiameterResults["columnDiameterTable"] = D;

    double b = get_b_from_D_and_N(D, N); // Принятый периметр слива
    double S = get_S_from_table_D(D); // Принятая ширина перелива
    double F_of = b * S / 2.0E3; // Принятое сечение перелива
    columnDiameterResults["acceptedPerimeter"] = b;
    columnDiameterResults["acceptedWidth"] = S;
    columnDiameterResults["acceptedCrossSection"] = F_of;

    return true;
}

bool CalculationModule::calculateColumnSectionData()
{
    double D = columnDiameterResults["columnDiameterTable"];
    double b = columnDiameterResults["acceptedPerimeter"];
    double d = geometryData["holeDiameter"];
    double G_max = weirData["steamLoad"];
    double G_min = weirData["steamLoad"];
    double L_max = weirData["liquidLoad"];
    double L_min = weirData["liquidLoad"];
    double rho_vapor = weirData["steamDensity"];
    double rho_liquid = weirData["liquidDensity"];
    double sigma = weirData["liquidSurfaceTension"];
    double h_p = constantsData["overflowBarHeight"];
    double K_h = constantsData["reserveCoeff"];
    double mu = constantsData["flowCoeff"];
    double xi = constantsData["dryResistCoeff_speed"];
    double g = 9.81;

    double F_w = get_F_w_from_D_b_and_d(D, b, d); // Рабочая площадь тарелки
    columnSectionResults["workingPlateArea"] = F_w;
    if (F_w <= 0) {
        handleError ("Ошибка при вычислении рабочей площади тарелки.", 1);
        handleError ("Проверьте диаметр колонны, принятый периметр слива и диаметр отверстия.", 0);
        return false;
    }
    double W_w = G_max / 3600.0 / rho_vapor / F_w; // Рабочая скорость газа в колонне
    columnSectionResults["workingGasSpeed"] = W_w;

    // Посмотреть на сноску у обнулений результатов ниже - ВАЖНО
    double L_v = L_max / rho_liquid / b; // Расход жидкости на единицу длины сливной планки
    columnSectionResults["liquidConsumptionPerUnit"] = L_v;

    double L_v_max = L_max / rho_liquid / b;
    columnSectionResults["liquidConsumptionPerUnit"] = L_v_max;
    if (L_v_max > 50) {
        handleError ("Предупреждение - слишком высокое значение расхода жидкости на единицу длины сливной планки.", 0);
    }
    double L_v_min = L_min / rho_liquid / b;
    columnSectionResults["LiquidConsumptionPerUnit"] = L_v_min;
    if (L_v_min < 2) {
        handleError ("Предупреждение - слишком низкое значение расхода жидкости на единицу длины сливной планки.", 0);
    }

    double n = G_max / G_min; // Диапазон устойчивой работы тарелки
    columnSectionResults["stableRangeOperation"] = n;
    double F_fr = 1.6 * W_w / n * std::sqrt(rho_vapor) / (1.0 - std::sqrt(1.0 - 3.2E-3 * (h_p * 1000.0 * rho_liquid / 1000.0 + 3.2 * std::pow(L_v / n, 2.0 / 3.0) + 4.0 * sigma / d + 63.0))); // Относительное свободное сечение тарелки
    columnSectionResults["relativeFreePlateSection"] = F_fr;
    if (F_fr <= 0) {
        handleError ("Ошибка при вычислении относительного свободного сечения тарелки.", 1);
        return false;
    }

    double F_col = 0.785 * D * D; // Площадь колонны
    columnSectionResults["areaColumn"] = F_col;
    double W1_w = G_max / 3600.0 / rho_vapor / F_col; // Скорость газа в сечении колонны
    columnSectionResults["columnSectionGasSpeed"] = W1_w;
    double F1_col_fr = F_w * F_fr / F_col; // Расчетное относительное свободное сечение колонны
    columnSectionResults["calcRelativeFreeSection"] = F1_col_fr;

    double dh_vel = 3.1 * std::pow(L_min / rho_liquid / b, 2.0 / 3.0); // Подпор жидкости над сливной планкой (для опр скор)
    if (dh_vel <= 0) {
        handleError ("Ошибка при вычислении подпора жидкости над сливной планкой.", 1);
        return false;
    }
    weirHydrResistResults["liquidDrainPlate_speed"] = dh_vel;

    double t1 = G_min / (3600.0 * rho_vapor);
    double t2 = L_min / (3600.0 * rho_liquid * mu * std::sqrt(2.0 * g * (h_p * 1000.0 + dh_vel) * 1.0E-3));
    double t3 = std::sqrt(2.0 * rho_liquid * g * (h_p * 1000.0 + dh_vel) * 1.0E-3 / ((2.0 * xi + 1.0) * rho_vapor));
    double F_h_max = t1 / t3 + t2;
    double F_h = K_h * F_h_max; // Площадь отверстий тарелки
    columnSectionResults["weirHoleArea"] = F_h;
    if (F_h <= 0) {
        handleError ("Ошибка при вычислении площади отверстий тарелки.", 1);
        return false;
    }

    double F_col_fr = F_h / (F_col * 1.0E-2); // Принятое относительное сечение колонны
    columnSectionResults["acceptedRelativeColumnSection"] = F_col_fr;

    double W_h_liquid;
    double W1_h_min;

    if (typeData["calcType"] == "Поверочный")
    {
        double F_h_in = geometryData["summaryArea"];
        W_h_liquid = L_min / 3600.0 / rho_liquid / F_h_in; // Скорость жидкости в отверстиях тарелки
        W1_h_min = G_min / 3600.0 / rho_vapor / F_h_in; // Расчетная минимальная скорость газа в отверстиях тарелки
    }
    else {
        W_h_liquid = L_min / 3600.0 / rho_liquid / F_h; // Скорость жидкости в отверстиях тарелки
        W1_h_min = G_min / 3600.0 / rho_vapor / F_h; // Расчетная минимальная скорость газа в отверстиях тарелки
    }
    columnSectionResults["liquidHoleSpeed"] = W_h_liquid;
    columnSectionResults["minSteamHoleSpeed"] = W1_h_min;

    return true;
}

bool CalculationModule::calculateWeirHydrResistData()
{
    double mu = constantsData["flowCoeff"];
    double xi_speed = constantsData["dryResistCoeff_speed"];
    double xi_resist = constantsData["dryResistCoeff_resist"];
    double g = 9.81;
    double K_foam = fluidsData["foamingCoeff"];
    double G_max = weirData["steamLoad"];
    double rho_liquid = weirData["liquidDensity"];
    double rho_vapor = weirData["steamDensity"];
    double F_h = columnSectionResults["weirHoleArea"];
    double L_v = columnSectionResults["liquidConsumptionPerUnit"];
    double W_h_liquid = columnSectionResults["liquidHoleSpeed"];
    double h_p = constantsData["overflowBarHeight"];
    double dh_vel = weirHydrResistResults["liquidDrainPlate_speed"];

    double W_h;

    if (typeData["calcType"] == "Поверочный")
    {
        double F_h_in = geometryData["summaryArea"];
        W_h = G_max / 3600.0 / rho_vapor / F_h_in; // Скорость газа в отверстиях тарелки
    }
    else {
        W_h = G_max / 3600.0 / rho_vapor / F_h; // Скорость газа в отверстиях тарелки
    }
    weirHydrResistResults["steamHoleSpeed"] = W_h;

    double dh = 3.1 * std::pow(L_v, 2.0 / 3.0); // Подпор жидкости над сливной планкой
    weirHydrResistResults["liquidDrainPlate"] = dh;
    double W_h_min = (1.0 - W_h_liquid / mu / std::sqrt(2.0 * g * (h_p * 1000.0 + dh_vel) * 1.0E-3)) * std::sqrt(2.0 * rho_liquid * g * (h_p * 1000.0 + dh_vel) * 1.0E-3 / (2.0 * xi_speed + 1.0) / rho_vapor); // Минимально допустимая скорость газа в отверстиях
    weirHydrResistResults["minGasHoleSpeed"] = W_h_min;
    if (W_h_min <= 0) {
        handleError ("Ошибка при вычислении минимально допустимой скорости газа в отверстиях.", 1);
        return false;
    }

    double dP_dry = xi_resist * W_h * W_h * rho_vapor / 2.0 / g; // Сопротивление сухой тарелки
    weirHydrResistResults["dryPlateResist"] = dP_dry;
    double dP_liquid = (h_p * 1000.0 + dh) * rho_liquid / 1000.0; // Потеря напора газового потока в слое жидкости на тарелке
    weirHydrResistResults["gasFlowLoss"] = dP_liquid;
    double dP = dP_dry + dP_liquid; // Общий перепад давления тарелки
    weirHydrResistResults["totalPressureDrop"] = dP;

    double H_f = 3.0 * dP_liquid / K_foam / (rho_liquid / 1000.0); // Высота вспененного слоя жидкости на тарелке
    weirHydrResistResults["foamedLayerHeight"] = H_f;
    double H_liquid = h_p * 1000.0 + dh; // Высота светлого слоя невспененной жидкости на тарелке
    weirHydrResistResults["nonFoamedLayerHeight"] = H_liquid;

    return true;
}

bool CalculationModule::calculateOverflowDeviceData()
{
    double D = columnDiameterResults["columnDiameterTable"];
    double H = geometryData["platesDistance"];
    double N = geometryData["passesNumber"];
    double h_cp = constantsData["boltHeight"];
    double rho_liquid = weirData["liquidDensity"];
    double rho1_vapor = columnDiameterResults["foamedRelativeDensity"];
    double xi_of = constantsData["overflowResistCoeff"];
    double L_v = columnSectionResults["liquidConsumptionPerUnit"];
    double dP = weirHydrResistResults["totalPressureDrop"];
    double g = 9.81;
    double a = 0.06;

    double K = xi_of * rho_liquid / 2.0 / g;
    double dP_liquid_of = K * std::pow(L_v / 3600.0 / a, 2.0); // Сопротивление движению жидкости в переливе
    overflowDeviceResults["fluidMovementResist"] = dP_liquid_of;

    double K3 = get_K3(N); // Коэффициент, зависящий от числа потоков на тарелке
    overflowDeviceResults["passesNumberCoeff"] = K3;
    double dh_cp = 3.1 * std::pow(L_v / K3, 2.0 / 3.0); // Подпор жидкости над затворной планкой
    overflowDeviceResults["liquidAboveDrainPlate"] = dh_cp;

    double h1 = dP_liquid_of / (rho_liquid / 1000.0) + h_cp + dh_cp + dP / (rho_liquid / 1000.0); // Высота слоя светлой жидкости в переливном устройстве
    overflowDeviceResults["lightLiquidHeight"] = h1;
    if (h1 < 0) {
        handleError ("Ошибка при вычислении высоты слоя светлой жидкости в переливном устройстве.", 1);
        return false;
    }

    double H1_of = 0.8 * h1 / rho1_vapor; // Высота вспененного слоя жидкости в переливном устройстве
    overflowDeviceResults["foamedLayerHeight"] = H1_of;

    double h = get_h(D, H); // Высота переливного устройства
    overflowDeviceResults["overflowDeviceHeight"] = h;
    if (h <= 0) {
        handleError ("Ошибка при вычислении высоты переливного устройства.", 1);
        handleError ("Проверьте корректность принятого диаметра колонны и расстояния между тарелками.", 0);
        return false;
    }

    return true;
}

void CalculationModule::calculateCheckFlags()
{
    double H_f = weirHydrResistResults["foamedLayerHeight"];
    double H = geometryData["platesDistance"];
    if (H_f >= 0.9 * H) {
        handleError ("Нужно принять большее расстояние между тарелками и повторить расчет.", 1);
    }
    else checkFlags["foamedHeight"] = true;

    double h1 = overflowDeviceResults["lightLiquidHeight"];
    double h = overflowDeviceResults["overflowDeviceHeight"];
    if (h1 > h) {
        handleError ("Необходимо увеличить диаметр колонны или уменьшить нагрузку на единицу длины слива и повторить расчет.", 1);
    }
    else checkFlags["deviceHeight"] = true;

    double rho1_vapor = columnDiameterResults["foamedRelativeDensity"];
    double H1_of = overflowDeviceResults["foamedLayerHeight"];
    if (rho1_vapor > 0 && H_f + H1_of > 0.9 * (H + h)) {
        handleError ("Нужно выбрать следующий больший размер расстояния между тарелками и повторить расчет.", 1);
    }
    else checkFlags["normalWork"] = true;

    if (H1_of > h) {
        handleError ("Провалена проверка условия нормальной работы переливного устройста.", 1);
    }
    else checkFlags["overflowDevice"] = true;

    if (H - h < H_f) {
        handleError ("Рекомендуется принять большее расстояние между тарелками.", 1);
    }
    else checkFlags["weirWork"] = true;

    if (H - (H_f + h1) <= 50) {
        handleError ("Провалена проверка на расстояние между тарелками.", 1);
    }
    else checkFlags["weirDistance"] = true;

    double W_w = columnSectionResults["workingGasSpeed"];
    double W_p_max = columnDiameterResults["maxGasSpeed"];
    if (W_w >= W_p_max) {
        handleError ("Провалена провервка условия на скорость газа.", 1);
    }
    else checkFlags["gasSpeed"] = true;

    double L_v = columnSectionResults["liquidConsumptionPerUnit"];
    double L1_v = fluidsData["liquidFlow"];
    if (L_v >= L1_v) {
        handleError ("Провалена проверка расхода жидкости.", 1);
    }
    else checkFlags["liquidFlow"] = true;

    double W1_h_min = columnSectionResults["minSteamHoleSpeed"];
    double W_h_min = weirHydrResistResults["minGasHoleSpeed"];
    if (W1_h_min < W_h_min) {
        handleError ("Провалена проверка скорости газа в отверстиях тарелки.", 1);
    }
    else checkFlags["gasHoleSpeed"] = true;
}

void CalculationModule::calculateVerificationFlags()
{
    verificationFlags["active"] = true;

    double D1 = columnDiameterResults["columnDiameter"];
    double D_in = geometryData["columnDiameter"];
    if (D1 > D_in) {
        handleError ("Ошибка. Фактический диаметр меньше рекомендуемого.", 1);
    }
    else verificationFlags["columnDiameter"] = true;

    double b = columnDiameterResults["acceptedPerimeter"];
    double b_in = geometryData["perimeter"];
    if (b > b_in) {
        handleError ("Ошибка. Фактический периметр слива меньше рекомендуемого.", 1);
    }
    else verificationFlags["perimeter"] = true;

    double F_of = columnDiameterResults["acceptedCrossSection"];
    // double F_of_in = columnDiameterData["crossSectionOverflow"]; ???
    double S_in = geometryData["widthOverflow"];
    double F_of_in = b_in * S_in / 2000.0;
    if (F_of > F_of_in) {
        handleError ("Ошибка. Фактическое сечение перелива меньше рекомендуемого.", 1);
    }
    else verificationFlags["crossSection"] = true;

    double F_w = columnSectionResults["workingPlateArea"];
    double F_w_in = geometryData["workingArea"];
    if (F_w > F_w_in) {
        handleError ("Ошибка. Фактическая рабочая площадь тарелки меньше рекомендуемой.", 1);
    }
    else verificationFlags["workingPlateArea"] = true;

    double F_col_fr = columnSectionResults["acceptedRelativeColumnSection"];
    double F_col_fr_in = geometryData["percentArea"];
    if (F_col_fr < F_col_fr_in) {
        handleError ("Ошибка. Фактическое относительное свободное сечение колонны больше рекомендуемого.", 1);
    }
    else verificationFlags["relativeColumnSection"] = true;
}

void CalculationModule::performCalculations(ColumnData& column)
{
    results.clear();
    messages.clear();

    for (auto& section : column.sections)
    {
        for (auto& weir : section.weirs)
        {
            CalculationResults result;
            nullData();
            newInitData(column, section, weir);

            if (calculateColumnDiameterData())
                if (calculateColumnSectionData())
                    if (calculateWeirHydrResistData())
                        if (calculateOverflowDeviceData()) {
                            calculateCheckFlags();
                            if (section.calcType == "Поверочный") calculateVerificationFlags();
                        }

            result.weirName = weir.name;
            {
                result.loadFactor = columnDiameterResults["loadFactor"];
                result.loadCoeff = columnDiameterResults["loadCoeff"];
                result.foamedRelativeDensity = columnDiameterResults["foamedRelativeDensity"];
                result.maxGasSpeed = columnDiameterResults["maxGasSpeed"];
                result.workingPlateArea_diameter = columnDiameterResults["workingPlateArea"];
                result.perimeter = columnDiameterResults["perimeter"];
                result.perimeterTable = columnDiameterResults["perimeterTable"];
                result.width = columnDiameterResults["width"];
                result.crossSection = columnDiameterResults["crossSection"];
                result.freeColumnSection = columnDiameterResults["freeColumnSection"];
                result.columnDiameter = columnDiameterResults["columnDiameter"];
                result.columnDiameterTable = columnDiameterResults["columnDiameterTable"];
                result.acceptedPerimeter = columnDiameterResults["acceptedPerimeter"];
                result.acceptedWidth = columnDiameterResults["acceptedWidth"];
                result.acceptedCrossSection = columnDiameterResults["acceptedCrossSection"];
            }
            {
                result.workingPlateArea_section = columnSectionResults["workingPlateArea"];
                result.workingGasSpeed = columnSectionResults["workingGasSpeed"];
                result.liquidConsumptionPerUnit = columnSectionResults["liquidConsumptionPerUnit"];
                result.stableRangeOperation = columnSectionResults["stableRangeOperation"];
                result.relativeFreePlateSection = columnSectionResults["relativeFreePlateSection"];
                result.areaColumn = columnSectionResults["areaColumn"];
                result.columnSectionGasSpeed = columnSectionResults["columnSectionGasSpeed"];
                result.calcRelativeFreeSection = columnSectionResults["calcRelativeFreeSection"];
                result.weirHoleArea = columnSectionResults["weirHoleArea"];
                result.acceptedRelativeColumnSection = columnSectionResults["acceptedRelativeColumnSection"];
                result.liquidHoleSpeed = columnSectionResults["liquidHoleSpeed"];
                result.minSteamHoleSpeed = columnSectionResults["minSteamHoleSpeed"];
            }
            {
                result.liquidDrainPlate_speed = weirHydrResistResults["liquidDrainPlate_speed"];
                result.steamHoleSpeed = weirHydrResistResults["steamHoleSpeed"];
                result.liquidDrainPlate = weirHydrResistResults["liquidDrainPlate"];
                result.minGasHoleSpeed = weirHydrResistResults["minGasHoleSpeed"];
                result.dryPlateResist = weirHydrResistResults["dryPlateResist"];
                result.gasFlowLoss = weirHydrResistResults["gasFlowLoss"];
                result.totalPressureDrop = weirHydrResistResults["totalPressureDrop"];
                result.foamedLayerHeight_weir = weirHydrResistResults["foamedLayerHeight"];
                result.nonFoamedLayerHeight = weirHydrResistResults["nonFoamedLayerHeight"];
            }
            {
                result.fluidMovementResist = overflowDeviceResults["fluidMovementResist"];
                result.passesNumberCoeff = overflowDeviceResults["passesNumberCoeff"];
                result.liquidAboveDrainPlate = overflowDeviceResults["liquidAboveDrainPlate"];
                result.lightLiquidHeight = overflowDeviceResults["lightLiquidHeight"];
                result.foamedLayerHeight_device = overflowDeviceResults["foamedLayerHeight"];
                result.overflowDeviceHeight = overflowDeviceResults["overflowDeviceHeight"];
            }
            {
                result.condition_foamedHeight = checkFlags["foamedHeight"];
                result.condition_deviceHeight = checkFlags["deviceHeight"];
                result.condition_normalWork = checkFlags["normalWork"];
                result.condition_overflowDevice = checkFlags["overflowDevice"];
                result.condition_weirWork = checkFlags["weirWork"];
                result.condition_weirDistance = checkFlags["weirDistance"];
                result.condition_gasSpeed = checkFlags["gasSpeed"];
                result.condition_liquidFlow = checkFlags["liquidFlow"];
                result.condition_gasHoleSpeed = checkFlags["gasHoleSpeed"];
            }
            {
                result.active = verificationFlags["active"];
                result.verification_columnDiameter = verificationFlags["columnDiameter"];
                result.verification_perimeter = verificationFlags["perimeter"];
                result.verification_crossSection = verificationFlags["crossSection"];
                result.verification_workingPlateArea = verificationFlags["workingPlateArea"];
                result.verification_relativeColumnSection = verificationFlags["relativeColumnSection"];
            }
            if (section.calcType == "Поверочный") result.active = true;

            results.push_back(result);
            messages.push_back(message);
        }
    }
}

std::vector<CalculationResults> CalculationModule::fetchResults()
{
    return results;
}

std::vector<std::vector<std::pair<int, QString>>> CalculationModule::fetchMessages()
{
    return messages;
}

void CalculationModule::newInitData(ColumnData& column, SectionData& section, WeirData& weir)
{
    weirName = weir.name;
    weirData["liquidLoad"] = weir.liquidLoad;
    weirData["steamLoad"] = weir.steamLoad;
    weirData["liquidDensity"] = weir.liquidDensity;
    weirData["steamDensity"] = weir.steamDensity;
    weirData["liquidSurfaceTension"] = weir.liquidSurfaceTension;

    geometryData["holeDiameter"] = section.holeDiameter;
    geometryData["platesDistance"] = section.weirDistance;
    geometryData["passesNumber"] = section.passesNumber;

    if (section.calcType == "Поверочный")
    {
        typeData["calcType"] = "Поверочный";
        geometryData["summaryArea"] = section.summaryArea;
        geometryData["columnDiameter"] = section.columnDiameter;
        geometryData["perimeter"] = section.perimeter;
        geometryData["widthOverflow"] = section.widthOverflow;
        geometryData["workingArea"] = section.workingArea;
        geometryData["percentArea"] = section.percentArea;
    }
    else typeData["calcType"] = "Проектный";

    fluidsData["foamingCoeff"] = column.foamingCoeff;
    fluidsData["liquidFlow"] = column.liquidFlow;

    constantsData["reliabilityCoeff"] = column.reliabilityCoeff;
    constantsData["occupiedAreaCoeff"] = column.occupiedAreaCoeff;
    constantsData["overflowBarHeight"] = column.overflowBarHeight;
    constantsData["reserveCoeff"] = column.reserveCoeff;
    constantsData["flowCoeff"] = column.flowCoeff;

    constantsData["dryResistCoeff_speed"] = 1.8;
    if (weir.weirWidth == 0.00635) constantsData["dryResistCoeff_resist"] = 1.81;
    else if (weir.weirWidth == 0.00635) constantsData["dryResistCoeff_resist"] = 1.80;
    else if (weir.weirWidth == 0.002642) constantsData["dryResistCoeff_resist"] = 1.79;
    else constantsData["dryResistCoeff_resist"] = 1.77;

    constantsData["boltHeight"] = column.boltHeight;
    constantsData["overflowResistCoeff"] = column.overflowResistCoeff;
}

void CalculationModule::nullData()
{
    message.clear();
    {
        columnDiameterResults["loadFactor"] = std::numeric_limits<double>::lowest();
        columnDiameterResults["loadCoeff"] = std::numeric_limits<double>::lowest();
        columnDiameterResults["foamedRelativeDensity"] = std::numeric_limits<double>::lowest();
        columnDiameterResults["maxGasSpeed"] = std::numeric_limits<double>::lowest();
        columnDiameterResults["workingPlateArea"] = std::numeric_limits<double>::lowest();
        columnDiameterResults["perimeter"] = std::numeric_limits<double>::lowest();
        columnDiameterResults["perimeterTable"] = std::numeric_limits<double>::lowest();
        columnDiameterResults["width"] = std::numeric_limits<double>::lowest();
        columnDiameterResults["crossSection"] = std::numeric_limits<double>::lowest();
        columnDiameterResults["freeColumnSection"] = std::numeric_limits<double>::lowest();
        columnDiameterResults["columnDiameter"] = std::numeric_limits<double>::lowest();
        columnDiameterResults["columnDiameterTable"] = std::numeric_limits<double>::lowest();
        columnDiameterResults["acceptedPerimeter"] = std::numeric_limits<double>::lowest();
        columnDiameterResults["acceptedWidth"] = std::numeric_limits<double>::lowest();
        columnDiameterResults["acceptedCrossSection"] = std::numeric_limits<double>::lowest();
    }
    {
        columnSectionResults["workingPlateArea"] = std::numeric_limits<double>::lowest();
        columnSectionResults["workingGasSpeed"] = std::numeric_limits<double>::lowest();

        columnSectionResults["liquidConsumptionPerUnit_min"] = std::numeric_limits<double>::lowest();
        columnSectionResults["liquidConsumptionPerUnit_max"] = std::numeric_limits<double>::lowest();

        // Существует Лв макс и Лв мин - для целостности кода я пока оставлю только Лв макс
        columnSectionResults["liquidConsumptionPerUnit"] = std::numeric_limits<double>::lowest();
        columnSectionResults["stableRangeOperation"] = std::numeric_limits<double>::lowest();
        columnSectionResults["relativeFreePlateSection"] = std::numeric_limits<double>::lowest();
        columnSectionResults["areaColumn"] = std::numeric_limits<double>::lowest();
        columnSectionResults["columnSectionGasSpeed"] = std::numeric_limits<double>::lowest();
        columnSectionResults["calcRelativeFreeSection"] = std::numeric_limits<double>::lowest();
        columnSectionResults["weirHoleArea"] = std::numeric_limits<double>::lowest();
        columnSectionResults["acceptedRelativeColumnSection"] = std::numeric_limits<double>::lowest();
        columnSectionResults["liquidHoleSpeed"] = std::numeric_limits<double>::lowest();
        columnSectionResults["minSteamHoleSpeed"] = std::numeric_limits<double>::lowest();
    }
    {
        weirHydrResistResults["liquidDrainPlate_speed"] = std::numeric_limits<double>::lowest();
        weirHydrResistResults["steamHoleSpeed"] = std::numeric_limits<double>::lowest();
        weirHydrResistResults["liquidDrainPlate"] = std::numeric_limits<double>::lowest();
        weirHydrResistResults["minGasHoleSpeed"] = std::numeric_limits<double>::lowest();
        weirHydrResistResults["dryPlateResist"] = std::numeric_limits<double>::lowest();
        weirHydrResistResults["gasFlowLoss"] = std::numeric_limits<double>::lowest();
        weirHydrResistResults["totalPressureDrop"] = std::numeric_limits<double>::lowest();
        weirHydrResistResults["foamedLayerHeight"] = std::numeric_limits<double>::lowest();
        weirHydrResistResults["nonFoamedLayerHeight"] = std::numeric_limits<double>::lowest();
    }
    {
        overflowDeviceResults["fluidMovementResist"] = std::numeric_limits<double>::lowest();
        overflowDeviceResults["passesNumberCoeff"] = std::numeric_limits<double>::lowest();
        overflowDeviceResults["liquidAboveDrainPlate"] = std::numeric_limits<double>::lowest();
        overflowDeviceResults["lightLiquidHeight"] = std::numeric_limits<double>::lowest();
        overflowDeviceResults["foamedLayerHeight"] = std::numeric_limits<double>::lowest();
        overflowDeviceResults["overflowDeviceHeight"] = std::numeric_limits<double>::lowest();
    }
    {
        checkFlags["foamedHeight"] = false;
        checkFlags["deviceHeight"] = false;
        checkFlags["normalWork"] = false;
        checkFlags["overflowDevice"] = false;
        checkFlags["weirWork"] = false;
        checkFlags["weirDistance"] = false;
        checkFlags["gasSpeed"] = false;
        checkFlags["liquidFlow"] = false;
        checkFlags["gasHoleSpeed"] = false;
    }
    {
        verificationFlags["active"] = false;
        verificationFlags["columnDiameter"] = false;
        verificationFlags["perimeter"] = false;
        verificationFlags["crossSection"] = false;
        verificationFlags["workingPlateArea"] = false;
        verificationFlags["relativeColumnSection"] = false;
    }
}

void CalculationModule::handleError (const QString& errorMessage, int errorLevel)
{
    message.push_back({errorLevel, weirName + " - " + errorMessage});
}

CalculationModule::CalculationModule(QObject *parent)
    : QObject{parent}
{}

double CalculationModule::get_K1(double H, double C)
{
    if (C >= 0.001 && C <= 0.004) {
        if (H < 410) {
            return -1;
        }
        else if (H == 410) {
            return 10.083 * std::pow(C, 2) - 0.0302 * C + 0.056;
        }
        else if (H <= 460) {
            return 10.083 * std::pow(C, 2) - 0.0302 * C + 0.06;
        }
        else if (H <= 510) {
            return 93.416 * std::pow(C, 2) - 0.2802 * C + 0.0642;
        }
        else if (H <= 560) {
            return 260.08 * std::pow(C, 2) - 0.7802 * C + 0.0705;
        }
        else if (H <= 600) {
            return 426.75 * std::pow(C, 2) - 1.2802 * C + 0.0749;
        }
        else if (H <= 650) {
            return 426.75 * std::pow(C, 2) - 1.2802 * C + 0.0809;
        }
        else if (H <= 700) {
            return 426.75 * std::pow(C, 2) - 1.2802 * C + 0.0869;
        }
        else if (H <= 750) {
            return 426.75 * std::pow(C, 2) - 1.2802 * C + 0.0929;
        }
        else {
            return 426.75 * std::pow(C, 2) - 1.2802 * C + 0.0989;
        }
    }
    else if (C >= 0.005 && C < 0.02) {
        if (H < 410) {
            return -1;
        }
        else if (H == 410) {
            return -6141.8 * std::pow(C, 3) + 179.58 * std::pow(C, 2) + 0.79 * C + 0.0502;
        }
        else if (H <= 460) {
            return -41.517 * std::pow(C, 2) + 3.603 * C + 0.0445;
        }
        else if (H <= 510) {
            return 9.3255 * std::pow(C, 2) + 3.0504 * C + 0.0486;
        }
        else if (H <= 560) {
            return 37.263 * std::pow(C, 2) + 2.6218 * C + 0.0578;
        }
        else if (H <= 600) {
            return 88.481 * std::pow(C, 2) + 1.8362 * C + 0.0678;
        }
        else if (H <= 650) {
            return 5.0 * std::pow(2.71828, -5) * std::pow(C, 4) - 2.0 * std::pow(2.71828, -6) * std::pow(C, 3) + 88.481 * std::pow(C, 2) + 1.8362 * C + 0.0738;
        }
        else if (H <= 700) {
            return 5.0 * std::pow(2.71828, -7) * std::pow(C, 3) + 88.481 * std::pow(C, 2) + 1.8362 * C + 0.0798;
        }
        else if (H <= 750) {
            return -2.0 * std::pow(2.71828, -5) * std::pow(C, 4) + 1.0 * std::pow(2.71828, -6) * std::pow(C, 3) + 88.481 * std::pow(C, 2) + 1.8362 * C + 0.0858;
        }
        else {
            return 1.0 * std::pow(2.71828, -6) * std::pow(C, 3) + 88.481 * std::pow(C, 2) + 1.8362 * C + 0.0918;
        }
    }
    else if (C > 0.004 && C < 0.005) {
        double C1 = 0.004;
        double C2 = 0.005;
        double f1;
        double f2;
        if (H < 410) {
            return -1;
        }
        else if (H == 410) {
            f1 = 10.083 * std::pow(C1, 2) - 0.0302 * C1 + 0.056;
            f2 = -6141.8 * std::pow(C2, 3) + 179.58 * std::pow(C2, 2) + 0.79 * C2 + 0.0502;
        }
        else if (H <= 460) {
            f1 = 10.083 * std::pow(C1, 2) - 0.0302 * C1 + 0.06;
            f2 = -41.517 * std::pow(C2, 2) + 3.603 * C2 + 0.0445;
        }
        else if (H <= 510) {
            f1 = 93.416 * std::pow(C1, 2) - 0.2802 * C1 + 0.0642;
            f2 = 9.3255 * std::pow(C2, 2) + 3.0504 * C2 + 0.0486;
        }
        else if (H <= 560) {
            f1 = 260.08 * std::pow(C1, 2) - 0.7802 * C1 + 0.0705;
            f2 = 37.263 * std::pow(C2, 2) + 2.6218 * C2 + 0.0578;
        }
        else if (H <= 600) {
            f1 = 426.75 * std::pow(C1, 2) - 1.2802 * C1 + 0.0749;
            f2 = 88.481 * std::pow(C2, 2) + 1.8362 * C2 + 0.0678;
        }
        else if (H <= 650) {
            f1 = 426.75 * std::pow(C1, 2) - 1.2802 * C1 + 0.0809;
            f2 = 5.0 * std::pow(2.71828, -5) * std::pow(C2, 4) - 2.0 * std::pow(2.71828, -6) * std::pow(C2, 3) + 88.481 * std::pow(C2, 2) + 1.8362 * C2 + 0.0738;
        }
        else if (H <= 700) {
            f1 = 426.75 * std::pow(C1, 2) - 1.2802 * C1 + 0.0869;
            f2 = 5.0 * std::pow(2.71828, -7) * std::pow(C2, 3) + 88.481 * std::pow(C2, 2) + 1.8362 * C2 + 0.0798;
        }
        else if (H <= 750) {
            f1 = 426.75 * std::pow(C1, 2) - 1.2802 * C1 + 0.0929;
            f2 = -2.0 * std::pow(2.71828, -5) * std::pow(C2, 4) + 1.0 * std::pow(2.71828, -6) * std::pow(C2, 3) + 88.481 * std::pow(C2, 2) + 1.8362 * C2 + 0.0858;
        }
        else {
            f1 = 426.75 * std::pow(C1, 2) - 1.2802 * C1 + 0.0989;
            f2 = 1.0 * std::pow(2.71828, -6) * std::pow(C2, 3) + 88.481 * std::pow(C2, 2) + 1.8362 * C2 + 0.0918;
        }
        double k = (f2 - f1) / (C2 - C1);
        double b = f1 - k * C1;
        return k * C + b;
    }
    else if (C >= 0.02 && C < 0.045) {
        if (H < 410) {
            return -1;
        }
        else if (H == 410) {
            return -22.82 * std::pow(C, 2) + 1.7823 * C + 0.0654;
        }
        else if (H <= 460) {
            return -22.485 * std::pow(C, 2) + 1.7191 * C + 0.0776;
        }
        else if (H <= 510) {
            return -23.993 * std::pow(C, 2) + 2.0036 * C + 0.0854;
        }
        else if (H <= 560) {
            return -24.16 * std::pow(C, 2) + 2.0351 * C + 0.0968;
        }
        else if (H <= 600) {
            return -22.485 * std::pow(C, 2) + 1.7191 * C + 0.1176;
        }
        else if (H <= 650) {
            return -22.485 * std::pow(C, 2) + 1.7191 * C + 0.1236;
        }
        else if (H <= 700) {
            return -22.485 * std::pow(C, 2) + 1.7191 * C + 0.1296;
        }
        else if (H <= 750) {
            return -22.485 * std::pow(C, 2) + 1.7191 * C + 0.1356;
        }
        else {
            return -22.485 * std::pow(C, 2) + 1.7191 * C + 0.1416;
        }
    }
    else if (C >= 0.045 && C < 0.35) {
        if (H < 410) {
            return -1;
        }
        else if (H == 410) {
            return -2370.0 * std::pow(C, 6) + 3068.5 * std::pow(C, 5) - 1573.4 * std::pow(C, 4) + 403.43 * std::pow(C, 3) - 53.074 * std::pow(C, 2) + 3.086 * C + 0.0377;
        }
        else if (H <= 460) {
            return -2348.4 * std::pow(C, 6) + 3040.7 * std::pow(C, 5) - 1559.1 * std::pow(C, 4) + 399.71 * std::pow(C, 3) - 52.558 * std::pow(C, 2) + 3.041 * C + 0.0489;
        }
        else if (H <= 510) {
            return -2269.1 * std::pow(C, 6) + 2938.8 * std::pow(C, 5) - 1506.8 * std::pow(C, 4) + 386.08 * std::pow(C, 3) - 50.671 * std::pow(C, 2) + 2.8762 * C + 0.0709;
        }
        else if (H <= 560) {
            return -2222.2 * std::pow(C, 6) + 2878.6 * std::pow(C, 5) - 1475.9 * std::pow(C, 4) + 378.03 * std::pow(C, 3) - 49.555 * std::pow(C, 2) + 2.7788 * C + 0.0861;
        }
        else if (H <= 600) {
            return -2211.4 * std::pow(C, 6) + 2864.7 * std::pow(C, 5) - 1468.8 * std::pow(C, 4) + 376.17 * std::pow(C, 3) - 49.298 * std::pow(C, 2) + 2.7563 * C + 0.0967;
        }
        else if (H <= 650) {
            return -2211.4 * std::pow(C, 6) + 2864.7 * std::pow(C, 5) - 1468.8 * std::pow(C, 4) + 376.17 * std::pow(C, 3) - 49.298 * std::pow(C, 2) + 2.7563 * C + 0.1027;
        }
        else if (H <= 700) {
            return -2211.4 * std::pow(C, 6) + 2864.7 * std::pow(C, 5) - 1468.8 * std::pow(C, 4) + 376.17 * std::pow(C, 3) - 49.298 * std::pow(C, 2) + 2.7563 * C + 0.1087;
        }
        else if (H <= 750) {
            return -2211.4 * std::pow(C, 6) + 2864.7 * std::pow(C, 5) - 1468.8 * std::pow(C, 4) + 376.17 * std::pow(C, 3) - 49.298 * std::pow(C, 2) + 2.7563 * C + 0.1147;
        }
        else {
            return -2211.4 * std::pow(C, 6) + 2864.7 * std::pow(C, 5) - 1468.8 * std::pow(C, 4) + 376.17 * std::pow(C, 3) - 49.298 * std::pow(C, 2) + 2.7563 * C + 0.1207;
        }
    }
    else if (C >= 0.35 && C < 1.0) {
        if (H < 410) {
            return -1;
        }
        else if (H == 410) {
            return -2.0 * std::pow(2.71828, -9) * std::pow(C, 6) + 7.0 * std::pow(2.71828, -9) * std::pow(C, 5) - 1.0 * std::pow(2.71828, -8) * std::pow(C, 4) + 1.0 * std::pow(2.71828, -8) * std::pow(C, 3) + 0.0613 * std::pow(C, 2) - 0.1211 * C + 0.0969;
        }
        else if (H <= 460) {
            return -2.0 * std::pow(2.71828, -9) * std::pow(C, 6) + 9.0 * std::pow(2.71828, -9) * std::pow(C, 5) - 2.0 * std::pow(2.71828, -8) * std::pow(C, 4) + 1.0 * std::pow(2.71828, -8) * std::pow(C, 3) + 0.0613 * std::pow(C, 2) - 0.1257 * C + 0.1055;
        }
        else if (H <= 510) {
            return -2.0 * std::pow(2.71828, -9) * std::pow(C, 6) + 8.0 * std::pow(2.71828, -9) * std::pow(C, 5) - 2.0 * std::pow(2.71828, -8) * std::pow(C, 4) + 2.0 * std::pow(2.71828, -8) * std::pow(C, 3) + 0.0613 * std::pow(C, 2) - 0.128 * C + 0.1128;
        }
        else if (H <= 560) {
            return -3.0 * std::pow(2.71828, -9) * std::pow(C, 6) + 1.0 * std::pow(2.71828, -8) * std::pow(C, 5) - 2.0 * std::pow(2.71828, -8) * std::pow(C, 4) + 2.0 * std::pow(2.71828, -8) * std::pow(C, 3) + 0.0613 * std::pow(C, 2) - 0.1326 * C + 0.1204;
        }
        else if (H <= 600) {
            return -2.0 * std::pow(2.71828, -9) * std::pow(C, 6) + 8.0 * std::pow(2.71828, -9) * std::pow(C, 5) - 1.0 * std::pow(2.71828, -8) * std::pow(C, 4) + 1.0 * std::pow(2.71828, -8) * std::pow(C, 3) + 0.0613 * std::pow(C, 2) - 0.138 * C + 0.1308;
        }
        else if (H <= 650) {
            return -3.0 * std::pow(2.71828, -9) * std::pow(C, 6) + 1.0 * std::pow(2.71828, -8) * std::pow(C, 5) - 3.0 * std::pow(2.71828, -8) * std::pow(C, 4) + 2.0 * std::pow(2.71828, -8) * std::pow(C, 3) + 0.0613 * std::pow(C, 2) - 0.138 * C + 0.1368;
        }
        else if (H <= 700) {
            return -2.0 * std::pow(2.71828, -9) * std::pow(C, 6) + 8.0 * std::pow(2.71828, -9) * std::pow(C, 5) - 1.0 * std::pow(2.71828, -8) * std::pow(C, 4) + 1.0 * std::pow(2.71828, -8) * std::pow(C, 3) + 0.0613 * std::pow(C, 2) - 0.138 * C + 0.1428;
        }
        else if (H <= 750) {
            return 2.0 * std::pow(2.71828, -10) * std::pow(C, 6) - 5.0 * std::pow(2.71828, -10) * std::pow(C, 5) - 7.0 * std::pow(2.71828, -10) * std::pow(C, 4) + 2.0 * std::pow(2.71828, -9) * std::pow(C, 3) + 0.0613 * std::pow(C, 2) - 0.138 * C + 0.1488;
        }
        else {
            return -1.0 * std::pow(2.71828, -9) * std::pow(C, 4) + 2.0 * std::pow(2.71828, -9) * std::pow(C, 3) + 0.0613 * std::pow(C, 2) - 0.138 * C + 0.1548;
        }
    }
    else if (C >= 1.0 && C < 4.0) {
        if (H < 410) {
            return -1;
        }
        else if (H == 410) {
            return -0.001 * std::pow(C, 6) + 0.0144 * std::pow(C, 5) - 0.0789 * std::pow(C, 4) + 0.2167 * std::pow(C, 3) - 0.3061 * std::pow(C, 2) + 0.1872 * C + 0.0063;
        }
        else if (H <= 460) {
            return -0.0008 * std::pow(C, 6) + 0.011 * std::pow(C, 5) - 0.0604 * std::pow(C, 4) + 0.1653 * std::pow(C, 3) - 0.2298 * std::pow(C, 2) + 0.1279 * C + 0.0289;
        }
        else if (H <= 510) {
            return -0.0005 * std::pow(C, 6) + 0.0068 * std::pow(C, 5) - 0.0371 * std::pow(C, 4) + 0.101 * std::pow(C, 3) - 0.1344 * std::pow(C, 2) + 0.0537 * C + 0.057;
        }
        else if (H <= 560) {
            return -0.0003 * std::pow(C, 6) + 0.0042 * std::pow(C, 5) - 0.0232 * std::pow(C, 4) + 0.0624 * std::pow(C, 3) - 0.0773 * std::pow(C, 2) + 0.0092 * C + 0.0739;
        }
        else if (H <= 600) {
            return 5.0 * std::pow(2.71828, -13) * std::pow(C, 6) - 8.0 * std::pow(2.71828, -12) * std::pow(C, 5) + 5.0 * std::pow(2.71828, -11) * std::pow(C, 4) - 0.0019 * std::pow(C, 3) + 0.0181 * std::pow(C, 2) - 0.065 * C + 0.1021;
        }
        else if (H <= 650) {
            return 0.0004 * std::pow(C, 6) - 0.0057 * std::pow(C, 5) + 0.0311 * std::pow(C, 4) - 0.0881 * std::pow(C, 3) + 0.1459 * std::pow(C, 2) - 0.1644 * C + 0.1401;
        }
        else if (H <= 700) {
            return 0.0014 * std::pow(C, 6) - 0.0189 * std::pow(C, 5) + 0.1031 * std::pow(C, 4) - 0.2875 * std::pow(C, 3) + 0.4415 * std::pow(C, 2) - 0.3944 * C + 0.227;
        }
        else if (H <= 750) {
            return 0.0009 * std::pow(C, 6) - 0.0126 * std::pow(C, 5) + 0.0687 * std::pow(C, 4) - 0.1923 * std::pow(C, 3) + 0.3004 * std::pow(C, 2) - 0.2846 * C + 0.1857;
        }
        else {
            return 0.0018 * std::pow(C, 6) - 0.0245 * std::pow(C, 5) + 0.1342 * std::pow(C, 4) - 0.3736 * std::pow(C, 3) + 0.5693 * std::pow(C, 2) - 0.4938 * C + 0.265;
        }
    }
    return -1;
}

double CalculationModule::get_rho1_vapor(double K_foam)
{
    double rho1_vapor = -1;
    if (K_foam == 0.9) rho1_vapor = 0.65;
    else if (K_foam == 0.85) rho1_vapor = 0.55;
    else if (K_foam == 0.75) rho1_vapor = 0.40;
    return rho1_vapor;
}

double CalculationModule::get_table_b_from_calculated_b(double b)
{
    std::vector<double> v{ 1.80, 2.15, 2.55, 2.95, 3.40, 3.77, 6.80, 4.20, 7.53, 4.55, 8.27, 4.976, 9.00, 9.75, 10.20, 16.30, 11.20, 11.90, 17.40, 22.90, 17.20, 24.70 };
    std::sort(v.begin(), v.end());
    for (auto n : v) {
        if (n > b) return n;
    }
    return -1;
}

double CalculationModule::get_S_from_table_b(double b)
{
    std::unordered_map<double, std::vector<double>> m{
        {150, {1.80, 2.15}},
        {200, {2.55, 2.95, 3.40, 3.77, 6.80}},
        {250, {4.20, 7.53, 4.55, 8.27, 4.976, 9.00, 9.75, 10.20, 16.30, 11.20, 11.90, 17.40, 22.90, 17.20, 24.70}}
    };
    for (auto &item : m) {
        for (auto n : item.second) {
            if (n == b) return item.first;
        }
    }
    return -1;
}

double CalculationModule::get_table_D_from_calculated_D(double D)
{
    std::vector<double> v{ 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6 };
    for (auto n : v) {
        if (n >= D) return n;
    }
    return -1;
}

double CalculationModule::get_table_b_from_table_D(double D, double b1)
{
    std::unordered_map<double, std::vector<double>> m{
        {1.0, {1.80}},
        {1.2, {2.15}},
        {1.4, {2.55}},
        {1.6, {2.95}},
        {1.8, {3.40}},
        {2.0, {3.77, 6.80}},
        {2.2, {4.20, 7.53}},
        {2.4, {4.55, 8.27}},
        {2.6, {4.976, 9.00}},
        {2.8, {9.75}},
        {3.0, {10.20}},
        {3.2, {16.30, 11.20}},
        {3.4, {11.90, 17.40, 22.90}},
        {3.6, {17.20, 24.70}}
    };
    if (m[D].size() == 1) return m[D][0];
    std::sort(m[D].begin(), m[D].end());
    for (auto n : m[D]) {
        if (n > b1) return n;
    }
    return m[D][m[D].size() - 1];
}

double CalculationModule::get_S_from_table_D(double D)
{
    if (D < 1.4) return 150;
    if (D < 2.2) return 200;
    return 250;
}

double CalculationModule::get_d_holes(double D, double b)
{
    if (D < 3.2) return 0.0063;
    if (D >= 3.4) return 0.010;
    if (b == 16.30) return 0.0063;
    return 0.010;
}

double CalculationModule::get_F_col_fr(double F1_col_fr, double D, double b, double d)
{
    std::unordered_map<double, std::vector<double>> general{
                                                            {1.0, {12.10, 6.20, 3.10}},
                                                            {1.2, {12.50, 6.60, 3.40}},
                                                            {1.4, {12.64, 7.28, 3.64}},
                                                            {1.6, {12.94, 7.20, 3.50}},
                                                            {1.8, {13.10, 7.57, 3.89}},
                                                            {2.8, {12.20, 7.46, 3.77}},
                                                            };

    std::unordered_map<double, std::vector<double>> D2_0{
        {3.77, {14.14, 8.12, 4.04}},
        {6.80, {10.16, 6.06, 3.10}}
    };

    std::unordered_map<double, std::vector<double>> D2_2{
        {4.20, {13.10, 7.20, 3.80}},
        {7.53, {10.30, 6.40, 2.80}}
    };

    std::unordered_map<double, std::vector<double>> D2_4{
        {4.55, {13.30, 7.60, 3.80}},
        {8.27, {10.68, 6.42, 3.25}}
    };

    std::unordered_map<double, std::vector<double>> D2_6{
        {4.98, {14.05, 8.60, 4.30}},
        {9.00, {11.40, 6.90, 3.50}}
    };

    std::unordered_map<double, std::vector<double>> D3_4{
        {11.90, {8.10, 4.20}},
        {17.40, {6.30, 3.50}},
        {22.90, {5.63, 2.94}}
    };

    std::unordered_map<double, std::vector<double>> D3_6{
        {17.20, {6.60, 3.50}},
        {24.70, {5.84, 3.20}}
    };

    std::unordered_map<double, std::vector<double>> D3_0_d6_3{
        {10.20, {12.90, 7.70, 3.93}}
    };

    std::unordered_map<double, std::vector<double>> D3_0_d10{
        {10.20, {7.47, 3.93}}
    };

    std::unordered_map<double, std::vector<double>> D3_2_d6_3{
        {16.30, {10.60, 6.30, 3.30}}
    };

    std::unordered_map<double, std::vector<double>> D3_2_d10{
        {11.20, {7.70, 4.05}},
        {16.30, {7.60, 4.10}}
    };

    double res = 0;
    double min_diff = std::numeric_limits<double>::max();
    std::vector<double> v;

    if (D < 2) v = general[D];
    else if (D == 2.0) v = D2_0[b];
    else if (D == 2.2) v = D2_2[b];
    else if (D == 2.4) v = D2_4[b];
    else if (D == 2.6) v = D2_6[b];
    else if (D == 3.4) v = D3_4[b];
    else if (D == 3.6) v = D3_6[b];
    else if (D == 3.0 && d == 0.0063) v = D3_0_d6_3[b];
    else if (D == 3.0 && d == 0.010) v = D3_0_d10[b];
    else if (D == 3.2 && d == 0.0063) v = D3_2_d6_3[b];
    else if (D == 3.2 && d == 0.010) v = D3_2_d10[b];
    else return -1;

    for (auto x : v) {
        double diff = std::abs(F1_col_fr - x);
        if (diff < min_diff) {
            min_diff = diff;
            res = x;
        }
    }

    return res;
}

int CalculationModule::get_N(double D, double b)
{
    if (D < 2) return 2;
    if (D == 2.0 && b == 3.77) return 2;
    if (D == 2.0 && b == 6.80) return 4;
    if (D == 2.2 && b == 4.20) return 2;
    if (D == 2.2 && b == 7.53) return 4;
    if (D == 2.4 && b == 4.55) return 2;
    if (D == 2.4 && b == 8.27) return 4;
    if (D == 2.6 && b == 4.98) return 2;
    if (D == 2.6 && b == 9.00) return 4;
    if (D == 2.8) return 4;
    if (D == 3.0) return 4;
    if (D == 3.2 && b == 11.20) return 4;
    if (D == 3.2 && b == 16.30) return 6;
    if (D == 3.4 && b == 11.90) return 4;
    if (D == 3.4 && b == 17.40) return 6;
    if (D == 3.4 && b == 22.90) return 8;
    if (D == 3.6 && b == 17.20) return 6;
    if (D == 3.6 && b == 24.70) return 8;
    return -1;
}

double CalculationModule::get_K3(int N)
{
    if (N >= 2 && N <= 4) return 0.90;
    if (N == 6) return 0.75;
    if (N == 8) return 0.60;
    return -1;
}

double CalculationModule::get_h(double D, double H)
{
    if (H < 500) return 240;
    if (D <= 2.0) return 330;
    return 310;
}

double CalculationModule::get_F_w_from_D_b_and_d(double D, double b, double d)
{
    if (D == 1.0) return 0.360;
    if (D == 1.2) return 0.619;
    if (D == 1.4) return 0.870;
    if (D == 1.6) return 1.239;
    if (D == 1.8) return 1.661;
    if (D == 2.0 && b == 3.77) return 2.160;
    if (D == 2.0 && b == 6.80) return 1.666;
    if (D == 2.2 && b == 4.20) return 2.607;
    if (D == 2.2 && b == 7.53) return 1.921;
    if (D == 2.4 && b == 4.55) return 3.225;
    if (D == 2.4 && b == 8.27) return 2.526;
    if (D == 2.6 && b == 4.98) return 3.893;
    if (D == 2.6 && b == 9.00) return 3.136;
    if (D == 2.8) return 3.805;
    if (D == 3.0 && d == 0.0063) return 3.319;
    if (D == 3.0 && d == 0.01) return 3.319;
    if (D == 3.0) return 3.319;
    if (D == 3.2 && b == 11.20) return 3.941;
    if (D == 3.2 && b == 16.30) return 2.345;
    if (D == 3.4 && b == 11.90) return 4.721;
    if (D == 3.4 && b == 17.40) return 8.999;
    if (D == 3.4 && b == 22.90) return 1.278;
    if (D == 3.6 && b == 17.20) return 4.123;
    if (D == 3.6 && b == 24.70) return 4.776;
    return -1;
}

double CalculationModule::get_b_from_D_and_N(double D, int N)
{
    if (D == 1.0 && N == 2) return 1.80;
    if (D == 1.2 && N == 2) return 2.15;
    if (D == 1.4 && N == 2) return 2.55;
    if (D == 1.6 && N == 2) return 2.95;
    if (D == 1.8 && N == 2) return 3.40;
    if (D == 2.0) {
        if (N == 2) return 3.77;
        if (N == 4) return 6.80;
    }
    if (D == 2.2) {
        if (N == 2) return 4.20;
        if (N == 4) return 7.53;
    }
    if (D == 2.4) {
        if (N == 2) return 4.55;
        if (N == 4) return 8.27;
    }
    if (D == 2.6) {
        if (N == 2) return 4.98;
        if (N == 4) return 9.00;
    }
    if (D == 2.8 && N == 4) return 9.75;
    if (D == 3.0 && N == 4) return 10.20;
    if (D == 3.2) {
        if (N == 4) return 11.20;
        if (N == 6) return 16.30;
    }
    if (D == 3.4) {
        if (N == 4) return 11.90;
        if (N == 6) return 17.40;
        if (N == 8) return 22.90;
    }
    if (D == 3.6) {
        if (N == 6) return 17.20;
        if (N == 8) return 24.70;
    }
    return -1;
}

CalculationModule::~CalculationModule() {}
