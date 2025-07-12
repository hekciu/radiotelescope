#include "usb_worker.h"

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

    if (m_dataSize + n > BFR_CAPACITY) {
        // handle error
    } else {
        memcpy(m_bfr + m_dataSize, data.data(), n);
        m_dataSize += n;
    }

    m_mutex->unlock();
}


void Radiotelescope::UsbWorker::onChangeUsbPortName(const QString portName) {
    this->usbPortName = portName;
};


void Radiotelescope::UsbWorker::process() {
    qInfo() << "starting processing usb commands";

    m_mutex = new QMutex();
    serial = new QSerialPort();

    success = false;

    timer = new QTimer();
    QThread::connect(timer, &QTimer::timeout, [this]() {
        if (!success) {
            serial->close();

            serial->setPortName(usbPortName);
            //serial->setPortName("/dev/ttyACM0");

            success = serial->open(QIODevice::ReadWrite);

            if (success) {
                // qInfo() << "successfully opened serial port";
                emit usbAvailable();
            } else {
                qWarning() << "could not open serial port: " << usbPortName;
                emit usbUnavailable();
            }
        }

        if (success) {
            m_mutex->lock();

            QByteArray requestData(m_bfr, m_dataSize);

            m_dataSize = 0;

            m_mutex->unlock();

            if (requestData.length() == 0) {
                return;
            }

            qDebug() << "sending " << requestData.length() << " bytes of data";

            serial->write(requestData);

            if (!serial->waitForBytesWritten(WAIT_TIMEOUT_MS)) {
                success = false;
                emit usbUnavailable();
            } else {
                /*
                if (serial->waitForReadyRead(300)) {
                    QByteArray responseData = serial->readAll();
                        while (serial->waitForReadyRead(10)) {
                            responseData += serial->readAll();
                        }

                        qDebug() << responseData;
                }
                */
            }
        }

    });

    timer->start(100);
};
