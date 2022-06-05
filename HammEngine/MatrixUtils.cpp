#include "MatrixUtils.h"

#include <glm/gtc/matrix_transform.hpp>

namespace GameEngine
{
	namespace MatrixUtils
	{
		glm::mat4 createTranslationMatrix(const Vector3& translation)
		{
			return glm::translate(glm::mat4(1.0f), glm::vec3(translation.x, translation.y, translation.z));
		}

		glm::mat4 createRotationMatrix(const Vector3& rotation)
		{
			glm::mat4 identity = glm::mat4(1.0f);
			glm::mat4 rotationMatrixX = glm::mat4(1.0f);
			glm::mat4 rotationMatrixY = glm::mat4(1.0f);
			glm::mat4 rotationMatrixZ = glm::mat4(1.0f);
			rotationMatrixX = glm::rotate(identity, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			rotationMatrixY = glm::rotate(identity, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			rotationMatrixZ = glm::rotate(identity, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
			return  rotationMatrixY * rotationMatrixZ * rotationMatrixX;
		}

		glm::mat4 createScaleMatrix(const Vector3& scale)
		{
			glm::mat4 scaleMatrix = glm::mat4(1.0f);
			return glm::scale(scaleMatrix, glm::vec3(scale.x, scale.y, scale.z));
		}
	}
}