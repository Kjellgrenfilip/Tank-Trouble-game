#include "Power_Up.h"
#include "Resource_Manager.h"
// Power_Up::Power_Up()
//     : expired{false}, lifetime{600}
// {
// }
Power_Up::Power_Up(sf::Vector2f &pos,sf::Texture& power_up_texture)
    : expired{false}, lifetime{600}, power{power_up_texture}, pos{pos}
{
    //power.setTexture(power_up_texture);
}
void Power_Up::update()
{
    lifetime--;
    if(lifetime < 0)
        expired = true;
}

void Power_Up::render(sf::RenderTarget & target)
{
    power.setPosition(pos);
    target.draw(power);
}

sf::Sprite& Power_Up::get_sprite()
{
    return power;
}

Speed_Boost::Speed_Boost(sf::Vector2f pos)
    : Power_Up(pos,Resource_Manager::get_texture_speedboost())
{
}

Shotgun::Shotgun(sf::Vector2f pos)
    : Power_Up(pos,Resource_Manager::get_texture_shotgun())
{
}
Shield::Shield(sf::Vector2f pos)
    : Power_Up(pos,Resource_Manager::get_texture_shield())
{
}
Rocket::Rocket(sf::Vector2f pos)
    : Power_Up(pos,Resource_Manager::get_texture_rocket())
{
}