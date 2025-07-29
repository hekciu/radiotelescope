#include <vector>

#include <QtWidgets/QMainWindow>
#include <QtCore/QThread>
#include <QtCharts/QLineSeries>

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
    void setPeriodSamples(const int &);
    int getPeriodSamples();

signals:
    void portNameChanged(const QString portName);

private:
    Ui::MainWindow *ui;
    void setUsbWorker();
    QThread * usbThread;
    Radiotelescope::UsbWorker * usbWorker;
    Radiotelescope::EventHandler * eventHandler;
    void updateChart(const Radiotelescope::AntennaData);

    int periodSamples = 10;
    std::vector<Radiotelescope::AntennaData> lineSeriesBuffer;
};

