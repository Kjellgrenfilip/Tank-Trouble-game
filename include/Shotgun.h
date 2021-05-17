#include <SFML/Graphics.hpp>

#include "Power_Up.h"

class Shotgun : public Power_Up
{
public:
    Shotgun(sf::Vector2f pos);
    
    sf::Sprite power;

    int time;

    sf::Vector2f pos;

    virtual void update() override;
    virtual void render(sf::RenderTarget & target) override;
    sf::Sprite& get_sprite();
};