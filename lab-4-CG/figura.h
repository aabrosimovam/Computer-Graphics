#ifndef FIGURA_H
#define FIGURA_H

#include <QWidget>
#include <cmath>

#include "matrix.h"
#include "camera.h"

#define exp 2.7182818284

class Figura : public QWidget
{
    Q_OBJECT
public:
    Figura(QWidget *parent = nullptr);

private:
    void paintEvent(QPaintEvent *event) override;
    const Matrix window(const Matrix &vertices);
    void SetterAlphas(float rotationX, float rotationY);

    float y(const float &x, const float &z)
    { return (abs(x)+abs(z)); }

    int CountSecants = 200;//количество секущих
    Matrix ver;
    Matrix rotation;
    Matrix corners_;
    float AlphaY = 0;// начальный угол
    float AlphaX = 5;
    float dA = 3;// коэф для угла
    int myTimer;
    void timerEvent(QTimerEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
};

#endif // FIGURA
