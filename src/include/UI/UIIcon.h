#pragma once

#include <string>

#include "UIElement.h"

class UIIcon : public UIElement {
public:
    UIIcon();
    UIIcon(const std::string& iname, const int sz);
    ~UIIcon();

    void draw() override;
    void destroy() override;

    void resize(const int sz);

    void setSourceX(const int x);

protected:
    SDL_Texture* texture;
    SDL_Rect srcRect;
};
