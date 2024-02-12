#pragma once
#include "../sdlutils/Texture.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/LayerGroup.hpp>
#include <tmxlite/TileLayer.hpp>
#include <iostream>

using namespace tmx;

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

class MapReader {
private:
    Map map;
    Texture* tilemap = nullptr;

public:
    MapReader();

    void renderMap(SDL_Rect rect);
};