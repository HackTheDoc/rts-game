#include "include/UI/UIIcon.h"

#include "include/Manager.h"

#include <iostream>
UIIcon::UIIcon(const std::string& iname) {
    std::cout << iname << std::endl;
    texture = Manager::LoadTexture(("assets/ressources/"+iname+".png").c_str());
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    place(0,0);
}

UIIcon::~UIIcon() {}

void UIIcon::draw() {
    Manager::Draw(texture, nullptr, &rect);
}

void UIIcon::destroy() {
    texture = nullptr;
}


void UIIcon::resize(const int sz) {
    rect.w = rect.h = sz;
}
