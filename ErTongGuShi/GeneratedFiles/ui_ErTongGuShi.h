/********************************************************************************
** Form generated from reading UI file 'ErTongGuShi.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERTONGGUSHI_H
#define UI_ERTONGGUSHI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ErTongGuShiClass
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_end;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLineEdit *lineEdit_begin;
    QPushButton *pushButton;
    QLabel *label_3;
    QLineEdit *lineEdit_url;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *ErTongGuShiClass)
    {
        if (ErTongGuShiClass->objectName().isEmpty())
            ErTongGuShiClass->setObjectName(QStringLiteral("ErTongGuShiClass"));
        ErTongGuShiClass->resize(778, 478);
        verticalLayout = new QVBoxLayout(ErTongGuShiClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEdit_end = new QLineEdit(ErTongGuShiClass);
        lineEdit_end->setObjectName(QStringLiteral("lineEdit_end"));

        gridLayout->addWidget(lineEdit_end, 2, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 3, 1, 1);

        label_2 = new QLabel(ErTongGuShiClass);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        label = new QLabel(ErTongGuShiClass);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 1, 1, 1);

        lineEdit_begin = new QLineEdit(ErTongGuShiClass);
        lineEdit_begin->setObjectName(QStringLiteral("lineEdit_begin"));

        gridLayout->addWidget(lineEdit_begin, 1, 2, 1, 1);

        pushButton = new QPushButton(ErTongGuShiClass);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 3, 2, 1, 1);

        label_3 = new QLabel(ErTongGuShiClass);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 1, 1, 1);

        lineEdit_url = new QLineEdit(ErTongGuShiClass);
        lineEdit_url->setObjectName(QStringLiteral("lineEdit_url"));

        gridLayout->addWidget(lineEdit_url, 0, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        textBrowser = new QTextBrowser(ErTongGuShiClass);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout->addWidget(textBrowser);


        retranslateUi(ErTongGuShiClass);

        QMetaObject::connectSlotsByName(ErTongGuShiClass);
    } // setupUi

    void retranslateUi(QWidget *ErTongGuShiClass)
    {
        ErTongGuShiClass->setWindowTitle(QApplication::translate("ErTongGuShiClass", "ErTongGuShi", Q_NULLPTR));
        label_2->setText(QApplication::translate("ErTongGuShiClass", "\347\273\223\346\235\237\357\274\232", Q_NULLPTR));
        label->setText(QApplication::translate("ErTongGuShiClass", "\345\274\200\345\247\213\357\274\232", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ErTongGuShiClass", "\350\216\267\345\217\226", Q_NULLPTR));
        label_3->setText(QApplication::translate("ErTongGuShiClass", "\347\275\221\345\235\200\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ErTongGuShiClass: public Ui_ErTongGuShiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERTONGGUSHI_H
