#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>

#include "figura.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QMainWindow
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    Figura* myFigura;
};

#endif // WIDGET_H
