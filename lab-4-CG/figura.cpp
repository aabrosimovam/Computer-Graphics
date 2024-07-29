#include "figura.h"
#include <QPainter>
#include <QPoint>
#include <cmath>
#include <QTimerEvent>

#include <algorithm>
using namespace std;

#define pi 3.1415926535

Figura::Figura(QWidget *parent) :QWidget(parent),
    ver(CountSecants*CountSecants,4), rotation(4,4), corners_
{
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
}
{
    setFixedSize(600,400); // фиксируем размер окна

    Camera::ObserverEye(0, 0, -1);
    Camera::Txy(300, 200); // настройка камеры через половину размера окна

    float xMin = -5; float xMax = 5; float zMin = -1; float zMax = 1;

    float stepZ = (zMax - zMin) / CountSecants;//подсчет количества итераций для сдвигов по секущим
    float stepX = (xMax - xMin) / CountSecants;
    int k = 0;
    float z = zMin;
    for(int i = 0; i < CountSecants; i++)
    {
        float x = xMin;
        for(int j = 0; j < CountSecants; j++)
        {
            ver[k][0] = x;
            ver[k][1] = y(x,z);
            ver[k][2] = z;
            ver[k][3] = 1;

            x += stepX;
            k++;
        }
        z += stepZ;
    }
    SetterAlphas(AlphaX,AlphaY);//обновление через сеттер углов
}

void Figura::paintEvent(QPaintEvent *)
{
    Matrix vertices = window(ver * rotation) * Camera::projection();
    QPainter painter(this);
    QVector<int> lower(this->width());// нижний и верхний горизонты
    QVector<int> upper(this->width());
    lower.fill(this->height());
    upper.fill(0);
    QVector<int> lower_n(lower);
    QVector<int> upper_n(upper);
    int x0, y0, x1, y1;
    bool flag_p;
    int flag;
    int v = 0;

    for (int z = 0; z < CountSecants; z++)
    {
        for (int x = 0; x < CountSecants; x++)
        {
            x1 = round(vertices[v][0]);
            y1 = round(vertices[v][1]);
            if(y1 < lower[x1] || y1 > upper[x1])//ниже нижней или выше верхней
                flag = 1;
            if (x != 0 && (flag_p || flag))
            {
                int dx = abs(x1 - x0);
                int xi = -1;
                if(x0 < x1)
                    xi = 1;
                int dy = -abs(y1 - y0);
                int yi = -1;
                if(y0 < y1)
                    yi = 1;
                int dxy = dx + dy;
                while (true)
                {
                    int flag = 0;
                    if (lower[x0] > y0)//проверки по горизонту
                    {
                        lower_n[x0] = y0;
                        flag = 1;//внешняя
                    }
                    if (upper[x0] < y0)
                    {
                        upper_n[x0] = y0;
                        flag = 2;//внутренняя
                    }
                    if (flag == 3)
                    {
                        painter.setPen(Qt::yellow);//первое сечение
                        painter.drawPoint(x0, y0);
                    }
                    else if (flag==1)
                    {
                        painter.setPen(Qt::red);//внешняя
                        painter.drawPoint(x0, y0);
                    }
                    else if (flag==2)
                    {
                        painter.setPen(Qt::darkBlue);//внутренняя
                        painter.drawPoint(x0, y0);
                    }
                    if (x0 == x1 && y0 == y1) break;
                    int _2dxy = 2 * dxy;//dx+dy
                    if (_2dxy >= dy)
                    {
                        dxy += dy;
                        x0 += xi;
                    }
                    if (_2dxy <= dx)
                    {
                        dxy += dx;
                        y0 += yi;
                    }
                }
            }
            else
            {
                x0 = x1;
                y0 = y1;
            }
            flag_p = flag;
            v++;
        }
        lower = lower_n;
        upper = upper_n;
    }
}

const Matrix Figura::window(const Matrix &vertices)
{
    Matrix corners = corners_ * rotation;
    float norm_x = abs((*max_element(corners.begin(), corners.end(), [](const row &a, const row &b) { return abs(a[0]) < abs(b[0]); }))[0]);
    float norm_y = abs((*max_element(vertices.begin(), vertices.end(), [](const row &a, const row &b) { return abs(a[1]) < abs(b[1]); }))[1]);
    float k = min(300*0.7 / norm_x, 200*0.7 / norm_y);

    return vertices * Matrix//scale
    {
        { k, 0, 0, 0 },
        { 0, k, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 1 },
    };
}

void Figura::SetterAlphas(float rotationX, float rotationY)//создание и перемножения матриц поворота
{
    rotation = Matrix({{cos(rotationY * pi / 180),0,sin(rotationY * pi / 180),0},
                       {0,1,0,0},
                       {-sin(rotationY * pi / 180),0,cos(rotationY * pi / 180),0},
                       {0,0,0,1}}) *
            Matrix({{1,0,0,0},
                    {0,cos(rotationX * pi / 180),-sin(rotationX * pi / 180),0},
                    {0,sin(rotationX * pi / 180),cos(rotationX * pi / 180),0},
                    {0,0,0,1}});
}



void Figura::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    myTimer = startTimer(200);
}

void Figura::timerEvent(QTimerEvent *event)//обновление отрсисовки
{
    int steps=0;
    if(event->timerId() == myTimer)
    {
        AlphaY += dA;
        steps+=1;
        SetterAlphas(AlphaX,AlphaY);
        if (steps < 100)
            update();
    } else {
        QWidget::timerEvent(event);
    }
}

void Figura::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
    killTimer(myTimer);
}
