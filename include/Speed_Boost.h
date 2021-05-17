#include <SFML/Graphics.hpp>

#include "Power_Up.h"

class Speed_Boost : public Power_Up
{
public:
    Speed_Boost(sf::Vector2f pos);
    
    sf::Sprite power;

    int time;

    sf::Vector2f pos;
    
    virtual void update() override;
    virtual void render(sf::RenderTarget & target) override;
    sf::FloatRect get_hitbox();
};