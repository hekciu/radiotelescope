/********************************************************************************

This file was initially generated by qt's uid tool but is now edited by hand.
Using .ui files was abandoned for this project.

********************************************************************************/

#ifndef MAINWINDOW_UI_H
#define MAINWINDOW_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>

#include "event_handler.h"

QT_BEGIN_NAMESPACE

class MainWindow_Ui
{
public:
    QPushButton * m1LButton;
    QPushButton * m1RButton;
    QPushButton * m2LButton;
    QPushButton * m2RButton;
    QLineEdit * portNameInput;
    QPushButton * savePortNameButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty()) {
            MainWindow->setObjectName("MainWindow");
        }
        MainWindow->resize(800, 600);

        m1LButton = new QPushButton("m1l", MainWindow);
        m1LButton->setGeometry(0, 50, 60, 20);

        m1RButton = new QPushButton("m1r", MainWindow);
        m1RButton->setGeometry(120, 50, 60, 20);

        m2LButton = new QPushButton("m2l", MainWindow);
        m2LButton->setGeometry(60, 30, 60, 20);

        m2RButton = new QPushButton("m2r", MainWindow);
        m2RButton->setGeometry(60, 70, 60, 20);

        portNameInput = new QLineEdit(MainWindow);
        portNameInput->setGeometry(200, 50, 100, 20);

        savePortNameButton = new QPushButton("Save port\nname", MainWindow);
        savePortNameButton->setGeometry(320, 40, 70, 40);

        // MainWindow->setCentralWidget(pushButton);

        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Radio telescope control software", nullptr));

        // QMetaObject::connectSlotsByName(MainWindow);
    }
};

namespace Ui {
    class MainWindow: public MainWindow_Ui {};
}

QT_END_NAMESPACE

#endif // MAINWINDOW_UI_H
