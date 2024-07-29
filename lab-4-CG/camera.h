#ifndef CAMERA_H
#define CAMERA_H
#include <QPainter>

#include "matrix.h"

class Camera
{
public:
    Camera() = delete;

    static const Matrix &projection() { return projection_; }//геттер проекции

    static void ObserverEye(float x, float y, float z); // точка зрения
    static void Txy(float Tx, float Ty);

private:
    static float x_;
    static float y_;
    static float z_;
    static Matrix view_;
    static Matrix projection_;
};

#endif // CAMERA_H
