#pragma once

#include <string>
#include <memory>

#include "common.h"

namespace GameEngine
{
    class Component
    {
    public:
        std::string componentTypeGuid;

        template <class T = Component, typename... Args> inline static std::shared_ptr<T> createComponent(Args... args)
        {
            return std::make_shared<T>(args...);
        }

        GAMEENGINE_API Component(std::string componentTypeGuid);
    };
}