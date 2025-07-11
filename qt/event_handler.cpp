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


void Radiotelescope::EventHandler::startUsbCommunication() {
    timer = new QTimer();

    QObject::connect(timer, &QTimer::timeout, [this]() {
        if (this->commandToSend.length() > 0) {
            sendData(commandToSend);
        };
    });

    timer->start(100);
};


QT_END_NAMESPACE
