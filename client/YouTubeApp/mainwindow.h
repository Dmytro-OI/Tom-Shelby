#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include <QThread>
#include "requestworker.h"

#include <curl/curl.h>
#include <iostream>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSubmitClicked();

private:
    QLineEdit *urlInput;
    QPushButton *submitButton;
    QLabel *welcomeLabel;
    QString summary = "";

    void createNewWindow();
    void sendRequest(const QString &url);
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp);

};

#endif
