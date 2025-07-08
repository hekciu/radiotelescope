#include "usb_worker.h"

#include <QtCore/QDebug>


Radiotelescope::UsbWorker::UsbWorker() {};


Radiotelescope::UsbWorker::~UsbWorker() {};


void Radiotelescope::UsbWorker::process() {
    qInfo() << "starting processing usb commands";
};
