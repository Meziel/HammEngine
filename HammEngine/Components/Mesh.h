#pragma once

#include <vector>

#include "../Component.h"
#include "../Vector3.h"

namespace GameEngine
{
    class Mesh : public Component
    {
    public:
        std::vector<Vector3> vertices;

        GAMEENGINE_API Mesh::Mesh();
    };
}