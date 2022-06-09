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

        /**
         * Utility method for creating new components
         *
         * @tparam T Component type to create
         * @param args Variable length parameters to pass to the constructor when creating the component of type T
         * @return shared pointer to the newly created component
         */
        template <class T = Component, typename... Args> inline static std::shared_ptr<T> createComponent(Args... args)
        {
            return std::make_shared<T>(args...);
        }

        /**
         * Component constructor
         * 
         * @param componentTypeGuid GUID value that uniquely identifies this component type
         */
        GAMEENGINE_API Component(std::string componentTypeGuid);
    };
}