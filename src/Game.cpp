#include "include/Game/Game.h"

#include "include/Window.h"

Camera Game::camera;
Cursor Game::cursor;

Game::Game() : map(nullptr) {}

Game::~Game() {}

void Game::init() {
    Window::manager->loadGameTextures();

    Manager::SetRenderDrawColor(hue::water);

    camera.width = Window::screen.w;
    camera.height = Window::screen.h;

    map = new Map();
    map->init("test map");
}

void Game::update() {
    camera.update();
    cursor.update();

    map->update();
    
}

void Game::render() {
    map->render();
}

void Game::clean() {
    camera.reset();
    cursor.reset();
    
    map->destroy();
    delete map;
    map = nullptr;

    Window::manager->clearGameTextures();

    Manager::SetRenderDrawColor(hue::background);
}
