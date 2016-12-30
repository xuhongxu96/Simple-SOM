#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xsom.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    chart = new XScatterChart(W, H, this);
    calc();
    setCentralWidget(chart);
}

MainWindow::~MainWindow()
{
}

void MainWindow::calc()
{
    XSOM<char> som(W, H, 13);
    char animals[][10] = {
        "Hen", "Dove", "Dog", "Tiger", "Zebra", "Goose", "Cat", "Horse", "Eagle", "Lion",
        "Owl", "Fox", "Wolf", "Hawk", "Duck", "Cow"
    };
    std::vector<std::vector<char>> samples = {
        {1,0,0,1,0,0,0,0,1,0,0,0,0},        // Hen
        {1,0,0,1,0,0,0,0,1,0,0,1,0},        // Dove
        {0,1,0,0,1,1,0,0,0,0,1,0,0},        // Dog
        {0,0,1,0,1,1,0,0,0,1,1,0,0},        // Tiger
        {0,0,1,0,1,1,1,1,0,0,1,0,0},        // Zebra
        {1,0,0,1,0,0,0,0,1,0,0,1,1},        // Goose
        {1,0,0,0,1,1,0,0,0,1,0,0,0},        // Cat
        {0,0,1,0,1,1,1,1,0,0,1,0,0},        // Horse
        {0,1,0,1,0,0,0,0,1,1,0,1,0},        // Eagle
        {0,0,1,0,1,1,0,1,0,1,1,0,0},        // Lion
        {1,0,0,1,0,0,0,0,1,1,0,1,0},        // Owl
        {0,1,0,0,1,1,0,0,0,1,0,0,0},        // Fox
        {0,1,0,0,1,1,0,1,0,1,1,0,0},        // Wolf
        {1,0,0,1,0,0,0,0,1,1,0,1,0},        // Hawk
        {1,0,0,1,0,0,0,0,1,0,0,1,1},        // Duck
        {0,0,1,0,1,1,1,0,0,0,0,0,0},        // Cow
    };
    som.train(samples, 50000);
    chart->showSOM(som);
    for (unsigned int i = 0; i < samples.size(); ++i) {
        auto res = som.classify(samples[i]);
        chart->addTip(animals[i], res);
    }
    chart->repaint();
    setFixedSize(chart->sizeHint());
}
