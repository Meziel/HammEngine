#pragma once

#include <glm/glm.hpp>

#include "Vector3.h"

namespace GameEngine
{
	namespace MatrixUtils
	{
		/**
		 * Creates a translation matrix from a vector
		 * 
		 * @param translation Vector of values to translate
		 * @return 4x4 translation matrix
		 */
		glm::mat4 createTranslationMatrix(const Vector3& translation);

		/**
		 * Creates a rotation matrix from a vector
		 *
		 * @param rotation Vector of euler rotations in radians
		 * @return 4x4 rotation matrix
		 */
		glm::mat4 createRotationMatrix(const Vector3& rotation);

		/**
		 * Creates a scale matrix from a vector
		 *
		 * @param scale Vector of scales
		 * @return 4x4 scale matrix
		 */
		glm::mat4 createScaleMatrix(const Vector3& scale);
	}
}