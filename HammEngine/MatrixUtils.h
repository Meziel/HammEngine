#pragma once

#include <glm/glm.hpp>

#include "Vector3.h"

namespace GameEngine
{
	namespace MatrixUtils
	{
		glm::mat4 createTranslationMatrix(const Vector3& translation);

		glm::mat4 createRotationMatrix(const Vector3& rotation);

		glm::mat4 createScaleMatrix(const Vector3& scale);
	}
}