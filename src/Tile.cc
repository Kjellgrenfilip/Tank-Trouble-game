
#include<SFML/Graphics.hpp>
#include "Tile.h"
#include <string>
Tile::Tile(sf::Vector2f const& pos,bool pas,std::string const& name)
{
    this->position = pos;
    this->passable = pas;
    this->name = name;
}

sf::Vector2f Tile::get_position()
{
    return position;
}

std::string Tile::get_name()
{
    return name;
}

void Tile::setPowerUp(std::shared_ptr<Power_Up> p)
{
    available_power = p;
}