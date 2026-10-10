/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *labelStep;
    QDoubleSpinBox *spinStep;
    QLabel *labelTarget;
    QDoubleSpinBox *spinTarget;
    QLabel *labelVel;
    QDoubleSpinBox *spinVel;
    QLabel *labelAcc;
    QDoubleSpinBox *spinAcc;
    QLabel *labelDec;
    QDoubleSpinBox *spinDec;
    QLabel *labelJerk;
    QDoubleSpinBox *spinJerk;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *btnStop;
    QPushButton *btnPlus;
    QPushButton *btnAbs;
    QPushButton *btnMinus;
    QPushButton *btnClear;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *labelPosTitle;
    QLabel *labelVelTitle;
    QLabel *labelVel_2;
    QLabel *labelStateTitle;
    QLabel *labelPos;
    QLabel *labelState;
    QWidget *plot;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1014, 656);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        formLayoutWidget = new QWidget(centralwidget);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(50, 50, 371, 211));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        labelStep = new QLabel(formLayoutWidget);
        labelStep->setObjectName("labelStep");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelStep);

        spinStep = new QDoubleSpinBox(formLayoutWidget);
        spinStep->setObjectName("spinStep");
        spinStep->setMinimum(-360.000000000000000);
        spinStep->setMaximum(360.000000000000000);
        spinStep->setValue(1.000000000000000);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, spinStep);

        labelTarget = new QLabel(formLayoutWidget);
        labelTarget->setObjectName("labelTarget");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, labelTarget);

        spinTarget = new QDoubleSpinBox(formLayoutWidget);
        spinTarget->setObjectName("spinTarget");
        spinTarget->setMinimum(-100000.000000000000000);
        spinTarget->setMaximum(100000.000000000000000);
        spinTarget->setValue(90.000000000000000);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, spinTarget);

        labelVel = new QLabel(formLayoutWidget);
        labelVel->setObjectName("labelVel");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, labelVel);

        spinVel = new QDoubleSpinBox(formLayoutWidget);
        spinVel->setObjectName("spinVel");
        spinVel->setDecimals(1);
        spinVel->setMinimum(0.100000000000000);
        spinVel->setMaximum(10000.000000000000000);
        spinVel->setValue(30.000000000000000);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, spinVel);

        labelAcc = new QLabel(formLayoutWidget);
        labelAcc->setObjectName("labelAcc");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, labelAcc);

        spinAcc = new QDoubleSpinBox(formLayoutWidget);
        spinAcc->setObjectName("spinAcc");
        spinAcc->setDecimals(1);
        spinAcc->setMinimum(0.100000000000000);
        spinAcc->setMaximum(100000.000000000000000);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, spinAcc);

        labelDec = new QLabel(formLayoutWidget);
        labelDec->setObjectName("labelDec");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, labelDec);

        spinDec = new QDoubleSpinBox(formLayoutWidget);
        spinDec->setObjectName("spinDec");
        spinDec->setDecimals(1);
        spinDec->setMinimum(0.100000000000000);
        spinDec->setMaximum(100000.000000000000000);
        spinDec->setValue(60.000000000000000);

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, spinDec);

        labelJerk = new QLabel(formLayoutWidget);
        labelJerk->setObjectName("labelJerk");

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, labelJerk);

        spinJerk = new QDoubleSpinBox(formLayoutWidget);
        spinJerk->setObjectName("spinJerk");
        spinJerk->setDecimals(1);
        spinJerk->setMinimum(0.100000000000000);
        spinJerk->setMaximum(100000000.000000000000000);
        spinJerk->setValue(300.000000000000000);

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, spinJerk);

        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(490, 50, 381, 201));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        btnStop = new QPushButton(gridLayoutWidget);
        btnStop->setObjectName("btnStop");

        gridLayout->addWidget(btnStop, 3, 0, 1, 1);

        btnPlus = new QPushButton(gridLayoutWidget);
        btnPlus->setObjectName("btnPlus");

        gridLayout->addWidget(btnPlus, 0, 0, 1, 1);

        btnAbs = new QPushButton(gridLayoutWidget);
        btnAbs->setObjectName("btnAbs");

        gridLayout->addWidget(btnAbs, 2, 0, 1, 1);

        btnMinus = new QPushButton(gridLayoutWidget);
        btnMinus->setObjectName("btnMinus");

        gridLayout->addWidget(btnMinus, 1, 0, 1, 1);

        btnClear = new QPushButton(gridLayoutWidget);
        btnClear->setObjectName("btnClear");

        gridLayout->addWidget(btnClear, 4, 0, 1, 1);

        formLayoutWidget_2 = new QWidget(centralwidget);
        formLayoutWidget_2->setObjectName("formLayoutWidget_2");
        formLayoutWidget_2->setGeometry(QRect(50, 340, 161, 221));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setObjectName("formLayout_2");
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        labelPosTitle = new QLabel(formLayoutWidget_2);
        labelPosTitle->setObjectName("labelPosTitle");

        formLayout_2->setWidget(0, QFormLayout::ItemRole::LabelRole, labelPosTitle);

        labelVelTitle = new QLabel(formLayoutWidget_2);
        labelVelTitle->setObjectName("labelVelTitle");

        formLayout_2->setWidget(2, QFormLayout::ItemRole::LabelRole, labelVelTitle);

        labelVel_2 = new QLabel(formLayoutWidget_2);
        labelVel_2->setObjectName("labelVel_2");

        formLayout_2->setWidget(3, QFormLayout::ItemRole::LabelRole, labelVel_2);

        labelStateTitle = new QLabel(formLayoutWidget_2);
        labelStateTitle->setObjectName("labelStateTitle");

        formLayout_2->setWidget(4, QFormLayout::ItemRole::LabelRole, labelStateTitle);

        labelPos = new QLabel(formLayoutWidget_2);
        labelPos->setObjectName("labelPos");

        formLayout_2->setWidget(1, QFormLayout::ItemRole::LabelRole, labelPos);

        labelState = new QLabel(formLayoutWidget_2);
        labelState->setObjectName("labelState");

        formLayout_2->setWidget(5, QFormLayout::ItemRole::LabelRole, labelState);

        plot = new QWidget(centralwidget);
        plot->setObjectName("plot");
        plot->setGeometry(QRect(300, 270, 631, 341));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1014, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        labelStep->setText(QCoreApplication::translate("MainWindow", "\346\255\245\351\225\277\357\274\210deg/mm\357\274\211", nullptr));
        labelTarget->setText(QCoreApplication::translate("MainWindow", "\347\273\235\345\257\271\347\233\256\346\240\207(deg/mm)", nullptr));
        labelVel->setText(QCoreApplication::translate("MainWindow", "\346\234\200\345\244\247\351\200\237\345\272\246(unit/s)", nullptr));
        labelAcc->setText(QCoreApplication::translate("MainWindow", "\345\212\240\351\200\237\345\272\246(unit/s\302\262)", nullptr));
        labelDec->setText(QCoreApplication::translate("MainWindow", "\345\207\217\351\200\237\345\272\246(unit/s\302\262)", nullptr));
        labelJerk->setText(QCoreApplication::translate("MainWindow", "\345\212\240\345\212\240\351\200\237\345\272\246(unit/s\302\263)", nullptr));
        btnStop->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        btnPlus->setText(QCoreApplication::translate("MainWindow", "+ \346\255\243\350\275\254/\345\211\215\350\277\233", nullptr));
        btnAbs->setText(QCoreApplication::translate("MainWindow", "\347\273\235\345\257\271\345\256\232\344\275\215", nullptr));
        btnMinus->setText(QCoreApplication::translate("MainWindow", "- \345\217\215\350\275\254/\345\220\216\351\200\200", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\346\233\262\347\272\277", nullptr));
        labelPosTitle->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\344\275\215\347\275\256", nullptr));
        labelVelTitle->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\351\200\237\345\272\246", nullptr));
        labelVel_2->setText(QCoreApplication::translate("MainWindow", "0.000", nullptr));
        labelStateTitle->setText(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201", nullptr));
        labelPos->setText(QCoreApplication::translate("MainWindow", "0.000", nullptr));
        labelState->setText(QCoreApplication::translate("MainWindow", "\347\251\272\351\227\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
