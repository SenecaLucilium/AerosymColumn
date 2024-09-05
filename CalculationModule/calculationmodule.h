#ifndef CALCULATIONMODULE_H
#define CALCULATIONMODULE_H

#include <QObject>
#include <limits>

#include "../datatypes.h"

class CalculationModule : public QObject
{
    Q_OBJECT
public:
    explicit CalculationModule(QObject *parent = nullptr);
    ~CalculationModule();

    void performCalculations(ColumnData& column);
    std::vector <CalculationResults> fetchResults();
    std::vector <std::vector <std::pair<int, QString>>> fetchMessages();

private:
    std::vector <CalculationResults> results;
    std::vector <std::vector <std::pair<int, QString>>> messages;
    std::vector <std::pair<int, QString>> message;

    QString weirName;
    std::unordered_map<QString, QString> typeData;
    std::unordered_map<QString, double> geometryData;
    std::unordered_map<QString, double> fluidsData;
    std::unordered_map<QString, double> constantsData;
    std::unordered_map<QString, double> weirData;
    void newInitData(ColumnData& column, SectionData& section, WeirData& weir);
    void nullData();
    void handleError (const QString& errorMessage, int errorLevel);

    bool checkInitData();

    std::unordered_map<QString, double> columnDiameterResults;
    bool calculateColumnDiameterData();
    std::unordered_map<QString, double> columnSectionResults;
    bool calculateColumnSectionData();
    std::unordered_map<QString, double> weirHydrResistResults;
    bool calculateWeirHydrResistData();
    std::unordered_map<QString, double> overflowDeviceResults;
    bool calculateOverflowDeviceData();
    std::unordered_map<QString, bool> checkFlags;
    void calculateCheckFlags();
    std::unordered_map<QString, bool> verificationFlags;
    void calculateVerificationFlags();

    double get_K1(double H, double C);
    double get_rho1_vapor(double K_foam);
    double get_table_b_from_calculated_b(double b);
    double get_S_from_table_b(double b);
    double get_table_D_from_calculated_D(double D);
    double get_table_b_from_table_D(double D, double b1);
    double get_S_from_table_D(double D);
    double get_d_holes(double D, double b);
    double get_F_col_fr(double F1_col_fr, double D, double b, double d);
    int get_N(double D, double b);
    double get_K3(int N);
    double get_h(double D, double H);
    double get_F_w_from_D_b_and_d(double D, double b, double d);
    double get_b_from_D_and_N(double D, int N);
};

#endif // CALCULATIONMODULE_H
