#include "include/Game/Camera.h"

#include "include/Window.h"

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
    pos.Zero();
    zoom = 1.0f;
}

Camera::~Camera() {}

void Camera::update() {
    const int inputX = Window::event.raised(Event::ID::MOVE_RIGHT) - Window::event.raised(Event::ID::MOVE_LEFT);
    const int inputY = Window::event.raised(Event::ID::MOVE_DOWN)  - Window::event.raised(Event::ID::MOVE_UP);

    pos.x = Lerp(pos.x, pos.x + inputX*SPEED*zoom, SPEED*Window::deltaTime);
    pos.y = Lerp(pos.y, pos.y + inputY*SPEED*zoom, SPEED*Window::deltaTime);
}

void Camera::applyZoom(const int s) {
    zoom += s * ZOOM_SPEED;
    zoom = std::clamp(zoom, ZOOM_MIN, ZOOM_MAX);

    Manager::SetScale(zoom, zoom);
}

void Camera::reset() {
    pos.Zero();
    zoom = 1.0f;
}
