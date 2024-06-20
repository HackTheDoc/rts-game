#pragma once

#include "UIElement.h"

class UILevelBar : public UIElement {
public:
    bool active;
    
    UILevelBar(const int mlevel, const int clevel, const int bwidth);
    ~UILevelBar();

    void update() override;
    void draw() override;
    
    void setCurrentLevel(const int clevel);
    int getCurrentLevel();
    bool isFinished();

private:
    int maxLevel, currentLevel, barWidth;
    SDL_Rect levelRect;
};
