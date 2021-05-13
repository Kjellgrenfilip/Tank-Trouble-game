#include <SFML/Graphics.hpp>

#include "Power_Up.h"

class Speed_Boost : public Power_Up
{
public:
    Speed_Boost();
    
    sf::Sprite power;

    int time;

    virtual void render(sf::RenderTarget & target) override;
};