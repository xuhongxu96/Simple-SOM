#include "xscatterchart.h"
#include <QPainter>
#include <QDebug>

XScatterChart::XScatterChart(unsigned int w, unsigned int h, QWidget *parent)
    : QWidget(parent), w(w), h(h), buffer(QSize(w * CELL_SIZE + LIST_WIDTH, h * CELL_SIZE), QImage::Format_ARGB32)
{
}

void XScatterChart::showSOM(XSOM<char> &som)
{
    QPainter painter(&buffer);
    for (unsigned int i = 0; i < w; ++i) {
        for (unsigned int j = 0; j < h; ++j) {
            auto weights = som.nodes[i][j].getWeight();
            int r = fmin(255, fmax(0, weights[0] * 128 + weights[1] * 64 + weights[2] * 32  + weights[3] * 16));
            int g = fmin(255, fmax(0, weights[4] * 128 + weights[5] * 64 + weights[6] * 32  + weights[7] * 16));
            int b = fmin(255, fmax(0, weights[8] * 128 + weights[9] * 64 + weights[10] * 32 + weights[11] * 16 + weights[12] * 8));
            painter.setBrush(QBrush(QColor(r, g, b)));
            painter.drawRect(i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE, CELL_SIZE);
        }
    }
    this->som = &som;
}

void XScatterChart::addTip(const QString &name, std::pair<unsigned int, unsigned int> pt)
{
    QPainter painter(&buffer);
    auto weights = som->nodes[pt.first][pt.second].getWeight();
    int r = fmin(255, fmax(0, weights[0] * 128 + weights[1] * 64 + weights[2] * 32  + weights[3] * 16));
    int g = fmin(255, fmax(0, weights[4] * 128 + weights[5] * 64 + weights[6] * 32  + weights[7] * 16));
    int b = fmin(255, fmax(0, weights[8] * 128 + weights[9] * 64 + weights[10] * 32 + weights[11] * 16 + weights[12] * 8));
    painter.setBrush(QBrush(QColor(r, g, b)));
    painter.drawRect(w * CELL_SIZE + 10, 20 + n * 30, LIST_WIDTH - 20, 24);
    painter.drawText(QPointF(w * CELL_SIZE + 20, 35 + n * 30), name + "  " + QString::number(pt.first) + ", " + QString::number(pt.second));
    ++n;
}


void XScatterChart::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawImage(QPoint(0, 0), buffer);
}
