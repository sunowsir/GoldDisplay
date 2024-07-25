#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    this->gold_price_fetcher = new GoldPriceFetcher();
}

MainWindow::~MainWindow() {
    delete this->gold_price_fetcher;
}

