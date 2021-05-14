#include "Shotgun.h"
#include "Resource_Manager.h"
Shotgun::Shotgun(sf::Vector2f pos)
    : power{Resource_Manager::get_texture_shotgun()}, time{200}, pos{pos}
{
}

void Shotgun::render(sf::RenderTarget & target)
{
    power.setPosition(pos);
    target.draw(power);
}