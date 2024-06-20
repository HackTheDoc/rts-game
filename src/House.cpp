#include "include/Game/Buildings/House.h"

#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/struct.h"

House::House(const std::string& faction, const Vector2D& pos) {
    this->faction = faction;
    type = HOUSE;
    
    position = pos;
    
    width = 2;
    height = 3;

    freeSpace = 2;

    texture = Window::manager->getTexture(faction+" house");
}

House::~House() {}

void House::update() {
    Building::update();

    if (!Cursor::enable) return;
    
    if (Builder::active) return;
    
    if (Game::CountSelectedEntities() > 0) return;

    if (!Game::cursor.inRect(&rect)) return;

    if (!Window::event.mouseClickLeft()) return;

    Game::SelectBuilding(this);

    Window::event.raise(Event::ID::SELECT_UNITS);
}

Struct::Building House::getStructure() {
    return {Struct::House{faction, position}};
}
