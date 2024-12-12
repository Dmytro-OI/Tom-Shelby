#ifndef REQUESTWORKER_H
#define REQUESTWORKER_H



#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <curl/curl.h>
#include <string>
#include <QThread>

class Worker : public QObject {
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr) : QObject(parent) {}

    void setUrl(const QString &url) {
        m_url = url;
    }

signals:
    void resultReady(const QString &summary);
    void errorOccurred(const QString &error);

public slots:
    void process() {
        CURL *curl;
        CURLcode res;
        std::string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            std::string strUrl = m_url.toStdString();

            curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8000");

            QJsonObject jsonData;
            jsonData["link"] = strUrl.c_str();  // Replace with actual video URL
            jsonData["lang"] = "en";         // Specify language
            jsonData["max_length"] = 100.0;  // Specify max length

            QJsonDocument jsonDoc(jsonData);
            QByteArray byteArray = jsonDoc.toJson();
            std::string postData(byteArray.constData(), byteArray.length());

            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

            struct curl_slist *headers = nullptr;
            headers = curl_slist_append(headers, "Content-Type: application/json");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                emit errorOccurred(curl_easy_strerror(res));
            } else {
                QJsonDocument doc = QJsonDocument::fromJson(QByteArray::fromStdString(readBuffer));
                if (!doc.isNull()) {
                    QJsonObject jsonObj = doc.object();
                    if (jsonObj.contains("data") && jsonObj["data"].isObject()) {
                        QJsonObject dataObj = jsonObj["data"].toObject();
                        if (dataObj.contains("summary") && dataObj["summary"].isString()) {
                            emit resultReady(dataObj["summary"].toString());
                        } else {
                            emit errorOccurred("Summary not found!");
                        }
                    }
                } else {
                    emit errorOccurred("Failed to parse JSON response!");
                }
            }

            // Cleanup
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
        }
    }

private:
    QString m_url;

    static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
        ((std::string *)userp)->append((char *)contents, size * nmemb);
        return size * nmemb;
    }
};


#endif // REQUESTWORKER_H
