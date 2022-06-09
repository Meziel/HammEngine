#pragma once

#include <GL/glew.h>
#include <string>
#include <set>

#include <cstdlib>

#include "../common.h"
#include "../Component.h"

namespace GameEngine
{
    class ShaderProgram : public Component
    {

    public:

        /// Keeps track of all shader programs that are being used
        static std::set<ShaderProgram*> shaderPrograms;

        /// Indicates if the shaders have alraedy be compiled
        bool shadersCompiled;

        /**
         * Constructor
         * @param vertexFilePath Vertex shader file path to use
         * @param fragmentFilePath Fragment shader file path to use
         */
        GAMEENGINE_API ShaderProgram(
            const std::string vertexFilePath = "C:/Users/Michael/source/repos/HammEngine/HammEngine/Shaders/PhongVertex.glsl",
            const std::string fragmentFilePath = "C:/Users/Michael/source/repos/HammEngine/HammEngine/Shaders/PhongFragment.glsl");
        
        /**
         * Decosntructor
         */
        GAMEENGINE_API ~ShaderProgram();

        /// Delete copy constructor
        ShaderProgram(const ShaderProgram& shader) = delete;

        /// Delete assignment operator
        ShaderProgram&operator=(const ShaderProgram& shader) = delete;

        /**
         * Creates a shader program
         *
         * This method creates a shader program from the vertex and fragment shader.
         * The program identifier can be received through getProgram.
         * This method must be called before calling the use method
         */
        void compileShaders();

        /**
         * Gets the shader program identifier 
         *
         * @return GLuint of the shader program
         **/
        GLuint getProgram();

        /**
         * Loads the shader program into the opengl context
         */
        void use();

    protected:

        static std::string getShaderSource(const char* filePath);
        static bool createShader(GLenum type, GLchar* source, GLuint* shader);
        static void deleteShaders(GLuint vertexShader, GLuint fragmentShader);

        static void printShaderErrors(GLuint shader);
        static void printProgramErrors(GLuint program);

        bool createProgram(GLuint vertexShader, GLuint fragmentShader);
        GLuint program;
        const std::string vertexFilePath;
        const std::string fragmentFilePath;
    };
}