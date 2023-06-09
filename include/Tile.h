#ifndef TILE_HPP
#define TILE_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "Power_Up.h"

class Tile
{
private:
    sf::Vector2f position;
    sf::Sprite tile;
    bool passable;    
    bool available_power;
public:
    Tile(sf::Vector2f const& pos, bool pas, sf::Texture & tile);
    sf::Vector2f get_position();
    sf::Sprite& get_sprite(); 
    
    bool is_passable();
    bool power_is_available();
    
    void setPowerUp();
    void set_available_power(bool new_val);
    void render(sf::RenderTarget & target);
    
};

#endif 