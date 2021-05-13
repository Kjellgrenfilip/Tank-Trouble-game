#include <SFML/Graphics.hpp>

#include "Power_Up.h"

class Shotgun : public Power_Up
{
public:
    Shotgun();
    
    sf::Sprite power;

    virtual void render(sf::RenderTarget & target) override;
};