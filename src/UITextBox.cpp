#include "include/UI/UITextBox.h"

#include "include/Manager.h"


UITextBox::UITextBox(const std::string& text, const std::string& font, const SDL_Color& fgcolor, const SDL_Color& bgcolor, const SDL_Color& bdcolor, const int mlength, const bool centered) {
    lbl = new UILabel(text, font, fgcolor, mlength, centered);
    rect.w = lbl->width();
    rect.h = lbl->height();

    background = bgcolor;
    border = bdcolor;
}

UITextBox::~UITextBox() {}

void UITextBox::draw() {
    Manager::DrawFilledRect(&rect, background);
    lbl->draw();
    Manager::DrawRect(&rect, border);
}

void UITextBox::destroy() {
    lbl->destroy();
}

void UITextBox::place(const int x, const int y) {
    lbl->place(
        x + (rect.w - lbl->width()) / 2,
        y + (rect.h - lbl->height()) / 2
    );
    rect.x = x;
    rect.y = y;
}

void UITextBox::setHeight(const int h) {
    rect.h = h;
}

void UITextBox::setWidth(const int w) {
    rect.w = w;
}

SDL_Rect* UITextBox::getRect() {
    return &rect;
}
