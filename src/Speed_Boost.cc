#include <SFML/Graphics.hpp>

#include "Speed_Boost.h"
#include "Power_Up.h"
#include "Resource_Manager.h"
Speed_Boost::Speed_Boost(sf::Vector2f pos)
    : Power_Up(), power{Resource_Manager::get_texture_speedboost()}, time{200}, pos{pos}
{
}

void Speed_Boost::update()
{
    lifetime--;
    if(lifetime < 0)
        expired = true;
}

void Speed_Boost::render(sf::RenderTarget & target)
{
    power.setPosition(pos);
    target.draw(power);
}