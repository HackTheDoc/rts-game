#include "include/Game/Camera.h"

#include "include/Game/Buildings/Building.h"

#include "include/Window.h"
#include "include/struct.h"

#include <iostream>
#include <algorithm>

const float Camera::SPEED =48.0f;
const float Camera::ZOOM_SPEED = 0.1f;
const float Camera::ZOOM_MARGIN = 0.1f;
const float Camera::ZOOM_MIN = 0.5f;
const float Camera::ZOOM_MAX = 3.0f;

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
}

void Camera::update() {
    const int inputX = Window::event.raised(Event::ID::MOVE_RIGHT) - Window::event.raised(Event::ID::MOVE_LEFT);
    const int inputY = Window::event.raised(Event::ID::MOVE_DOWN)  - Window::event.raised(Event::ID::MOVE_UP);

    const float b = SPEED * zoom;
    const float c = SPEED * Window::deltaTime;
    pos.x = Lerp(pos.x, pos.x + inputX * b, c);
    pos.y = Lerp(pos.y, pos.y + inputY * b, c);
}

void Camera::applyZoom(const int s) {
    zoom += s * ZOOM_SPEED;
    zoom = std::clamp(zoom, ZOOM_MIN, ZOOM_MAX);
}

void Camera::reset() {
    pos.Zero();
    zoom = 1.0f;
}

void Camera::centerOn(Building* b) {
    pos.x = b->position.x * Tile::SIZE + (b->getWidth() - width) / 2;
    pos.y = b->position.y * Tile::SIZE + (b->getHeight() - height) / 2;
}

Struct::Camera Camera::getStructure() {
    return {pos, zoom};
}
