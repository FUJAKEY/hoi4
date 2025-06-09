#pragma once

#include <unordered_map>
#include <typeindex>
#include <vector>
#include <memory>
#include <span>

namespace engine::core {

using Entity = std::uint32_t;

class ComponentStorageBase {
public:
    virtual ~ComponentStorageBase() = default;
};

template<typename T>
class ComponentStorage : public ComponentStorageBase {
public:
    std::unordered_map<Entity, T> components;
};

class ECS {
public:
    Entity createEntity();

    template<typename T>
    void addComponent(Entity e, T component);

    template<typename T>
    T* getComponent(Entity e);

private:
    Entity nextEntity{1};
    std::unordered_map<std::type_index, std::unique_ptr<ComponentStorageBase>> stores;
};

} // namespace engine::core

#include "ECS.inl"
