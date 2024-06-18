#include "include/Game/Components/Builder.h"

#include "include/Game/Components/Collision.h"
#include "include/Game/Game.h"
#include "include/Window.h"

bool Builder::active = false;
Building::Type Builder::type = Building::Type::HOUSE;

std::array<Vector2D, 3> Builder::dimensions = {
    Vector2D{5, 4}, // CASTLE
    Vector2D{2, 3}, // HOUSE
    Vector2D{2, 4}, // TOWER
};

void Builder::update() {
    if (!active) return;

    position = Game::cursor.getPosOnMap();
    position -= Vector2D{1, dimensions[type].y - 1};

    if (justActived) {
        justActived = false;
        return;
    }
    
    if (Collision::IsValidBuildingPosition(position, dimensions[type]) && Window::event.mouseClickLeft())
        Game::AddBuilding(type, position, Game::playerFaction.name);
    else if (Window::event.mouseClickRight())
        active = false;
}

void Builder::draw() {
    if (!active) return;

    // get drawing rect

    const int tileSize = Map::TileSize();

    rect.w = dimensions[type].x * tileSize;
    rect.h = dimensions[type].y * tileSize;

    rect.x = position.x * tileSize - Game::camera.pos.x;
    rect.y = position.y  * tileSize - Game::camera.pos.y;

    // get texture

    switch (type) {
    case Building::Type::HOUSE:
        texture = Window::manager->getTexture("white house");
        break;
    case Building::Type::TOWER:
        texture = Window::manager->getTexture("white tower");
        break;
    case Building::Type::CASTLE:
        texture = Window::manager->getTexture("white castle");
        break;    
    default:
        break;
    }

    SDL_SetTextureAlphaMod(texture, 128);

    // render texture

    if (Collision::IsValidBuildingPosition(position, dimensions[type]))
        Manager::DrawFilledRect(&rect, hue::blur_green);
    else Manager::DrawFilledRect(&rect, hue::blur_red);

    Manager::Draw(texture, nullptr, &rect);

    if (Collision::IsValidBuildingPosition(position, dimensions[type]))
        Manager::DrawRect(&rect, hue::green);
    else Manager::DrawRect(&rect, hue::red);

    // free ressources
    
    SDL_SetTextureAlphaMod(texture, 255);

    texture = nullptr;
}
