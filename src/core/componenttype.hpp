#pragma once

#include <array>

using ComponentTypeId = std::size_t;

inline ComponentTypeId getComponentTypeId()
{
    static ComponentTypeId lastId = 0;
    return lastId++;
}

template <typename T>
inline ComponentTypeId getComponentTypeId() noexcept
{
    static ComponentTypeId typeId = getComponentTypeId();
    return typeId;
}
