#ifndef GRAPHSECTIONDIAGRAM_H
#define GRAPHSECTIONDIAGRAM_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

#include "../../datatypes.h"

class GraphSectionDiagram : public QWidget {
    Q_OBJECT
public:
    GraphSectionDiagram (QWidget* parent = nullptr) : QWidget(parent), highlightedSection(-1), activeSection(-1) { setMouseTracking(true); }
    ~GraphSectionDiagram () {}

    void addInformation(std::vector <CalculationResults>& _results) {
        results = _results;
        update();
    }

signals:
    void weirChanged(int weirIndex);

private:
    std::vector <CalculationResults> results;
    int highlightedSection;
    int activeSection;

    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);

        int width = this->size().width();
        int height = this->size().height();

        int centerX = width / 2;
        int columnRadius = width / 4;

        painter.setPen(Qt::black);

        painter.setBrush(Qt::gray);
        painter.drawChord(centerX - columnRadius, 0, 2 * columnRadius, 2 * columnRadius, 180 * 16, -180 * 16);

        int weirHeight = (height - 2 * columnRadius) / (results.size() + 1);
        int currentHeight = columnRadius;
        for (size_t index = 0; index < results.size(); ++index)
        {
            if (results[index].condition_deviceHeight && results[index].condition_foamedHeight && results[index].condition_overflowDevice && results[index].condition_gasHoleSpeed &&
                results[index].condition_gasSpeed && results[index].condition_liquidFlow && results[index].condition_normalWork && results[index].condition_weirWork && results[index].condition_weirDistance)
                painter.setBrush(Qt::green);
            else painter.setBrush(Qt::red);

            if (static_cast<int>(index) == activeSection) painter.setPen(QPen(Qt::blue, 2));
            else if (static_cast<int>(index) == highlightedSection) painter.setPen(QPen(Qt::cyan, 2));
            else painter.setPen(QPen(Qt::black, 1));

            painter.drawRect(centerX - columnRadius, currentHeight, 2 * columnRadius, weirHeight);
            currentHeight += weirHeight;
        }

        painter.setBrush(Qt::gray);
        painter.drawChord(centerX - columnRadius, currentHeight - columnRadius, 2 * columnRadius, 2 * columnRadius, 180 * 16, 180 * 16);
    }

    void mouseMoveEvent(QMouseEvent* event) override {
        int width = this->size().width();
        int height = this->size().height();

        int centerX = width / 2;
        int columnRadius = width / 4;

        int weirHeight = (height - 2 * columnRadius) / (results.size() + 1);
        int currentHeight = columnRadius;

        highlightedSection = -1;

        for (size_t index = 0; index < results.size(); ++index) {
            QRect rect(centerX - columnRadius, currentHeight, 2 * columnRadius, weirHeight);

            if (rect.contains(event->pos())) {
                highlightedSection = index;
                break;
            }
            currentHeight += weirHeight;
        }

        update();
    }

    void mousePressEvent(QMouseEvent* event) override {
        int width = this->size().width();
        int height = this->size().height();

        int centerX = width / 2;
        int columnRadius = width / 4;

        int weirHeight = (height - 2 * columnRadius) / (results.size() + 1);
        int currentHeight = columnRadius;

        for (size_t index = 0; index < results.size(); ++index) {
            QRect rect(centerX - columnRadius, currentHeight, 2 * columnRadius, weirHeight);

            if (rect.contains(event->pos())) {
                activeSection = index;
                emit weirChanged(activeSection);
                break;
            }
            currentHeight += weirHeight;
        }

        update();
    }
};

#endif // GRAPHSECTIONDIAGRAM_H
