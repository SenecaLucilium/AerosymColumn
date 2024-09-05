#ifndef DATATYPES_H
#define DATATYPES_H

#include <QString>
#include <QDebug>

class Weir {
public:
    virtual ~Weir() = default;

    Weir() = default;

    Weir(const Weir& original) : name(original.name) {qDebug() << "Weir copy activated";}

    QString name;
};

class SieveWeir : public Weir {
public:
    SieveWeir() = default;

    SieveWeir(const SieveWeir& original)
        : Weir(original),
        liquidLoad(original.liquidLoad),
        steamLoad(original.steamLoad),
        liquidDensity(original.liquidDensity),
        steamDensity(original.steamDensity),
        liquidSurfaceTension(original.liquidSurfaceTension),
        weirWidth(original.weirWidth)
    {qDebug() << "SieveWeir copy activated";}

    double liquidLoad;
    double steamLoad;
    double liquidDensity;
    double steamDensity;
    double liquidSurfaceTension;

    double weirWidth;
};

class Section {
public:
    virtual ~Section() = default;

    Section() : name(""), calcType("Проектный"), weirType("Ситчатая") {}

    Section(const Section& original) : name(original.name), calcType(original.calcType), weirType(original.weirType)
    {qDebug() << "Section copy activated";}

    QString name;

    QString calcType;
    QString weirType;
};

class SieveSection : public Section {
public:
    SieveSection() : Section(), weirs({}), passesNumber(2), holeDiameter(0.0), weirDistance(0.0), flowNumberCoeff(0.0) {}

    SieveSection(const SieveSection& original)
        : Section(original),
        passesNumber(original.passesNumber),
        holeDiameter(original.holeDiameter),
        weirDistance(original.weirDistance),
        flowNumberCoeff(original.flowNumberCoeff)
    {
        qDebug() << "SieveSection copy activated";
        for (const auto& weir : original.weirs) {
            weirs.push_back(std::make_shared<SieveWeir>(*weir));
        }
    }

    std::vector<std::shared_ptr<SieveWeir>> weirs;

    int passesNumber;
    double holeDiameter;
    double weirDistance;
    double flowNumberCoeff;
};

class SieveSectionVerification : public SieveSection {
public:
    SieveSectionVerification() = default;

    SieveSectionVerification(const SieveSectionVerification& original)
        : SieveSection(original),
        columnDiameter(original.columnDiameter),
        workingArea(original.workingArea),
        summaryArea(original.summaryArea),
        percentArea(original.percentArea),
        perimeter(original.perimeter),
        widthOverflow(original.widthOverflow),
        crossSectionOverflow(original.crossSectionOverflow)
    {qDebug() << "SieveSectionVerification copy activated";}

    SieveSectionVerification(const SieveSection& sieveOriginal)
        : SieveSection(sieveOriginal),
        columnDiameter(1.0),
        workingArea(0.0),
        summaryArea(0.0),
        percentArea(0.0),
        perimeter(0.0),
        widthOverflow(0.0),
        crossSectionOverflow(0.0)
    {qDebug() << "SieveSectionVerification upgrade";}

    double columnDiameter;
    double workingArea;
    double summaryArea;
    double percentArea;
    double perimeter;
    double widthOverflow;
    double crossSectionOverflow;
};

class Column {
public:
    ~Column() = default;

    Column() = default;

    Column(const Column& original)
        : liquidFlow(original.liquidFlow),
        foamingCoeff(original.foamingCoeff),
        overflowBarHeight(original.overflowBarHeight),
        boltHeight(original.boltHeight),
        flowCoeff(original.flowCoeff),
        dryResistCoeff(original.dryResistCoeff),
        overflowResistCoeff(original.overflowResistCoeff),
        occupiedAreaCoeff(original.occupiedAreaCoeff),
        reliabilityCoeff(original.reliabilityCoeff),
        loadCoeff(original.loadCoeff),
        reserveCoeff(original.reserveCoeff)
    {
        qDebug() << "Column copy activated";
        for (const auto& section : original.sections) {
            sections.push_back(section);
        }
    }

    QString name;
    std::vector <std::shared_ptr<Section>> sections;

    double liquidFlow;
    double foamingCoeff;

    double overflowBarHeight;
    double boltHeight;

    double flowCoeff;
    double dryResistCoeff;
    double overflowResistCoeff;
    double occupiedAreaCoeff;
    double reliabilityCoeff;
    double loadCoeff;
    double reserveCoeff;
};

class CalculationResults {
public:
    virtual ~CalculationResults() = default;

    CalculationResults() = default;

    QString weirName;
};

class SieveCalculationResults : public CalculationResults {
public:
    SieveCalculationResults() = default;

    double loadFactor;
    double loadCoeff;
    double foamedRelativeDensity;
    double maxGasSpeed;
    double workingPlateArea_diameter;
    double perimeter;
    double perimeterTable;
    double width;
    double crossSection;
    double freeColumnSection;
    double columnDiameter;
    double columnDiameterTable;
    double acceptedPerimeter;
    double acceptedWidth;
    double acceptedCrossSection;

    double workingPlateArea_section;
    double workingGasSpeed;
    double liquidConsumptionPerUnit;
    double stableRangeOperation;
    double relativeFreePlateSection;
    double areaColumn;
    double columnSectionGasSpeed;
    double calcRelativeFreeSection;
    double weirHoleArea;
    double acceptedRelativeColumnSection;
    double liquidHoleSpeed;
    double minSteamHoleSpeed;

    double liquidDrainPlate_speed;
    double steamHoleSpeed;
    double liquidDrainPlate;
    double minGasHoleSpeed;
    double dryPlateResist;
    double gasFlowLoss;
    double totalPressureDrop;
    double foamedLayerHeight_weir;
    double nonFoamedLayerHeight;

    double fluidMovementResist;
    double passesNumberCoeff;
    double liquidAboveDrainPlate;
    double lightLiquidHeight;
    double foamedLayerHeight_device;
    double overflowDeviceHeight;

    bool condition_foamedHeight;
    bool condition_deviceHeight;
    bool condition_normalWork;
    bool condition_overflowDevice;
    bool condition_weirWork;
    bool condition_weirDistance;
    bool condition_gasSpeed;
    bool condition_liquidFlow;
    bool condition_gasHoleSpeed;
};

class SieveCalculationResultsVerification : public SieveCalculationResults {
public:
    SieveCalculationResultsVerification() = default;

    bool verification_columnDiameter;
    bool verification_perimeter;
    bool verification_crossSection;
    bool verification_workingPlateArea;
    bool verification_relativeColumnSection;
};

#endif // DATATYPES_H
