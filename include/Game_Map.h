#ifndef MAP_HPP
#define MAP_HPP
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Power_Up.h"
#include <memory>

#include <fstream>
#include <vector>
#include <memory>

class Game_Map
{
private:
    std::string random_map(int mapID = 0);  //returnerar filväg till en karta, slumpas om mapID = 0

    std::vector<std::shared_ptr<Power_Up>> powerups; 
    std::vector<std::unique_ptr<Tile>> tiles;
public:
    Game_Map();

    void generate(int mapID = 0);           //skapar kartan
    void render(sf::RenderTarget &window);  //ritar upp kartan och power_ups på kartan
    void update();                          //updaterar puwer_ups på kartan

    std::vector<std::unique_ptr<Tile>>& get_tiles();
    std::vector<std::shared_ptr<Power_Up>>& get_powerups();
    
};
#endif 