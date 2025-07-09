#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtSerialPort/QSerialPort>

#include <stdint.h>

#ifndef USB_WORKER_H
#define USB_WORKER_H

QT_BEGIN_NAMESPACE
namespace Radiotelescope {
class UsbWorker;
}
QT_END_NAMESPACE


class Radiotelescope::UsbWorker : public QObject {
    Q_OBJECT

public:
    UsbWorker();
    ~UsbWorker();

    // https://doc.qt.io/qt-6/qtserialport-blockingsender-example.html
    // https://mayaposch.wordpress.com/2011/11/01/how-to-really-truly-use-qthreads-the-full-explanation/

public slots:
    void process();
    void sendData(const char * data, const uint32_t n);

signals:
    void connectionSuccess();
    void connectionFailure();

private:
    static const uint32_t BFR_CAPACITY = 50000;
    static const uint32_t WAIT_TIMEOUT_MS = 30000;
    QMutex * m_mutex;
    uint32_t m_dataSize = 0;
    char m_bfr[BFR_CAPACITY];
    bool success = false;
    QSerialPort * serial;
};


#endif
