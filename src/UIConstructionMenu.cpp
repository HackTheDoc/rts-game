#include "include/UI/UIConstructionMenu.h"

#include "include/Window.h"

UIConstructionMenu::UIConstructionMenu() {
    btn_house = new UIIconButton(Event::ID::SELECT_HOUSE_SCHEMATIC, "building icons", 64);
    btn_tower = new UIIconButton(Event::ID::SELECT_TOWER_SCHEMATIC, "building icons", 64);
    btn_castle = new UIIconButton(Event::ID::SELECT_CASTLE_SCHEMATIC, "building icons", 64);

    rect.h = 192 + 16*(Window::fullscreen+1);
    rect.w = 64 + 8*(Window::fullscreen+1);

    rect.x = 4*(Window::fullscreen+1);
    rect.y = (Window::screen.h - rect.h) / 2;

    btn_house->place(
        rect.x + (rect.w - btn_house->width()) / 2,
        rect.y + 4*(Window::fullscreen+1)
    );
    
    btn_tower->place(
        rect.x + (rect.w - btn_tower->width()) / 2,
        btn_house->y() + btn_house->height() + 4*(Window::fullscreen+1)
    );
    
    btn_castle->place(
        rect.x + (rect.w - btn_castle->width()) / 2,
        btn_tower->y() + btn_tower->height() + 4*(Window::fullscreen+1)
    );
}

UIConstructionMenu::~UIConstructionMenu() {}

void UIConstructionMenu::draw() {
    if (!shown) return;
    
    Manager::DrawFilledRect(&rect, hue::blur);

    btn_house->draw();
    btn_tower->draw();
    btn_castle->draw();

    Manager::DrawRect(&rect, hue::border);
}

void UIConstructionMenu::update() {
    if (!shown) return;

    btn_house->update();
    btn_tower->update();
    btn_castle->update();
}

void UIConstructionMenu::destroy() {
    btn_house->destroy();
    btn_tower->destroy();
    btn_castle->destroy();
}
