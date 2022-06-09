#pragma once

#include <SDL.h>

namespace GameEngine
{
    class KeyboardListener
    {
    public:
        /**
         * Method to respond to key down events
         *
         * @param event Information about the key down event
         */
        virtual void onKeyDown(SDL_KeyboardEvent event) = 0;
        
        /**
         * Method to respond to key up events
         *
         * @param event Information about the key up event
         */
        virtual void onKeyUp(SDL_KeyboardEvent event) = 0;
    };
}