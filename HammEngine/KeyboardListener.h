#pragma once

#include <SDL.h>

namespace GameEngine
{
    class KeyboardListener
    {
    public:
        virtual void onKeyDown(SDL_KeyboardEvent event) = 0;
        virtual void onKeyUp(SDL_KeyboardEvent event) = 0;
    };
}