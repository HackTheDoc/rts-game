#include "include/Game/Buildings/Castle.h"

#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/struct.h"

Castle::Castle(const std::string& faction, const Vector2D& pos) {
    this->faction = faction;
    type = CASTLE;
    
    position = pos;
    entry = pos + Vector2D{2, 3};
    std::cout << pos << entry << std::endl;
    
    width = 5;
    height = 4;

    freeSpace = 4;

    texture = Window::manager->getTexture(faction+" castle");

    foodStorage = 0;
    goldStorage = 0;
    woodStorage = 0;

    addColliders();
}

Castle::~Castle() {}

void Castle::update() {
    Building::update();

    if (!Cursor::enable) return;
    
    if (Builder::active) return;

    if (!Game::cursor.inRect(&rect)) return;

    if (Game::CountSelectedEntities() == 1 && Window::event.mouseClickRight()) {
        Entity* e = Game::GetSelectedEntity(0);
        e->goTo(entry);
    }
    else if (Game::CountSelectedEntities() == 0 && Window::event.mouseClickLeft()) {
        Game::SelectBuilding(this);
        Window::event.raise(Event::ID::SELECT_UNITS);
    }
}

Struct::Building Castle::getStructure() {
    return {Struct::Castle{faction, position, foodStorage, goldStorage, woodStorage}};
}
