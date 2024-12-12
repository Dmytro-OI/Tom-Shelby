#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    setWindowTitle("YouTube Link App");
    resize(400, 200);

    welcomeLabel = new QLabel("Enter the link to the YouTube video", this);
    urlInput = new QLineEdit(this);
    submitButton = new QPushButton("Святко сільвер Бог", this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(welcomeLabel);
    layout->addWidget(urlInput);
    layout->addWidget(submitButton);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(submitButton, &QPushButton::clicked, this, &MainWindow::onSubmitClicked);
}

MainWindow::~MainWindow() {
}

void MainWindow::onSubmitClicked() {
    QString url = urlInput->text();
    if (url.isEmpty()) {
        QMessageBox::warning(this, "Ероро", "Гандон введи норм посиання йопта");
        return;
    }
    sendRequest(url);
}

void MainWindow::createNewWindow() {
    QDialog *newWindow = new QDialog(this);
    newWindow->setWindowTitle("Результат");
    newWindow->resize(300, 100);

    QLabel *label = new QLabel("Summary of your yt video:\n" + summary, newWindow);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(label);
    newWindow->setLayout(layout);

    newWindow->exec();
}

size_t MainWindow::writeCallback(void* contents, size_t size, size_t nmemb, void* userp){
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


void MainWindow::sendRequest(const QString &url) {
    QThread *thread = new QThread;
    Worker *worker = new Worker;

    worker->setUrl(url);
    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &Worker::process);
    connect(worker, &Worker::resultReady, this, [this](const QString &summary) {
        qDebug() << "Summary: " << summary;
        this->summary = summary; // Store or use the summary
        this->createNewWindow();
    });
    connect(worker, &Worker::errorOccurred, this, [](const QString &error) {
        qDebug() << "Error: " << error;
    });
    connect(worker, &Worker::resultReady, thread, &QThread::quit);
    connect(worker, &Worker::errorOccurred, thread, &QThread::quit);
    connect(thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    thread->start();
}

