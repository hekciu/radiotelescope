#include "mainwindow.h"
#include "./mainwindow_ui.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    this->ui->setupUi(this);
}


MainWindow::~MainWindow() {
    delete this->ui;
}
