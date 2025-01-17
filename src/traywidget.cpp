#include "traywidget.h"

TrayWidget::TrayWidget(QMainWindow *parent) {
    /* tray */

    this->tray_icon = new QSystemTrayIcon(this);
    this->tray_icon->setIcon(QIcon(":/image/resource/icon.png"));
    this->tray_icon->show();

    this->menu = new QMenu(this);
    this->show_act = new QAction(this);
    this->hide_act = new QAction(this);
    this->setting_act = new QAction(this);
    this->about_act = new QAction(this);
    this->exit_act = new QAction(this);

    this->show_act->setText(tr("显示"));
    this->hide_act->setText(tr("隐藏"));
    this->setting_act->setText(tr("设置"));
    this->about_act->setText(tr("关于"));
    this->exit_act->setText(tr("退出"));


    // this->tray_icon->setToolTip("test set tool tip for tray_icon");

    this->tray_icon->setContextMenu(this->menu);
    this->menu->addAction(this->show_act);
    this->menu->addAction(this->hide_act);
    this->menu->addAction(this->setting_act);
    this->menu->addAction(this->about_act);
    this->menu->addAction(this->exit_act);


    /* setting widget */


    /* connect signal with slot. */

    QWidget::connect(this->tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                    parent, SLOT(trayAction(QSystemTrayIcon::ActivationReason)),
                    Qt::AutoConnection);
    QWidget::connect(this->show_act, SIGNAL(triggered()),
                    parent, SLOT(show()),
                    Qt::AutoConnection);
    QWidget::connect(this->hide_act, SIGNAL(triggered()),
                    parent, SLOT(hide()),
                    Qt::AutoConnection);
    QWidget::connect(this->setting_act, SIGNAL(triggered()),
                    this, SLOT(setting()),
                    Qt::AutoConnection);
    QWidget::connect(this->about_act, SIGNAL(triggered()),
                    this, SLOT(show_about()),
                    Qt::AutoConnection);
    QWidget::connect(this->exit_act, SIGNAL(triggered()),
                    qApp, SLOT(quit()),
                    Qt::AutoConnection);
}

/* slot */

void TrayWidget::setting() {
}

void TrayWidget::show_about() {

}

void TrayWidget::on_clicked_save_cfg_button(const QStringList& st_info) {
    emit this->save_cfg_button_released(st_info);
}
