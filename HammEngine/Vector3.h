#pragma once

#include <glm/glm.hpp>
#include <iostream>

namespace GameEngine
{
    struct Vector3
    {
        float x;
        float y;
        float z;

        // Operator overrides to allows operations with different datatypes

        /**
         * Scalar multiplication 
         */
        Vector3 operator *(const float& multiplier) const
        {
            return { this->x * multiplier, this->y * multiplier, this->z * multiplier };
        }

        /**
         * Cross product with another vector
         */
        Vector3 operator *(const Vector3& other) const
        {
            glm::vec3 a = glm::vec3(this->x, this->y, this->z);
            glm::vec3 b = glm::vec3(other.x, other.y, other.z);
            glm::vec3 cross = glm::cross(a, b);
            return { cross.x, cross.y, cross.z };
        }

        /**
         * Cross product reassignment with another vector
         */
        Vector3& operator*=(const Vector3& other)
        {
            glm::vec3 a = glm::vec3(this->x, this->y, this->z);
            glm::vec3 b = glm::vec3(other.x, other.y, other.z);
            glm::vec3 cross = glm::cross(a, b);
            this->x = cross.x;
            this->y = cross.y;
            this->z = cross.z;
            return *this;
        }

        /**
         * Vector addition
         */
        Vector3 operator+(const Vector3& other) const
        {
            return { this->x + other.x, this->y + other.y, this->z + other.z };
        }

        /**
         * Vector addition reassignment
         */
        Vector3& operator+=(const Vector3& other)
        {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            return *this;
        }

        /**
         * Scalar multitiplication with negative 1
         */
        Vector3 operator-() const
        {
            return *this * -1;
        }

        /**
         * Vector subtraction
         */
        Vector3 operator-(const Vector3& other) const
        {
            return *this - other;
        }

        /**
         * Vector subtraction reassignment
         */
        Vector3& operator-=(const Vector3& other)
        {
            *this += -other;
            return *this;
        }
    };

    /**
     * Output stream override
     */
    inline std::ostream& operator<<(std::ostream& os, const Vector3& vector3)
    {
        os << "(x=" << vector3.x << "," << "y=" << vector3.y << "," << "z=" << vector3.z << ")";
        return os;
    }

    /**
     * Affine transformation override with glm mat4
     */
    inline Vector3& operator*(glm::mat4 mat, const Vector3& vector3)
    {
        glm::vec4 result = mat * glm::vec4(vector3.x, vector3.y, vector3.z, 1.0f);
        return Vector3{ result.x, result.y, result.z };
    }
}