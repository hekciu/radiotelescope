#include <QtCore/QDebug>
#include <QtSerialPort/QSerialPort>

#include "event_handler.h"

QT_BEGIN_NAMESPACE

Events::EventHandler::EventHandler(QObject * parent)
    : QObject(parent) {
};

Events::EventHandler::~EventHandler() {};

void Events::EventHandler::on_btn1_clicked() {
    const QString TMP_NAME = "/dev/ttyACM0";

    qInfo() << "buton 1 clicked";
    QSerialPort serial;

    serial.close();
    serial.setPortName(TMP_NAME);

    const QByteArray requestData = "a";

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
};

QT_END_NAMESPACE
