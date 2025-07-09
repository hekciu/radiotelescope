#include <QtCore/QObject>

#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

QT_BEGIN_NAMESPACE
namespace Radiotelescope {
class EventHandler;
}
QT_END_NAMESPACE

class Radiotelescope::EventHandler : public QObject {
    Q_OBJECT

public:
    explicit EventHandler(QObject * parent = nullptr);
    ~EventHandler();

public slots:
    void onUsbThreadStarted();
    void onBtn1Clicked();

signals:
    void sendData(const char * data, const uint32_t n);

private:
    bool usbThreadStarted = false;
};

#endif
