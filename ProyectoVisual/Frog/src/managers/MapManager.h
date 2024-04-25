#pragma once
#include "../sdlutils/Texture.h"
#include "../utils/assets.h"
#include "../ecs/Entity.h"
#include "DataManager.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/LayerGroup.hpp>
#include <tmxlite/TileLayer.hpp>
#include <iostream>
#include <vector>
using namespace tmx;
using namespace std;
typedef int gid;

using uint = unsigned int;
constexpr uint MAP_MULT = 5;
constexpr bool DEBUG = true;

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
    // bool to see if Flonk can walk it 
    bool walkable;
    // bool para ver si hay objeto
    bool theresObj;
    // si hay objeto puntero a su entidad
    Entity* objInTile;


    tile(SDL_Texture* tset, int x = 0, int y = 0, int tx = 0, int ty = 0, int w = 0, 
        int h = 0, bool walkable = true, bool theresObj = false, Entity* objInTile = nullptr);
    void draw(SDL_Renderer* ren, int num, Vector2D cameraPos);
};

class RoomScene;

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
    int boundRight;
    int boundLeft;
    int boundTop;
    int boundBottom;
    // All of the tiles we will draw to the screen.
    std::vector<tile> tiles;
    // All of the tilesets used by our Tiled map.
    std::map<gid, SDL_Texture*> tilesets;

    //the coordinate in which the map starts

    RoomScene* room = nullptr;

public:
    MapManager(const std::string& path, RoomScene* room);
    ~MapManager();
    void loadBg(const std::string& path, SDL_Renderer* ren);
    void loadObj(const std::string& path);
    void draw(SDL_Renderer* ren);

    Vector2D getMapSize();
    //la matriz para gestionar colisiones etc
    vector<vector<tile*>> walkableTiles;
    bool isTileWalkable(Vector2D);
    int getTileSize();
    tile* getTile(Vector2D);
    int getCols() { return cols; }
    int getRows() { return rows; }
    void move(std::string dir);
    
};