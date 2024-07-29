#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class arrow
{
private:
    QLineF list[6];
    double angle = 3.1415926535/360;
    int T[3][3] =
    {
        {1,0,0},
        {0,1,0},
        {100,225,1}
    };
    double R[3][3] =
    {
        {cos(angle),sin(angle),0},
        {-sin(angle),cos(angle),0},
        {0,0,1}
    };
public:
    arrow()
    {
        list[0] = QLineF(225,225,215,125);
        list[1] = QLineF(215,125,205,125);
        list[2] = QLineF(205,125,225,25);
        list[3] = QLineF(225,25,245,125);
        list[4] = QLineF(245,125,235,125);
        list[5] = QLineF(235,125,225,225);
    }

    void updateLines()
    {
        double shift_x = list[0].x1();
        double shift_y = list[0].y1();

        for(int i=0;i<6;i++)
        {
            double x1 = list[i].x1()- shift_x;
            double y1 = list[i].y1()- shift_y;
            double x2 = list[i].x2()- shift_x;
            double y2 = list[i].y2()- shift_y;

            double new_x1 = x1*cos(angle)-y1*sin(angle);
            double new_y1 = x1*sin(angle)+y1*cos(angle);
            double new_x2 = x2*cos(angle)-y2*sin(angle);
            double new_y2 = x2*sin(angle)+y2*cos(angle);

            new_x1+=shift_x;
            new_y1+=shift_y;
            new_x2+=shift_x;
            new_y2+=shift_y;

            list[i].setPoints(QPointF(new_x1,new_y1),QPointF(new_x2,new_y2));
        }
    }

    QLineF getLine(int i)
    {
        return list[i];
    }
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void Draw();
private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    QTimer *animationTimer;
    arrow *obj;
};
#endif // WIDGET_H
