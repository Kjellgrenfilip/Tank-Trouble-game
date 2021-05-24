#include<SFML/Graphics.hpp>
#include "Tile.h"
#include "GameMap_Manager.h"
#include <string>

Tile::Tile(sf::Vector2f const& pos, bool pas, sf::Texture & t)
    : position{pos}, tile{t}, passable{pas}, available_power{false}
{
    tile.setScale(0.2, 0.2);
    tile.setPosition(pos);
}

void Tile::render(sf::RenderTarget & target)
{
    target.draw(tile);
}

sf::Vector2f Tile::get_position()
{
    return position;
}

void Tile::setPowerUp()
{
    set_available_power(true);
}

sf::Sprite& Tile::get_sprite()
{
    return tile;
}

bool Tile::is_passable()
{
    return passable;
}

bool Tile::power_is_available()
{
    return available_power;
}

void Tile::set_available_power(bool new_val)
{
    available_power = new_val;
}