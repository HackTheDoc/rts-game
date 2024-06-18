#pragma once

#include "UIElement.h"
#include "UIIconButton.h"

class UIConstructionMenu : public UIElement {
public:
    UIConstructionMenu();
    ~UIConstructionMenu();

    void draw() override;
    void update() override;
    void destroy() override;

private:
    UIIconButton* btn_house;
    UIIconButton* btn_tower;
    UIIconButton* btn_castle;
};
