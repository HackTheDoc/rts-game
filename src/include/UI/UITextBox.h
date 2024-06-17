#pragma once

#include "UILabel.h"

class UITextBox : public UIElement {
public:
    UITextBox(const std::string& text, const std::string& font, const SDL_Color& fgcolor, const SDL_Color& bgcolor, const SDL_Color& bdcolor, const int mlength = -1, const bool centered = false);
    ~UITextBox();

    void draw() override;
    void destroy() override;

    void place(const int x, const int y);

    void setHeight(const int h);
    void setWidth(const int w);

    SDL_Rect* getRect();

private:
    UILabel* lbl;
    SDL_Color background, border;
};
