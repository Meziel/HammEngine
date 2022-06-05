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
		std::set<std::shared_ptr<GameObject>> gameObjects;
		std::shared_ptr<Camera> activeCamera;

		static GAMEENGINE_API std::shared_ptr<Scene> createScene();

		GAMEENGINE_API Scene();
		GAMEENGINE_API void addGameObject(std::shared_ptr<GameObject> gameObject);
		GAMEENGINE_API void removeGameObject(std::shared_ptr<GameObject> gameObject);

		void draw();
	
	protected:
		void executeGameObjectTick(std::shared_ptr<GameObject> gameObject);
		void renderGameObject(std::shared_ptr<GameObject> gameObject);

	private:
		glm::mat4 createMVP(GameObject* gameObject);
		glm::mat4 createModelMatrix(GameObject* gameObject, bool multiplyTranslation = true, bool multiplyScale = true, bool multiplyRotation = true);
	};
}