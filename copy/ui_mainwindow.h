/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLabel *label;
    QLCDNumber *lcdNumber_x;
    QLCDNumber *lcdNumber_y;
    QLCDNumber *lcdNumber_z;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit_2;
    QLCDNumber *lcdNumber_x_2;
    QLCDNumber *lcdNumber_y_2;
    QLCDNumber *lcdNumber_z_2;
    QLineEdit *lineEdit_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1061, 518);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(20, 40, 121, 25));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(210, 40, 391, 25));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(210, 10, 391, 20));
        lcdNumber_x = new QLCDNumber(centralWidget);
        lcdNumber_x->setObjectName(QStringLiteral("lcdNumber_x"));
        lcdNumber_x->setGeometry(QRect(50, 190, 321, 71));
        lcdNumber_x->setDigitCount(6);
        lcdNumber_y = new QLCDNumber(centralWidget);
        lcdNumber_y->setObjectName(QStringLiteral("lcdNumber_y"));
        lcdNumber_y->setGeometry(QRect(400, 190, 281, 71));
        lcdNumber_y->setDigitCount(6);
        lcdNumber_z = new QLCDNumber(centralWidget);
        lcdNumber_z->setObjectName(QStringLiteral("lcdNumber_z"));
        lcdNumber_z->setGeometry(QRect(710, 190, 311, 71));
        lcdNumber_z->setDigitCount(6);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(170, 150, 67, 17));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(510, 150, 67, 17));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(900, 150, 41, 17));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(50, 280, 971, 61));
        lcdNumber_x_2 = new QLCDNumber(centralWidget);
        lcdNumber_x_2->setObjectName(QStringLiteral("lcdNumber_x_2"));
        lcdNumber_x_2->setGeometry(QRect(50, 360, 321, 71));
        lcdNumber_x_2->setDigitCount(6);
        lcdNumber_y_2 = new QLCDNumber(centralWidget);
        lcdNumber_y_2->setObjectName(QStringLiteral("lcdNumber_y_2"));
        lcdNumber_y_2->setGeometry(QRect(400, 360, 281, 71));
        lcdNumber_y_2->setDigitCount(6);
        lcdNumber_z_2 = new QLCDNumber(centralWidget);
        lcdNumber_z_2->setObjectName(QStringLiteral("lcdNumber_z_2"));
        lcdNumber_z_2->setGeometry(QRect(710, 360, 311, 71));
        lcdNumber_z_2->setDigitCount(6);
        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(730, 70, 113, 61));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1061, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", ".csv einlesen", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("MainWindow", "/home/timohin/Documents/Messpunkte_csv.csv", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "pfad: /home/timohin/Documents/Messpunkte_csv.csv", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "X", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Y", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Z", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
