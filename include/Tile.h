#ifndef TILE_HPP
#define TILE_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "Power_Up.h"

class Tile
{
private:
    sf::Vector2f position{};
    std::string name{};
public:
    Tile(sf::Vector2f const& pos,bool pas,std::string const& name);
    sf::Vector2f get_position();
    std::string get_name();

    void setPowerUp();

    bool passable{};
    bool available_power{false};
};
#endif 