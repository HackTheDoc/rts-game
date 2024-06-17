#include "include/WindowStates/StartingUnitSelectionMenu.h"

#include "include/Window.h"

int StartingUnitSelectionMenu::avalaible = 4;

UIUnitSelector* StartingUnitSelectionMenu::pawnSelector = nullptr;
UIUnitSelector* StartingUnitSelectionMenu::warriorSelector = nullptr;
UIUnitSelector* StartingUnitSelectionMenu::archerSelector = nullptr;

StartingUnitSelectionMenu::StartingUnitSelectionMenu() {}

StartingUnitSelectionMenu::~StartingUnitSelectionMenu() {}

void StartingUnitSelectionMenu::init() {
    avalaible = 4;

    warriorSelector = new UIUnitSelector(Entity::Type::WARRIOR, &avalaible);
    warriorSelector->place(
        (Window::screen.w - warriorSelector->width()) / 2,
        (Window::screen.h - warriorSelector->height()) / 2
    );

    pawnSelector = new UIUnitSelector(Entity::Type::PAWN, &avalaible);
    pawnSelector->place(
        (warriorSelector->x() - pawnSelector->width()) / 2,
        (Window::screen.h - pawnSelector->height()) / 2
    );

    archerSelector = new UIUnitSelector(Entity::Type::ARCHER, &avalaible);
    archerSelector->place(
        (Window::screen.w + warriorSelector->x() + warriorSelector->width() - archerSelector->width()) / 2,
        (Window::screen.h - archerSelector->height()) / 2
    );


    btn_valid = new UIButton("VALID", Event::ID::VALID_STARTING_UNIT_SELECTION, "h3", hue::font, UIButton::Type::DOUBLE_CURSOR);
    btn_valid->place(
        (Window::screen.w - btn_valid->width()) / 2,
        (Window::screen.h + warriorSelector->y() + warriorSelector->height() - btn_valid->height()) / 2
    );
}

void StartingUnitSelectionMenu::update() {
    pawnSelector->update();
    warriorSelector->update();
    archerSelector->update();
    btn_valid->update();
}

void StartingUnitSelectionMenu::render() {
    Manager::DrawFilledRect(&Window::screen, hue::blur);
    
    pawnSelector->draw();
    warriorSelector->draw();
    archerSelector->draw();
    btn_valid->draw();
}

void StartingUnitSelectionMenu::clean() {
    avalaible = 0;
    
    pawnSelector->destroy();
    pawnSelector = nullptr;

    warriorSelector->destroy();
    warriorSelector = nullptr;

    archerSelector->destroy();
    archerSelector = nullptr;

    btn_valid->destroy();
}
