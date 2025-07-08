#include <QtCore/QObject>

#include <stdint.h>

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

private:
    static const uint32_t BFR_CAPACITY = 50000;
    uint8_t m_bfr[BFR_CAPACITY];
    uint32_t m_bfr_size = 0;
};
