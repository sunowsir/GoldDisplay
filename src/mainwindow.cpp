#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    this->setFixedSize(300, 300);
    // this->setWindowTitle(tr("锐捷校园网有线认证linux辅助客户端"));
    this->setWindowIcon(QIcon(QString(":/image/resource/icon.png")));


    //实体列表 窗体背景透明
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);//无边框
    this->setAttribute(Qt::WA_TranslucentBackground, true);//窗体背景全透明
    // this->setWindowFlags(Qt::WindowStaysOnTopHint);

    this->info_display_widget = new Info_Display_Widget(this);
    // this->resize(this->w->size()); //设置窗口大小
    setCentralWidget(this->info_display_widget);

    this->t = new TrayWidget(this);


    QWidget::connect(this->t, SIGNAL(save_cfg_button_released(const QStringList&)),
                      this->info_display_widget, SLOT(on_clicked_save_cfg_button(const QStringList&)),
                      Qt::AutoConnection);
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


