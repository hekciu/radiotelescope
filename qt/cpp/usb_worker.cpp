#include "usb_worker.h"
#include "decoder.h"

#include <QtCore/QDebug>
#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <QtCore/QTimer>
#include <QtSerialPort/QSerialPort>


Radiotelescope::UsbWorker::UsbWorker() {
};


Radiotelescope::UsbWorker::~UsbWorker() {
    if (m_mutex != nullptr) {
        delete m_mutex;
    }

    if (serial != nullptr) {
        delete serial;
    }
};


void Radiotelescope::UsbWorker::sendData(const QString data) {
    uint32_t n = data.length();

    m_mutex->lock();

    bufferArray.append(data.toLocal8Bit());

    m_mutex->unlock();
}


void Radiotelescope::UsbWorker::onChangeUsbPortName(const QString portName) {
    this->usbPortName = portName;
};


static uint16_t n = 0;

void Radiotelescope::UsbWorker::process() {
    qInfo() << "starting processing usb commands";

    m_mutex = new QMutex();
    serial = new QSerialPort();

    success = false;

    timer = new QTimer();

    QThread::connect(timer, &QTimer::timeout, [this]() {
        uint32_t timestamp_test = n*2;

        QByteArray test;
        test.append(timestamp_test >> 24);
        test.append(timestamp_test >> 16);
        test.append(timestamp_test >> 8);
        test.append(timestamp_test);
        test.append(n >> 8);
        test.append(n);

        qDebug() << "n: " << n;

        gotData(test);
        n++;
        return;

        if (usbPortName.length() == 0) return;

        if (!success) {
            serial->close();

            serial->setPortName(usbPortName);
            //serial->setPortName("/dev/ttyACM0");

            success = serial->open(QIODevice::ReadWrite);

            if (success) {
                qInfo() << "successfully opened serial port" << usbPortName;
                emit usbAvailable();
            } else {
                qWarning() << "could not open serial port: " << usbPortName;
                emit usbUnavailable();
            }
        }

        // read data
        if (success) {
            QByteArray responseData = serial->readAll();

            if (responseData.length() > 0) {
                emit gotData(responseData);
            }
        }

        // write data
        if (success) {
            m_mutex->lock();

            QByteArray requestData(bufferArray);
            bufferArray.clear(); // will this one make segfault?

            m_mutex->unlock();

            if (requestData.length() == 0) {
                return;
            }

            qDebug() << "sending " << requestData.length() << " bytes of data";

            serial->write(requestData);

            if (!serial->waitForBytesWritten(WAIT_TIMEOUT_MS)) {
                success = false;
                emit usbUnavailable();
            }
        }

    });

    timer->start(200);
};
