#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMenu>
#include <QtGui>
#include <QWidget>

#include <QMainWindow>

#include <QMessageBox>

#include "traywidget.h"
#include "info_display_widget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    TrayWidget  *t;
    Info_Display_Widget *info_display_widget;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent *e);
    // void paintEvent(QPaintEvent *e);
public slots:
    void trayAction(QSystemTrayIcon::ActivationReason reason);
};

#endif // MAINWINDOW_H
