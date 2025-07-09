#include "usb_worker.h"

#include <QtCore/QDebug>
#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <QtSerialPort/QSerialPort>


Radiotelescope::UsbWorker::UsbWorker(QObject * parent)
    : QObject (parent) {
    m_mutex = new QMutex();
};


Radiotelescope::UsbWorker::~UsbWorker() {
    delete m_mutex;
};


void Radiotelescope::UsbWorker::sendData(const char * data, const uint32_t n) {
    m_mutex->lock();

    if (m_dataSize + n > BFR_CAPACITY) {
        // handle error
    } else {
        memcpy(m_bfr + m_dataSize, data, n);
        m_dataSize += n;
    }

    m_mutex->unlock();
}


void Radiotelescope::UsbWorker::process() {
    qInfo() << "starting processing usb commands";

    const QString TMP_NAME = "/dev/ttyACM0";

    QSerialPort serial;

    bool success = false;

    serial.setPortName(TMP_NAME);

    while (true) {
        QThread::msleep(50);

        if (!success) {
            serial.close();
            success = serial.open(QIODevice::ReadWrite);

            if (success) {
                qInfo() << "successfully opened serial port";
                emit connectionSuccess();
            } else {
                qWarning() << "could not open serial port";
                emit connectionFailure();
            }
        }

        if (success) {
            m_mutex->lock();

            QByteArray requestData(m_bfr, m_dataSize);

            m_dataSize = 0;

            m_mutex->unlock();

            if (requestData.length() == 0) {
                continue;
            }

            serial.write(requestData);

            if (!serial.waitForBytesWritten(WAIT_TIMEOUT_MS)) {
                success = false;
                emit connectionFailure();
            } else {
                if (serial.waitForReadyRead(300)) {
                    QByteArray responseData = serial.readAll();
                        while (serial.waitForReadyRead(10)) {
                            responseData += serial.readAll();
                        }
                }
            }
        }
    }

    serial.close();
};
