#pragma once

#include <vector>

#include "../Component.h"
#include "../Vector3.h"

namespace GameEngine
{
    class Mesh : public Component
    {
    public:
        /// All the vertices
        std::vector<Vector3> vertices;
        
        /// All the normals
        std::vector<Vector3> normals;

        /// Allows us to not send the same vertices twice to the graphics card
        std::vector<Vector3> indices;

        /**
         * Mesh constructor
         */
        GAMEENGINE_API Mesh::Mesh();
    };
}