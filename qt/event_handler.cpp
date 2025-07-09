#include <QtCore/QDebug>

#include "event_handler.h"

QT_BEGIN_NAMESPACE

Radiotelescope::EventHandler::EventHandler(QObject * parent)
    : QObject(parent) {
};

Radiotelescope::EventHandler::~EventHandler() {};


void Radiotelescope::EventHandler::onUsbConnected() {
    usbConnected = true;
};


void Radiotelescope::EventHandler::onUsbDisconnected() {
    usbConnected = false;
};


void Radiotelescope::EventHandler::onBtn1Clicked() {
    const char * data = "a";

    qDebug() << "emitting data";
    emit sendData(data, strlen(data));
};


QT_END_NAMESPACE
