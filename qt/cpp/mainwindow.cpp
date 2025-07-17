#include "mainwindow.h"
#include "mainwindow_ui.h"
#include "usb_worker.h"
#include "decoder.h"

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

    eventHandler->startUsbCommunication();

    usbThread = new QThread(this);

    usbWorker = new Radiotelescope::UsbWorker();

    /*
        Buttons
    */
    QObject::connect(
        ui->m1LButton,
        &QPushButton::pressed,
        eventHandler,
        &Radiotelescope::EventHandler::onM1LBtnPressed
    );

    QObject::connect(
        ui->m1LButton,
        &QPushButton::released,
        eventHandler,
        &Radiotelescope::EventHandler::onMotorButtonReleased
    );


    QObject::connect(
        ui->m1RButton,
        &QPushButton::pressed,
        eventHandler,
        &Radiotelescope::EventHandler::onM1RBtnPressed
    );

    QObject::connect(
        ui->m1RButton,
        &QPushButton::released,
        eventHandler,
        &Radiotelescope::EventHandler::onMotorButtonReleased
    );


    QObject::connect(
        ui->m2LButton,
        &QPushButton::pressed,
        eventHandler,
        &Radiotelescope::EventHandler::onM2LBtnPressed
    );

    QObject::connect(
        ui->m2LButton,
        &QPushButton::released,
        eventHandler,
        &Radiotelescope::EventHandler::onMotorButtonReleased
    );


    QObject::connect(
        ui->m2RButton,
        &QPushButton::pressed,
        eventHandler,
        &Radiotelescope::EventHandler::onM2RBtnPressed
    );

    QObject::connect(
        ui->m2RButton,
        &QPushButton::released,
        eventHandler,
        &Radiotelescope::EventHandler::onMotorButtonReleased
    );

    /*
        Threads and handlers
    */

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
        &Radiotelescope::UsbWorker::usbAvailable,
        eventHandler,
        &Radiotelescope::EventHandler::onUsbAvailable
    );

    QObject::connect(
        usbWorker,
        &Radiotelescope::UsbWorker::usbUnavailable,
        eventHandler,
        &Radiotelescope::EventHandler::onUsbUnavailable
    );

    /*
        Port name
    */

    QObject::connect(
        ui->savePortNameButton,
        &QPushButton::clicked,
        [this]() {
            const QString portName = ui->portNameInput->text();

            emit portNameChanged(portName);
        }
    );

    QObject::connect(
        this,
        &MainWindow::MainWindow::portNameChanged,
        eventHandler,
        &Radiotelescope::EventHandler::onPortNameChanged
    );

    QObject::connect(
        eventHandler,
        &Radiotelescope::EventHandler::changeUsbPortName,
        usbWorker,
        &Radiotelescope::UsbWorker::onChangeUsbPortName
    );

    /*
        Handle incoming data
    */

    QObject::connect(
        usbWorker,
        &Radiotelescope::UsbWorker::gotData,
        eventHandler,
        &Radiotelescope::EventHandler::onIncomingData
    );

    /*
        Update chart
    */

    QObject::connect(
        eventHandler,
        &Radiotelescope::EventHandler::updateChart,
        [this](const Radiotelescope::AntennaData data) {
            qDebug() << "updating chart with data" << data.timestamp << " " << data.value;

            ui->lineSeries->append(data.timestamp, data.value);
            ui->chart->removeSeries(ui->lineSeries);
            ui->chart->addSeries(ui->lineSeries);
            ui->chart->createDefaultAxes();
            ui->chartView->update(); 
        }
    );

    usbWorker->moveToThread(usbThread);

    usbThread->start();
}
