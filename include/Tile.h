#ifndef TILE_HPP
#define TILE_HPP
#include <SFML/Graphics.hpp>
#include <string>
class Tile
{
private:
    sf::Vector2f position{};
    bool passable{};
    std::string name{};
public:
    Tile(sf::Vector2f const& pos,bool pas,std::string const& name);
    sf::Vector2f get_position();
    std::string get_name();
};
#endif 