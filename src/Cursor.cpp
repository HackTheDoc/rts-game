#include "include/Game/Cursor.h"

#include "include/Window.h"
#include "include/Game/Game.h"

Cursor::Cursor() {
    reset();
}

Cursor::~Cursor() {}

void Cursor::update() {
    SDL_GetMouseState(&pos.x, &pos.y);

    // single selection

    if (Window::event.mouseClickLeft())
        Game::SelectEntityAt(&pos);
    
    // selecting system

    if (selecting) {
        if (Window::event.mouseClickLeft(SDL_MOUSEBUTTONUP)) {
            selecting = false;
            Game::SelectEntities();
        }
        else {
            selectionRect.w = pos.x - selectionRect.x;
            selectionRect.h = pos.y - selectionRect.y;
        }
    }
    else if (Window::event.mouseClickLeft(SDL_MOUSEBUTTONDOWN)) {
        selecting = true;
        selectionRect = {pos.x, pos.y, 1, 1};        
    }
}

void Cursor::draw() {
    if (!selecting) return;

    Manager::DrawFilledRect(&selectionRect, hue::blur_yellow);
    Manager::DrawRect(&selectionRect, hue::yellow);
}

void Cursor::reset() {
    pos.Zero();
}

bool Cursor::inRect(const SDL_Rect* r) {
    SDL_Point p{pos.x, pos.y};
    return SDL_PointInRect(&p, r);
}
