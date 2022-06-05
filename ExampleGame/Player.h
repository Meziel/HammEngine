#pragma once

#include <ctime>

#include <GameObject.h>
#include <GameObjects/Camera.h>
#include <KeyboardListener.h>
#include <MouseListener.h>

using namespace GameEngine;

namespace ExampleGame
{
    // Player inherits GameObject so that it can be attached to a scene
    // Keyboard listener allows you to respond to key inputs on the game window
    class Player : public GameObject, public KeyboardListener, public MouseListener
    {
    public:
        static const float WALKING_SPEED_MPS;

        Camera* followCamera;

        virtual void onTick();

        // Implements KeyboardListener interface
        virtual void onKeyUp(SDL_KeyboardEvent event);
        virtual void onKeyDown(SDL_KeyboardEvent event);
        // Implements MouseListener interface
        virtual void onMouseMotion(SDL_MouseMotionEvent event);
        virtual void onMouseDown(SDL_MouseButtonEvent event);
        virtual void onMouseUp(SDL_MouseButtonEvent event);

    private:
        float upKeyDown;
        float downKeyDown;
        float leftKeyDown;
        float rightKeyDown;
        clock_t lastTick;
    };
}