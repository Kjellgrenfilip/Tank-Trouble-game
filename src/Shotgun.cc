#include "Shotgun.h"
#include "Power_Up.h"
#include "Resource_Manager.h"
Shotgun::Shotgun(sf::Vector2f pos)
    : Power_Up(), power{Resource_Manager::get_texture_shotgun()}, time{200}, pos{pos}
{
}

void Shotgun::update()
{
    lifetime--;
    if(lifetime < 0)
        expired = true;
}

void Shotgun::render(sf::RenderTarget & target)
{
    power.setPosition(pos);
    target.draw(power);
}