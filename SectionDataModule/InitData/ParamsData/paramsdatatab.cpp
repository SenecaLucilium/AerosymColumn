#include "paramsdatatab.h"

ParamsDataTab::ParamsDataTab(Column& _column, QWidget *parent)
    : QWidget{parent}, column{_column}
{
    fluidContainer = new QWidget(this);
    {
        fluidGroup = new QGroupBox("Жидкость и Пар", fluidContainer);
        {
            liquidFlowLabel = new QLabel("Расход жидкости на единицу длины сливной планки (м^3/м*ч)", fluidGroup);
            foamingCoeffLabel = new QLabel("Коэффициент вспениваемости жидкости", fluidGroup);

            liquidFlowLineEdit = new QLineEdit(fluidGroup);
            foamingCoeffLineEdit = new QLineEdit(fluidGroup);

            fluidGrid = new QGridLayout();

            fluidGrid->addWidget(liquidFlowLabel, 0, 0, Qt::AlignLeft);
            fluidGrid->addWidget(foamingCoeffLabel, 1, 0, Qt::AlignLeft);
            fluidGrid->addWidget(liquidFlowLineEdit, 0, 1, Qt::AlignRight);
            fluidGrid->addWidget(foamingCoeffLineEdit, 1, 1, Qt::AlignRight);

            fluidGrid->setColumnStretch(0, 8);
            fluidGrid->setColumnStretch(1, 2);

            fluidGroup->setLayout(fluidGrid);
            fluidGroup->setMaximumWidth(450);
        }

        fluidHLayout = new QHBoxLayout();
        fluidHLayout->addWidget(fluidGroup);
        fluidHLayout->addStretch();
        fluidContainer->setLayout(fluidHLayout);
    }

    constantsContainer = new QWidget(this);
    {
        constantsGroup = new QGroupBox("Константы", constantsContainer);
        {
            overflowBarHeightLabel = new QLabel("Высота переливной планки (м)", constantsGroup);
            boltHeightLabel = new QLabel("Высота затворной планки (мм)", constantsGroup);
            flowCoeffLabel = new QLabel("Коэффициент расхода", constantsGroup);
            dryResisCoeffLabel = new QLabel("Коэффициент сопротивления сухой тарелки", constantsGroup);
            overflowResistCoeffLabel = new QLabel("Коэффициент сопротивления перелива", constantsGroup);
            occupiedAreaCoeffLabel = new QLabel("Коэффициент площади, занятой опорными конструкциями тарелки", constantsGroup);
            reliabilityCoeffLabel = new QLabel("Коэффициент надежности", constantsGroup);
            loadCoeffLabel = new QLabel("Коэффициент нагрузки", constantsGroup);
            reserveCoeffLabel = new QLabel("Коэффициент запаса для относительного свободного сечения колонны", constantsGroup);

            overflowBarHeightLineEdit = new QLineEdit(constantsGroup);
            boltHeightLineEdit = new QLineEdit(constantsGroup);
            flowCoeffLineEdit = new QLineEdit(constantsGroup);
            dryResistCoeffLineEdit = new QLineEdit(constantsGroup);
            overflowResistCoeffLineEdit = new QLineEdit(constantsGroup);
            occupiedAreaCoeffLineEdit = new QLineEdit(constantsGroup);
            reliabilityCoeffLineEdit = new QLineEdit(constantsGroup);
            loadCoeffLineEdit = new QLineEdit(constantsGroup);
            reserveCoeffLineEdit = new QLineEdit(constantsGroup);

            constantsGrid = new QGridLayout();

            constantsGrid->addWidget(overflowBarHeightLabel, 0, 0, Qt::AlignLeft);
            constantsGrid->addWidget(boltHeightLabel, 1, 0, Qt::AlignLeft);
            constantsGrid->addWidget(flowCoeffLabel, 2, 0, Qt::AlignLeft);
            constantsGrid->addWidget(dryResisCoeffLabel, 3, 0, Qt::AlignLeft);
            constantsGrid->addWidget(overflowResistCoeffLabel, 4, 0, Qt::AlignLeft);
            constantsGrid->addWidget(occupiedAreaCoeffLabel, 5, 0, Qt::AlignLeft);
            constantsGrid->addWidget(reliabilityCoeffLabel, 6, 0, Qt::AlignLeft);
            constantsGrid->addWidget(loadCoeffLabel, 7, 0, Qt::AlignLeft);
            constantsGrid->addWidget(reserveCoeffLabel, 8, 0, Qt::AlignLeft);
            constantsGrid->addWidget(overflowBarHeightLineEdit, 0, 1, Qt::AlignRight);
            constantsGrid->addWidget(boltHeightLineEdit, 1, 1, Qt::AlignRight);
            constantsGrid->addWidget(flowCoeffLineEdit, 2, 1, Qt::AlignRight);
            constantsGrid->addWidget(dryResistCoeffLineEdit, 3, 1, Qt::AlignRight);
            constantsGrid->addWidget(overflowResistCoeffLineEdit, 4, 1, Qt::AlignRight);
            constantsGrid->addWidget(occupiedAreaCoeffLineEdit, 5, 1, Qt::AlignRight);
            constantsGrid->addWidget(reliabilityCoeffLineEdit, 6, 1, Qt::AlignRight);
            constantsGrid->addWidget(loadCoeffLineEdit, 7, 1, Qt::AlignRight);
            constantsGrid->addWidget(reserveCoeffLineEdit, 8, 1, Qt::AlignRight);

            constantsGrid->setColumnStretch(0, 8);
            constantsGrid->setColumnStretch(1, 2);

            constantsGroup->setLayout(constantsGrid);
            constantsGroup->setMaximumWidth(550);
        }

        constantsHLayout = new QHBoxLayout();
        constantsHLayout->addWidget(constantsGroup);
        constantsHLayout->addStretch();
        constantsContainer->setLayout(constantsHLayout);
    }

    QList<QLineEdit*> lineEdits = {liquidFlowLineEdit, foamingCoeffLineEdit, overflowBarHeightLineEdit, boltHeightLineEdit,
                                    flowCoeffLineEdit, dryResistCoeffLineEdit, overflowResistCoeffLineEdit, occupiedAreaCoeffLineEdit,
                                    reliabilityCoeffLineEdit, loadCoeffLineEdit, reserveCoeffLineEdit};
    QDoubleValidator* DoubleValidator = new QDoubleValidator(this);
    DoubleValidator->setDecimals(5);
    DoubleValidator->setNotation(QDoubleValidator::StandardNotation);
    for (int iter = 0; iter < lineEdits.size(); ++iter)
    {
        lineEdits[iter]->setValidator(DoubleValidator);
        lineEdits[iter]->setAlignment(Qt::AlignRight);
    }

    mainVLayout = new QVBoxLayout();
    mainVLayout->addWidget(fluidContainer);
    mainVLayout->addWidget(constantsContainer);
    mainVLayout->addStretch();
    setLayout(mainVLayout);

    connect(liquidFlowLineEdit, &QLineEdit::textChanged, this, &ParamsDataTab::onLiquidFlowChanged);
    connect(foamingCoeffLineEdit, &QLineEdit::textChanged, this, &ParamsDataTab::onFoamingCoeffChanged);
    connect(overflowBarHeightLineEdit, &QLineEdit::textChanged, this, &ParamsDataTab::onOverflowBarHeightChanged);
    connect(boltHeightLineEdit, &QLineEdit::textChanged, this, &ParamsDataTab::onBoltHeightChanged);
    connect(flowCoeffLineEdit, &QLineEdit::textChanged, this, &ParamsDataTab::onFlowCoeffChanged);
    connect(dryResistCoeffLineEdit, &QLineEdit::textChanged, this, &ParamsDataTab::onDryResistCoeffChanged);
    connect(overflowResistCoeffLineEdit, &QLineEdit::textChanged, this, &ParamsDataTab::onOverflowResistCoeffChanged);
    connect(occupiedAreaCoeffLineEdit, &QLineEdit::textChanged, this, &ParamsDataTab::onOccupiedAreaCoeffChanged);
    connect(reliabilityCoeffLineEdit, &QLineEdit::textChanged, this, &ParamsDataTab::onReliabilityCoeffChanged);
    connect(loadCoeffLineEdit, &QLineEdit::textChanged, this, &ParamsDataTab::onLoadCoeffChanged);
    connect(reserveCoeffLineEdit, &QLineEdit::textChanged, this, &ParamsDataTab::onReserveCoeffChanged);

    liquidFlowLineEdit->setText(QString::number(column.liquidFlow));
    foamingCoeffLineEdit->setText(QString::number(column.foamingCoeff));
    overflowBarHeightLineEdit->setText(QString::number(column.overflowBarHeight));
    boltHeightLineEdit->setText(QString::number(column.boltHeight));
    flowCoeffLineEdit->setText(QString::number(column.flowCoeff));
    dryResistCoeffLineEdit->setText(QString::number(column.dryResistCoeff));
    overflowResistCoeffLineEdit->setText(QString::number(column.overflowResistCoeff));
    occupiedAreaCoeffLineEdit->setText(QString::number(column.occupiedAreaCoeff));
    reliabilityCoeffLineEdit->setText(QString::number(column.reliabilityCoeff));
    loadCoeffLineEdit->setText(QString::number(column.loadCoeff));
    reserveCoeffLineEdit->setText(QString::number(column.reserveCoeff));
}

void ParamsDataTab::onLiquidFlowChanged() { column.liquidFlow = liquidFlowLineEdit->text().toDouble(); }

void ParamsDataTab::onFoamingCoeffChanged() { column.foamingCoeff = foamingCoeffLineEdit->text().toDouble(); }

void ParamsDataTab::onOverflowBarHeightChanged() { column.overflowBarHeight = overflowBarHeightLineEdit->text().toDouble(); }

void ParamsDataTab::onBoltHeightChanged() { column.boltHeight = boltHeightLineEdit->text().toDouble(); }

void ParamsDataTab::onFlowCoeffChanged() { column.flowCoeff = flowCoeffLineEdit->text().toDouble(); }

void ParamsDataTab::onDryResistCoeffChanged() { column.dryResistCoeff = dryResistCoeffLineEdit->text().toDouble(); }

void ParamsDataTab::onOverflowResistCoeffChanged() { column.overflowResistCoeff = overflowResistCoeffLineEdit->text().toDouble(); }

void ParamsDataTab::onOccupiedAreaCoeffChanged() { column.occupiedAreaCoeff = occupiedAreaCoeffLineEdit->text().toDouble(); }

void ParamsDataTab::onReliabilityCoeffChanged() { column.reliabilityCoeff = reliabilityCoeffLineEdit->text().toDouble(); }

void ParamsDataTab::onLoadCoeffChanged() { column.loadCoeff = loadCoeffLineEdit->text().toDouble(); }

void ParamsDataTab::onReserveCoeffChanged() { column.reserveCoeff = reserveCoeffLineEdit->text().toDouble(); }

ParamsDataTab::~ParamsDataTab() {}
