#include <SFML/Graphics.hpp>

#include "Power_Up.h"

class Rocket : public Power_Up
{
public:
    Rocket();
    
    sf::Sprite power;

    virtual void render(sf::RenderTarget & target) override;
};