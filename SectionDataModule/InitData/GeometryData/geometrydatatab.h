#ifndef GEOMETRYDATATAB_H
#define GEOMETRYDATATAB_H

#include <QWidget>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>

#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QComboBox>

#include "WeirTypes/sievegeometry.h"
#include "../../../datatypes.h"

class GeometryDataTab : public QWidget
{
    Q_OBJECT
public:
    explicit GeometryDataTab(Column& column, int sectionIndex, QWidget *parent = nullptr);
    ~GeometryDataTab();

private:
    QVBoxLayout* mainVLayout;

    QWidget* infoContainer;
    QHBoxLayout* infoHLayout;

    QLabel* nameLabel;
    QLineEdit* nameLineEdit;
    QLabel* startLabel;
    QLineEdit* startLineEdit;
    QLabel* endLabel;
    QLineEdit* endLineEdit;
    QLabel* modeLabel;
    QRadioButton* projectRadioButton;
    QRadioButton* verificationRadioButton;

    QWidget* typeContainer;
    QHBoxLayout* typeHLayout;

    QLabel* trayTypeLabel;
    QLabel* passesNumberLabel;
    QComboBox* trayTypeComboBox;

    // Относится к ситчатым тарелкам
    QComboBox* passesNumberComboBox;
    SieveGeometry* sieveGeometry;

private slots:
    void onCalcModeChanged();
    void onWeirTypeChanged(QString weirType);
};

#endif // GEOMETRYDATATAB_H
