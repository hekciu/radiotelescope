#include <QtCore/QObject>
#include <QtCore/QTimer>

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
    void startUsbCommunication();

public slots:
    void onUsbAvailable();
    void onUsbUnavailable();

    void onM1LBtnPressed();

    void onM1RBtnPressed();

    void onM2LBtnPressed();

    void onM2RBtnPressed();

    void onMotorButtonReleased();

    void onPortNameChanged(const QString);

signals:
    void sendData(const QString);
    void changeUsbPortName(const QString);

private:
    bool usbWorkerAvailable = false;
    QString commandToSend = "";
    QTimer * timer;
    QString portName = "";
    QString lastPortName = "";
};

#endif
