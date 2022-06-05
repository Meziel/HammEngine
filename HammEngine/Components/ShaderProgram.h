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

        static std::set<ShaderProgram*> shaderPrograms;

        bool shadersCompiled;

        GAMEENGINE_API ShaderProgram(
            const std::string vertexFilePath = "C:/Users/Michael/source/repos/HammEngine/HammEngine/Shaders/PhongVertex.glsl",
            const std::string fragmentFilePath = "C:/Users/Michael/source/repos/HammEngine/HammEngine/Shaders/PhongFragment.glsl");
        GAMEENGINE_API ~ShaderProgram();
        ShaderProgram(const ShaderProgram& shader) = delete;
        ShaderProgram&operator=(const ShaderProgram& shader) = delete;

        void compileShaders();
        GLuint getProgram();
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