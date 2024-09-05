#ifndef INITIALDATATAB_H
#define INITIALDATATAB_H

#include <QWidget>

#include <QTabWidget>

#include "GeometryData/geometrydatatab.h"
#include "ParamsData/paramsdatatab.h"
#include "SummaryData/summarydatatab.h"

#include "../../datatypes.h"

#include <QProxyStyle>
#include <QTabBar>
#include <QStyleOptionTab>

class CustomTabStyle : public QProxyStyle {
public:
    QSize sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& size, const QWidget* widget) const
    {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab) s.transpose();
        return s;
    }

    void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const{
        if (element == CE_TabBarTabLabel) {
            if (const QStyleOptionTab* tab = qstyleoption_cast<const QStyleOptionTab*>(option)) {
                QStyleOptionTab opt(*tab);
                opt.shape = QTabBar::RoundedNorth;
                QProxyStyle::drawControl(element, &opt, painter, widget);
                return;
            }
        }
        QProxyStyle::drawControl(element, option, painter, widget);
    }
};

class InitialDataTab : public QWidget
{
    Q_OBJECT
public:
    explicit InitialDataTab(Column& column, int sectionIndex, QWidget *parent = nullptr);
    ~InitialDataTab();

private:
    GeometryDataTab* geometryDataTab;
    ParamsDataTab* paramsDataTab;
    SummaryDataTab* summaryDataTab;

    QTabWidget* verticalTabWidget;
};

#endif // INITIALDATATAB_H
