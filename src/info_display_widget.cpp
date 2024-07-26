/*
	* File     : info_display_widget.h
	* Author   : sunowsir
	* Mail     : sunowsir@163.com
	* Github   : github.com/sunowsir
	* Creation : 2021年02月13日 星期六 16时03分26秒
*/

#include "info_display_widget.h"

Info_Display_Widget::Info_Display_Widget(QMainWindow *parent) {
    this->parent = parent;
    this->setParent(parent);

    this->info_label = new QLabel(this);

    int gold_price;
    this->gold_price_fetcher->gold_price_get(gold_price);
    this->info_label->setText(QString::number(gold_price));

    this->info_label->move(150, 140);
    this->info_label->setScaledContents(true);

    this->gold_price_fetcher = new GoldPriceFetcher();

    this->timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &Info_Display_Widget::info_label_text_update);

    this->timer->start(60 * 1000);
}

Info_Display_Widget::~Info_Display_Widget() {
    delete this->info_label;
    delete this->gold_price_fetcher;
}


void Info_Display_Widget::info_label_text_update() {
    int gold_price;
    this->gold_price_fetcher->gold_price_get(gold_price);
    this->info_label->setText(QString::number(gold_price));
}
