/*
	* File     : info_display_widget.h
	* Author   : sunowsir
	* Mail     : sunowsir@163.com
	* Github   : github.com/sunowsir
	* Creation : 2021年02月13日 星期六 16时03分26秒
*/

#include "info_display_widget.h"

Info_Display_Widget::Info_Display_Widget(QMainWindow *parent) {
    this->setFixedSize(1000, 1000);
    // this->showMaximized();

    this->parent = parent;
    this->setParent(parent);

    QFont info_font;
    info_font.setPointSize(100);

    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::black);

    this->info_label = new QLabel(this);
    this->info_label->setFont(info_font);
    this->info_label->setPalette(pa);
    this->info_label->move(150, 140);
    // this->info_label->setFixedSize(500, 500);
    this->info_label->setScaledContents(true);
    this->info_label->adjustSize();
    this->info_label->setAlignment(Qt::AlignCenter);

    this->layout = new QVBoxLayout(this);
    this->layout->addWidget(this->info_label);
    this->setLayout(this->layout);

    this->gold_price_fetcher = new GoldPriceFetcher();
    this->gold_price_fetcher->gold_price_get();

    this->timer = new QTimer(this);

    QWidget::connect(timer, SIGNAL(timeout()),
                     this, SLOT(gold_price_get_timer_call_callback()), Qt::AutoConnection);

    QWidget::connect(this->gold_price_fetcher, SIGNAL(gold_price_update(QString&)),
                     this, SLOT(info_label_text_update(QString&)), Qt::AutoConnection);

    this->timer->start(10 * 60 * 1000);
}

Info_Display_Widget::~Info_Display_Widget() {
    delete this->info_label;
    delete this->layout;
    delete this->gold_price_fetcher;
    delete this->timer;
}

/* slots function */

void Info_Display_Widget::gold_price_get_timer_call_callback() {
    this->gold_price_fetcher->gold_price_get();
}


void Info_Display_Widget::info_label_text_update(QString &gold_price) {
    // qDebug() << "info_label_text_update: " << gold_price;
    this->info_label->setText(gold_price);
}
