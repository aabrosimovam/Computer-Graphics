#include "camera.h"
#include "matrix.h"
#include <cmath>

Matrix Camera::view_(4, 4);
Matrix Camera::projection_(4, 4);//проекция

void Camera::ObserverEye(float x, float y, float z)
{
    Matrix T
    {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { -x, -y, -z, 1 },
    };

    Matrix S
    {
        { -1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 },
    };

    Matrix Rx90
    {
        { 1, 0, 0, 0 },
        { 0, 0, -1, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 0, 1 },
    };

    float sin, cos;
    float sqxy = sqrt(x * x + y * y);

    if (sqxy == 0)
    {
        cos = 1;
        sin = 0;
    }
    else
    {
        cos = y / sqxy;
        sin = x / sqxy;
    }

    Matrix Ry
    {
        { cos, 0, sin, 0 },
        { 0, 1, 0, 0 },
        { -sin, 0, cos, 0 },
        { 0, 0, 0, 1 },
    };


    if (sqrt(sqxy * sqxy + z * z) == 0)
    {
        cos = 1;
        sin = 0;
    }
    else
    {
        cos = sqxy / sqrt(sqxy * sqxy + z * z);
        sin = z / sqrt(sqxy * sqxy + z * z);
    }

    Matrix Rx
    {
        { 1, 0, 0, 0 },
        { 0, cos, -sin, 0 },
        { 0, sin, cos, 0 },
        { 0, 0, 0, 1 },
    };

    view_ = T * S * Rx90 * Ry * Rx;
}

void Camera::Txy(float Tx, float Ty)//сдвиг
{
    projection_ = Matrix
    {
    { 1, 0, 0, 0 },
    { 0, -1, 0, 0 },
    { 0, 0, 0, 0 },
    { Tx, Ty, 0, 1 },
};
}

