#include "include/Game/Buildings/Castle.h"

#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/struct.h"

Castle::Castle(const std::string& faction, const Vector2D& pos) {
    this->faction = faction;
    type = CASTLE;
    
    position = pos;
    
    width = 5;
    height = 4;

    freeSpace = 4;

    texture = Window::manager->getTexture(faction+" castle");

    foodStorage = 0;
    goldStorage = 0;
    woodStorage = 0;
}

Castle::~Castle() {}

void Castle::update() {
    Building::update();

    if (!Cursor::enable) return;
    
    if (Builder::active) return;
    
    if (Game::CountSelectedEntities() > 0) return;

    if (!Game::cursor.inRect(&rect)) return;

    if (!Window::event.mouseClickLeft()) return;

    Game::SelectBuilding(this);

    Window::event.raise(Event::ID::SELECT_UNITS);
}

Struct::Building Castle::getStructure() {
    return {Struct::Castle{faction, position, foodStorage, goldStorage, woodStorage}};
}
