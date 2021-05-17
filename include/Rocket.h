#include <SFML/Graphics.hpp>

#include "Power_Up.h"

class Rocket : public Power_Up
{
public:
    Rocket(sf::Vector2f pos);
    
    sf::Sprite power;

    int time;

    sf::Vector2f pos;

    virtual void update() override;
    virtual void render(sf::RenderTarget & target) override;
    sf::FloatRect get_hitbox();
};