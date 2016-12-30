#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "xscatterchart.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    const unsigned int W = 15, H = 15;

    XScatterChart *chart;

    void calc();
};

#endif // MAINWINDOW_H
