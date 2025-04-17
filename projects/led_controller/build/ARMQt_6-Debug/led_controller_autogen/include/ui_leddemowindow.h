/********************************************************************************
** Form generated from reading UI file 'leddemowindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEDDEMOWINDOW_H
#define UI_LEDDEMOWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LEDDemoWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *status_btn;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LEDDemoWindow)
    {
        if (LEDDemoWindow->objectName().isEmpty())
            LEDDemoWindow->setObjectName("LEDDemoWindow");
        LEDDemoWindow->resize(605, 435);
        centralwidget = new QWidget(LEDDemoWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(0, 100));

        verticalLayout->addWidget(pushButton);

        status_btn = new QPushButton(widget);
        status_btn->setObjectName("status_btn");
        status_btn->setMinimumSize(QSize(0, 100));

        verticalLayout->addWidget(status_btn);


        horizontalLayout->addWidget(widget);

        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        LEDDemoWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LEDDemoWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 605, 27));
        LEDDemoWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(LEDDemoWindow);
        statusbar->setObjectName("statusbar");
        LEDDemoWindow->setStatusBar(statusbar);

        retranslateUi(LEDDemoWindow);

        QMetaObject::connectSlotsByName(LEDDemoWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LEDDemoWindow)
    {
        LEDDemoWindow->setWindowTitle(QCoreApplication::translate("LEDDemoWindow", "LEDDemoWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("LEDDemoWindow", "Press Me to switch the led status", nullptr));
        status_btn->setText(QCoreApplication::translate("LEDDemoWindow", "Current_status:", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LEDDemoWindow: public Ui_LEDDemoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEDDEMOWINDOW_H
