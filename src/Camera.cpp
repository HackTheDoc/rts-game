#include "include/Game/Camera.h"

#include "include/Game/Buildings/Building.h"
#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/struct.h"

#include <iostream>
#include <algorithm>

const float Camera::SPEED = 48.0f;
const float Camera::ZOOM_SPEED = 0.1f;
const float Camera::ZOOM_MARGIN = 0.1f;
const float Camera::ZOOM_MIN = 0.5f;
const float Camera::ZOOM_MAX = 1.0f;

SDL_Rect Camera::NorthRect = {0,0,0,0};
SDL_Rect Camera::SouthRect = {0,0,0,0};
SDL_Rect Camera::EastRect = {0,0,0,0};
SDL_Rect Camera::WeastRect = {0,0,0,0};

float Lerp(float a, float b, float c) {
    const float t = std::clamp(c, 0.0f, 1.0f);
    return a + t * (b - a);
}

Camera::Camera() {
    reset();
}

Camera::~Camera() {}

void Camera::load(const Struct::Camera& c) {
    pos = c.pos;
    zoom = c.zoom;

    NorthRect = {
        0,
        0,
        Window::screen.w,
        10 * Window::screen.h / 100
    };

    SouthRect = {
        0,
        Window::screen.h - NorthRect.h,
        Window::screen.w,
        NorthRect.h
    };

    WeastRect = {
        0,
        0,
        10 * Window::screen.w / 100,
        Window::screen.h
    };

    EastRect = {
        Window::screen.w - WeastRect.w,
        0,
        WeastRect.w,
        Window::screen.h        
    };
}

void Camera::update() {
    // movement from keys
    {
        const int inputX = Window::event.raised(Event::ID::MOVE_RIGHT) - Window::event.raised(Event::ID::MOVE_LEFT);
        const int inputY = Window::event.raised(Event::ID::MOVE_DOWN)  - Window::event.raised(Event::ID::MOVE_UP);

        const float b = SPEED * zoom;
        const float c = SPEED * Window::deltaTime;
        pos.x = Lerp(pos.x, pos.x + inputX * b, c);
        pos.y = Lerp(pos.y, pos.y + inputY * b, c);
    }
    
    // movement from cursor
    {
        const int inputX = PointInRect(&Game::cursor.pos, &EastRect) - PointInRect(&Game::cursor.pos, &WeastRect);
        const int inputY = PointInRect(&Game::cursor.pos, &SouthRect) - PointInRect(&Game::cursor.pos, &NorthRect);

        const float b = SPEED * zoom;
        const float c = SPEED * Window::deltaTime;
        pos.x = Lerp(pos.x, pos.x + inputX * b, c);
        pos.y = Lerp(pos.y, pos.y + inputY * b, c);
    }
}


/// TODO: reactive zoom
void Camera::applyZoom(const int s) {
    //zoom += s * ZOOM_SPEED;
    //zoom = std::clamp(zoom, ZOOM_MIN, ZOOM_MAX);
}

void Camera::reset() {
    pos.Zero();
    zoom = 1.0f;
}

void Camera::centerOn(Building* b) {
    if (b == nullptr) return;

    pos.x = b->position.x * Tile::SIZE + (b->getWidth() - width) / 2;
    pos.y = b->position.y * Tile::SIZE + (b->getHeight() - height) / 2;
}

Struct::Camera Camera::getStructure() {
    return {pos, zoom};
}
