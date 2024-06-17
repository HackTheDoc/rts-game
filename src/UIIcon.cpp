#include "include/UI/UIIcon.h"

#include "include/Window.h"

UIIcon::UIIcon() {
    texture = nullptr;
    srcRect = rect = {0,0,0,0};
}

UIIcon::UIIcon(const std::string& iname, const int sz) {
    texture = Window::manager->getTexture(iname);
    
    srcRect = rect = { 0, 0, sz, sz };

    place(0,0);
}

UIIcon::~UIIcon() {}

void UIIcon::draw() {
    Manager::Draw(texture, &srcRect, &rect);
}

void UIIcon::destroy() {
    texture = nullptr;
}

void UIIcon::resize(const int sz) {
    rect.w = rect.h = sz;
}

void UIIcon::setSourceX(const int x) {
    srcRect.x = x;
}
