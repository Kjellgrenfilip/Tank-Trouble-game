#include "GameMap_Manager.h"
#include "Game_Map.h"

void GameMap_Manager::get_texture()
{
    if(!floor_texture.loadFromFile("resources/textures/rusty_texture.png"))
    {
        throw std::invalid_argument("cannot open floor_texture");
    }
    if(!wall_texture.loadFromFile("resources/textures/rusty_wall.png"))
    {
        throw std::invalid_argument("cannot open wall_texture");
    }
}

sf::Texture& GameMap_Manager::get_texture_floor()
{
    if(floor_texture.getSize() == sf::Vector2u(0,0))
    {
        get_texture();
    }
    return floor_texture;
}

sf::Texture& GameMap_Manager::get_texture_wall()
{
    if(wall_texture.getSize() == sf::Vector2u(0,0))
    {
        get_texture();
    }
    return wall_texture;
}

void GameMap_Manager::load_game_map(int mapID)
{
    game_map.generate(mapID);
}

Game_Map& GameMap_Manager::get_game_map()
{
    return game_map;
}