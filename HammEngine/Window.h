#pragma once

#include <stdlib.h>
#include <iostream>
#include <SDL.h>
#include <set>

#include "common.h"
#include "Scene.h"
#include "Vector3.h"
#include "KeyboardListener.h"
#include "MouseListener.h"

namespace GameEngine
{

    class Window
    {

    public:
        Vector3 backgroundColor;
        int width;
        int height;
        std::string title;
        bool shouldLockCursor;

        GAMEENGINE_API Window(std::string title, int width, int height);
        GAMEENGINE_API ~Window();
        Window(const Window& window) = delete;
        Window& operator=(const Window&) = delete;
        GAMEENGINE_API void setScene(std::shared_ptr<Scene>);
        GAMEENGINE_API void registerKeyboardListener(KeyboardListener* keyboardListener);
        GAMEENGINE_API void unregisterKeyboardListener(KeyboardListener* keyboardListener);
        GAMEENGINE_API void registerMouseListener(MouseListener* mouseListener);
        GAMEENGINE_API void unregisterMouseListener(MouseListener* mouseListener);
        GAMEENGINE_API void lockCursor(bool shouldLock);
        GAMEENGINE_API void init();
        GAMEENGINE_API void quit();

    protected:
        SDL_Window* window;
        SDL_GLContext context;
        std::shared_ptr<Scene> scene;

    private:
        std::set<KeyboardListener*> keyboardListeners;
        std::set<MouseListener*> mouseListeners;
        bool shouldQuit;

        void updateWindowSettings();
        void processOneWindowTick();
        void processWindowEvents();
    };

}