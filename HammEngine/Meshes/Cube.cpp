#include "Cube.h"

namespace GameEngine
{
    Cube::Cube()
    {
        this->vertices = {
            // Front
            {-1.0f,  1.0f,  1.0f}, // Front top left
            { 1.0f,  1.0f,  1.0f}, // Front top right
            { 1.0f, -1.0f,  1.0f}, // Front bottom right
            {-1.0f, -1.0f,  1.0f}, // Front bottom left
            // Back
            {-1.0f,  1.0f, -1.0f}, // Back top left 
            { 1.0f,  1.0f, -1.0f}, // Back top right 
            { 1.0f, -1.0f, -1.0f}, // Back bottom right 
            {-1.0f, -1.0f, -1.0f}, // Back bottom left 
            // top
            {-1.0f,  1.0f,  1.0f}, // Front top left
            { 1.0f,  1.0f,  1.0f}, // Front top right
            {-1.0f,  1.0f, -1.0f}, // Back top left
            { 1.0f,  1.0f, -1.0f}, // Back top right 
            // Botom
            {-1.0f, -1.0f,  1.0f}, // Front bottom left
            { 1.0f, -1.0f,  1.0f}, // Front bottom right
            {-1.0f, -1.0f, -1.0f}, // Back bottom left
            { 1.0f, -1.0f, -1.0f}, // Back bottom right
            // left
            {-1.0f,  1.0f,  1.0f}, // Front top left
            {-1.0f, -1.0f,  1.0f}, // Front bottom left
            {-1.0f,  1.0f, -1.0f}, // Back top left
            {-1.0f, -1.0f, -1.0f}, // Back bottom left  
            // right
            { 1.0f,  1.0f,  1.0f}, // Front top right
            { 1.0f, -1.0f,  1.0f}, // Front bottom right
            { 1.0f,  1.0f, -1.0f}, // Back top right
            { 1.0f, -1.0f, -1.0f}, // Back bottom right  
        };

        this->indices = {
            // Front
            1, 0, 2,
            0, 3, 2,
            // Back
            5, 6, 7,
            4, 5, 7,
            // top
            10, 8, 9,
            11, 10, 9,
            // bottom
            15, 13, 12,
            14, 15, 12,
            // left
            18, 19, 17,
            16, 18, 17,
            // right
            20, 21, 23,
            22, 20, 23
        };

        this->normals = {
            // Front
            {0.0f, 0.0f, 1.0f},
            {0.0f, 0.0f, 1.0f},
            {0.0f, 0.0f, 1.0f},
            {0.0f, 0.0f, 1.0f},

            // Back
            {0.0f, 0.0f, -1.0f},
            {0.0f, 0.0f, -1.0f},
            {0.0f, 0.0f, -1.0f},
            {0.0f, 0.0f, -1.0f},
            
            // top
            {0.0f, 1.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            
            // bottom
            {0.0f, -1.0f, 0.0f},
            {0.0f, -1.0f, 0.0f},
            {0.0f, -1.0f, 0.0f},
            {0.0f, -1.0f, 0.0f},
            
            // left
            {-1.0f, 0.0f, 0.0f},
            {-1.0f, 0.0f, 0.0f},
            {-1.0f, 0.0f, 0.0f},
            {-1.0f, 0.0f, 0.0f},
            
            // right
            {1.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 0.0f}
        };
    }
}