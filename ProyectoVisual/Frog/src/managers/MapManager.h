#pragma once
#include "../sdlutils/Texture.h"
#include "../utils/assets.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/LayerGroup.hpp>
#include <tmxlite/TileLayer.hpp>
#include <iostream>
#include "../utils/Vector2D.h"
using namespace tmx;
typedef int gid;

using uint = unsigned int;
constexpr uint MAP_MULT = 8;

namespace
{
    const std::array<std::string, 4u> LayerStrings =
    {
        std::string("Tile"),
        std::string("Object"),
        std::string("Image"),
        std::string("Group"),
    };
}

struct tile {
    SDL_Texture* sheet;
    // x coordinate in the world
    int x;
    // y coordinate in the world
    int y;
    // the x coordinate on the sprite sheet
    int tx;
    // the y coordinate on the sprite sheet
    int ty;
    int width;
    int height;

    tile(SDL_Texture* tset, int x = 0, int y = 0,
        int tx = 0, int ty = 0, int w = 0, int h = 0);
    void draw(SDL_Renderer* ren);
};

class MapManager {
private:
    std::string name;
    // Think of the dimensions as a 2D array (after all, that's what our
    // Tiled map is)
    // The rows variable is the number of tiles from top to bottom (Y axis).
    int rows;
    // The cols variable is the number of tiles from left to right (X axis).
    int cols;
    int tile_width = 0;
    int tile_height = 0;
    // All of the tiles we will draw to the screen.
    std::vector<tile> tiles;
    // All of the tilesets used by our Tiled map.
    std::map<gid, SDL_Texture*> tilesets;
    Vector2D position;
    SDL_Rect mapRect;

public:
    MapManager(const std::string& name, const Vector2D& position);
    void load(const std::string& path, SDL_Renderer* ren);
    void draw(SDL_Renderer* ren);

    Vector2D getMapSize();
    int getTileSize();

    //revisar position map
    //int getX() { return x; }
    //int getY() { return y; }
    int getX() { return position.getX(); }
    int getY() { return position.getY(); }
    void moveRight(int speed, int limit);
    void moveLeft(int speed, int limit);
    void moveUp(int speed, int limit);
    void moveDown(int speed, int limit);
};