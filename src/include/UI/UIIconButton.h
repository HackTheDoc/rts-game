#pragma once

#include "UIButton.h"

class UIIconButton : public UIButton {
public:
    UIIconButton(const Event::ID eid, const std::string& iname, const int sz);
    ~UIIconButton();

    void draw() override;
    void destroy() override;

    void resize(const int sz);

    void setSourceX(const int x);

    void place(const int x, const int y);

private:
    SDL_Rect srcRect;
};
