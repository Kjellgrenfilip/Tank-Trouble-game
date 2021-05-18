
#include<SFML/Graphics.hpp>
#include "Tile.h"
#include <string>
Tile::Tile(sf::Vector2f const& pos,bool pas,std::string const& name, sf::Texture & tile)
{
    this->position = pos;
    this->passable = pas;
    this->name = name;
    this->tile.setTexture(tile);
    this->tile.setScale(0.2, 0.2);
    this->tile.setPosition(pos);
}

sf::Vector2f Tile::get_position()
{
    return position;
}

std::string Tile::get_name()
{
    return name;
}

void Tile::setPowerUp()
{
    available_power = true;
}