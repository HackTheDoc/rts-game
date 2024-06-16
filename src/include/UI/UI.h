#pragma once

#include <map>
#include <queue>
#include <string>

#include "UIElement.h"

class UI {
private:
    std::map<std::string, UIElement*> elements;

public:
    UI();
    ~UI();

    void add(const std::string& tag, UIElement* element);
    void remove(const std::string& tag);

    void init();
    void update();
    void display();
    void destroy();
};
