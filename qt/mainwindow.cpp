#include "mainwindow.h"
#include "./mainwindow_ui.h"
#include "usb_worker.h"

#include <QtCore/QDebug>
#include <QtCore/QThread>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setUsbWorker();
}


MainWindow::~MainWindow() {
    delete this->ui;
}


void MainWindow::setUsbWorker() {
    qInfo() << "setting up";

    eventHandler = new Radiotelescope::EventHandler(this);

    usbThread = new QThread(this);

    usbWorker = new Radiotelescope::UsbWorker();

    QObject::connect(
        ui->pushButton,
        &QPushButton::clicked,
        eventHandler,
        &Radiotelescope::EventHandler::onBtn1Clicked
    );

    QObject::connect(
        usbThread,
        &QThread::started,
        usbWorker,
        &Radiotelescope::UsbWorker::process
    );

    QObject::connect(
        eventHandler,
        &Radiotelescope::EventHandler::sendData,
        usbWorker,
        &Radiotelescope::UsbWorker::sendData
    );

    QObject::connect(
        usbWorker,
        &Radiotelescope::UsbWorker::connectionSuccess,
        eventHandler,
        &Radiotelescope::EventHandler::onUsbConnected
    );

    QObject::connect(
        usbWorker,
        &Radiotelescope::UsbWorker::connectionFailure,
        eventHandler,
        &Radiotelescope::EventHandler::onUsbDisconnected
    );

    usbWorker->moveToThread(usbThread);

    usbThread->start();
}
