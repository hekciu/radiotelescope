#include <QtCore/QObject>

QT_BEGIN_NAMESPACE
namespace Events {
class EventHandler;
}
QT_END_NAMESPACE

class Events::EventHandler : public QObject {
    Q_OBJECT

public:
    EventHandler(QObject * parent = nullptr);
    ~EventHandler();
public slots:
    void on_btn1_clicked();
};
