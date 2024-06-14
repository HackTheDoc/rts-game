#include "include/Game/Game.h"

#include "include/Window.h"

SDL_Rect Game::camera = { 0, 0, 0, 0 };

Game::Game() : map(nullptr) {}

Game::~Game() {}

void Game::init() {
    Window::manager->loadGameTextures();

    camera = Window::screen;

    map = new Map();
    map->init("test map");
}

void Game::update() {
    map->update();
}

void Game::render() {
    map->render();
}

void Game::clean() {
    map->destroy();
    delete map;
    map = nullptr;

    Window::manager->clearGameTextures();
}
