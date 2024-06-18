#include "include/UI/UILevelBar.h"

#include "include/Game/Game.h"
#include "include/Manager.h"

UILevelBar::UILevelBar(const int mlevel, const int clevel) {
    maxLevel = mlevel;
    currentLevel = clevel;

    levelRect = {0, 0, currentLevel, 0};

    rect = {0, 0, maxLevel, 16};
}

UILevelBar::~UILevelBar() {}

void UILevelBar::update() {
    currentLevel++;

    rect.w = maxLevel * Game::camera.zoom;
    rect.h = 16 * Game::camera.zoom;

    levelRect.w = currentLevel * Game::camera.zoom;
    levelRect.h = rect.h;
}

void UILevelBar::draw() {
    Manager::DrawFilledRect(&rect, hue::blur_white);

    Manager::SetViewport(&rect);

    Manager::DrawFilledRect(&levelRect, hue::green);

    Manager::SetViewport(nullptr);

    Manager::DrawRect(&rect, hue::black);
}

int UILevelBar::getCurrentLevel() {
    return currentLevel;
}

bool UILevelBar::isFinished() {
    return currentLevel >= maxLevel;
}
