namespace engine::core {

template<typename Event>
void EventBus::subscribe(Listener<Event> listener) {
    listeners[typeid(Event)].push_back([listener](const void* e) {
        listener(*static_cast<const Event*>(e));
    });
}

template<typename Event>
void EventBus::emit(const Event& event) {
    auto it = listeners.find(typeid(Event));
    if (it == listeners.end()) return;
    for (auto& cb : it->second) cb(&event);
}

} // namespace engine::core
