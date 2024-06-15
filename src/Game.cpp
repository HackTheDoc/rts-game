#include "include/Game/Game.h"

#include "include/Window.h"
#include "include/Save.h"

Camera Game::camera;
Cursor Game::cursor;

Map* Game::map = nullptr;
std::vector<Entity*> Game::selectedEntities{};

Game::Game() {}

Game::~Game() {}

void Game::init() {
    Window::manager->loadGameTextures();

    Manager::SetRenderDrawColor(hue::water);

    camera.width = Window::screen.w;
    camera.height = Window::screen.h;

    const Struct::Game g = Save::Load();

    camera.load(g.camera);

    map = new Map();
    map->init(g.map);
}

void Game::update() {
    camera.update();
    cursor.update();

    map->update();
    
}

void Game::render() {
    map->render();
    cursor.draw();
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

void Game::ReleaseSelectedEntities() {
    for (Entity* e : selectedEntities)
        e->selected = false;
    selectedEntities.clear();
}

void Game::SelectEntities() {
    if (!Window::event.raised(Event::ID::SELECT_MULTIPLE))
        Game::ReleaseSelectedEntities();

    // format selection rect
    SDL_Rect r = cursor.selectionRect;
    if (cursor.selectionRect.w < 0) {
        r.x = cursor.selectionRect.x + cursor.selectionRect.w;
        r.w = -cursor.selectionRect.w;
    }
    if (cursor.selectionRect.h < 0) {
        r.y = cursor.selectionRect.y + cursor.selectionRect.h;
        r.h = -cursor.selectionRect.h;
    }
        
    std::vector<Entity*> newlySelectedEntities = map->getEntitiesInRect(r);
    for (Entity* e :  newlySelectedEntities) {
        e->selected = true;
        selectedEntities.push_back(e);
    }
}

void Game::SelectEntityAt(const Vector2D* pos) {
    if (!Window::event.raised(Event::ID::SELECT_MULTIPLE))
        Game::ReleaseSelectedEntities();

    std::optional<Entity*> e = map->getEntitiesAt(pos);
    
    if (e.has_value()) {
        e.value()->selected = true;
        selectedEntities.push_back(e.value());
    }

}

Struct::Game Game::GetStructure() {
    return {camera.getStructure(), map->getStructure()};
}
