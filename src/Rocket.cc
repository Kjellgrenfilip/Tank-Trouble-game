#include "Rocket.h"
#include "Power_Up.h"
#include "Resource_Manager.h"

Rocket::Rocket(sf::Vector2f pos)
    : Power_Up(pos,Resource_Manager::get_texture_rocket())//, power{Resource_Manager::get_texture_rocket()}, time{200}, pos{pos}
{
}

// void Rocket::update()
// {
//     lifetime--;
//     if(lifetime < 0)
//         expired = true;
// }

// void Rocket::render(sf::RenderTarget & target)
// {
//     power.setPosition(pos);
//     target.draw(power);
// }

// sf::Sprite& Rocket::get_sprite()
// {
//     return power;
// }