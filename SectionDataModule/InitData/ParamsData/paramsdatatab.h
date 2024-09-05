#ifndef PARAMSDATATAB_H
#define PARAMSDATATAB_H

#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDoubleValidator>

#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>

#include "../../../datatypes.h"

class ParamsDataTab : public QWidget
{
    Q_OBJECT
public:
    explicit ParamsDataTab(Column& column, QWidget *parent = nullptr);
    ~ParamsDataTab();

private:
    Column& column;

    QVBoxLayout* mainVLayout;

    QWidget* fluidContainer;
    QHBoxLayout* fluidHLayout;
    QGroupBox* fluidGroup;
    QGridLayout* fluidGrid;

    QLabel* liquidFlowLabel;
    QLineEdit* liquidFlowLineEdit;
    QLabel* foamingCoeffLabel;
    QLineEdit* foamingCoeffLineEdit;

    QWidget* constantsContainer;
    QHBoxLayout* constantsHLayout;
    QGroupBox* constantsGroup;
    QGridLayout* constantsGrid;

    QLabel* overflowBarHeightLabel;
    QLineEdit* overflowBarHeightLineEdit;
    QLabel* boltHeightLabel;
    QLineEdit* boltHeightLineEdit;
    QLabel* flowCoeffLabel;
    QLineEdit* flowCoeffLineEdit;
    QLabel* dryResisCoeffLabel;
    QLineEdit* dryResistCoeffLineEdit;
    QLabel* overflowResistCoeffLabel;
    QLineEdit* overflowResistCoeffLineEdit;
    QLabel* occupiedAreaCoeffLabel;
    QLineEdit* occupiedAreaCoeffLineEdit;
    QLabel* reliabilityCoeffLabel;
    QLineEdit* reliabilityCoeffLineEdit;
    QLabel* loadCoeffLabel;
    QLineEdit* loadCoeffLineEdit;
    QLabel* reserveCoeffLabel;
    QLineEdit* reserveCoeffLineEdit;

private slots:
    void onLiquidFlowChanged();
    void onFoamingCoeffChanged();
    void onOverflowBarHeightChanged();
    void onBoltHeightChanged();
    void onFlowCoeffChanged();
    void onDryResistCoeffChanged();
    void onOverflowResistCoeffChanged();
    void onOccupiedAreaCoeffChanged();
    void onReliabilityCoeffChanged();
    void onLoadCoeffChanged();
    void onReserveCoeffChanged();
};

#endif // PARAMSDATATAB_H
