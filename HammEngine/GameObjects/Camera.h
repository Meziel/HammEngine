#pragma once

#include "../common.h"
#include "../GameObject.h"
#include "../Vector3.h"

namespace GameEngine
{
    class Camera : public GameObject
    {
    public:
        float fov;
        float aspect;
        float near;
        float far;

        GAMEENGINE_API Camera();

        GAMEENGINE_API Vector3 Camera::up();
        GAMEENGINE_API Vector3 Camera::forward();
    };
}