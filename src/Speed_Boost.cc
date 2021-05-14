#include <SFML/Graphics.hpp>

#include "Speed_Boost.h"
#include "Resource_Manager.h"
Speed_Boost::Speed_Boost(sf::Vector2f pos)
    : power{Resource_Manager::get_texture_speedboost()}, time{200}, pos{pos}
{
}

void Speed_Boost::render(sf::RenderTarget & target)
{
    power.setPosition(pos);
    target.draw(power);
}