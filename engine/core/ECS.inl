namespace engine::core {

inline Entity ECS::createEntity() {
    return nextEntity++;
}

template<typename T>
void ECS::addComponent(Entity e, T component) {
    auto& store = stores[typeid(T)];
    if (!store) store = std::make_unique<ComponentStorage<T>>();
    static_cast<ComponentStorage<T>*>(store.get())->components[e] = std::move(component);
}

template<typename T>
T* ECS::getComponent(Entity e) {
    auto it = stores.find(typeid(T));
    if (it == stores.end()) return nullptr;
    auto* store = static_cast<ComponentStorage<T>*>(it->second.get());
    auto c = store->components.find(e);
    if (c == store->components.end()) return nullptr;
    return &c->second;
}

} // namespace engine::core
