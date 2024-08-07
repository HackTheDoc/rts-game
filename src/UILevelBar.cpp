#include "include/UI/UILevelBar.h"

#include "include/Game/Game.h"
#include "include/Manager.h"

UILevelBar::UILevelBar(const int mlevel, const int clevel, const int bwidth) {
    maxLevel = mlevel;
    setCurrentLevel(clevel);
    barWidth = bwidth;

    levelRect = {0, 0, 0, 16};

    rect = {0, 0, 0, 16};
}

UILevelBar::~UILevelBar() {}

void UILevelBar::update() {
    if (active)
        currentLevel++;

    rect.w = barWidth * Game::camera.zoom;
    rect.h = 16 * Game::camera.zoom;

    levelRect.w = (barWidth * currentLevel / maxLevel) * Game::camera.zoom;
    levelRect.h = rect.h;
}

void UILevelBar::draw() {
    Manager::DrawFilledRect(&rect, hue::blur_white);

    Manager::SetViewport(&rect);

    Manager::DrawFilledRect(&levelRect, hue::blur_green);

    Manager::SetViewport(nullptr);

    Manager::DrawRect(&rect, hue::black);
}

void UILevelBar::setCurrentLevel(const int clevel) {
    currentLevel = clevel;
}

int UILevelBar::getCurrentLevel() {
    return currentLevel;
}

bool UILevelBar::isFinished() {
    return currentLevel >= maxLevel;
}
