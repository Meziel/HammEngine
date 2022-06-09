#pragma once

#include <SDL.h>

namespace GameEngine
{
    class MouseListener
    {
    public:
        /**
         * Method to respond to mouse movement events
         *
         * @param event Information about the mouse movement
         */
        virtual void onMouseMotion(SDL_MouseMotionEvent event) = 0;

        /**
         * Method to respond to mouse down events
         *
         * @param event Information about the mouse down event
         */
        virtual void onMouseDown(SDL_MouseButtonEvent event) = 0;

        /**
         * Method to respond to mouse up events
         *
         * @param event Information about the mouse up event
         */
        virtual void onMouseUp(SDL_MouseButtonEvent event) = 0;
    };
}