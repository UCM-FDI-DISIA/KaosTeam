#include "MapManager.h"
#include "../sdlutils/SDLUtils.h"
#include "../scenes/RoomScene.h"
#include "CameraManager.h"

tile::tile(SDL_Texture* tset, int x, int y, int tx, int ty, int w, int h, bool walkable, bool theresObj, Entity* objInTile)
: sheet(tset), x(x), y(y), tx(tx), ty(ty), width(w), height(h), walkable(walkable), theresObj(theresObj), objInTile(objInTile){}

void tile::draw(SDL_Renderer* ren, int num, Vector2D cameraPos) {
    if (!ren || !sheet)
        return;

    SDL_Rect src;
    src.x = tx;
    src.y = ty;
    src.w = width;
    src.h = height;

    SDL_Rect dest;
    dest.x = x * MAP_MULT - cameraPos.getX(); 
    dest.y = y * MAP_MULT - cameraPos.getY();  
    dest.w = src.w* MAP_MULT;
    dest.h = src.h* MAP_MULT;

    if (DEBUG) {
        if (walkable){ //SOLO SE VER�N CASILLAS EN LAS PARTES EN LAS QUE SE PUEDE CAMINAR
            if (num % 2 == 0) {
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
    : name(name), rows(0), cols(0), tile_width(16), tile_height(16), room(room){
        std::cout << path << std::endl;
        loadBg(path, sdlutils().renderer());
        boundLeft = -((cols * tile_width)-(5*tile_width));
        boundTop = -((rows * tile_height) - (3 * tile_height));
        boundRight = cols * tile_width;
        boundBottom = rows * tile_height;
    }

MapManager::~MapManager()
{
   for (int i = 0; i < walkableTiles.size(); i++)
   {
       for (int j = 0; j < walkableTiles[0].size(); j++)
       {
           delete walkableTiles[i][j];

       }
   }
 
}

void MapManager::loadBg(const std::string& path, SDL_Renderer* ren) {

    // Load and parse the Tiled map with tmxlite
    Map tiled_map;

    tiled_map.load(path);
    //std::cout << "Loaded Map version: " << tiled_map.getVersion().upper << ", " << tiled_map.getVersion().lower << std::endl;

    // We need to know the size of the map (in tiles)
    auto map_dimensions = tiled_map.getTileCount();
    rows = map_dimensions.y;
    cols = map_dimensions.x;

    //it starts in the origin
    if (tiled_map.isInfinite())
    {
        std::cout << "Map is infinite.\n";
    }
    else
    {
        walkableTiles = vector<vector<tile*>>(cols, vector<tile*>(rows)); //reservamos el espacio para la matriz de booleanos de tiles
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
    //std::cout << "Map has " << mapProperties.size() << " properties" << std::endl;
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
        //std::cout << "Layer Type: " << LayerStrings[static_cast<std::int32_t>(layer->getType())] << std::endl;
        //std::cout << "Layer Dimensions: " << layer->getSize() << std::endl;
        //std::cout << "Layer Tint: " << layer->getTintColour() << std::endl;

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
                    tile* t = new tile(tilesets[tset_gid], x_pos, y_pos,
                        region_x, region_y, tile_width, tile_height, walkable);
                    tiles.push_back(*t);

                    //la añadimos a el mapa de tiles caminables
                    if (walkable)
                        walkableTiles[x][y] = t;
                    else 
                        walkableTiles[x][y] = nullptr; //por si hay tiles no walkables sobre walkables
                }
            }
            std::cout << "Tile vector size: " << tiles.size() << std::endl;
        }

        const auto& properties = layer->getProperties();
        //std::cout << properties.size() << " Layer Properties:" << std::endl;
        for (const auto& prop : properties)
        {
            std::cout << "Found property: " << prop.getName() << std::endl;
            std::cout << "Type: " << int(prop.getType()) << std::endl;
        }
    }
}

void MapManager::loadObj(const std::string& path)
{
    // Load and parse the Tiled map with tmxlite
    Map tiled_map;
    tiled_map.load(path);

    auto& map_layers = tiled_map.getLayers();
    for (auto& layer : map_layers) {
        //TILES DE OBJETOS
        if (layer->getType() == Layer::Type::Object) {
            const auto& objects = layer->getLayerAs<ObjectGroup>().getObjects();
            std::cout << "Found " << objects.size() << " objects in layer" << std::endl;
            for (const auto& object : objects)
            {
                int x = (int)object.getPosition().x / tiled_map.getTileSize().x;
                int y = (int)object.getPosition().y / tiled_map.getTileSize().y;
                Vector2D pos;
                pos.setX(x);
                pos.setY(y);

                std::cout << "Object " << object.getName() << ", in posX = " << x << " , posY = " << y << std::endl;

                Entity* ent = room->createEntity(pos, object.getName(), object.getClass(), object.getProperties());
                if (ent != nullptr) {
                    walkableTiles[x][y]->objInTile = ent;
                    std::cout << "Anadida entidad a tile: " << object.getName() << std::endl;
/*
                    if (prop.getName() == "TexPath") {
                        texPath = prop.getStringValue();
                    }

                    //Abstraerlo para que se llame a metodo de Crear Entidades y que de ahi se gestione que es lo que se crea
                    if (prop.getName() == "isPlayer") {
                        if (prop.getBoolValue()) {
                            Vector2D pos;
                            pos.setX((int)object.getPosition().x / tiled_map.getTileSize().x);
                            pos.setY((int)object.getPosition().y / tiled_map.getTileSize().y);
                            room->createPlayer(texPath, pos, cols, rows);
                        }
                    }*/
                }

                if (!object.getTilesetName().empty())
                {
                    std::cout << "Object uses template tile set " << object.getTilesetName() << "\n";
                }
            }
        }
        const auto& properties = layer->getProperties();
        //std::cout << properties.size() << " Layer Properties:" << std::endl;
        for (const auto& prop : properties)
        {
            std::cout << "Found property: " << prop.getName() << std::endl;
            std::cout << "Type: " << int(prop.getType()) << std::endl;
        }
    }
}

void MapManager::draw(SDL_Renderer* ren) {
    //Dibujamos cada tile
    Vector2D cameraPos = Camera::instance()->getCameraMovement();
    for (int i = 0; i < tiles.size(); i++ ) {
        tiles[i].draw(ren, i, cameraPos);
    }
}

Vector2D MapManager::getMapSize()
{
    return Vector2D(cols, rows);
}

bool MapManager::isTileWalkable(Vector2D pos)
{
    if (pos.getX() < walkableTiles.size() && pos.getY() < walkableTiles[0].size()
        && pos.getX() >= 0 && pos.getY() >= 0) 
        return walkableTiles[pos.getX()][pos.getY()] != nullptr;
    else
        return false;
}

int MapManager::getTileSize()
{
    return tile_width*MAP_MULT; //width y height son iguales
}

//por ahora esto no es del todo funcional. usar con precaución
tile* MapManager::getTile(Vector2D v)
{
    return walkableTiles[v.getX()][v.getY()];
}

void MapManager::move(std::string direction) {

}