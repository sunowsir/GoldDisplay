#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMenu>
#include <QtGui>
#include <QWidget>

#include <QMainWindow>
#include <QMessageBox>

#include "gold_price_fetcher.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    GoldPriceFetcher    *gold_price_fetcher;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif // MAINWINDOW_H
