#include <QDebug>

#include "event_handler.h"

QT_BEGIN_NAMESPACE

Events::EventHandler::EventHandler(QObject * parent)
    : QObject(parent) {
};

Events::EventHandler::~EventHandler() {};

void Events::EventHandler::on_btn1_clicked() {
    qInfo() << "buton 1 clicked";
};

QT_END_NAMESPACE
