#include "Player.h"

#include <iostream>

namespace ExampleGame
{
    const float Player::WALKING_SPEED_MPS = 1.2f;

    void Player::onTick()
    {
        clock_t now = clock();

        float timeSinceLastTickSeconds = float(now - this->lastTick) / CLOCKS_PER_SEC;

        // Compute vertical and horizontal movement based on key positions
        float verticalAxisRaw = -1 * (this->downKeyDown ? 1 : 0) + 1 * (this->upKeyDown ? 1 : 0);
        float horizontalAxisRaw = -1 * (this->leftKeyDown ? 1 : 0) + 1 * (this->rightKeyDown ? 1 : 0);

        // Makes it so player cannot walk faster by strafing
        float verticalAxisNormalized;
        float horizontalAxisNormalized;
        float movementAxisSum = abs(verticalAxisRaw + horizontalAxisRaw);
        if (movementAxisSum > 1)
        {
            verticalAxisNormalized = verticalAxisRaw / movementAxisSum;
            horizontalAxisNormalized = horizontalAxisRaw / movementAxisSum;
        }
        else
        {
            verticalAxisNormalized = verticalAxisRaw;
            horizontalAxisNormalized = horizontalAxisRaw;
        }

        if (verticalAxisNormalized != 0)
        {
            this->position(this->position() + this->followCamera->forward() * (verticalAxisNormalized * Player::WALKING_SPEED_MPS * timeSinceLastTickSeconds));
        }
        if (horizontalAxisNormalized != 0)
        {
            this->position(this->position() + (this->followCamera->forward() * this->followCamera->up()) * (horizontalAxisNormalized * Player::WALKING_SPEED_MPS * timeSinceLastTickSeconds));
        }

        this->lastTick = now;
    }

    void Player::onKeyUp(SDL_KeyboardEvent event)
    {
        switch (event.keysym.sym)
        {
            case SDLK_w:
                this->upKeyDown = false;
                break;
            case SDLK_s:
                this->downKeyDown = false;
                break;
            case SDLK_a:
                this->leftKeyDown = false;
                break;
            case SDLK_d:
                this->rightKeyDown = false;
                break;
            default:
                break;
        }
    }

    void Player::onKeyDown(SDL_KeyboardEvent event)
    {
        switch (event.keysym.sym)
        {
            case SDLK_w:
                this->upKeyDown = true;
                break;
            case SDLK_s:
                this->downKeyDown = true;
                break;
            case SDLK_a:
                this->leftKeyDown = true;
                break;
            case SDLK_d:
                this->rightKeyDown = true;
                break;
            default:
                break;
        }
    }

    void Player::onMouseMotion(SDL_MouseMotionEvent event)
    {
        float SENSITIVITY = 0.001;
        this->relativeRotation(Vector3{
            fmodf(this->relativeRotation().x - event.yrel * SENSITIVITY, 2 * M_PI),
            fmodf(this->relativeRotation().y - event.xrel * SENSITIVITY, 2 * M_PI),
            fmodf(this->relativeRotation().z, 2 * M_PI)
            });
    }

    void Player::onMouseDown(SDL_MouseButtonEvent event)
    {

    }

    void Player::onMouseUp(SDL_MouseButtonEvent event)
    {

    }
}