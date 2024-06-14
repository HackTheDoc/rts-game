#include "include/Game/Cursor.h"

#include "include/Window.h"

Cursor::Cursor() {
    reset();
}

Cursor::~Cursor() {}

void Cursor::update() {
    SDL_GetMouseState(&pos.x, &pos.y);
}

void Cursor::reset() {
    pos.Zero();
}

bool Cursor::inRect(const SDL_Rect* r) {
    SDL_Point p{pos.x, pos.y};
    return SDL_PointInRect(&p, r);
}
