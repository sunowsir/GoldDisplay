/*
	* File     : gold_price_fetcher.h
	* Author   : sunowsir
	* Mail     : sunowsir@163.com
	* Github   : github.com/sunowsir
	* Creation : Thu 25 Jul 2024 01:52:29 PM CST
*/

#ifndef _GOLD_PRICE_FETCHER_H
#define _GOLD_PRICE_FETCHER_H

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>

class GoldPriceFetcher {
private: 
    int gold_price;

private: 
    void fetchUrl(const QUrl &);
    void parseHtml(const QByteArray &);

public: 
    GoldPriceFetcher();
    ~GoldPriceFetcher();
    
    void gold_price_get(int &);
};

#endif
