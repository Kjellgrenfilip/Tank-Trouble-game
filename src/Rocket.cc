#include "Rocket.h"
#include "Resource_Manager.h"

Rocket::Rocket(sf::Vector2f pos)
    : power{Resource_Manager::get_texture_rocket()}, time{200}, pos{pos}
{
}

void Rocket::render(sf::RenderTarget & target)
{
    power.setPosition(pos);
    target.draw(power);
}