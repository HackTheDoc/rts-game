#include "include/UI/UIRessourceCounter.h"

#include "include/Window.h"
#include "include/Game/Game.h"

UIRessourceCounter::UIRessourceCounter(const std::string& r) {
    lbl = new UILabel();
    ico = new UIIcon(r);

    if (r == "food")
        ressource = &Game::playerFaction.food;
    else if (r == "wood")
        ressource = &Game::playerFaction.wood;
    else
        ressource = &Game::playerFaction.gold;
}

UIRessourceCounter::~UIRessourceCounter() {}

void UIRessourceCounter::draw() {
    lbl->draw();
    ico->draw();
}

void UIRessourceCounter::update() {
    lbl->setText(std::to_string(*ressource), "default", hue::font);
}

void UIRessourceCounter::destroy() {
    lbl->destroy();
    ico->destroy();
}

void UIRessourceCounter::place(const int x, const int y) {
    ico->place(x, y);
    lbl->place(
        x + ico->width() + 8*(Window::fullscreen+1),
        y + (ico->height() - lbl->height()) / 2
    );
}
