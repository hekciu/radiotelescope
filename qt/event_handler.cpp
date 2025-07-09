#include <QtCore/QDebug>

#include "event_handler.h"

QT_BEGIN_NAMESPACE

Radiotelescope::EventHandler::EventHandler(QObject * parent)
    : QObject(parent) {
};

Radiotelescope::EventHandler::~EventHandler() {};


void Radiotelescope::EventHandler::onUsbThreadStarted() {
    usbThreadStarted = true;
};


void Radiotelescope::EventHandler::onBtn1Clicked() {
};


QT_END_NAMESPACE
