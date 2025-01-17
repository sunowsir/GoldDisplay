/*
	* File     : info_display_widget.h
	* Author   : sunowsir
	* Mail     : sunowsir@163.com
	* Github   : github.com/sunowsir
	* Creation : 2021年02月13日 星期六 16时03分26秒
*/

#ifndef _INFO_DISPLAY_WIDGET_H
#define _INFO_DISPLAY_WIDGET_H

#include <QtGui>
#include <QMenu>
#include <QList>
#include <QWidget>
#include <QDialog>
#include <QString>
#include <qlabel.h>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QTimer>

#include <qlineedit.h>
#include <qtextedit.h>

#include <QMainWindow>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPalette>

#include "gold_price_fetcher.h"

class Info_Display_Widget : public QWidget {
    Q_OBJECT

    QMainWindow     *parent;

    QLabel          *info_label;

    QVBoxLayout     *layout;

    GoldPriceFetcher *gold_price_fetcher;
    QTimer          *timer;

public:
    explicit Info_Display_Widget(QMainWindow *parent = nullptr);
    ~Info_Display_Widget();

private slots:
    void gold_price_get_timer_call_callback();
    void info_label_text_update(QString&);
};

#endif
