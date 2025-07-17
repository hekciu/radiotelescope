#include <QtWidgets/QMainWindow>
#include <QtCore/QThread>

#include "usb_worker.h"
#include "event_handler.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget * parent = nullptr);
    ~MainWindow();

signals:
    void portNameChanged(const QString portName);

private:
    Ui::MainWindow *ui;
    void setUsbWorker();
    QThread * usbThread;
    Radiotelescope::UsbWorker * usbWorker;
    Radiotelescope::EventHandler * eventHandler;
};
