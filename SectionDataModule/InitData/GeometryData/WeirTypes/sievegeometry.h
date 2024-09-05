#ifndef SIEVEGEOMETRY_H
#define SIEVEGEOMETRY_H

#include <QWidget>
#include <QPainter>

#include <QVBoxLayout>
#include <QStackedLayout>

#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QStackedWidget>
#include <QRadioButton>
#include <QButtonGroup>

#include "../../../datatypes.h"

inline QPen getDashedPen () {
    QPen dashPen;
    dashPen.setDashPattern({5, 5});
    return dashPen;
}
inline QPen getThickPen () {
    QPen thickPen;
    thickPen.setWidth(3);
    return thickPen;
}
inline QPen getDefaultPen () {
    QPen defaultPen;
    return defaultPen;
}

inline void drawArrow(QPainter& painter, const QPointF& start, const QPointF& end)
{
    double angle = std::atan2(end.y() - start.y(), end.x() - start.x());

    double arrowSize = 7.0;

    QPointF arrowP1 = end + QPointF(cos(angle - M_PI / 6) * arrowSize, -sin(angle - M_PI / 6) * arrowSize);
    QPointF arrowP2 = end + QPointF(cos(angle + M_PI / 6) * arrowSize, -sin(angle + M_PI / 6) * arrowSize);

    QPolygonF arrowHead;
    arrowHead << end << arrowP1 << arrowP2;
    painter.setBrush(Qt::black);
    painter.drawPolygon(arrowHead);
}

class TopViewDiagram_2 : public QWidget {
public:
    TopViewDiagram_2 (QWidget *parent = nullptr) : QWidget(parent) {}
    ~TopViewDiagram_2() {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class TopViewDiagram_4 : public QWidget {
public:
    TopViewDiagram_4 (QWidget *parent = nullptr) : QWidget(parent) {}
    ~TopViewDiagram_4() {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class TopViewDiagram_6 : public QWidget {
public:
    TopViewDiagram_6 (QWidget *parent = nullptr) : QWidget(parent) {}
    ~TopViewDiagram_6() {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class TopViewDiagram_8 : public QWidget {
public:
    TopViewDiagram_8 (QWidget *parent = nullptr) : QWidget(parent) {}
    ~TopViewDiagram_8() {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class SideViewDiagram_2 : public QWidget {
public:
    SideViewDiagram_2 (QWidget *parent = nullptr) : QWidget(parent) {}
    ~SideViewDiagram_2() {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class SideViewDiagram_4 : public QWidget {
public:
    SideViewDiagram_4 (QWidget *parent = nullptr) : QWidget(parent) {}
    ~SideViewDiagram_4() {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class SideViewDiagram_6 : public QWidget {
public:
    SideViewDiagram_6 (QWidget *parent = nullptr) : QWidget(parent) {}
    ~SideViewDiagram_6() {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class SideViewDiagram_8 : public QWidget {
public:
    SideViewDiagram_8 (QWidget *parent = nullptr) : QWidget(parent) {}
    ~SideViewDiagram_8() {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class WeirDiagram : public QWidget
{
    Q_OBJECT
public:
    explicit WeirDiagram(QWidget *parent = nullptr);
    ~WeirDiagram() {};
public slots:
    void onPassesNumberChanged(int passesNumber);
private:
    QVBoxLayout* mainVLayout;

    QStackedWidget* topViewStack;
    TopViewDiagram_2* topViewDiagram2;
    TopViewDiagram_4* topViewDiagram4;
    TopViewDiagram_6* topViewDiagram6;
    TopViewDiagram_8* topViewDiagram8;

    QStackedWidget* sideViewStack;
    SideViewDiagram_2* sideViewDiagram2;
    SideViewDiagram_4* sideViewDiagram4;
    SideViewDiagram_6* sideViewDiagram6;
    SideViewDiagram_8* sideViewDiagram8;
};

class HoleDiagram : public QWidget
{
public:
    HoleDiagram (QWidget *parent = nullptr) : QWidget{parent} {}
protected:
    void paintEvent(QPaintEvent *event) override;
};

class MeasurementWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MeasurementWidget(const QString& initName, double initValue, const QString& unit, bool vertical, QWidget *parent = nullptr);
    ~MeasurementWidget() {};

    std::unordered_map <QString, double> unitValues;
    QLineEdit* value;
private:
    QHBoxLayout* hMainLayout;
    QVBoxLayout* vMainLayout;

    QWidget* vSubContainer;
    QHBoxLayout* hSubLayout;

    QLabel* name;
    QComboBox* units;

    const QStringList unitList;

    void initUnitValues (double initValue, const QString& initUnit);
    void updateValueFromComboBox (const QString& newUnit);
    void updateUnitsFromLineEdit (const QString& newValue);
};

class SieveGeometry : public QWidget
{
    Q_OBJECT
public:
    explicit SieveGeometry(Column& column, int sectionIndex, QWidget *parent = nullptr);
    ~SieveGeometry() {};

    //     void toggleVerification(bool enabled);

    // signals:
    //     void onPassesNumberChanged(int passesNumber);

private:
    QHBoxLayout* mainHLayout;

    QFrame* rightSchemeFrame;
    QVBoxLayout* rightSchemeFrameVLayout;
    WeirDiagram* weirDiagram;

    QWidget* leftSchemeContainer;
    QVBoxLayout* leftSchemeVLayout;

    QFrame* leftSchemeFrame;
    QVBoxLayout* leftSchemeFrameVLayout;

    HoleDiagram* holeDiagram;
    QLabel* imageLabel;
    MeasurementWidget* holeDiameter;

    QWidget* leftSchemeVerificationContainer;
    QGridLayout* leftSchemeVerificationGrid;

    QLabel* columnDiameterLabel;
    QComboBox* columnDiameterComboBox;
    QLabel* workingAreaLabel;
    QLineEdit* workingAreaLineEdit;

    QWidget* summaryContainer;
    QHBoxLayout* summaryHLayout;
    QLabel* summaryAreaHoleLabel;
    QRadioButton* summaryAreaHoleRadio;
    QLineEdit* summaryAreaHoleLineEdit;

    QWidget* percentContainer;
    QHBoxLayout* percentHLayout;
    QLabel* percentAreaHoleLabel;
    QRadioButton* percentAreaHoleRadio;
    QLineEdit* percentAreaHoleLineEdit;

    QLabel* chooseLabel;
    QComboBox* chooseComboBox;
    QLabel* perimeterLabel;
    QLineEdit* perimeterLineEdit;
    QLabel* widthOverflowLabel;
    QLineEdit* widthOverflowLineEdit;
    QLabel* crossSectionOverflowLabel;
    QLineEdit* crossSectionOverflowLineEdit;

signals:
    void passesNumberChanged(int passesNumber);
    void calcModeChanged(bool verificationMode);

private slots:
    void updateAreaSection(const QString& text);
    void updateLineEdits(int index);
    void updateChooseSection(const QString& text);
};

#endif // SIEVEGEOMETRY_H
