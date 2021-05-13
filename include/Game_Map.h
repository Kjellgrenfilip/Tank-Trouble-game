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
    std::vector<Tile> tiles{};
    std::string random_map();
    void generate();
public:
    Game_Map();
    void render(sf::RenderTarget &window);
    void update();

    std::vector<std::shared_ptr<Power_Up>> power_ups; 


};
#endif 