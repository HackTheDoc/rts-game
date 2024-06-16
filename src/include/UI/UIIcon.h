#pragma once

#include <string>

#include "UIElement.h"

class UIIcon : public UIElement {
public:
    UIIcon(const std::string& iname);
    ~UIIcon();

    void draw() override;
    void destroy() override;

    void resize(const int sz);

private:
    SDL_Texture* texture;
};
