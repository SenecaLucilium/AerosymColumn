#ifndef SECTIONSCHEME_H
#define SECTIONSCHEME_H

#include <QWidget>

#include <QPainter>
#include <QRandomGenerator>

class SectionsDiagram : public QWidget {
public:
    SectionsDiagram (QWidget *parent = nullptr) : QWidget(parent) {}
    void updateSection (std::vector<std::pair<int, int>> _sections) {
        sections = _sections;
        update();
    }

private:
    std::vector<std::pair<int, int>> sections;

    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);

        int width = this->size().width();
        int height = this->size().height();

        int centerX = width / 2;
        int columnRadius = width / 4;

        painter.setPen(Qt::black);

        painter.setBrush(Qt::gray);
        painter.drawChord(centerX - columnRadius, 0, 2 * columnRadius, 2 * columnRadius, 180 * 16, -180 * 16);

        int N;
        if (!sections.empty()) N = sections.back().second + 1;
        else N = 1;

        int weirHeight = (height - 2 * columnRadius) / N;

        int currentHeight = columnRadius;
        int currentSectionNumber = 1;
        for (auto& _pair : sections)
        {
            painter.drawLine(centerX - columnRadius, currentHeight, centerX - columnRadius - 20, currentHeight);
            painter.drawText(centerX - columnRadius - 60, currentHeight - 10, QString("Секция %1").arg(currentSectionNumber));

            painter.setBrush(generateColor(_pair.second));
            for (int i = _pair.first; i <= _pair.second; ++i) {
                QRect rect(centerX - columnRadius, currentHeight, 2 * columnRadius, weirHeight);

                painter.drawRect(rect);
                painter.drawText(rect.adjusted(10, 0, -10, 0), Qt::AlignVCenter | Qt::AlignLeft, QString::number(i + 1));

                currentHeight += weirHeight;
            }

            painter.drawLine(centerX - columnRadius, currentHeight, centerX - columnRadius - 20, currentHeight);
            currentSectionNumber++;
        }
        painter.setBrush(Qt::gray);
        painter.drawChord(centerX - columnRadius, currentHeight - columnRadius, 2 * columnRadius, 2 * columnRadius, 180 * 16, 180 * 16);
    }

    QColor generateColor(int index) { // Можно поменять на колор-пикер. Можно подобрать 10 цветов и брать их по очереди.
        QRandomGenerator generator(index);

        int red = generator.bounded(256);
        int green = generator.bounded(256);
        int blue = generator.bounded(256);
        return QColor(red, green, blue, 180);
    }
};

#endif // SECTIONSCHEME_H
