#include "Component.h"

namespace GameEngine
{
    Component::Component(std::string componentTypeGuid)
    {
        this->componentTypeGuid = componentTypeGuid;
    }
}