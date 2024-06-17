#include "include/UI/UIUnitSelector.h"

#include "include/Window.h"

UIUnitSelector::UIUnitSelector(const Entity::Type etype, int* available) {
    count = 0;
    this->available = available;

    ico = new UIIcon("unit icons", 192);
    ico->resize(128);

    switch (etype) {
    case Entity::Type::PAWN:
        ico->setSourceX(192);
        break;
    case Entity::Type::WARRIOR:
        ico->setSourceX(0);
        break;
    case Entity::Type::ARCHER:
        ico->setSourceX(384);
        break;
    default:
        break;
    }

    lbl = new UILabel("0", "big", hue::font);

    rect.w = ico->width();
    rect.h = ico->height() + lbl->height();

    minus = new UITextBox("-", "h2", hue::font, hue::blur, hue::invisible);
    minus->setWidth(rect.w/2);
    minus->setHeight(rect.h);

    plus = new UITextBox("+", "h2", hue::font, hue::blur, hue::invisible);
    plus->setWidth(rect.w/2);
    plus->setHeight(rect.h);


    place(0,0);
}
    
UIUnitSelector::~UIUnitSelector() {}

void UIUnitSelector::draw() {
    Manager::DrawFilledRect(&rect, hue::card_background);

    ico->draw();
    lbl->draw();

    SDL_Point m;
    SDL_GetMouseState(&m.x, &m.y);
    
    if (SDL_PointInRect(&m, minus->getRect()))
        minus->draw();
    else if (SDL_PointInRect(&m, plus->getRect()))
        plus->draw();

    Manager::DrawRect(&rect, hue::card_border);
}

void UIUnitSelector::update() {
    if (!Window::event.mouseClickLeft()) return;

    SDL_Point m;
    SDL_GetMouseState(&m.x, &m.y);
    
    if (SDL_PointInRect(&m, minus->getRect()))
        decreaseCounter();
    else if (SDL_PointInRect(&m, plus->getRect()))
        increaseCounter();
}

void UIUnitSelector::destroy() {
    ico->destroy();
    lbl->destroy();
    minus->destroy();
    plus->destroy();
}

void UIUnitSelector::place(const int x, const int y) {
    rect.x = x;
    rect.y = y;

    ico->place(x,y);
    lbl->place(
        x + (rect.w - lbl->width()) / 2,
        y + ico->width()
    );

    minus->place(x,y);
    plus->place(x+minus->width(), y);
}

void UIUnitSelector::decreaseCounter() {
    if (count <= 0) return;

    count--;
    *available = *available + 1;

    lbl->setText(std::to_string(count), "big", hue::font);
    place(rect.x, rect.y);
}

void UIUnitSelector::increaseCounter() {
    if (*available <= 0) return;

    count++;
    *available = *available - 1;

    lbl->setText(std::to_string(count), "big", hue::font);
    place(rect.x, rect.y);
}
