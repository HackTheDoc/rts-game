#pragma once

#include <SDL2/SDL.h>

#include "../Components/Vector2D.h"

class Tile {
public:
    static const int SIZE;

    enum Type {
        NONE,
        
        WATER,
        FOAM,

        // grass

        GRASS,
        GRASS_TOP,
        GRASS_TOP_LEFT,
        GRASS_TOP_RIGHT,
        GRASS_MID,
        GRASS_MID_LEFT,
        GRASS_MID_RIGHT,
        GRASS_BOT,
        GRASS_BOT_LEFT,
        GRASS_BOT_RIGHT,
        GRASS_ROW_MID,
        GRASS_ROW_LEFT,
        GRASS_ROW_RIGHT,
        GRASS_COL_TOP,
        GRASS_COL_MID,
        GRASS_COL_BOT,

        // sand

        SAND,
        SAND_TOP,
        SAND_TOP_LEFT,
        SAND_TOP_RIGHT,
        SAND_MID,
        SAND_MID_LEFT,
        SAND_MID_RIGHT,
        SAND_BOT,
        SAND_BOT_LEFT,
        SAND_BOT_RIGHT,
        SAND_ROW_MID,
        SAND_ROW_LEFT,
        SAND_ROW_RIGHT,
        SAND_COL_TOP,
        SAND_COL_MID,
        SAND_COL_BOT,

        // stone

        STONE,
        STONE_TOP,
        STONE_TOP_LEFT,
        STONE_TOP_RIGHT,
        STONE_MID,
        STONE_MID_LEFT,
        STONE_MID_RIGHT,
        STONE_BOT,
        STONE_BOT_LEFT,
        STONE_BOT_RIGHT,
        STONE_ROW_MID,
        STONE_ROW_LEFT,
        STONE_ROW_RIGHT,
        STONE_COL_TOP,
        STONE_COL_MID,
        STONE_COL_BOT,
        STONE_WALL,
        STONE_WALL_LEFT,
        STONE_WALL_MID,
        STONE_WALL_RIGHT,
    };
    
    Vector2D position;
    SDL_Rect rect;

    Tile(const Type t = Type::WATER);
    ~Tile();

    void place(const int x, const int y);
    
    void update();
    void draw();
    void destroy();

protected:
    SDL_Texture* texture;
    SDL_Rect srcRect;    
};

class Foam : public Tile {
public:
    Foam();
    ~Foam();

    void place(const int x, const int y);

    void update();

private:
    static constexpr int FRAMES = 8;
};
