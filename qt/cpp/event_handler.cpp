#include <QtCore/QDebug>
#include <QtCore/QTimer>

#include "event_handler.h"

QT_BEGIN_NAMESPACE


Radiotelescope::EventHandler::EventHandler(QObject * parent)
    : QObject(parent) {
};

Radiotelescope::EventHandler::~EventHandler() {};


void Radiotelescope::EventHandler::onUsbAvailable() {
    usbWorkerAvailable = true;
};


void Radiotelescope::EventHandler::onUsbUnavailable() {
    usbWorkerAvailable = false;
};


void Radiotelescope::EventHandler::onM1LBtnPressed() {
    commandToSend += "b";
};


void Radiotelescope::EventHandler::onM1RBtnPressed() {
    commandToSend += "a";
};


void Radiotelescope::EventHandler::onM2LBtnPressed() {
    commandToSend += "d";
};


void Radiotelescope::EventHandler::onM2RBtnPressed() {
    commandToSend += "c";
};


void Radiotelescope::EventHandler::onMotorButtonReleased() {
    commandToSend = "";
};


void Radiotelescope::EventHandler::onIncomingData(QByteArray data) {
    while (data.length() >= RT_ANTENNA_DATA_SIZE) {
        auto dataPortion = data.last(RT_ANTENNA_DATA_SIZE);
        qDebug() << "1" << data.length();
        data.remove(0, RT_ANTENNA_DATA_SIZE);
        qDebug() << "2" << data.length();

        auto parsedData = Decoder::decode(dataPortion);

        emit updateChart(parsedData);
    }
};


void Radiotelescope::EventHandler::onPortNameChanged(const QString newPortName) {
    lastPortName = portName;
    portName = newPortName;
};


void Radiotelescope::EventHandler::startUsbCommunication() {
    timer = new QTimer();

    QObject::connect(timer, &QTimer::timeout, [this]() {
        if (portName != lastPortName) {
            emit changeUsbPortName(portName);
        }

        if (this->commandToSend.length() > 0) {
            emit sendData(commandToSend);
        };
    });

    timer->start(100);
};


QT_END_NAMESPACE
