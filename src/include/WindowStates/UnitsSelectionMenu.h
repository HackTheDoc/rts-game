#pragma once

#include "WindowState.h"

#include "../UI/UIElements.h"

class UnitsSelectionMenu : public WindowState {
public:
    static int avalaible;
    static UIUnitSelector* pawnSelector;
    static UIUnitSelector* warriorSelector;
    static UIUnitSelector* archerSelector;

    UnitsSelectionMenu();
    ~UnitsSelectionMenu();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;

private:
    UILabel* lbl;
    UIButton* btn_valid;
};
