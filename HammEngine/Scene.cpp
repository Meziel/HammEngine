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
			GLuint vbos[2];
			GLuint ebo;
			GLint attrib;

			// Tell OpenGL to allocate 1 buffer & array object
			glGenVertexArrays(1, vaos);
			glGenBuffers(2, vbos);
			glGenBuffers(1, &ebo);

			glBindVertexArray(vaos[0]);;

			// Add vertices to buffer object
			glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
			glBufferData(GL_ARRAY_BUFFER, meshComponent->vertices.size() * sizeof(Vector3), (GLfloat*)(&meshComponent->vertices[0]), GL_STATIC_DRAW);
			
			// Add index array in an element buffer object
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshComponent->indices.size() * sizeof(float), (GLfloat*)(&meshComponent->indices[0]), GL_STATIC_DRAW);

			// Specify to opengl how vPosition in vertex shader is to interpret GL_ARRAY_BUFFER data
			attrib = glGetAttribLocation(shaderComponent->getProgram(), "vPosition");
			glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

			// Sets vPosition to use currently bound GL_ARRAY_BUFFER
			glEnableVertexAttribArray(attrib);

			// Add normals to buffer object
			glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
			glBufferData(GL_ARRAY_BUFFER, meshComponent->normals.size() * sizeof(Vector3), (GLfloat*)(&meshComponent->normals[0]), GL_STATIC_DRAW);

			// Specify to opengl how vNormal in vertex shader is to interpret GL_ARRAY_BUFFER data
			attrib = glGetAttribLocation(shaderComponent->getProgram(), "vNormal");
			glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

			// Sets vNormal to use currently bound GL_ARRAY_BUFFER
			glEnableVertexAttribArray(attrib);

			// Set Uniforms
			GLint modelUniform = glGetUniformLocation(shaderComponent->getProgram(), "model");
			GLint viewUniform = glGetUniformLocation(shaderComponent->getProgram(), "view");
			GLint projectionUniform = glGetUniformLocation(shaderComponent->getProgram(), "projection");
			GLint colorUniform = glGetUniformLocation(shaderComponent->getProgram(), "color");
			GLint ambientUniform = glGetUniformLocation(shaderComponent->getProgram(), "ambient");

			// Lighting
			GLint lightWorldPositionUniform = glGetUniformLocation(shaderComponent->getProgram(), "lightWorldPosition");
			GLint lightDiffuseColorUniform = glGetUniformLocation(shaderComponent->getProgram(), "lightDiffuseColor");

			glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(this->createModelMatrix(gameObject.get())));
			glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(this->createViewMatrix(gameObject.get())));
			glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, glm::value_ptr(this->createProjectionMatrix(gameObject.get())));
			glUniform4fv(colorUniform, 1, glm::value_ptr(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
			glUniform3fv(ambientUniform, 1, glm::value_ptr(glm::vec3(0.2f, 0.2f, 0.2f)));

			glUniform3fv(lightWorldPositionUniform, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
			glUniform4fv(lightDiffuseColorUniform, 1, glm::value_ptr(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));

			// Draw triangles
			glDrawElements(GL_TRIANGLES, meshComponent->indices.size(), GL_UNSIGNED_INT, 0);

			glDeleteBuffers(2, vbos);
			glDeleteVertexArrays(1, vaos);
		}

		for (std::shared_ptr<GameObject> gameObject : gameObject->subGameObjects)
		{
			// Making assumption user did not create a cyclical object tree
			this->renderGameObject(gameObject);
		}
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

		return thisGameObjectsModelMatrix;
	}

	glm::mat4 Scene::createViewMatrix(GameObject* gameObject)
	{
		Vector3 cameraAbsolutePosition = this->activeCamera->position();
		glm::vec3 cameraPosition = glm::vec3(cameraAbsolutePosition.x, cameraAbsolutePosition.y, cameraAbsolutePosition.z);
		glm::vec3 cameraForward = glm::vec3(this->activeCamera->forward().x, this->activeCamera->forward().y, this->activeCamera->forward().z);
		glm::vec3 cameraUp = glm::vec3(this->activeCamera->up().x, this->activeCamera->up().y, this->activeCamera->up().z);

		return glm::lookAt(cameraPosition, cameraPosition + cameraForward, cameraUp);
	}

	glm::mat4 Scene::createProjectionMatrix(GameObject* gameObject)
	{
		return glm::perspective(this->activeCamera->fov, this->activeCamera->aspect, this->activeCamera->near, this->activeCamera->far);
	}

}