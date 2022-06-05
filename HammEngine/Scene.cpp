#include "Scene.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "ComponentTypes.h"
#include "Components/ShaderProgram.h"
#include "Components/Mesh.h"
#include "MatrixUtils.h"

namespace GameEngine
{

	std::shared_ptr<Scene> Scene::createScene()
	{
		return std::make_shared<Scene>();
	}

	Scene::Scene()
	{
	}
	
	void Scene::addGameObject(std::shared_ptr<GameObject> gameObject)
	{
		this->gameObjects.insert(std::move(gameObject));
	}

	void Scene::removeGameObject(std::shared_ptr<GameObject> gameObject)
	{
		this->gameObjects.erase(std::move(gameObject));
	}

	void Scene::draw()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// If there is active camera, there is nothing to render
		if (this->activeCamera == nullptr)
		{
			return;
		}

		for (std::shared_ptr gameObject : this->gameObjects)
		{
			executeGameObjectTick(gameObject);
		}

		for (std::shared_ptr gameObject : this->gameObjects)
		{
			renderGameObject(gameObject);
		}
	}

	void Scene::executeGameObjectTick(std::shared_ptr<GameObject> gameObject)
	{
		gameObject->onTick();

		for (std::shared_ptr<GameObject> gameObject : gameObject->subGameObjects)
		{
			// Making assumption user did not create a cyclical object tree
			this->executeGameObjectTick(gameObject);
		}
	}

	void Scene::renderGameObject(std::shared_ptr<GameObject> gameObject)
	{
		ShaderProgram* shaderComponent = static_cast<ShaderProgram*>(gameObject->getComponentOfType(ComponentTypes::SHADER_PROGRAM).get());
		Mesh* meshComponent = static_cast<Mesh*>(gameObject->getComponentOfType(ComponentTypes::MESH).get());

		if (shaderComponent != nullptr && meshComponent != nullptr && meshComponent->vertices.size() > 0)
		{
			// Sets the shader to use for this object
			shaderComponent->use();

			// Put vertices in a vertex buffer object
			GLuint vaos[1];
			GLuint vbos[1];
			GLint attrib;

			// Tell OpenGL to allocate 1 buffer & array object
			glGenVertexArrays(1, vaos);
			glGenBuffers(1, vbos);

			glBindVertexArray(vaos[0]);;

			// Bind to index 0 of the buffer object. Subsequent buffer functions will use this index
			glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);

			// Add vertices to buffer object
			glBufferData(GL_ARRAY_BUFFER, meshComponent->vertices.size() * sizeof(Vector3), (GLfloat*)(&meshComponent->vertices[0]), GL_STATIC_DRAW);

			// Specify to opengl how vPosition in vertex shader is to interpret GL_ARRAY_BUFFER data
			attrib = glGetAttribLocation(shaderComponent->getProgram(), "vPosition");
			glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

			// Sets vPosition to use currently bound GL_ARRAY_BUFFER
			glEnableVertexAttribArray(attrib);

			// Set MVP
			GLint mvpUniform;
			mvpUniform = glGetUniformLocation(shaderComponent->getProgram(), "mvp");
			glm::mat4 mvp = this->createMVP(gameObject.get());
			glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, glm::value_ptr(mvp));

			// Draw triangles
			glDrawArrays(GL_TRIANGLES, 0, meshComponent->vertices.size());

			glDeleteBuffers(1, vbos);
			glDeleteVertexArrays(1, vaos);
		}

		for (std::shared_ptr<GameObject> gameObject : gameObject->subGameObjects)
		{
			// Making assumption user did not create a cyclical object tree
			this->renderGameObject(gameObject);
		}
	}

	glm::mat4 Scene::createMVP(GameObject* gameObject)
	{
		glm::mat4 modelMatrix = this->createModelMatrix(gameObject);

		// Get camera absolute position, forward, and up. Camera can be child of object which can change what is in the camera object
		Vector3 cameraAbsolutePosition = this->activeCamera->position();
		glm::vec3 cameraPosition = glm::vec3(cameraAbsolutePosition.x, cameraAbsolutePosition.y, cameraAbsolutePosition.z);
		glm::vec3 cameraForward = glm::vec3(this->activeCamera->forward().x, this->activeCamera->forward().y, this->activeCamera->forward().z);
		glm::vec3 cameraUp = glm::vec3(this->activeCamera->up().x, this->activeCamera->up().y, this->activeCamera->up().z);

		// Create view matrix
		glm::mat4 viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraForward, cameraUp);

		// Create projection matrix
		glm::mat4 projectionMatrix = glm::perspective(this->activeCamera->fov, this->activeCamera->aspect, this->activeCamera->near, this->activeCamera->far);

		return projectionMatrix * viewMatrix * modelMatrix;
	}

	glm::mat4 Scene::createModelMatrix(GameObject* gameObject, bool multiplyTranslation, bool multiplyScale, bool multiplyRotation)
	{
		glm::mat4 thisGameObjectsModelMatrix = glm::mat4(1.0f);

		if (multiplyTranslation)
		{
			thisGameObjectsModelMatrix *= MatrixUtils::createTranslationMatrix(gameObject->position());
		}

		if (multiplyRotation)
		{
			thisGameObjectsModelMatrix *= MatrixUtils::createRotationMatrix(gameObject->rotation());
		}

		if (multiplyScale)
		{
			thisGameObjectsModelMatrix *= MatrixUtils::createScaleMatrix(gameObject->scale());
		}

		if (gameObject->parent == nullptr)
		{
			return thisGameObjectsModelMatrix;
		}

		// Multiply the model matrix of this game object with it's parent's model matrix
		//return this->createModelMatrix(gameObject->parent, multiplyTranslation, multiplyScale, multiplyRotation) * thisGameObjectsModelMatrix;
		return thisGameObjectsModelMatrix;
	}


}