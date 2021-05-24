#ifndef GAMEMAP_MANAGER_H
#define GAMEMAP_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdexcept>

#include "Game_Map.h"

class GameMap_Manager
{
private:
    static inline sf::Texture wall_texture;
    static inline sf::Texture floor_texture;
    static inline Game_Map game_map;
    
public:
    static sf::Texture& get_texture_wall();
    static sf::Texture& get_texture_floor();
    static void load_game_map(int mapID = 0);
    static void get_texture();
    static Game_Map& get_game_map();
};
#endif
