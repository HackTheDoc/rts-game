#include "include/Game/Game.h"

#include "include/Window.h"

Game::Game() {}

Game::~Game() {}

void Game::init() {

}

void Game::update() {

}

void Game::render() {
    Manager::DrawFilledRect(&Window::screen, hue::white);
}

void Game::clean() {

}
