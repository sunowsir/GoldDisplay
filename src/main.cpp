#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include <iostream>

void fetchUrl(const QUrl &url);
void parseHtml(const QByteArray &html);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QUrl url("https://www.sge.com.cn/sjzx/yshqbg"); // 替换为你的URL
    fetchUrl(url);

    return a.exec();
}

void fetchUrl(const QUrl &url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    QObject::connect(manager, &QNetworkAccessManager::finished, [](QNetworkReply *reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            parseHtml(data);
        } else {
            std::cerr << "Network error: " << reply->errorString().toStdString() << std::endl;
        }
        reply->deleteLater();
        QCoreApplication::quit();
    });

    QNetworkRequest request(url);
    manager->get(request);
}

void parseHtml(const QByteArray &html)
{
    htmlDocPtr doc = htmlReadMemory(html.data(), html.size(), NULL, NULL, HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
    if (doc == nullptr) {
        std::cerr << "Failed to parse HTML." << std::endl;
        return;
    }

    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    if (context == nullptr) {
        std::cerr << "Failed to create XPath context." << std::endl;
        xmlFreeDoc(doc);
        return;
    }

    // xmlXPathObjectPtr result = xmlXPathEvalExpression(BAD_CAST "//*[@align='center' and @class='colorRed']", context);
    xmlXPathObjectPtr result = xmlXPathEvalExpression(BAD_CAST "//td", context);
    if (result == nullptr) {
        std::cerr << "Failed to evaluate XPath expression." << std::endl;
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        return;
    }

    xmlNodeSetPtr nodes = result->nodesetval;
    for (int i = 0; i < nodes->nodeNr; ++i) {
        xmlNodePtr node = nodes->nodeTab[i];
        xmlChar *content = xmlNodeGetContent(node);
        if (content) {
            std::cout << "Found: " << content << std::endl;
            xmlFree(content);
        }
    }

    xmlXPathFreeObject(result);
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);
}

