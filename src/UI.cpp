#include "include/UI/UI.h"

#include "include/Window.h"

UI::UI() {}

UI::~UI() {
    elements.clear();
}

void UI::add(const std::string& tag, UIElement* element) {
    elements.emplace(tag, element);
}

void UI::remove(const std::string& tag) {
    elements.erase(tag);
}

void UI::init() {
    destroy();
}

void UI::update() {
    for (auto e : elements)
        e.second->update();
}

void UI::display() {
    for (auto e : elements)
        e.second->draw();
}

void UI::destroy() {
    for (auto e : elements)
        e.second->destroy();
    elements.clear();
}
