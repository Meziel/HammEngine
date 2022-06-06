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
        /// Sets the color of pixels with no objects on them
        Vector3 backgroundColor;

        /// Window width
        int width;

        /// Window height
        int height;

        /// Window title
        std::string title;

        /**
         * Window constructor
         *
         * @param title Sets the title of the window
         * @param width Sets the width of the window
         * @param height Sets the height of the window
         */
        GAMEENGINE_API Window(std::string title, int width, int height);

        /**
         * Window decosntructor
         */
        GAMEENGINE_API ~Window();

        /// Copy constructor deleted
        Window(const Window& window) = delete;
        /// Assignment operator deleted
        Window& operator=(const Window&) = delete;

        /**
         * Set the scene used for the window
         */
        GAMEENGINE_API void setScene(std::shared_ptr<Scene>);
        
        /**
         * Registers a keyboard listener
         * 
         * A keyboard listener can respond to keyboard events on the window through callback functions.
         * This functions registers a keyboard listener so that when a keyboard event happens, it calls all the approciate callback function
         * on all keyboard listeners registered
         * 
         * @param keyboardListener KeyboardListener to register
         */
        GAMEENGINE_API void registerKeyboardListener(KeyboardListener* keyboardListener);

        /**
         * Unregisters a keyboard listener
         *
         * When calling this function, all keyboard events made on the window will no longer call callback functions on the keyboard listener passed in.
         * 
         * @param keyboardListener KeyboardListener to unregister
         */
        GAMEENGINE_API void unregisterKeyboardListener(KeyboardListener* keyboardListener);

        /**
         * Registers a mouse listener
         * 
         * @param mouseListener MouseListener to register
         */
        GAMEENGINE_API void registerMouseListener(MouseListener* mouseListener);

        /**
         * Unregisters a mouse listener
         * 
         * @param mouseListener MouseListener to unregister
         */
        GAMEENGINE_API void unregisterMouseListener(MouseListener* mouseListener);

        /** 
         * Updates the windows settings to lock or unlock the cursor to the center of the window and change its visibility
         * 
         * @param shouldLock Whether to lock or unlock the cursor
         */
        GAMEENGINE_API void lockCursor(bool shouldLock);

        /**
         * Shows the window and begins executing main loop
         *
         * Begins showing the window and executes its processing loop. Call will take over execution until the window is closed
         **/
        GAMEENGINE_API void init();

        /**
         * Closes the window and stop the main execution loop
         */
        GAMEENGINE_API void quit();

    protected:
        SDL_Window* window;
        SDL_GLContext context;
        std::shared_ptr<Scene> scene;
        bool shouldLockCursor;

    private:
        std::set<KeyboardListener*> keyboardListeners;
        std::set<MouseListener*> mouseListeners;
        bool shouldQuit;

        void updateWindowSettings();
        void processOneWindowTick();
        void processWindowEvents();
    };

}