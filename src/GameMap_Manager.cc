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

sf::Texture& GameMap_Manager::get_texture_floor()   // Borde ligga/kunna hämtas i Resource_Manager men fungerar ej. Därav här.
{
    if(floor_texture.getSize() == sf::Vector2u(0,0))    // Kolla om texturen finns inladdad
    {
        get_texture();
    }
    return floor_texture;
}

sf::Texture& GameMap_Manager::get_texture_wall()    // Borde ligga/kunna hämtas i Resource_Manager men fungerar ej. Därav här.
{
    if(wall_texture.getSize() == sf::Vector2u(0,0))     // Kolla om texturen finns inladdad
    {
        get_texture();
    }
    return wall_texture;
}

void GameMap_Manager::load_game_map(int mapID) // Möjligör att ladda olika maps under "spelets" gång.
{
    game_map.generate(mapID);
}

Game_Map& GameMap_Manager::get_game_map()   // Hämta en referens till game_map
{
    return game_map;
}