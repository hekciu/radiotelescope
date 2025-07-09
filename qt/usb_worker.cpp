#include "usb_worker.h"

#include <QtCore/QDebug>
#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <QtCore/QTimer>
#include <QtSerialPort/QSerialPort>


Radiotelescope::UsbWorker::UsbWorker() {
    m_mutex = new QMutex();
    serial = new QSerialPort(); // without this it is created in a wrong thread??
};


Radiotelescope::UsbWorker::~UsbWorker() {
    delete m_mutex;
    delete serial;
};


void Radiotelescope::UsbWorker::sendData(const char * data, const uint32_t n) {
    qDebug() << "got data: " << data;

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

    success = false;

    const QString TMP_NAME = "/dev/ttyACM0";

    serial->setPortName(TMP_NAME);

    QTimer * timer = new QTimer();
    QThread::connect(timer, &QTimer::timeout, [this]() {

        if (!success) {
            serial->close();
            success = serial->open(QIODevice::ReadWrite);

            if (success) {
                // qInfo() << "successfully opened serial port";
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
                return;
            }

            qDebug() << "writing data: " << requestData;

            serial->write(requestData);

            if (!serial->waitForBytesWritten(WAIT_TIMEOUT_MS)) {
                success = false;
                emit connectionFailure();
            } else {
                if (serial->waitForReadyRead(300)) {
                    QByteArray responseData = serial->readAll();
                        while (serial->waitForReadyRead(10)) {
                            responseData += serial->readAll();
                        }

                        qDebug() << responseData;
                }
            }
        }

    });

    timer->start(1000);

    serial->close();
};
