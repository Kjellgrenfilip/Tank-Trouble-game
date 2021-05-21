
#include<SFML/Graphics.hpp>
#include "Tile.h"
#include <string>
Tile::Tile(sf::Vector2f const& pos, bool pas, sf::Texture & tile, std::string const& name)
    : position{pos}, name{name}, tile{tile}, passable{pas}
{
    this->tile.setScale(0.2, 0.2);
    this->tile.setPosition(pos);
}

sf::Vector2f Tile::get_position()
{
    return position;
}

void Tile::setPowerUp()
{
    available_power = true;
}

sf::Sprite & Tile::get_sprite()
{
    return tile;
}