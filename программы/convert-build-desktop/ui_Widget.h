/********************************************************************************
** Form generated from reading UI file 'Widget.ui'
**
** Created: Sun 3. Apr 15:43:56 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *fileNameEdit;
    QPushButton *inputFileButton;
    QLabel *label;
    QLineEdit *freqIndexEdit;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *convertButton;
    QSpacerItem *horizontalSpacer_2;
    QRadioButton *azRadio;
    QRadioButton *elRadio;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(587, 193);
        gridLayout = new QGridLayout(Widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        fileNameEdit = new QLineEdit(Widget);
        fileNameEdit->setObjectName(QString::fromUtf8("fileNameEdit"));

        gridLayout->addWidget(fileNameEdit, 0, 1, 1, 2);

        inputFileButton = new QPushButton(Widget);
        inputFileButton->setObjectName(QString::fromUtf8("inputFileButton"));

        gridLayout->addWidget(inputFileButton, 0, 3, 1, 1);

        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        freqIndexEdit = new QLineEdit(Widget);
        freqIndexEdit->setObjectName(QString::fromUtf8("freqIndexEdit"));

        gridLayout->addWidget(freqIndexEdit, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        convertButton = new QPushButton(Widget);
        convertButton->setObjectName(QString::fromUtf8("convertButton"));

        horizontalLayout->addWidget(convertButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 5, 0, 1, 4);

        azRadio = new QRadioButton(Widget);
        azRadio->setObjectName(QString::fromUtf8("azRadio"));
        azRadio->setCheckable(true);
        azRadio->setChecked(true);

        gridLayout->addWidget(azRadio, 2, 0, 1, 1);

        elRadio = new QRadioButton(Widget);
        elRadio->setObjectName(QString::fromUtf8("elRadio"));

        gridLayout->addWidget(elRadio, 3, 0, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "\320\237\321\200\320\265\320\276\320\261\321\200\320\260\320\267\320\276\320\262\320\260\320\275\320\270\320\265 \321\204\320\276\321\200\320\274\320\260\321\202\320\260 \321\204\320\260\320\271\320\273\320\276\320\262", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Widget", "\320\230\321\201\321\205\320\276\320\264\320\275\321\213\320\271 \321\204\320\260\320\271\320\273:", 0, QApplication::UnicodeUTF8));
        inputFileButton->setText(QApplication::translate("Widget", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\204\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Widget", "\320\235\320\276\320\274\320\265\321\200 \321\207\320\260\321\201\321\202. \321\202\320\276\321\207\320\272\320\270:", 0, QApplication::UnicodeUTF8));
        convertButton->setText(QApplication::translate("Widget", "\320\232\320\276\320\275\320\262\320\265\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", 0, QApplication::UnicodeUTF8));
        azRadio->setText(QApplication::translate("Widget", "\320\220\320\267\320\270\320\274\321\203\321\202", 0, QApplication::UnicodeUTF8));
        elRadio->setText(QApplication::translate("Widget", "\320\243\320\263\320\276\320\273 \320\274\320\265\321\201\321\202\320\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
