#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    this->setFixedSize(1000, 1000);
    // this->showMaximized();
    this->setWindowIcon(QIcon(QString(":/image/resource/icon.png")));


    //实体列表 窗体背景透明
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint | Qt::Tool);//无边框
    // this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);//无边框
    this->setAttribute(Qt::WA_TranslucentBackground, true);//窗体背景全透明

    this->info_display_widget = new Info_Display_Widget(this);
    setCentralWidget(this->info_display_widget);

    this->t = new TrayWidget(this);
}

MainWindow::~MainWindow() {
    this->info_display_widget->close();
    delete this->info_display_widget;
    this->t->close();
    delete this->t;
}

/* slot */

void MainWindow::trayAction(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger) {
        this->showNormal();
    }
}


/* rewrite */

void MainWindow::changeEvent( QEvent *e ) {
    if ( ( e->type() == QEvent::WindowStateChange ) && this->isMinimized() ) {
        QTimer::singleShot( 100, this, SLOT( close() ) );
    }
}


void MainWindow::closeEvent( QCloseEvent *e ) {
    e->ignore();
    this->hide();
}


