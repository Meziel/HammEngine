#include "GameObject.h"

#include "MatrixUtils.h"

namespace GameEngine
{

    GameObject::GameObject() :
        parent(nullptr)
    {
        this->relativePosition(Vector3{ 0.0f, 0.0f, 0.0f });
        this->relativeScale(Vector3{ 1.0f, 1.0f, 1.0f });
        this->relativeRotation(Vector3{ 0.0f, 0.0f, 0.0f });
    }

    // Position getter
    Vector3 GameObject::position()
    {
        return this->position_;
    }

    // Position setter
    void GameObject::position(Vector3& position)
    {
        // Set absolute
        this->position_ = position;

        if (this->parent != nullptr)
        {
            this->relativePosition_ = glm::inverse(MatrixUtils::createTranslationMatrix(this->parent->position())) * position;
        }
        else
        {
            this->relativePosition_ = position;
        }

        // Recompute the rotation of the children game objects
        for (std::shared_ptr<GameObject> gameObject : this->subGameObjects)
        {
            // Trick to recompute child
            gameObject->relativePosition(gameObject->relativePosition());
        }
    }

    // Relative position getter
    Vector3 GameObject::relativePosition()
    {
        return this->relativePosition_;
    }

    // Relative position setter
    void GameObject::relativePosition(Vector3& relativePosition)
    {
        this->relativePosition_ = relativePosition;

        // Update the absolute position
        if (this->parent != nullptr)
        {
            this->position_ = MatrixUtils::createTranslationMatrix(relativePosition) * this->parent->position();
        }
        else
        {
            this->position_ = relativePosition;
        }

        for (std::shared_ptr<GameObject> gameObject : this->subGameObjects)
        {
            // Trick to recompute child
            gameObject->relativePosition(gameObject->relativePosition());
        }
    }

    // Scale getter
    Vector3 GameObject::scale()
    {
        return this->scale_;
    }

    // Scale setter
    void GameObject::scale(Vector3& scale)
    {
        // Set absolute
        this->scale_ = scale;

        if (this->parent != nullptr)
        {
            this->relativeScale_ = glm::inverse(MatrixUtils::createRotationMatrix(this->parent->scale())) * scale;
        }
        else
        {
            this->relativeScale_ = scale;
        }

        // Recompute the rotation of the children game objects
        for (std::shared_ptr<GameObject> gameObject : this->subGameObjects)
        {
            // Trick to recompute child
            gameObject->relativeScale(gameObject->relativeScale());
        }
    }

    // Relative scale getter
    Vector3 GameObject::relativeScale()
    {
        return this->relativeScale_;
    }

    // Relative scale setter
    void GameObject::relativeScale(Vector3& relativeScale)
    {
        this->relativeScale_ = relativeScale;

        // Update the absolute scale
        if (this->parent != nullptr)
        {
            this->scale_ = MatrixUtils::createScaleMatrix(relativeScale) * this->parent->scale();
        }
        else
        {
            this->scale_ = relativeScale;
        }

        for (std::shared_ptr<GameObject> gameObject : this->subGameObjects)
        {
            // Trick to recompute child
            gameObject->relativeScale(gameObject->relativeScale());
        }
    }

    // Rotation getter
    Vector3 GameObject::rotation()
    {
        return this->rotation_;
    }

    // Rotation setter
    void GameObject::rotation(Vector3& rotation)
    {
        // Set absolute
        this->rotation_ = rotation;

        if (this->parent != nullptr)
        {
            this->relativeRotation_ = glm::inverse(MatrixUtils::createRotationMatrix(this->parent->rotation())) * rotation;
        }
        else
        {
            this->relativeRotation_ = rotation;
        }

        // Recompute the rotation of the children game objects
        for (std::shared_ptr<GameObject> gameObject : this->subGameObjects)
        {
            // Trick to recompute child
            gameObject->relativeRotation(gameObject->relativeRotation());
        }
    }

    // Relative rotation getter
    Vector3 GameObject::relativeRotation()
    {
        return this->relativeRotation_;
    }

    // Relative rotation setter
    void GameObject::relativeRotation(Vector3& relativeRotation)
    {
        this->relativeRotation_ = relativeRotation;

        // Update the absolute position
        if (this->parent != nullptr)
        {
            this->rotation_ = MatrixUtils::createRotationMatrix(relativeRotation) * this->parent->rotation();
        }
        else
        {
            this->rotation_ = relativeRotation;
        }

        for (std::shared_ptr<GameObject> gameObject : this->subGameObjects)
        {
            // Trick to recompute child
            gameObject->relativeRotation(gameObject->relativeRotation());
        }
    }

    void GameObject::addGameObject(std::shared_ptr<GameObject> gameObject)
    {
        gameObject->parent = this;
        this->subGameObjects.insert(std::move(gameObject));
    }

    void GameObject::removeGameObject(std::shared_ptr<GameObject> gameObject)
    {
        gameObject->parent = nullptr;
        this->subGameObjects.erase(std::move(gameObject));
    }

    void GameObject::addComponent(std::shared_ptr<Component> component)
    {
        this->componenets.insert(std::move(component));
    }

    void GameObject::removeComponent(std::shared_ptr<Component> component)
    {
        this->componenets.erase(std::move(component));
    }

    bool GameObject::hasComponentOfType(std::string componentTypeGuid)
    {
        for (std::shared_ptr<Component> component : this->componenets)
        {
            if (component->componentTypeGuid == componentTypeGuid)
            {
                return true;
            }
        }
        return false;
    }

    std::shared_ptr<Component> GameObject::getComponentOfType(std::string componentTypeGuid)
    {
        for (std::shared_ptr<Component> component : this->componenets)
        {
            if (component->componentTypeGuid == componentTypeGuid)
            {
                return component;
            }
        }
        return nullptr;
    }

    void GameObject::onTick() { }
}
