#pragma once

#include <SDL.h>

namespace GameEngine
{
    class MouseListener
    {
    public:
        virtual void onMouseMotion(SDL_MouseMotionEvent event) = 0;
        virtual void onMouseDown(SDL_MouseButtonEvent event) = 0;
        virtual void onMouseUp(SDL_MouseButtonEvent event) = 0;
    };
}