#include "include/Game/Map/Tile.h"

#include "include/Game/Components/Animation.h"

#include "include/Game/Game.h"
#include "include/Window.h"

/* ---------- TILE CLASS ---------- */

const int Tile::SIZE = 128;

Tile::Tile(const Type t) {
    switch (t) {
    /* ----- WATER TILES ----- */

    case WATER:
        texture = Window::manager->getTexture("water");
        srcRect = { 0, 0, 64, 64 };
        break;
    case FOAM: // unreachable
        break; 
        
    /* ----- GRASS TILES ----- */

    case GRASS:
        texture = Window::manager->getTexture("ground");
        srcRect = { 192, 192, 64, 64 };
        break;
    case GRASS_TOP:
        texture = Window::manager->getTexture("ground");
        srcRect = { 64, 0, 64, 64 };
        break;
    case GRASS_TOP_LEFT:
        texture = Window::manager->getTexture("ground");
        srcRect = { 0, 0, 64, 64 };
        break;
    case GRASS_TOP_RIGHT:
        texture = Window::manager->getTexture("ground");
        srcRect = { 128, 0, 64, 64 };
        break;
    case GRASS_MID:
        texture = Window::manager->getTexture("ground");
        srcRect = { 64, 64, 64, 64 };
        break;
    case GRASS_MID_LEFT:
        texture = Window::manager->getTexture("ground");
        srcRect = { 0, 64, 64, 64 };
        break;
    case GRASS_MID_RIGHT:
        texture = Window::manager->getTexture("ground");
        srcRect = { 128, 64, 64, 64 };
        break;
    case GRASS_BOT:
        texture = Window::manager->getTexture("ground");
        srcRect = { 64, 128, 64, 64 };
        break;
    case GRASS_BOT_LEFT:
        texture = Window::manager->getTexture("ground");
        srcRect = { 0, 128, 64, 64 };
        break;
    case GRASS_BOT_RIGHT:
        texture = Window::manager->getTexture("ground");
        srcRect = { 128, 128, 64, 64 };
        break;
    case GRASS_ROW_MID:
        texture = Window::manager->getTexture("ground");
        srcRect = { 64, 192, 64, 64 };
        break;
    case GRASS_ROW_LEFT:
        texture = Window::manager->getTexture("ground");
        srcRect = { 0, 192, 64, 64 };
        break;
    case GRASS_ROW_RIGHT:
        texture = Window::manager->getTexture("ground");
        srcRect = { 128, 192, 64, 64 };
        break;
    case GRASS_COL_TOP:
        texture = Window::manager->getTexture("ground");
        srcRect = { 192, 0, 64, 64 };
        break;
    case GRASS_COL_MID:
        texture = Window::manager->getTexture("ground");
        srcRect = { 192, 64, 64, 64 };
        break;
    case GRASS_COL_BOT:
        texture = Window::manager->getTexture("ground");
        srcRect = { 192, 128, 64, 64 };
        break;
        
    /* ----- SAND TILES ----- */


    case SAND:
        texture = Window::manager->getTexture("ground");
        srcRect = { 512, 192, 64, 64 };
        break;
    case SAND_TOP:
        texture = Window::manager->getTexture("ground");
        srcRect = { 384, 0, 64, 64 };
        break;
    case SAND_TOP_LEFT:
        texture = Window::manager->getTexture("ground");
        srcRect = { 320, 0, 64, 64 };
        break;
    case SAND_TOP_RIGHT:
        texture = Window::manager->getTexture("ground");
        srcRect = { 448, 0, 64, 64 };
        break;
    case SAND_MID:
        texture = Window::manager->getTexture("ground");
        srcRect = { 384, 64, 64, 64 };
        break;
    case SAND_MID_LEFT:
        texture = Window::manager->getTexture("ground");
        srcRect = { 320, 64, 64, 64 };
        break;
    case SAND_MID_RIGHT:
        texture = Window::manager->getTexture("ground");
        srcRect = { 448, 64, 64, 64 };
        break;
    case SAND_BOT:
        texture = Window::manager->getTexture("ground");
        srcRect = { 384, 128, 64, 64 };
        break;
    case SAND_BOT_LEFT:
        texture = Window::manager->getTexture("ground");
        srcRect = { 320, 128, 64, 64 };
        break;
    case SAND_BOT_RIGHT:
        texture = Window::manager->getTexture("ground");
        srcRect = { 448, 128, 64, 64 };
        break;
    case SAND_ROW_MID:
        texture = Window::manager->getTexture("ground");
        srcRect = { 384, 0, 64, 64 };
        break;
    case SAND_ROW_LEFT:
        texture = Window::manager->getTexture("ground");
        srcRect = { 448, 192, 64, 64 };
        break;
    case SAND_ROW_RIGHT:
        texture = Window::manager->getTexture("ground");
        srcRect = { 320, 192, 64, 64 };
        break;
    case SAND_COL_TOP:
        texture = Window::manager->getTexture("ground");
        srcRect = { 512, 192, 64, 64 };
        break;
    case SAND_COL_MID:
        texture = Window::manager->getTexture("ground");
        srcRect = { 512, 64, 64, 64 };
        break;
    case SAND_COL_BOT:
        texture = Window::manager->getTexture("ground");
        srcRect = { 512, 128, 64, 64 };
        break;
        
    /* ----- STONE TILES ----- */


    case STONE:
        texture = Window::manager->getTexture("stone");
        srcRect = { 192, 256, 64, 64 };
        break;
    case STONE_TOP:
        texture = Window::manager->getTexture("stone");
        srcRect = { 64, 0, 64, 64 };
        break;
    case STONE_TOP_LEFT:
        texture = Window::manager->getTexture("stone");
        srcRect = { 0, 0, 64, 64 };
        break;
    case STONE_TOP_RIGHT:
        texture = Window::manager->getTexture("stone");
        srcRect = { 128, 0, 64, 64 };
        break;
    case STONE_MID:
        texture = Window::manager->getTexture("stone");
        srcRect = { 64, 64, 64, 64 };
        break;
    case STONE_MID_LEFT:
        texture = Window::manager->getTexture("stone");
        srcRect = { 0, 64, 64, 64 };
        break;
    case STONE_MID_RIGHT:
        texture = Window::manager->getTexture("stone");
        srcRect = { 128, 64, 64, 64 };
        break;
    case STONE_BOT:
        texture = Window::manager->getTexture("stone");
        srcRect = { 64, 128, 64, 64 };
        break;
    case STONE_BOT_LEFT:
        texture = Window::manager->getTexture("stone");
        srcRect = { 0, 128, 64, 64 };
        break;
    case STONE_BOT_RIGHT:
        texture = Window::manager->getTexture("stone");
        srcRect = { 128, 128, 64, 64 };
        break;
    case STONE_ROW_MID:
        texture = Window::manager->getTexture("stone");
        srcRect = { 64, 256, 64, 64 };
        break;
    case STONE_ROW_LEFT:
        texture = Window::manager->getTexture("stone");
        srcRect = { 0, 256, 64, 64 };
        break;
    case STONE_ROW_RIGHT:
        texture = Window::manager->getTexture("stone");
        srcRect = { 128, 256, 64, 64 };
        break;
    case STONE_COL_TOP:
        texture = Window::manager->getTexture("stone");
        srcRect = { 192, 0, 64, 64 };
        break;
    case STONE_COL_MID:
        texture = Window::manager->getTexture("stone");
        srcRect = { 192, 64, 64, 64 };
        break;
    case STONE_COL_BOT:
        texture = Window::manager->getTexture("stone");
        srcRect = { 192, 128, 64, 64 };
        break;
    case STONE_WALL:
        texture = Window::manager->getTexture("stone");
        srcRect = { 192, 192, 64, 64 };
        break;
    case STONE_WALL_LEFT:
        texture = Window::manager->getTexture("stone");
        srcRect = { 0, 192, 64, 64 };
        break;
    case STONE_WALL_MID:
        texture = Window::manager->getTexture("stone");
        srcRect = { 64, 192, 64, 64 };
        break;
    case STONE_WALL_RIGHT:
        texture = Window::manager->getTexture("stone");
        srcRect = { 128, 192, 64, 64 };
        break;

    case NONE:
    default:
        texture = nullptr;
        srcRect = {0,0,0,0};
        break;
    }

    rect = { 0, 0, Tile::SIZE, Tile::SIZE };

    place(0, 0);
}

Tile::~Tile() {}

void Tile::update() {
    rect.x = position.x - Game::camera.pos.x;
    rect.y = position.y - Game::camera.pos.y;
}

void Tile::draw() {
    Manager::Draw(texture, &srcRect, &rect);
}

void Tile::destroy() {
    texture = nullptr;
    srcRect = rect = {0,0,0,0};
}

void Tile::place(const int x, const int y) {
    position.x = x * Tile::SIZE;
    position.y = y * Tile::SIZE;
}

/* ---------- FLOAM CLASS ---------- */

Foam::Foam() {
    texture = Window::manager->getTexture("foam");
    srcRect = { 0, 0, 192, 192};
    const int s = Tile::SIZE * 3;
    rect = { 0, 0, s, s};
    place(0,0);
}

Foam::~Foam() {}

void Foam::place(const int x, const int y) {
    position.x = (x-1) * Tile::SIZE;
    position.y = (y-1) * Tile::SIZE;
}

void Foam::update() {
    const int currentFrame = (int)((SDL_GetTicks64() / Animation::SPEED) % FRAMES);
    srcRect.x = srcRect.w * currentFrame;

    rect.x = position.x - Game::camera.pos.x;
    rect.y = position.y - Game::camera.pos.y;
}
