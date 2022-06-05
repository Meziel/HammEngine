#include "Camera.h"
#include "../MatrixUtils.h"

namespace GameEngine
{
    Camera::Camera()
    {
        this->fov = 45.0f;
        this->aspect = 800.0f / 600.f;
        this->near = 0.1f;
        this->far = 100.0f;
    }

    Vector3 Camera::up()
    {
        return MatrixUtils::createRotationMatrix(this->rotation()) * Vector3 { 0.0f, 1.0f, 0.0f };
    }

    Vector3 Camera::forward()
    {
        return MatrixUtils::createRotationMatrix(this->rotation()) * Vector3 { 0.0f, 0.0f, -1.0f };
    }
}