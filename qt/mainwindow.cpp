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
    qInfo() << "setting up usb worker";

    QThread * usbThread = new QThread();

    Radiotelescope::UsbWorker * usbWorker = new Radiotelescope::UsbWorker();

    usbWorker->moveToThread(usbThread);

    usbThread->start();
    QObject::connect(
        usbThread,
        &QThread::started,
        usbWorker,
        &Radiotelescope::UsbWorker::process
    );
}
