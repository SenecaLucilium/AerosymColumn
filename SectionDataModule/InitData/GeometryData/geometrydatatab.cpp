#include "geometrydatatab.h"

GeometryDataTab::GeometryDataTab(Column& column, int sectionIndex, QWidget *parent)
    : QWidget{parent}
{
    infoContainer = new QWidget(this);
    {
        nameLabel = new QLabel("Название", infoContainer);
        startLabel = new QLabel("Стартовая ступень", infoContainer);
        endLabel = new QLabel("Последняя ступень", infoContainer);
        modeLabel = new QLabel("Тип", infoContainer);

        nameLineEdit = new QLineEdit(infoContainer);
        nameLineEdit->setReadOnly(true);
        nameLineEdit->setMaximumWidth(70);
        startLineEdit = new QLineEdit(infoContainer);
        startLineEdit->setReadOnly(true);
        startLineEdit->setMaximumWidth(100);
        endLineEdit = new QLineEdit(infoContainer);
        endLineEdit->setReadOnly(true);
        endLineEdit->setMaximumWidth(100);

        projectRadioButton = new QRadioButton("Проектный", infoContainer);
        verificationRadioButton = new QRadioButton("Поверочный", infoContainer);

        infoHLayout = new QHBoxLayout();

        infoHLayout->addWidget(nameLabel);
        infoHLayout->addWidget(nameLineEdit);
        infoHLayout->addWidget(startLabel);
        infoHLayout->addWidget(startLineEdit);
        infoHLayout->addWidget(endLabel);
        infoHLayout->addWidget(endLineEdit);
        infoHLayout->addItem(new QSpacerItem(40, 0, QSizePolicy::Minimum, QSizePolicy::Minimum));
        infoHLayout->addWidget(modeLabel);
        infoHLayout->addItem(new QSpacerItem(10, 0, QSizePolicy::Minimum, QSizePolicy::Minimum));
        infoHLayout->addWidget(projectRadioButton);
        infoHLayout->addWidget(verificationRadioButton);
        infoHLayout->addItem(new QSpacerItem(400, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

        infoContainer->setLayout(infoHLayout);
    }
    typeContainer = new QWidget(this);
    {
        trayTypeLabel = new QLabel("Тип тарелки", typeContainer);
        passesNumberLabel = new QLabel("Количество проходов", typeContainer);

        trayTypeComboBox = new QComboBox(typeContainer);
        trayTypeComboBox->addItems({"Ситчатая", "Клапанная"});

        if (auto sieveSection = std::dynamic_pointer_cast<SieveSection>(column.sections[sectionIndex])) {
            passesNumberComboBox = new QComboBox(typeContainer);
            passesNumberComboBox->addItems({"2", "4", "6", "8"});
        }

        typeHLayout = new QHBoxLayout();

        typeHLayout->addWidget(trayTypeLabel);
        typeHLayout->addWidget(trayTypeComboBox);
        typeHLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Minimum));
        typeHLayout->addWidget(passesNumberLabel);
        if (auto sieveSection = std::dynamic_pointer_cast<SieveSection>(column.sections[sectionIndex]))
            typeHLayout->addWidget(passesNumberComboBox);
        typeHLayout->addStretch();

        typeContainer->setLayout(typeHLayout);
    }

    mainVLayout = new QVBoxLayout();

    mainVLayout->addWidget(infoContainer, 1);
    mainVLayout->addWidget(typeContainer, 1);

    if (auto sieveSection = std::dynamic_pointer_cast<SieveSection>(column.sections[sectionIndex])) {
        sieveGeometry = new SieveGeometry(column, sectionIndex, this);
        mainVLayout->addWidget(sieveGeometry, 18);
    }

    setLayout(mainVLayout);

    nameLineEdit->setText(column.sections[sectionIndex]->name);
    if (column.sections[sectionIndex]->calcType == "Проектный") projectRadioButton->setChecked(true);
    else verificationRadioButton->setChecked(true);
    trayTypeComboBox->setCurrentText(column.sections[sectionIndex]->weirType);

    if (auto sieveSection = std::dynamic_pointer_cast<SieveSection>(column.sections[sectionIndex])) {
        startLineEdit->setText(sieveSection->weirs.front()->name);
        endLineEdit->setText(sieveSection->weirs.back()->name);
        passesNumberComboBox->setCurrentText(QString::number(sieveSection->passesNumber));

        connect(passesNumberComboBox, &QComboBox::currentTextChanged, this, [this, sieveSection]() {
            sieveSection->passesNumber = passesNumberComboBox->currentText().toInt();
            emit sieveGeometry->passesNumberChanged(sieveSection->passesNumber);
        });
    }

    connect(projectRadioButton, &QRadioButton::clicked, this, &GeometryDataTab::onCalcModeChanged);
    connect(verificationRadioButton, &QRadioButton::clicked, this, &GeometryDataTab::onCalcModeChanged);
    connect(trayTypeComboBox, &QComboBox::currentTextChanged, this, &GeometryDataTab::onWeirTypeChanged);
}

void GeometryDataTab::onCalcModeChanged()
{
    if (projectRadioButton->isChecked()) {
        if (sieveGeometry != nullptr) emit sieveGeometry->calcModeChanged(false);
    }
    else {
        if (sieveGeometry != nullptr) emit sieveGeometry->calcModeChanged(true);
    }
}

void GeometryDataTab::onWeirTypeChanged(QString weirType)
{

}

GeometryDataTab::~GeometryDataTab() {}
