#include "MapManager.h"
#include "../sdlutils/SDLUtils.h"
#include "../scenes/RoomScene.h"

tile::tile(SDL_Texture* tset, int x, int y, int tx, int ty, int w, int h, bool walkable, bool theresObj, Entity* objInTile)
: sheet(tset), x(x), y(y), tx(tx), ty(ty), width(w), height(h), walkable(walkable), theresObj(theresObj), objInTile(objInTile){}

void tile::draw(SDL_Renderer* ren) {
    if (!ren || !sheet)
        return;

    SDL_Rect src;
    src.x = tx;
    src.y = ty;
    src.w = width;
    src.h = height;

    SDL_Rect dest;
    dest.x = x* MAP_MULT;
    dest.y = y* MAP_MULT;
    dest.w = src.w* MAP_MULT;
    dest.h = src.h* MAP_MULT;

    if (DEBUG) {
        if (walkable){ //SOLO SE VER�N CASILLAS EN LAS PARTES EN LAS QUE SE PUEDE CAMINAR
            if (((this->x / this->width % 2 == 0) && (this->y / this->height % 2 == 1)) || ((this->x / this->width % 2 == 1) && (this->y / this->height % 2 == 0))) {
                SDL_SetTextureColorMod(sheet, 200, 200, 200);
            }
            else {
                SDL_SetTextureColorMod(sheet, 255, 255, 255);
            }
        }
        else
            SDL_SetTextureColorMod(sheet, 255, 255, 255);
    }
    
    SDL_RenderCopy(ren, sheet, &src, &dest);
}

MapManager::MapManager(const std::string& path, RoomScene* room)
    : name(name), rows(0), cols(0), tile_width(10), tile_height(10), room(room){
        load(path, sdlutils().renderer());
    }

void MapManager::load(const std::string& path, SDL_Renderer* ren) {

    // Load and parse the Tiled map with tmxlite
    Map tiled_map;

    tiled_map.load(path);
    std::cout << "Loaded Map version: " << tiled_map.getVersion().upper << ", " << tiled_map.getVersion().lower << std::endl;

    // We need to know the size of the map (in tiles)
    auto map_dimensions = tiled_map.getTileCount();
    rows = map_dimensions.y;
    cols = map_dimensions.x;
    walkableTiles = vector<vector<tile*>>(rows, vector<tile*>(cols)); //reservamos el espacio para la matriz de tiles
    if (tiled_map.isInfinite())
    {
        std::cout << "Map is infinite.\n";
    }
    else
    {
        std::cout << "Map Dimensions: " << tiled_map.getBounds() << std::endl;
    }

    // We also need to know the dimensions of the tiles.
    auto tilesize = tiled_map.getTileSize();
    tile_width = tilesize.x;
    tile_height = tilesize.y;

    // Load all of the tilesets and store them in a data structure.
    // I chose to store them in a map.
    auto& map_tilesets = tiled_map.getTilesets();
    for (auto& tset : map_tilesets) {
        auto tex = assets::instance()
            .load_texture(tset.getImagePath(), ren);
        tilesets.insert(std::pair<gid, SDL_Texture*>(tset.getFirstGID(), tex));
    }

    std::cout << "Map tileset has " << tiled_map.getTilesets().size() << " tilesets" << std::endl;
    for (const auto& tileset : tiled_map.getTilesets())
    {
        std::cout << "Tileset: " << tileset.getName() << std::endl;
        std::cout << "Tileset class: " << tileset.getClass() << std::endl;
    }

    const auto& mapProperties = tiled_map.getProperties();
    std::cout << "Map has " << mapProperties.size() << " properties" << std::endl;
    for (const auto& prop : mapProperties)
    {
        std::cout << "Found property: " << prop.getName() << std::endl;
        std::cout << "Type: " << int(prop.getType()) << std::endl;
    }

    std::cout << std::endl;

    // This is the hard part; iterate through each layer in the map,
    // poke each tile for the information you need, and store it in
    // our tiles data structure. 
    //
    // We start at the bottom most layer, and work our way up with this
    // outer for-loop.
    auto& map_layers = tiled_map.getLayers();
    std::cout << "Map has " << map_layers.size() << " layers" << std::endl;
    for (auto& layer : map_layers) {

        std::cout << "Found Layer: " << layer->getName() << std::endl;
        std::cout << "Layer Type: " << LayerStrings[static_cast<std::int32_t>(layer->getType())] << std::endl;
        std::cout << "Layer Dimensions: " << layer->getSize() << std::endl;
        std::cout << "Layer Tint: " << layer->getTintColour() << std::endl;

        //TILES BG PARA RENDER 
        if (layer->getType() == Layer::Type::Tile) {
            bool walkable = true;
            if (layer->getName() == "NotWalk") {
                walkable = false;
            }

            auto* tile_layer = dynamic_cast<const TileLayer*>(layer.get());

            // Grab all of this layer's tiles. 
            auto& layer_tiles = tile_layer->getTiles();

            // Remember when we needed the size of the Tiled map? This
            // is where it comes into play. Because we're making a simple
            // 2D game, each tile belongs in an x,y coordinate, so using
            // a loop can help us visit each place if there's a tile there.
            for (auto y = 0; y < rows; ++y) {
                for (auto x = 0; x < cols; ++x) {
                    // the `layer_tiles` vector that our `getTiles()` call
                    // returned on line 78 isn't a 2D array, but we can
                    // convert our x, y coordinates into an index that we
                    // can access it at.
                    auto tile_index = x + (y * cols);
                    // Grab the GID of the tile we're at.
                    auto cur_gid = layer_tiles[tile_index].ID;
                    // If the GID is 0, that means it's an empty tile,
                    // we don't want to waste time on nothing, nor do we
                    // want to store an empty tile.
                    if (cur_gid == 0) {
                        continue;
                    }

                    // Find the tileset that this tile belongs to. The tileset
                    // whose first GID is less-than-or-equal to this GID, is
                    // the tileset our GID belongs to. A tileset with a first
                    // GID that is greater than this tile means that this tile
                    // does not belong to that tileset.
                    auto tset_gid = -1;
                    for (auto& ts : tilesets) {
                        if (ts.first <= cur_gid) {
                            tset_gid = ts.first;
                            break;
                        }
                    }
                    // If we didn't find a valid tileset, skip the tile. We can't
                    // render it if we don't have a tileset to pull from.
                    if (tset_gid == -1) {
                        continue;
                    }

                    // Normalize the GID.
                    cur_gid -= tset_gid;
                    // Find the dimensions of the tile sheet. This is important,
                    // because our tile is only a small sprite on that sheet, not
                    // the whole sheet.
                    auto ts_width = 0;
                    auto ts_height = 0;
                    SDL_QueryTexture(tilesets[tset_gid],
                        NULL, NULL, &ts_width, &ts_height);

                    // Calculate the area on the tilesheet to draw from.
                    auto region_x = (cur_gid % (ts_width / tile_width)) * tile_width;
                    auto region_y = (cur_gid / (ts_width / tile_width)) * tile_height;

                    // Calculate the world position of our tile. This is easy,
                    // because we're using nested for-loop to visit each x,y
                    // coordinate.
                    auto x_pos = x * tile_width;
                    auto y_pos = y * tile_height;

                    // Phew, all done. 
                    tile t(tilesets[tset_gid], x_pos, y_pos,
                        region_x, region_y, tile_width, tile_height, walkable);
                    tiles.push_back(t);

                    //la añadimos a el mapa de tiles caminables
                    if (walkable)
                        walkableTiles[x][y] = &t;
                }
            }
        }

        //TILES DE OBJETOS
        else if (layer->getType() == Layer::Type::Object) {
            const auto& objects = layer->getLayerAs<ObjectGroup>().getObjects();
            std::cout << "Found " << objects.size() << " objects in layer" << std::endl;
            for (const auto& object : objects)
            {
                std::string texPath = "";

                std::cout << "Object " << object.getUID() << ", " << object.getName() << std::endl;
                const auto& properties = object.getProperties();
                std::cout << "Object has " << properties.size() << " properties" << std::endl;
                for (const auto& prop : properties)
                {
                    std::cout << "Found property: " << prop.getName() << std::endl;
                    std::cout << "Type: " << int(prop.getType()) << std::endl;

                    if (prop.getName() == "TexPath") {
                        texPath = prop.getStringValue();
                    }


                    if (prop.getName() == "isPlayer") {
                        if (prop.getBoolValue()) {
                            Vector2D pos;
                            pos.setX((int)object.getPosition().x / tiled_map.getTileSize().x);
                            pos.setY((int)object.getPosition().y / tiled_map.getTileSize().y);
                            room->createPlayer(texPath, pos, getTile(pos));
                        }

                    }
                }

                if (!object.getTilesetName().empty())
                {
                    std::cout << "Object uses template tile set " << object.getTilesetName() << "\n";
                }
            }
        }

        //TILES DE GRUPO (SOLO PORSEACA EN UN FUTURO)
        else if (layer->getType() == Layer::Type::Group)
        {
            /*
            std::cout << "Checking sublayers" << std::endl;
            const auto& sublayers = layer->getLayerAs<LayerGroup>().getLayers();
            std::cout << "LayerGroup has " << sublayers.size() << " layers" << std::endl;
            for (const auto& sublayer : sublayers)
            {
                std::cout << "Found Layer: " << sublayer->getName() << std::endl;
                std::cout << "Sub-layer Type: " << LayerStrings[static_cast<std::int32_t>(sublayer->getType())] << std::endl;
                std::cout << "Sub-layer Class: " << sublayer->getClass() << std::endl;
                std::cout << "Sub-layer Dimensions: " << sublayer->getSize() << std::endl;
                std::cout << "Sub-layer Tint: " << sublayer->getTintColour() << std::endl;

                if (sublayer->getType() == Layer::Type::Object)
                {
                    std::cout << sublayer->getName() << " has " << sublayer->getLayerAs<ObjectGroup>().getObjects().size() << " objects" << std::endl;
                }
                else if (sublayer->getType() == Layer::Type::Tile)
                {
                    std::cout << sublayer->getName() << " has " << sublayer->getLayerAs<TileLayer>().getTiles().size() << " tiles" << std::endl;
                }
            }
            */
        }

        const auto& properties = layer->getProperties();
        std::cout << properties.size() << " Layer Properties:" << std::endl;
        for (const auto& prop : properties)
        {
            std::cout << "Found property: " << prop.getName() << std::endl;
            std::cout << "Type: " << int(prop.getType()) << std::endl;
        }
    }
}

void MapManager::draw(SDL_Renderer* ren) {
    //Dibujamos cada tile
    for (auto& tile : tiles) {
        tile.draw(ren);
    }
}

Vector2D MapManager::getMapSize()
{
    return Vector2D(cols, rows);
}

int MapManager::getTileSize()
{
    return tile_width*MAP_MULT; //width y height son iguales
}

tile* MapManager::getTile(Vector2D v)
{
    if (walkableTiles[v.getX()][v.getY()] != nullptr)
        return walkableTiles[v.getX()][v.getY()];
    else
        return nullptr;
}

void MapManager::move(std::string direction) {

    int dx = 0, dy = 0;
    //determinar la velocidad
    if (direction == "right") {
        dx = tile_width/2;
    }
    else  if (direction == "left") {
        dx = -tile_width/2;
    }
    else  if (direction == "up") {
        dy = -tile_height/2;
    }
    else  if (direction == "down") {
        dy = tile_height/2;
    }
    //comprobar que al moverse los tiles, no se superen los bordes del mapa
    //COMPROBAR LIMITES
    bool canMove = true;
   /* for (auto& tile : tiles) {
        if (direction == "right" || direction == "left") {
            int nextX = tile.x + dx;
            if (nextX > getTileSize() + tile_width || nextX <  -(getTileSize()/2)) {
                canMove = false;
                break;
            }
        }
        else if (direction == "up" || direction == "down") {
            int nextY = tile.y + dy;
            if (nextY > getTileSize() + tile_height || nextY < -((getTileSize()/2) + tile_height)) {
                canMove = false;
                break;
            }
        }
    }*/
    //si se pueden mover los tiles, se actualiza su posicion
    if (canMove) {
        if (direction == "right" || direction == "left") {
            for (auto& tile : tiles) {
                tile.x += dx;
            }
        }
        else if (direction == "up" || direction == "down") {
            for (auto& tile : tiles) {
                tile.y += dy;
            }
        }
       
    }
}