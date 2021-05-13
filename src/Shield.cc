#include <SFML/Graphics.hpp>
#include <iostream>

#include "Shield.h"
#include "Resource_Manager.h"

Shield::Shield(sf::Vector2f pos)
    : power{Resource_Manager::get_texture_shield()}, time{200}, pos{pos}
{
    power.setScale(1, 1);

    // std::cout << power.getGlobalBounds().width << ", " << power.getGlobalBounds().height << std::endl;
    // auto size {power.getGlobalBounds()};
    // power.setOrigin(size.width / 2, size.height / 2); 
}

void Shield::render(sf::RenderTarget & target)
{
    power.setPosition(pos);
    target.draw(power);
}