#ifndef MAP_HPP
#define MAP_HPP
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Power_Up.h"

#include <fstream>
#include <vector>
#include <memory>

class Game_Map
{
private:
    std::string random_map(int mapID = 0);

    std::vector<std::shared_ptr<Power_Up>> powerups; 
    std::vector<Tile> tiles;
public:
    Game_Map();

    void generate(int mapID = 0);
    void render(sf::RenderTarget &window);
    void update();

    std::vector<Tile>& get_tiles();
    std::vector<std::shared_ptr<Power_Up>>& get_powerups();
    
};
#endif 