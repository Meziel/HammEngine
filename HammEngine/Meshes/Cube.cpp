#include "Cube.h"

namespace GameEngine
{
    Cube::Cube()
    {
        this->vertices = {
            {-1.0f, 1.0f, 1.0f}, {-1.0f, -1.0f, 1.0f}, {1.0f, -1.0f, 1.0f},
            {-1.0f, 1.0f, 1.0f}, {1.0f, -1.0f, 1.0f},  {1.0f, 1.0f, 1.0f}
        };
    }
}