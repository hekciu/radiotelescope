#include <QtCore/QDebug>
#include <QtSerialPort/QSerialPort>

#include "event_handler.h"

QT_BEGIN_NAMESPACE

Radiotelescope::EventHandler::EventHandler(QObject * parent)
    : QObject(parent) {
};

Radiotelescope::EventHandler::~EventHandler() {};


void Radiotelescope::EventHandler::onBtn1Clicked() {
    sendData("a");
};


void Radiotelescope::EventHandler::sendData(const QString & request) {
    const QString TMP_NAME = "/dev/ttyACM0";

    const QByteArray requestData = request.toUtf8();

    qInfo() << "buton 1 clicked";
    QSerialPort serial;

    serial.close();
    serial.setPortName(TMP_NAME);

    if (!serial.open(QIODevice::ReadWrite)) {
        qWarning() << "could not open serial port";
        return;
    }

    serial.write(requestData);
    if (serial.waitForBytesWritten(9999)) {
        if (serial.waitForReadyRead(300)) {
            QByteArray responseData = serial.readAll();
                while (serial.waitForReadyRead(10)) {
                    responseData += serial.readAll();
                }

            const QString response = QString::fromUtf8(responseData);

            qInfo() << "got data: \n" << response;
        }
    } else {
        qWarning() << "timeouted";
    }

    serial.close();
}

QT_END_NAMESPACE
