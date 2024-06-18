#include "include/UI/UI.h"
#include "include/UI/UIElements.h"

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

void UI::show(const std::string& tag) {
    elements[tag]->shown = true;
}

void UI::hide(const std::string& tag) {
    elements[tag]->shown = false;
}

void UI::init() {
    destroy();

    UIRessourceCounter* foodCounter = new UIRessourceCounter("food");
    foodCounter->place(
        8*(Window::fullscreen+1),
        0
    );
    add("food counter", foodCounter);
    
    UIRessourceCounter* goldCounter = new UIRessourceCounter("gold");
    goldCounter->place(
        UIRessourceCounter::WIDTH + 8*(Window::fullscreen+1),
        0
    );
    add("gold counter", goldCounter);

    UIRessourceCounter* woodCounter = new UIRessourceCounter("wood");
    woodCounter->place(
        UIRessourceCounter::WIDTH*2 + 8*(Window::fullscreen+1),
        0
    );
    add("wood counter", woodCounter);

    UIConstructionMenu* constructionMenu = new UIConstructionMenu();
    add("construction menu", constructionMenu);
    hide("construction menu");
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
