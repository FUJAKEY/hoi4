#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>

namespace engine::core {

class EventBus {
public:
    template<typename Event>
    using Listener = std::function<void(const Event&)>;

    template<typename Event>
    void subscribe(Listener<Event> listener);

    template<typename Event>
    void emit(const Event& event);

private:
    std::unordered_map<std::type_index, std::vector<std::function<void(const void*)>>> listeners;
};

} // namespace engine::core

#include "EventBus.inl"
