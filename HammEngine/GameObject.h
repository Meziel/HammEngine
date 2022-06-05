#pragma once

#include <memory>
#include <set>

#include "common.h"
#include "Component.h"
#include "Vector3.h"

namespace GameEngine
{
    class GameObject
    {
    public:
        
        GameObject* parent;
        std::set<std::shared_ptr<GameObject>> subGameObjects;
        std::set<std::shared_ptr<Component>> componenets;

        template <class T = GameObject, typename... Args> inline static std::shared_ptr<T> createGameObject(Args... args)
        {
            return std::make_shared<T>(args...);
        }

        GAMEENGINE_API GameObject();

        // Position getter
        GAMEENGINE_API Vector3 position();

        // Position setter
        GAMEENGINE_API void position(Vector3&);

        // Relative position getter
        GAMEENGINE_API Vector3 relativePosition();

        // Relative position setter
        GAMEENGINE_API void relativePosition(Vector3&);

        // Scale getter
        GAMEENGINE_API Vector3 scale();

        // Scale setter
        GAMEENGINE_API void scale(Vector3&);

        // Relative scale getter
        GAMEENGINE_API Vector3 relativeScale();

        // Relative scale setter
        GAMEENGINE_API void relativeScale(Vector3&);

        // Rotation getter
        GAMEENGINE_API Vector3 rotation();

        // Rotation setter
        GAMEENGINE_API void rotation(Vector3&);

        // Relative rotation getter
        GAMEENGINE_API Vector3 relativeRotation();

        // Relative rotation getter
        GAMEENGINE_API void relativeRotation(Vector3&);

        // Child Game Objects
        GAMEENGINE_API void addGameObject(std::shared_ptr<GameObject> gameObject);
        GAMEENGINE_API void removeGameObject(std::shared_ptr<GameObject> gameObject);

        // Components
        GAMEENGINE_API void addComponent(std::shared_ptr<Component> component);
        GAMEENGINE_API void removeComponent(std::shared_ptr<Component> component);

        // Utility methods
        GAMEENGINE_API bool hasComponentOfType(std::string componentTypeGuid);
        GAMEENGINE_API std::shared_ptr<Component> getComponentOfType(std::string componentTypeGuid);

        // Tick methods
        GAMEENGINE_API virtual void onTick();
   
    private:
        Vector3 position_;
        Vector3 relativePosition_;
        Vector3 scale_;
        Vector3 relativeScale_;
        Vector3 rotation_;
        Vector3 relativeRotation_;
    };
}