#ifndef WIDGET_H
#define WIDGET_H

#include "ui_Widget.h"

class Widget : public QWidget, private Ui::Widget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_inputFileButton_clicked();
    void on_convertButton_clicked();
};

#endif // WIDGET_H
