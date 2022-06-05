#include "Window.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "Components/ShaderProgram.h"

using namespace std;

namespace GameEngine
{

    Window::Window(std::string title, int width, int height) :
        window(NULL),
        context(NULL),
        shouldQuit(false),
        shouldLockCursor(false)
    {
        this->title = title;
        this->width = width;
        this->height = height;
        this->backgroundColor.x = 0;
        this->backgroundColor.y = 0;
        this->backgroundColor.z = 0;
    }

    Window::~Window()
    {
        SDL_GL_DeleteContext(this->context);
        SDL_DestroyWindow(this->window);
        SDL_Quit();
    }

    void Window::setScene(std::shared_ptr<Scene> scene)
    {
        this->scene = std::move(scene);
    }

    void Window::registerKeyboardListener(KeyboardListener* keyboardListener)
    {
        this->keyboardListeners.insert(keyboardListener);
    }

    void Window::unregisterKeyboardListener(KeyboardListener* keyboardListener)
    {
        this->keyboardListeners.erase(keyboardListener);
    }
    void Window::registerMouseListener(MouseListener* mouseListener)
    {
        this->mouseListeners.insert(mouseListener);
    }

    void Window::unregisterMouseListener(MouseListener* mouseListener)
    {
        this->mouseListeners.erase(mouseListener);
    }

    void Window::lockCursor(bool shouldLock)
    {
        this->shouldLockCursor = shouldLock;
    }

    void Window::init()
    {
        // TODO: comment on what everything is doing
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            cerr << "Could not initialize SDL: " << SDL_GetError() << endl;
            return;
        }

        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        this->window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_OPENGL);

        if (this->window == NULL)
        {
            cerr << "Could not create window: " << SDL_GetError() << endl;
            return;
        }

        this->context = SDL_GL_CreateContext(this->window);

        // Vsync
        SDL_GL_SetSwapInterval(1);

        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        }

        glViewport(0, 0, width, height);
        glEnable(GL_DEPTH_TEST);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // Compile shader programs
        for (ShaderProgram* shaderProgram : ShaderProgram::shaderPrograms)
        {
            shaderProgram->compileShaders();
        }

        this->shouldQuit = false;

        while (!shouldQuit) {
            this->processOneWindowTick();
        }
    }

    void Window::quit()
    {
        this->shouldQuit = true;
    }

    void Window::processOneWindowTick()
    {
        this->updateWindowSettings();

        this->processWindowEvents();

        if (this->scene != nullptr)
        {
            this->scene->draw();
        }

        SDL_GL_SwapWindow(this->window);
    }
    
    void Window::updateWindowSettings()
    {
        // Update background color
        glClearColor(this->backgroundColor.x, this->backgroundColor.y, this->backgroundColor.z, 1.0f);

        // Update window size
        SDL_SetWindowSize(this->window, this->width, this->height);

        // Update window title
        SDL_SetWindowTitle(this->window, this->title.c_str());

        // Update cursor lock
        if (this->shouldLockCursor)
        {
            SDL_SetRelativeMouseMode(SDL_TRUE);
        }
        else
        {
            SDL_SetRelativeMouseMode(SDL_FALSE);
        }
    }

    void Window::processWindowEvents()
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
                case SDL_KEYDOWN:
                    for (KeyboardListener* keyboardListener : this->keyboardListeners)
                    {
                        keyboardListener->onKeyDown(*reinterpret_cast<SDL_KeyboardEvent*>(&event));
                    }
                    break;

                case SDL_KEYUP:
                    for (KeyboardListener* keyboardListener : this->keyboardListeners)
                    {
                        keyboardListener->onKeyUp(*reinterpret_cast<SDL_KeyboardEvent*>(&event));
                    }
                    break;

                case SDL_MOUSEMOTION:
                    for (MouseListener* mouseListener : this->mouseListeners)
                    {
                        mouseListener->onMouseMotion(*reinterpret_cast<SDL_MouseMotionEvent*>(&event));
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    for (MouseListener* mouseListener : this->mouseListeners)
                    {
                        mouseListener->onMouseUp(*reinterpret_cast<SDL_MouseButtonEvent*>(&event));
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    for (MouseListener* mouseListener : this->mouseListeners)
                    {
                        mouseListener->onMouseDown(*reinterpret_cast<SDL_MouseButtonEvent*>(&event));
                    }
                    break;

                case SDL_QUIT:
                    this->shouldQuit = true;
                    break;

                default:
                    break;
            }

        }
    }
}
