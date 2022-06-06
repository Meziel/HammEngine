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
        
        /// Parent game object. If nullptr, the parent is a scene or is not attached to anything
        GameObject* parent;

        /// Hierarchy of child game objects
        std::set<std::shared_ptr<GameObject>> subGameObjects;

        /// Components are things like meshes and shaders attached to this game object
        std::set<std::shared_ptr<Component>> componenets;

        /**
         * Utility method for creating new game objects
         * 
         * @tparam T Game object type to create
         * @param args Variable length parameters to pass to the constructor when creating the game object of type T
         * @return shared pointer to the newly created game object
         */
        template <class T = GameObject, typename... Args> inline static std::shared_ptr<T> createGameObject(Args... args)
        {
            return std::make_shared<T>(args...);
        }

        GAMEENGINE_API GameObject();

        /**
         * Gets the absolute position of the game object in the world
         * 
         * @return absolute position
         */
        GAMEENGINE_API Vector3 position();

        /**
         * Sets the absolute position of the game object in the world
         * 
         * Setting the absolute position recomputes the relative position of the game object
         * and all positions of the child game objects
         * 
         * @param position New absolute position
         */
        GAMEENGINE_API void position(Vector3& position);

        /**
         * Gets the position of the game object relative to its parent
         *
         * @return position relative to the parent game object
         */
        GAMEENGINE_API Vector3 relativePosition();

        /**
         * Sets the position of the game object relative to its parent
         * 
         * Setting the relative position recomputes the absolute position of the game object
         * and all positions of the child game objects
         * 
         * @param relativePosition New position relative to the parent game object
         */
        GAMEENGINE_API void relativePosition(Vector3& relativePosition);

        /**
         * Gets the absolute scale of the game object in the world
         *
         * @return absolute scale
         */
        GAMEENGINE_API Vector3 scale();

        /**
         * Sets the absolute scale of the game object in the world
         *
         * Setting the absolute scale recomputes the relative scale of the game object
         * and all scales of the child game objects
         *
         * @param scale New absolute scale
         */
        GAMEENGINE_API void scale(Vector3& scale);

        /**
         * Gets the scale of the game object relative to its parent
         *
         * @return scale relative to the parent game object
         */
        GAMEENGINE_API Vector3 relativeScale();

        /**
         * Sets the scale of the game object relative to its parent
         *
         * Setting the relative scale recomputes the absolute scale of the game object
         * and all scales of the child game objects
         *
         * @param relativeScale New scale relative to the parent game object
         */
        GAMEENGINE_API void relativeScale(Vector3& relativeScale);

        /**
         * Gets the absolute rotation of the game object in the world
         *
         * @return absolute rotation in radians
         */
        GAMEENGINE_API Vector3 rotation();

        /**
         * Sets the absolute rotation of the game object in the world
         *
         * Setting the absolute rotation recomputes the relative rotation of the game object
         * and all rotations of the child game objects
         *
         * @param rotation New absolute rotation
         */
        GAMEENGINE_API void rotation(Vector3& rotation);

        /**
         * Gets the rotation of the game object relative to its parent
         *
         * @return rotation relative to the parent game object
         */
        GAMEENGINE_API Vector3 relativeRotation();

        /**
         * Sets the rotation of the game object relative to its parent
         *
         * Setting the relative rotation recomputes the absolute rotation of the game object
         * and all rotations of the child game objects
         *
         * @param relativeRotation New rotation relative to the parent game object
         */
        GAMEENGINE_API void relativeRotation(Vector3& relativeRotation);

        /**
         * Adds a game object as a child to this game object 
         * 
         * @param gameObject Child game object to add
         */
        GAMEENGINE_API void addGameObject(std::shared_ptr<GameObject> gameObject);

        /**
         * Removes a game object as a child from this game object
         *
         * @param gameObject Child game object to remove
         */
        GAMEENGINE_API void removeGameObject(std::shared_ptr<GameObject> gameObject);

        /**
         * Adds a component to this game object
         *
         * @param component Child component to add
         */
        GAMEENGINE_API void addComponent(std::shared_ptr<Component> component);

        /**
         * Removes a component from this game object
         *
         * @param component Child component to remove
         */
        GAMEENGINE_API void removeComponent(std::shared_ptr<Component> component);

        /**
         * Checks if the game obejct has a component of a certain type
         * 
         * In order to type check, this function uses guids to identify components types.
         * When component objects are made they have guid which identifies them
         * 
         * @param componentTypeGuid Globally unique identifier for the component type to check
         * @return Boolean whether or not the game object has a component of the guid type
         */
        GAMEENGINE_API bool hasComponentOfType(std::string componentTypeGuid);

        /**
         * Gets a component from the game object of a certain type
         *
         * This function gets the first instance of a component inside the game object that has a 
         * guid that matches the specified. If not such component exists, this method return a nullptr
         *
         * @param componentTypeGuid Globally unique identifier for the component type to get
         * @return Component if one exists of that type the game object; otherwise nullptr
         */
        GAMEENGINE_API std::shared_ptr<Component> getComponentOfType(std::string componentTypeGuid);

        /**
         * Executes logic for this game object for 1 tick
         *
         * Time between ticks varies
         */
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