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
public:
    void generate(int mapID = 0);

    Game_Map();
    void render(sf::RenderTarget &window);
    void update();

    std::vector<std::shared_ptr<Power_Up>> power_ups; 
    std::vector<Tile> tiles{};

    bool loaded;
};
#endif 