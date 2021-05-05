#ifndef MAP_HPP
#define MAP_HPP
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <fstream>
#include <vector>


class Game_Map
{
private:
    std::vector<Tile> tiles{};
    std::string random_map();
    void generate();
public:
    Game_Map();
    void render(sf::RenderTarget &window);


};
#endif 