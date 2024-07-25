/*
	* File     : gold_price_fetcher.cpp
	* Author   : sunowsir
	* Mail     : sunowsir@163.com
	* Github   : github.com/sunowsir
	* Creation : Thu 25 Jul 2024 01:52:25 PM CST
*/


#include "gold_price_fetcher.h"


void GoldPriceFetcher::fetchUrl(const QUrl &url) {
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    QObject::connect(manager, &QNetworkAccessManager::finished, [this](QNetworkReply *reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            parseHtml(data);
        } else {
            qDebug() << "Network error: " << reply->errorString().toStdString() ;
        }
        reply->deleteLater();
        QCoreApplication::quit();
    });

    QNetworkRequest request(url);
    manager->get(request);

    return ;
}

void GoldPriceFetcher::parseHtml(const QByteArray &html) {
    htmlDocPtr doc = htmlReadMemory(html.data(), html.size(), NULL, NULL, HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
    if (doc == nullptr) {
        qDebug() << "Failed to parse HTML." ;
        return;
    }

    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    if (context == nullptr) {
        qDebug() << "Failed to create XPath context." ;
        xmlFreeDoc(doc);
        return;
    }

    // xmlXPathObjectPtr result = xmlXPathEvalExpression(BAD_CAST "//*[@align='center' and @class='colorRed']", context);
    xmlXPathObjectPtr result = xmlXPathEvalExpression(BAD_CAST "//td", context);
    if (result == nullptr) {
        qDebug() << "Failed to evaluate XPath expression." ;
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        return;
    }

    bool is_found = false;
    xmlNodeSetPtr nodes = result->nodesetval;
    for (int i = 0; i < nodes->nodeNr; ++i) {
        xmlNodePtr node = nodes->nodeTab[i];
        xmlChar *content = xmlNodeGetContent(node);
        if (!content) continue;
        char *charContent = reinterpret_cast<char*>(content);
        QString qStrContent = QString::fromUtf8(charContent);

        if (is_found) {
            this->gold_price = qStrContent.toInt();
            is_found = false;
        }
        
        if (qStrContent == QString("Au99.99")) {
            is_found = true;
            xmlFree(content);
            continue;
        }

        if (content) 
            xmlFree(content);
    }

    xmlXPathFreeObject(result);
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);

    return ;
}


GoldPriceFetcher::GoldPriceFetcher() {
    this->gold_price = 0;
}

GoldPriceFetcher::~GoldPriceFetcher() {
    
}
    
void GoldPriceFetcher::gold_price_get(int &gold_price) {
    QUrl url("https://www.sge.com.cn/sjzx/yshqbg"); 
    this->fetchUrl(url);
    gold_price = this->gold_price;

    return ;
}
