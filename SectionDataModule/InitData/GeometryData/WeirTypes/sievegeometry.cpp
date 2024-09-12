#include "sievegeometry.h"

void TopViewDiagram_2::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    int width = this->size().width();
    int height = this->size().height();

    int radius = 180;
    int centerX = width / 2;
    int centerY = height / 2;

    painter.setPen(getDefaultPen());
    painter.setBrush(Qt::darkGray);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 140 * 16, 80 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, -40 * 16, 80 * 16);

    painter.setBrush(Qt::NoBrush);
    painter.setPen(getDashedPen());
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 95 * 16, 170 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 275 * 16, 170 * 16);

    painter.setPen(getThickPen());
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);
}

void TopViewDiagram_4::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    int width = this->size().width();
    int height = this->size().height();

    int radius = 180;
    int centerX = width / 2;
    int centerY = height / 2;

    painter.setPen(getThickPen());
    painter.setBrush(Qt::darkGray);
    painter.drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);

    painter.setPen(getDefaultPen());
    painter.setBrush(Qt::white);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 95 * 16, 170 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 275 * 16, 170 * 16);

    painter.setBrush(Qt::darkGray);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 150 * 16, 60 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, -30 * 16, 60 * 16);

    painter.setPen(getDashedPen());
    painter.setBrush(Qt::NoBrush);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, -55 * 16, 110 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, -65 * 16, 130 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 115 * 16, 130 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 125 * 16, 110 * 16);
}

void TopViewDiagram_6::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    int width = this->size().width();
    int height = this->size().height();

    int radius = 180;
    int centerX = width / 2;
    int centerY = height / 2;

    painter.setPen(getDashedPen());
    painter.setBrush(Qt::NoBrush);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 95 * 16, 170 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 275 * 16, 170 * 16);

    painter.setPen(getDefaultPen());
    painter.setBrush(Qt::darkGray);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, -70 * 16, 140 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 110 * 16, 140 * 16);
    painter.setBrush(Qt::white);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, -65 * 16, 130 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 115 * 16, 130 * 16);

    painter.setPen(getDashedPen());
    painter.setBrush(Qt::NoBrush);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, -50 * 16, 100 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 130 * 16, 100 * 16);

    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, -45 * 16, 90 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 135 * 16, 90 * 16);

    painter.setPen(getDefaultPen());
    painter.setBrush(Qt::darkGray);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, -30 * 16, 60 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 150 * 16, 60 * 16);

    painter.setPen(getThickPen());
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);
}

void TopViewDiagram_8::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    int width = this->size().width();
    int height = this->size().height();

    int radius = 180;
    int centerX = width / 2;
    int centerY = height / 2;

    painter.setPen(getThickPen());
    painter.setBrush(Qt::darkGray);
    painter.drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);

    painter.setPen(getDefaultPen());
    painter.setBrush(Qt::white);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, -85 * 16, 170 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 95 * 16, 170 * 16);

    painter.setPen(getDashedPen());
    painter.setBrush(Qt::NoBrush);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, -75 * 16, 150 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 105 * 16, 150 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, -70 * 16, 140 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 110 * 16, 140 * 16);

    painter.setPen(getDefaultPen());
    painter.setBrush(Qt::darkGray);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, -60 * 16, 120 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 120 * 16, 120 * 16);
    painter.setBrush(Qt::white);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, -55 * 16, 110 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 125 * 16, 110 * 16);


    painter.setPen(getDashedPen());
    painter.setBrush(Qt::NoBrush);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, -45 * 16, 90 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 135 * 16, 90 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, -40 * 16, 80 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 140 * 16, 80 * 16);

    painter.setPen(getDefaultPen());
    painter.setBrush(Qt::darkGray);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, -30 * 16, 60 * 16);
    painter.drawChord(centerX - radius, centerY - radius, radius * 2, radius * 2, 150 * 16, 60 * 16);
}

void SideViewDiagram_2::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    int width = this->size().width();
    int height = this->size().height();

    int radius = 160;
    int centerX = width / 2;
    int centerY = height / 2;

    int plankHeight = 80;
    int plankWidth = 30;

    int offset = 20;

    painter.setPen(getDefaultPen());
    painter.drawLine(centerX - radius, centerY - plankHeight + offset, centerX + radius, centerY - plankHeight + offset);
    painter.drawLine(centerX - radius, centerY + offset, centerX + radius, centerY + offset);
    painter.drawLine(centerX - radius, centerY - plankHeight, centerX - radius, centerY + plankHeight);
    painter.drawLine(centerX + radius, centerY - plankHeight, centerX + radius, centerY + plankHeight);

    painter.setBrush(Qt::darkGray);
    painter.setPen(getDefaultPen());
    painter.drawRect(centerX - radius, centerY - plankHeight, plankWidth, plankHeight);
    painter.drawRect(centerX + radius - plankWidth, centerY - plankHeight, plankWidth, plankHeight);

    painter.setBrush(Qt::white);
    painter.setPen(getDashedPen());
    painter.drawRect(centerX - (plankWidth / 2), centerY, plankWidth, plankHeight);
}

void SideViewDiagram_4::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    int width = this->size().width();
    int height = this->size().height();

    int radius = 200;
    int centerX = width / 2;
    int centerY = height / 2;

    int plankHeight = 80;
    int plankWidth = 30;

    int offset = 20;

    painter.setPen(getDefaultPen());
    painter.drawLine(centerX - radius, centerY - plankHeight + offset, centerX + radius, centerY - plankHeight + offset);
    painter.drawLine(centerX - radius, centerY + offset, centerX + radius, centerY + offset);
    painter.drawLine(centerX - radius, centerY - plankHeight, centerX - radius, centerY + plankHeight);
    painter.drawLine(centerX + radius, centerY - plankHeight, centerX + radius, centerY + plankHeight);

    painter.setPen(getDashedPen());
    painter.drawLine(centerX, centerY - plankHeight, centerX, centerY + plankHeight);

    painter.setBrush(Qt::darkGray);
    painter.setPen(getDefaultPen());
    painter.drawRect(centerX - radius, centerY - plankHeight, plankWidth, plankHeight);
    painter.drawRect(centerX - (plankWidth / 2), centerY - plankHeight, plankWidth, plankHeight);
    painter.drawRect(centerX + radius - plankWidth, centerY - plankHeight, plankWidth, plankHeight);

    painter.setBrush(Qt::white);
    painter.setPen(getDashedPen());
    painter.drawRect(centerX - (radius / 2) - (plankWidth / 2), centerY, plankWidth, plankHeight);
    painter.drawRect(centerX + (radius / 2) - (plankWidth / 2), centerY, plankWidth, plankHeight);
}

void SideViewDiagram_6::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    int width = this->size().width();
    int height = this->size().height();

    int radius = 240;
    int centerX = width / 2;
    int centerY = height / 2;

    int plankHeight = 80;
    int plankWidth = 30;

    int offset = 20;

    painter.setPen(getDefaultPen());
    painter.drawLine(centerX - radius, centerY - plankHeight + offset, centerX + radius, centerY - plankHeight + offset);
    painter.drawLine(centerX - radius, centerY + offset, centerX + radius, centerY + offset);
    painter.drawLine(centerX - radius, centerY + plankHeight + offset, centerX + radius, centerY + plankHeight + offset);
    painter.drawLine(centerX - radius, centerY - plankHeight, centerX - radius, centerY + plankHeight);
    painter.drawLine(centerX + radius, centerY - plankHeight, centerX + radius, centerY + plankHeight);

    painter.setPen(getDashedPen());
    painter.drawLine(centerX, centerY - plankHeight, centerX, centerY + plankHeight * 2);
    painter.drawLine(centerX - (radius / 2) - plankWidth, centerY - plankHeight,
                     centerX - (radius / 2) - plankWidth, centerY + plankHeight * 2);
    painter.drawLine(centerX + (radius / 2) + plankWidth, centerY - plankHeight,
                     centerX + (radius / 2) + plankWidth, centerY + plankHeight * 2);

    painter.setBrush(Qt::darkGray);
    painter.setPen(getDefaultPen());
    painter.drawRect(centerX - radius, centerY - plankHeight, plankWidth, plankHeight);
    painter.drawRect(centerX - radius + (radius * 2 / 3) - (plankWidth / 2), centerY - plankHeight, plankWidth, plankHeight);
    painter.drawRect(centerX - radius + (radius * 4 / 3) - (plankWidth / 2), centerY - plankHeight, plankWidth, plankHeight);
    painter.drawRect(centerX + radius - plankWidth, centerY - plankHeight, plankWidth, plankHeight);

    painter.setBrush(Qt::white);
    painter.setPen(getDashedPen());
    painter.drawRect(centerX - (radius / 2) - (plankWidth / 2) - plankWidth, centerY, plankWidth, plankHeight);
    painter.drawRect(centerX - (plankWidth / 2), centerY, plankWidth, plankHeight);
    painter.drawRect(centerX + (radius / 2) + (plankWidth / 2), centerY, plankWidth, plankHeight);

    painter.setBrush(Qt::darkGray);
    painter.setPen(getDefaultPen());
    painter.drawRect(centerX - radius, centerY + plankHeight, plankWidth, plankHeight);
    painter.drawRect(centerX - radius + (radius * 2 / 3) - (plankWidth / 2), centerY + plankHeight, plankWidth, plankHeight);
    painter.drawRect(centerX - radius + (radius * 4 / 3) - (plankWidth / 2), centerY + plankHeight, plankWidth, plankHeight);
    painter.drawRect(centerX + radius - plankWidth, centerY + plankHeight, plankWidth, plankHeight);
}

void SideViewDiagram_8::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    int width = this->size().width();
    int height = this->size().height();

    int radius = 280;
    int centerX = width / 2;
    int centerY = height / 2;

    int plankHeight = 80;
    int plankWidth = 30;

    int offset = 20;

    painter.setPen(getDefaultPen());
    painter.drawLine(centerX - radius, centerY - plankHeight + offset, centerX + radius, centerY - plankHeight + offset);
    painter.drawLine(centerX - radius, centerY + offset, centerX + radius, centerY + offset);
    painter.drawLine(centerX - radius, centerY + plankHeight + offset, centerX + radius, centerY + plankHeight + offset);
    painter.drawLine(centerX - radius, centerY - plankHeight, centerX - radius, centerY + plankHeight);
    painter.drawLine(centerX + radius, centerY - plankHeight, centerX + radius, centerY + plankHeight);

    painter.setPen(getDashedPen());
    painter.drawLine(centerX - (3 * radius / 4) + (3 * plankWidth / 8), centerY - plankHeight,
                     centerX - (3 * radius / 4) + (3 * plankWidth / 8), centerY + 2 * plankHeight);
    painter.drawLine(centerX - (radius / 4) + (plankWidth / 8), centerY - plankHeight,
                     centerX - (radius / 4) + (plankWidth / 8), centerY + 2 * plankHeight);
    painter.drawLine(centerX + (radius / 4) - (plankWidth / 8), centerY - plankHeight,
                     centerX + (radius / 4) - (plankWidth / 8), centerY + 2 * plankHeight);
    painter.drawLine(centerX + (3 * radius / 4) - (3 * plankWidth / 8), centerY - plankHeight,
                     centerX + (3 * radius / 4) - (3 * plankWidth / 8), centerY + 2 * plankHeight);

    painter.setBrush(Qt::darkGray);
    painter.setPen(getDefaultPen());
    painter.drawRect(centerX - radius, centerY + plankHeight, plankWidth, plankHeight);
    painter.drawRect(centerX - (radius / 2) - (plankWidth / 4), centerY + plankHeight, plankWidth, plankHeight);
    painter.drawRect(centerX - (plankWidth / 2), centerY + plankHeight, plankWidth, plankHeight);
    painter.drawRect(centerX + (radius / 2) - (3 * plankWidth / 4), centerY + plankHeight, plankWidth, plankHeight);
    painter.drawRect(centerX + radius - plankWidth, centerY + plankHeight, plankWidth, plankHeight);

    painter.setBrush(Qt::white);
    painter.setPen(getDashedPen());
    painter.drawRect(centerX - (3 * radius / 4) + (3 * plankWidth / 8) - (plankWidth / 2), centerY, plankWidth, plankHeight);
    painter.drawRect(centerX - (radius / 4) + (plankWidth / 8) - (plankWidth / 2), centerY, plankWidth, plankHeight);
    painter.drawRect(centerX + (radius / 4) - (plankWidth / 8) - (plankWidth / 2), centerY, plankWidth, plankHeight);
    painter.drawRect(centerX + (3 * radius / 4) - (3 * plankWidth / 8) - (plankWidth / 2), centerY, plankWidth, plankHeight);

    painter.setBrush(Qt::darkGray);
    painter.setPen(getDefaultPen());
    painter.drawRect(centerX - radius, centerY - plankHeight, plankWidth, plankHeight);
    painter.drawRect(centerX - (radius / 2) - (plankWidth / 4), centerY - plankHeight, plankWidth, plankHeight);
    painter.drawRect(centerX - (plankWidth / 2), centerY - plankHeight, plankWidth, plankHeight);
    painter.drawRect(centerX + (radius / 2) - (3 * plankWidth / 4), centerY - plankHeight, plankWidth, plankHeight);
    painter.drawRect(centerX + radius - plankWidth, centerY - plankHeight, plankWidth, plankHeight);
}

WeirDiagram::WeirDiagram(QWidget *parent) : QWidget{parent}
{
    topViewStack = new QStackedWidget(this);
    topViewDiagram2 = new TopViewDiagram_2(topViewStack);
    topViewDiagram4 = new TopViewDiagram_4(topViewStack);
    topViewDiagram6 = new TopViewDiagram_6(topViewStack);
    topViewDiagram8 = new TopViewDiagram_8(topViewStack);

    topViewStack->addWidget(topViewDiagram2);
    topViewStack->addWidget(topViewDiagram4);
    topViewStack->addWidget(topViewDiagram6);
    topViewStack->addWidget(topViewDiagram8);

    sideViewStack = new QStackedWidget(this);
    sideViewDiagram2 = new SideViewDiagram_2(sideViewStack);
    sideViewDiagram4 = new SideViewDiagram_4(sideViewStack);
    sideViewDiagram6 = new SideViewDiagram_6(sideViewStack);
    sideViewDiagram8 = new SideViewDiagram_8(sideViewStack);

    sideViewStack->addWidget(sideViewDiagram2);
    sideViewStack->addWidget(sideViewDiagram4);
    sideViewStack->addWidget(sideViewDiagram6);
    sideViewStack->addWidget(sideViewDiagram8);

    mainVLayout = new QVBoxLayout();
    mainVLayout->addWidget(topViewStack, 1);
    mainVLayout->addWidget(sideViewStack, 1);

    mainVLayout->setContentsMargins(0, 0, 0, 0);
    mainVLayout->setSpacing(0);

    setLayout(mainVLayout);
}

void WeirDiagram::onPassesNumberChanged(int passesNumber)
{
    switch (passesNumber) {
    case (2):
        topViewStack->setCurrentWidget(topViewDiagram2);
        sideViewStack->setCurrentWidget(sideViewDiagram2);
        break;
    case (4):
        topViewStack->setCurrentWidget(topViewDiagram4);
        sideViewStack->setCurrentWidget(sideViewDiagram4);
        break;
    case (6):
        topViewStack->setCurrentWidget(topViewDiagram6);
        sideViewStack->setCurrentWidget(sideViewDiagram6);
        break;
    case (8):
        topViewStack->setCurrentWidget(topViewDiagram8);
        sideViewStack->setCurrentWidget(sideViewDiagram8);
        break;
    }
}

void HoleDiagram::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    int xLevel = 170;
    int yLevel = 100;

    QPointF leftPoint(xLevel, yLevel);
    QPointF leftPointH(xLevel - 1, yLevel);
    QPointF rightPoint(xLevel + 85, yLevel);
    QPointF rightPointH(xLevel + 85 + 1, yLevel);

    painter.drawLine(leftPoint.x(), leftPoint.y() - 10, leftPoint.x(), leftPoint.y() + 10);
    painter.drawLine(rightPoint.x(), rightPoint.y() - 10, rightPoint.x(), rightPoint.y() + 10);
    painter.drawLine(leftPoint, rightPoint);

    drawArrow(painter, leftPointH, leftPoint);
    drawArrow(painter, rightPointH, rightPoint);
}

MeasurementWidget::MeasurementWidget(const QString& initName, double initValue, const QString& unit, bool vertical, QWidget *parent)
    : QWidget{parent}, unitList({"мм", "см", "м"})
{
    // if (!unitList.contains(unit)) throw std::invalid_argument("Invalid unit");
    initUnitValues(initValue, unit);

    name = new QLabel(initName, this);

    QDoubleValidator* DoubleValidator = new QDoubleValidator(this);
    DoubleValidator->setDecimals(5);
    DoubleValidator->setNotation(QDoubleValidator::StandardNotation);

    value = new QLineEdit(this);
    value->setValidator(DoubleValidator);
    value->setAlignment(Qt::AlignRight);
    value->setText(QString::number (initValue));
    value->setMaximumWidth(60);

    units = new QComboBox(this);
    units->addItems(unitList);
    units->setCurrentText(unit);
    units->setMaximumWidth(45);

    connect(units, &QComboBox::currentTextChanged, this, &MeasurementWidget::updateValueFromComboBox);
    connect(value, &QLineEdit::textChanged, this, &MeasurementWidget::updateUnitsFromLineEdit);

    if (vertical)
    {
        vSubContainer = new QWidget(this);
        {
            hSubLayout = new QHBoxLayout();

            hSubLayout->addWidget(value);
            hSubLayout->addWidget(units);

            vSubContainer->setLayout(hSubLayout);
        }

        vMainLayout = new QVBoxLayout();
        vMainLayout->setSpacing(0);

        vMainLayout->addWidget(name);
        vMainLayout->addWidget(vSubContainer);

        setLayout(vMainLayout);
    }
    else
    {
        hMainLayout = new QHBoxLayout();

        hMainLayout->addWidget(name);
        hMainLayout->addWidget(value);
        hMainLayout->addWidget(units);

        setLayout(hMainLayout);
    }
}

void MeasurementWidget::initUnitValues (double initValue, const QString& initUnit)
{
    if (initUnit == "мм") {
        unitValues["мм"] = initValue;
        unitValues["см"] = initValue * 0.1;
        unitValues["м"] = initValue * 0.01;
    }
    else if (initUnit == "см") {
        unitValues["см"] = initValue;
        unitValues["мм"] = initValue * 10;
        unitValues["м"] = initValue * 0.1;
    }
    else if (initUnit == "м") {
        unitValues["м"] = initValue;
        unitValues["мм"] = initValue * 100;
        unitValues["см"] = initValue * 10;
    }
}

void MeasurementWidget::updateValueFromComboBox (const QString& newUnit) { value->setText(QString::number(unitValues[newUnit])); }

void MeasurementWidget::updateUnitsFromLineEdit (const QString& newValue) { initUnitValues(newValue.toDouble(), units->currentText()); }

SieveGeometry::SieveGeometry(Column& column, int sectionIndex, QWidget *parent)
    : QWidget{parent}
{
    std::shared_ptr<SieveSection> sieveSection = std::dynamic_pointer_cast<SieveSection>(column.sections[sectionIndex]);

    QDoubleValidator* DoubleValidator = new QDoubleValidator(this);
    DoubleValidator->setDecimals(5);
    DoubleValidator->setNotation(QDoubleValidator::StandardNotation);

    leftSchemeContainer = new QWidget(this);
    {
        leftSchemeFrame = new QFrame(leftSchemeContainer);
        {
            leftSchemeFrame->setMinimumHeight(250);
            leftSchemeFrame->setFrameStyle(QFrame::Box | QFrame::Plain);
            leftSchemeFrame->setLineWidth(1);

            holeDiagram = new HoleDiagram(leftSchemeFrame);

            imageLabel = new QLabel(leftSchemeFrame);
            QPixmap pixmap (":/3dmodel.png");
            imageLabel->setPixmap(pixmap);

            leftSchemeFrameVLayout = new QVBoxLayout();
            leftSchemeFrameVLayout->addWidget(holeDiagram, 1);
            leftSchemeFrameVLayout->addWidget(imageLabel, 1, Qt::AlignCenter);
            leftSchemeFrame->setLayout(leftSchemeFrameVLayout);

            holeDiameter = new MeasurementWidget("Диаметр отверстия", sieveSection->holeDiameter, "м", true, holeDiagram);
            holeDiameter->setGeometry(145, 5, 150, 80);
        }

        leftSchemeVerificationContainer = new QWidget(leftSchemeContainer);
        {
            columnDiameterLabel = new QLabel("Диаметр колонны (м)", leftSchemeVerificationContainer);
            columnDiameterComboBox = new QComboBox(leftSchemeVerificationContainer);
            columnDiameterComboBox->addItems({"1.0", "1.2", "1.4", "1.6", "1.8",
                                              "2", "2.2", "2.4", "2.6", "2.8",
                                              "3", "3.2", "3.4", "3.6"});
            columnDiameterComboBox->setMinimumWidth(60);

            workingAreaLabel = new QLabel("Рабочая площадь тарелки (м^2)", leftSchemeVerificationContainer);
            workingAreaLineEdit = new QLineEdit(leftSchemeVerificationContainer);
            workingAreaLineEdit->setValidator(DoubleValidator);
            workingAreaLineEdit->setAlignment(Qt::AlignRight);

            summaryAreaHoleLabel = new QLabel("Общая площадь отверстий тарелки (м^2)", leftSchemeVerificationContainer);
            summaryContainer = new QWidget(leftSchemeVerificationContainer);
            {
                summaryAreaHoleRadio = new QRadioButton(summaryContainer);
                summaryAreaHoleLineEdit = new QLineEdit(summaryContainer);
                summaryAreaHoleLineEdit->setValidator(DoubleValidator);
                summaryAreaHoleLineEdit->setAlignment(Qt::AlignRight);

                summaryAreaHoleRadio->setChecked(true);
                summaryAreaHoleLineEdit->setEnabled(true);

                summaryHLayout = new QHBoxLayout();
                summaryHLayout->addWidget(summaryAreaHoleRadio);
                summaryHLayout->addWidget(summaryAreaHoleLineEdit);
                summaryContainer->setLayout(summaryHLayout);
            }
            percentAreaHoleLabel = new QLabel("Относительное свободное сечение колонны (%)", leftSchemeVerificationContainer);
            percentContainer = new QWidget(leftSchemeVerificationContainer);
            {
                percentAreaHoleRadio = new QRadioButton(percentContainer);
                percentAreaHoleLineEdit = new QLineEdit(percentContainer);
                percentAreaHoleLineEdit->setValidator(DoubleValidator);
                percentAreaHoleLineEdit->setAlignment(Qt::AlignRight);

                percentAreaHoleRadio->setChecked(false);
                percentAreaHoleLineEdit->setEnabled(false);

                percentHLayout = new QHBoxLayout();
                percentHLayout->addWidget(percentAreaHoleRadio);
                percentHLayout->addWidget(percentAreaHoleLineEdit);
                percentContainer->setLayout(percentHLayout);
            }

            QButtonGroup* radioGroup = new QButtonGroup();
            radioGroup->addButton(summaryAreaHoleRadio);
            radioGroup->addButton(percentAreaHoleRadio);

            chooseLabel = new QLabel("Задать начальные", leftSchemeVerificationContainer);
            chooseComboBox = new QComboBox(leftSchemeVerificationContainer);
            chooseComboBox->addItems({"b и S", "b и F", "S и F"});

            perimeterLabel = new QLabel("b: Периметр слива (м)", leftSchemeVerificationContainer);
            widthOverflowLabel = new QLabel("S: Ширина перелива (мм)", leftSchemeVerificationContainer);
            crossSectionOverflowLabel = new QLabel("F: Сечение перелива (м^2)", leftSchemeVerificationContainer);

            perimeterLineEdit = new QLineEdit(leftSchemeVerificationContainer);
            perimeterLineEdit->setValidator(DoubleValidator);
            perimeterLineEdit->setAlignment(Qt::AlignRight);

            widthOverflowLineEdit = new QLineEdit(leftSchemeVerificationContainer);
            widthOverflowLineEdit->setValidator(DoubleValidator);
            widthOverflowLineEdit->setAlignment(Qt::AlignRight);

            crossSectionOverflowLineEdit = new QLineEdit(leftSchemeVerificationContainer);
            crossSectionOverflowLineEdit->setValidator(DoubleValidator);
            crossSectionOverflowLineEdit->setAlignment(Qt::AlignRight);
            crossSectionOverflowLineEdit->setEnabled(false);

            leftSchemeVerificationGrid = new QGridLayout();

            leftSchemeVerificationGrid->addWidget(columnDiameterLabel, 0, 0, Qt::AlignLeft);
            leftSchemeVerificationGrid->addWidget(columnDiameterComboBox, 0, 1, Qt::AlignRight);

            leftSchemeVerificationGrid->addWidget(workingAreaLabel, 1, 0, Qt::AlignLeft);
            leftSchemeVerificationGrid->addWidget(workingAreaLineEdit, 1, 1, Qt::AlignRight);

            leftSchemeVerificationGrid->addWidget(summaryAreaHoleLabel, 2, 0, Qt::AlignLeft);
            leftSchemeVerificationGrid->addWidget(summaryContainer, 2, 1, Qt::AlignRight);
            leftSchemeVerificationGrid->addWidget(percentAreaHoleLabel, 3, 0, Qt::AlignLeft);
            leftSchemeVerificationGrid->addWidget(percentContainer, 3, 1, Qt::AlignRight);

            leftSchemeVerificationGrid->addWidget(chooseLabel, 4, 0, Qt::AlignLeft);
            leftSchemeVerificationGrid->addWidget(chooseComboBox, 4, 1, Qt::AlignRight);

            leftSchemeVerificationGrid->addWidget(perimeterLabel, 5, 0, Qt::AlignLeft);
            leftSchemeVerificationGrid->addWidget(perimeterLineEdit, 5, 1, Qt::AlignRight);
            leftSchemeVerificationGrid->addWidget(widthOverflowLabel, 6, 0, Qt::AlignLeft);
            leftSchemeVerificationGrid->addWidget(widthOverflowLineEdit, 6, 1, Qt::AlignRight);
            leftSchemeVerificationGrid->addWidget(crossSectionOverflowLabel, 7, 0, Qt::AlignLeft);
            leftSchemeVerificationGrid->addWidget(crossSectionOverflowLineEdit, 7, 1, Qt::AlignRight);

            QSpacerItem* spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
            leftSchemeVerificationGrid->addItem(spacer, 8, 0, 1, 2);

            leftSchemeVerificationGrid->setColumnStretch(0, 8);
            leftSchemeVerificationGrid->setColumnStretch(1, 2);
            leftSchemeVerificationContainer->setLayout(leftSchemeVerificationGrid);
        }

        leftSchemeVLayout = new QVBoxLayout();
        leftSchemeVLayout->addWidget(leftSchemeFrame, 3);
        leftSchemeVLayout->addWidget(leftSchemeVerificationContainer, 6);
        leftSchemeContainer->setLayout(leftSchemeVLayout);
    }

    rightSchemeFrame = new QFrame(this);
    {
        rightSchemeFrame->setMinimumHeight(750);
        rightSchemeFrame->setFrameStyle(QFrame::Box | QFrame::Plain);
        rightSchemeFrame->setLineWidth(1);

        weirDiagram = new WeirDiagram(rightSchemeFrame);

        rightSchemeFrameVLayout = new QVBoxLayout();
        rightSchemeFrameVLayout->addWidget(weirDiagram);
        rightSchemeFrame->setLayout(rightSchemeFrameVLayout);
    }

    mainHLayout = new QHBoxLayout();
    mainHLayout->addWidget(leftSchemeContainer, 3);
    mainHLayout->addWidget(rightSchemeFrame, 5);
    setLayout(mainHLayout);

    if (auto sieveSectionVerification = std::dynamic_pointer_cast<SieveSectionVerification>(sieveSection)) {
        columnDiameterComboBox->setCurrentText(QString::number(sieveSectionVerification->columnDiameter, 'g', 2));
        workingAreaLineEdit->setText(QString::number(sieveSectionVerification->workingArea));
        summaryAreaHoleLineEdit->setText(QString::number(sieveSectionVerification->summaryArea));
        percentAreaHoleLineEdit->setText(QString::number(sieveSectionVerification->percentArea));
        perimeterLineEdit->setText(QString::number(sieveSectionVerification->perimeter));
        widthOverflowLineEdit->setText(QString::number(sieveSectionVerification->widthOverflow));
        crossSectionOverflowLineEdit->setText(QString::number(sieveSectionVerification->crossSectionOverflow));
        leftSchemeVerificationContainer->setEnabled(true);
    }
    else {
        columnDiameterComboBox->setCurrentText(QString::number(1.0, 'g', 2));
        workingAreaLineEdit->setText(QString::number(0.0));
        summaryAreaHoleLineEdit->setText(QString::number(0.0));
        percentAreaHoleLineEdit->setText(QString::number(0.0));
        perimeterLineEdit->setText(QString::number(0.0));
        widthOverflowLineEdit->setText(QString::number(0.0));
        crossSectionOverflowLineEdit->setText(QString::number(0.0));
        leftSchemeVerificationContainer->setDisabled(true);
    }

    connect(this, &SieveGeometry::passesNumberChanged, weirDiagram, &WeirDiagram::onPassesNumberChanged);
    connect(this, &SieveGeometry::calcModeChanged, this, [this, &column, sectionIndex](bool verificationMode) {
        auto sieveSection = std::dynamic_pointer_cast<SieveSection>(column.sections[sectionIndex]);
        if (verificationMode) {
            auto sieveSectionVerification = std::make_shared<SieveSectionVerification>(*sieveSection);
            sieveSectionVerification->calcType = "Поверочный";
            sieveSectionVerification->columnDiameter = columnDiameterComboBox->currentText().toDouble();
            sieveSectionVerification->workingArea = workingAreaLineEdit->text().toDouble();
            sieveSectionVerification->summaryArea = summaryAreaHoleLineEdit->text().toDouble();
            sieveSectionVerification->percentArea = percentAreaHoleLineEdit->text().toDouble();
            sieveSectionVerification->perimeter = perimeterLineEdit->text().toDouble();
            sieveSectionVerification->widthOverflow = widthOverflowLineEdit->text().toDouble();
            sieveSectionVerification->crossSectionOverflow = crossSectionOverflowLineEdit->text().toDouble();

            leftSchemeVerificationContainer->setEnabled(true);
            column.sections[sectionIndex] = sieveSectionVerification;
        }
        else {
            column.sections[sectionIndex] = std::make_shared<SieveSection>(*sieveSection);
            column.sections[sectionIndex]->calcType = "Проектный";
            leftSchemeVerificationContainer->setDisabled(true);
        }
    });

    connect(summaryAreaHoleLineEdit, &QLineEdit::textChanged, this, &SieveGeometry::updateAreaSection);
    connect(percentAreaHoleLineEdit, &QLineEdit::textChanged, this, &SieveGeometry::updateAreaSection);
    updateAreaSection("");

    connect(chooseComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SieveGeometry::updateLineEdits);

    connect(perimeterLineEdit, &QLineEdit::textChanged, this, &SieveGeometry::updateChooseSection);
    connect(widthOverflowLineEdit, &QLineEdit::textChanged, this, &SieveGeometry::updateChooseSection);
    connect(crossSectionOverflowLineEdit, &QLineEdit::textChanged, this, &SieveGeometry::updateChooseSection);
    updateChooseSection("");

    connect(summaryAreaHoleRadio, &QRadioButton::toggled, summaryAreaHoleLineEdit, &QLineEdit::setEnabled);
    connect(percentAreaHoleRadio, &QRadioButton::toggled, percentAreaHoleLineEdit, &QLineEdit::setEnabled);

    connect(holeDiameter->value, &QLineEdit::textChanged, this, [this, &column, sectionIndex](){
        auto sieveSection = std::dynamic_pointer_cast<SieveSection>(column.sections[sectionIndex]);
        sieveSection->holeDiameter = holeDiameter->unitValues["м"];
    });

    connect(columnDiameterComboBox, &QComboBox::currentTextChanged, this, [this, &column, sectionIndex]() {
        auto sieveSectionVerification = std::dynamic_pointer_cast<SieveSectionVerification>(column.sections[sectionIndex]);
        sieveSectionVerification->columnDiameter = columnDiameterComboBox->currentText().toDouble();
    });
    connect(workingAreaLineEdit, &QLineEdit::textChanged, this, [this, &column, sectionIndex]() {
        auto sieveSectionVerification = std::dynamic_pointer_cast<SieveSectionVerification>(column.sections[sectionIndex]);
        sieveSectionVerification->workingArea = workingAreaLineEdit->text().toDouble();
    });
    connect(summaryAreaHoleLineEdit, &QLineEdit::textChanged, this, [this, &column, sectionIndex]() {
        auto sieveSectionVerification = std::dynamic_pointer_cast<SieveSectionVerification>(column.sections[sectionIndex]);
        sieveSectionVerification->summaryArea = summaryAreaHoleLineEdit->text().toDouble();
    });
    connect(percentAreaHoleLineEdit, &QLineEdit::textChanged, this, [this, &column, sectionIndex]() {
        auto sieveSectionVerification = std::dynamic_pointer_cast<SieveSectionVerification>(column.sections[sectionIndex]);
        sieveSectionVerification->percentArea = percentAreaHoleLineEdit->text().toDouble();
    });
    connect(perimeterLineEdit, &QLineEdit::textChanged, this, [this, &column, sectionIndex]() {
        auto sieveSectionVerification = std::dynamic_pointer_cast<SieveSectionVerification>(column.sections[sectionIndex]);
        sieveSectionVerification->perimeter = perimeterLineEdit->text().toDouble();
    });
    connect(widthOverflowLineEdit, &QLineEdit::textChanged, this, [this, &column, sectionIndex]() {
        auto sieveSectionVerification = std::dynamic_pointer_cast<SieveSectionVerification>(column.sections[sectionIndex]);
        sieveSectionVerification->widthOverflow = widthOverflowLineEdit->text().toDouble();
    });
    connect(crossSectionOverflowLineEdit, &QLineEdit::textChanged, this, [this, &column, sectionIndex]() {
        auto sieveSectionVerification = std::dynamic_pointer_cast<SieveSectionVerification>(column.sections[sectionIndex]);
        sieveSectionVerification->crossSectionOverflow = crossSectionOverflowLineEdit->text().toDouble();
    });
}

void SieveGeometry::updateAreaSection(const QString& text)
{
    double columnArea = (M_PI / 4) * pow(columnDiameterComboBox->currentText().toDouble(), 2);
    double newValue;

    if(summaryAreaHoleRadio->isChecked()) {
        newValue = (summaryAreaHoleLineEdit->text().toDouble() / columnArea) * 100;
        percentAreaHoleLineEdit->setText(QString::number(newValue));
    }
    else {
        newValue = (percentAreaHoleLineEdit->text().toDouble() * columnArea) / 100;
        summaryAreaHoleLineEdit->setText(QString::number(newValue));
    }
}

void SieveGeometry::updateLineEdits(int index)
{
    switch(index)
    {
    case 0:
        perimeterLineEdit->setEnabled(true);
        widthOverflowLineEdit->setEnabled(true);
        crossSectionOverflowLineEdit->setEnabled(false);
        break;
    case 1:
        perimeterLineEdit->setEnabled(true);
        widthOverflowLineEdit->setEnabled(false);
        crossSectionOverflowLineEdit->setEnabled(true);
        break;
    case 2:
        perimeterLineEdit->setEnabled(false);
        widthOverflowLineEdit->setEnabled(true);
        crossSectionOverflowLineEdit->setEnabled(true);
        break;
    }
}

void SieveGeometry::updateChooseSection(const QString& text)
{
    double newValue;
    switch(chooseComboBox->currentIndex())
    {
    case 0:
        newValue = (perimeterLineEdit->text().toDouble() * widthOverflowLineEdit->text().toDouble())/2000;
        crossSectionOverflowLineEdit->setText(QString::number(newValue));
        break;
    case 1:
        newValue = (crossSectionOverflowLineEdit->text().toDouble() / perimeterLineEdit->text().toDouble())*2000;
        widthOverflowLineEdit->setText(QString::number(newValue));
        break;
    case 2:
        newValue = (crossSectionOverflowLineEdit->text().toDouble() / (widthOverflowLineEdit->text().toDouble()/1000))*2;
        perimeterLineEdit->setText(QString::number(newValue));
        break;
    }
}

