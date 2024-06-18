#include "include/UI/UIIconButton.h"

#include "include/Window.h"

UIIconButton::UIIconButton(const Event::ID eid, const std::string& iname, const int sz) {
    setID(eid);

    texture = Window::manager->getTexture(iname);
    
    srcRect = rect = { 0, 0, sz, sz };

    place(0,0);
}

UIIconButton::~UIIconButton() {}

void UIIconButton::draw() {
    Manager::DrawFilledRect(&rect, hue::card_background);
    Manager::Draw(texture, &srcRect, &rect);
    Manager::DrawRect(&rect, hue::card_border);
}

void UIIconButton::destroy() {
    texture = nullptr;
}

void UIIconButton::place(const int x, const int y) {
    rect.x = x;
    rect.y = y;
}

void UIIconButton::resize(const int sz) {
    rect.w = rect.h = sz;
}

void UIIconButton::setSourceX(const int x) {
    srcRect.x = x;
}