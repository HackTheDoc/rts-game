#include "include/WindowStates/UnitsSelectionMenu.h"

#include "include/Game/Cursor.h"
#include "include/Window.h"

int UnitsSelectionMenu::avalaible = 4;

UIUnitSelector* UnitsSelectionMenu::pawnSelector = nullptr;
UIUnitSelector* UnitsSelectionMenu::warriorSelector = nullptr;
UIUnitSelector* UnitsSelectionMenu::archerSelector = nullptr;

UnitsSelectionMenu::UnitsSelectionMenu() {}

UnitsSelectionMenu::~UnitsSelectionMenu() {}

void UnitsSelectionMenu::init() {
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

    lbl = new UILabel();

    btn_valid = new UIButton("VALID", Event::ID::VALID_UNITS_SELECTION, "h3", hue::font, UIButton::Type::DOUBLE_CURSOR);
    btn_valid->place(
        (Window::screen.w - btn_valid->width()) / 2,
        (Window::screen.h + warriorSelector->y() + warriorSelector->height() - btn_valid->height()) / 2
    );

    Cursor::enable = false;
}

void UnitsSelectionMenu::update() {
    pawnSelector->update();
    warriorSelector->update();
    
    /// TODO: reactivate when archers will be implemented
    //archerSelector->update();

    lbl->setText("Available: "+std::to_string(avalaible), "h2", hue::font);
    lbl->place(
        (Window::screen.w - lbl->width()) / 2,
        (pawnSelector->y() - lbl->height()) / 2
    );

    btn_valid->update();
}

void UnitsSelectionMenu::render() {
    Manager::DrawFilledRect(&Window::screen, hue::blur);
    
    pawnSelector->draw();
    warriorSelector->draw();
    archerSelector->draw();
    lbl->draw();
    btn_valid->draw();
}

void UnitsSelectionMenu::clean() {
    avalaible = 0;
    
    pawnSelector->destroy();
    pawnSelector = nullptr;

    warriorSelector->destroy();
    warriorSelector = nullptr;

    archerSelector->destroy();
    archerSelector = nullptr;

    lbl->destroy();

    btn_valid->destroy();

    Cursor::enable = true;
}
