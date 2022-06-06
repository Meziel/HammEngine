#pragma once

#include <memory>
#include <set>
#include <glm/glm.hpp>

#include "common.h"
#include "Vector3.h"
#include "GameObject.h"
#include "GameObjects/Camera.h"

namespace GameEngine
{
	class Scene
	{
	public:
		/// Hierarchy of game objects in the scene
		std::set<std::shared_ptr<GameObject>> gameObjects;

		/// Camera that is used for view out of. Must be set for game objects to get rendered.
		std::shared_ptr<Camera> activeCamera;

		/**
		 * Creates a scene
		 *
		 * Utility method for creating a new scene.
		 * 
		 * @return shared pointer to a newly created scene
		 **/
		static GAMEENGINE_API std::shared_ptr<Scene> createScene();

		/**
		 * Scene constructor 
		 */
		GAMEENGINE_API Scene();

		/**
		 * Adds a game object to the scene
		 *
		 * @param gameObject Game object to add to the scene
		 */
		GAMEENGINE_API void addGameObject(std::shared_ptr<GameObject> gameObject);

		/**
		 * Adds a game object to the scene
		 * 
		 * @param GameObject Game object to remove from the scene
		 */
		GAMEENGINE_API void removeGameObject(std::shared_ptr<GameObject> gameObject);

		/**
		 * Draws the game objects attached to the scene
		 * 
		 * Calling draw iterates through all game objects. Objects are called in preorder depth first.
		 * All game objects will have their init() functions and any meshe components attached to the game object will be drawn to the scene as long
		 * as the game object also has a shader component and the active camera is set for the scene. 
		 */
		void draw();
	
	protected:
		void executeGameObjectTick(std::shared_ptr<GameObject> gameObject);
		void renderGameObject(std::shared_ptr<GameObject> gameObject);

	private:
		glm::mat4 createModelMatrix(GameObject* gameObject, bool multiplyTranslation = true, bool multiplyScale = true, bool multiplyRotation = true);
		glm::mat4 createViewMatrix(GameObject* gameObject);
		glm::mat4 createProjectionMatrix(GameObject* gameObject);
	};
}