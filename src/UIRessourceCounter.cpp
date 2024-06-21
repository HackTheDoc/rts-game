#include "include/UI/UIRessourceCounter.h"

#include "include/Window.h"
#include "include/Game/Game.h"

UIRessourceCounter::UIRessourceCounter(const std::string& r) {
    lbl = new UILabel();
    ico = new UIIcon("ressources icons", 64);

    if (r == "food") {
        ico->setSourceX(0);
        ressource = &Game::playerFaction.food;
    }
    else if (r == "wood") {
        ico->setSourceX(128);
        ressource = &Game::playerFaction.wood;
    }
    else {
        ico->setSourceX(64);
        ressource = &Game::playerFaction.gold;
    }

    ico->resize(64*(Window::fullscreen+1));
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
