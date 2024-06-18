#pragma once

#include "UIElement.h"

class UILevelBar : public UIElement {
public:
    UILevelBar(const int mlevel, const int clevel = 0);
    ~UILevelBar();

    void update() override;
    void draw() override;
    
    int getCurrentLevel();
    bool isFinished();

private:
    int maxLevel, currentLevel;
    SDL_Rect levelRect;
};
