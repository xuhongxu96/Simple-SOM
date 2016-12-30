#ifndef XSCATTERCHART_H
#define XSCATTERCHART_H

#include <vector>
#include <utility>
#include <QWidget>
#include <QBitmap>
#include "xsom.h"

class XScatterChart : public QWidget
{
    Q_OBJECT
public:
    XScatterChart(unsigned int w, unsigned int h, QWidget *parent = 0);
    void showSOM(XSOM<char> &som);
    QSize sizeHint() const { return buffer.size(); }
    QSize minimumSizeHint() const { return buffer.size(); }
    void addTip(const QString &name, std::pair<unsigned int, unsigned int> pt);
private:
    const unsigned int CELL_SIZE = 50, LIST_WIDTH = 150;
    unsigned int w, h;
    unsigned int n;
    QImage buffer;
    XSOM<char> *som;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // XSCATTERCHART_H
