/********************************************************************************
** Form generated from reading UI file 'Laboratorul1314.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LABORATORUL1314_H
#define UI_LABORATORUL1314_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Laboratorul1314Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Laboratorul1314Class)
    {
        if (Laboratorul1314Class->objectName().isEmpty())
            Laboratorul1314Class->setObjectName(QString::fromUtf8("Laboratorul1314Class"));
        Laboratorul1314Class->resize(600, 400);
        menuBar = new QMenuBar(Laboratorul1314Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Laboratorul1314Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Laboratorul1314Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Laboratorul1314Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Laboratorul1314Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Laboratorul1314Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Laboratorul1314Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Laboratorul1314Class->setStatusBar(statusBar);

        retranslateUi(Laboratorul1314Class);

        QMetaObject::connectSlotsByName(Laboratorul1314Class);
    } // setupUi

    void retranslateUi(QMainWindow *Laboratorul1314Class)
    {
        Laboratorul1314Class->setWindowTitle(QCoreApplication::translate("Laboratorul1314Class", "Laboratorul1314", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Laboratorul1314Class: public Ui_Laboratorul1314Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LABORATORUL1314_H
