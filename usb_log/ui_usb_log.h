/********************************************************************************
** Form generated from reading UI file 'usb_log.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USB_LOG_H
#define UI_USB_LOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Usb_log
{
public:
    QTextEdit *edit_log;

    void setupUi(QWidget *Usb_log)
    {
        if (Usb_log->objectName().isEmpty())
            Usb_log->setObjectName(QString::fromUtf8("Usb_log"));
        Usb_log->resize(691, 216);
        edit_log = new QTextEdit(Usb_log);
        edit_log->setObjectName(QString::fromUtf8("edit_log"));
        edit_log->setGeometry(QRect(10, 10, 661, 191));

        retranslateUi(Usb_log);

        QMetaObject::connectSlotsByName(Usb_log);
    } // setupUi

    void retranslateUi(QWidget *Usb_log)
    {
        Usb_log->setWindowTitle(QApplication::translate("Usb_log", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Usb_log: public Ui_Usb_log {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USB_LOG_H
