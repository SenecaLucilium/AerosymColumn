#include "columnmodule.h"

#include <QApplication>
#include <QLocale>

#include <QFile>
#include <QFileDialog>

Column parseInitData ()
{
    QString columnFilePath = "://TestFiles/1 COL. TOP.txt";

    QFile columnFile (columnFilePath);
    if (!columnFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл";
        QCoreApplication::exit();
    }

    QTextStream columnIn (&columnFile);
    columnIn.readLine(); // Первая строка не нужна?

    QVector<QVector<double>> parameters;

    while (!columnIn.atEnd()) {
        QString line = columnIn.readLine();
        QStringList values = line.split(';');
        QVector<double> row;

        for (const QString &value : values) {
            row.append(value.toDouble());
        }

        parameters.append(row);
    }

    columnFile.close();
    if (parameters.size() != 5) QCoreApplication::exit();
    int weirsAmount = parameters[0].size();
    for (const auto& row : parameters) {
        if (row.size() != weirsAmount) QCoreApplication::exit();
    }

    std::vector <std::shared_ptr<SieveWeir>> weirsInfo1;
    std::vector <std::shared_ptr<SieveWeir>> weirsInfo2;
    std::vector <std::shared_ptr<SieveWeir>> weirsInfo3;
    for (int weirNum = 0; weirNum < weirsAmount; ++weirNum)
    {
        auto newWeir = std::make_shared<SieveWeir>();

        newWeir->name = QString("%1_Main Tower").arg(weirNum + 1);
        newWeir->liquidLoad = parameters[0][weirNum];
        newWeir->steamLoad = parameters[1][weirNum];
        newWeir->liquidDensity = parameters[2][weirNum];
        newWeir->steamDensity = parameters[3][weirNum];
        newWeir->liquidSurfaceTension = parameters[4][weirNum];
        newWeir->weirWidth = 0.003404;

        if (weirNum < 6) weirsInfo1.push_back(newWeir);
        else if (weirNum < 10) weirsInfo2.push_back(newWeir);
        else weirsInfo3.push_back(newWeir);
    }

    auto sectionInfo1 = std::make_shared<SieveSection>();
    sectionInfo1->name = "CS-1";
    sectionInfo1->weirs = weirsInfo1;
    sectionInfo1->passesNumber = 2;
    sectionInfo1->calcType = "Проектный";
    sectionInfo1->weirType = "Ситчатая";

    sectionInfo1->holeDiameter = 0.0063;
    sectionInfo1->weirDistance = 500;
    sectionInfo1->flowNumberCoeff = 0.9;

    auto sectionInfo2 = std::make_shared<SieveSectionVerification>();
    sectionInfo2->name = "CS-2";
    sectionInfo2->weirs = weirsInfo2;
    sectionInfo2->passesNumber = 2;
    sectionInfo2->calcType = "Поверочный";
    sectionInfo2->weirType = "Ситчатая";

    sectionInfo2->holeDiameter = 0.0063;
    sectionInfo2->weirDistance = 500;
    sectionInfo2->flowNumberCoeff = 0.9;

    sectionInfo2->columnDiameter = 1.0;
    sectionInfo2->workingArea = 0.36;
    sectionInfo2->summaryArea = 0.05;
    sectionInfo2->percentArea = 2.5;
    sectionInfo2->perimeter = 1.8;
    sectionInfo2->widthOverflow = 150;
    sectionInfo2->crossSectionOverflow = 6.3;

    auto sectionInfo3 = std::make_shared<SieveSection>();
    sectionInfo3->name = "CS-3";
    sectionInfo3->weirs = weirsInfo3;
    sectionInfo3->passesNumber = 2;
    sectionInfo3->calcType = "Проектный";
    sectionInfo3->weirType = "Ситчатая";

    sectionInfo3->holeDiameter = 0.0063;
    sectionInfo3->weirDistance = 500;
    sectionInfo3->flowNumberCoeff = 0.9;

    Column columnInfo;
    columnInfo.name = "T-100";
    columnInfo.sections = {sectionInfo1, sectionInfo2, sectionInfo3};

    columnInfo.liquidFlow = 45;
    columnInfo.foamingCoeff = 0.85;

    columnInfo.overflowBarHeight = 0.04;
    columnInfo.boltHeight = 75;
    columnInfo.flowCoeff = 0.62;
    columnInfo.dryResistCoeff = 1.8;
    columnInfo.overflowResistCoeff = 3.7;
    columnInfo.occupiedAreaCoeff = 1.05;
    columnInfo.reliabilityCoeff = 0.9;
    columnInfo.loadCoeff = 0.0998;
    columnInfo.reserveCoeff = 0.95;

    return columnInfo;
}

int main(int argc, char *argv[])
{
    QLocale::setDefault(QLocale::c());

    // Придумать как в начале парсить данные, которые будут поступать из аеросима (уже потом)
    Column initData = parseInitData();

    // for (auto& section : initData.sections) {
    //     if (auto sieveSection = std::dynamic_pointer_cast<SieveSection>(section)) {
    //         qDebug() << sieveSection->name << sieveSection->passesNumber;
    //         for (auto& weir : sieveSection->weirs) {
    //             qDebug() << weir->name << weir->liquidDensity;
    //         }
    //     }
    // }

    QApplication a(argc, argv);
    ColumnModule w(initData);
    w.show();
    return a.exec();
}
