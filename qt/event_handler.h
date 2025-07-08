#include <QtCore/QObject>

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
    void onBtn1Clicked();

private:
    void sendData(const QString &);
};
