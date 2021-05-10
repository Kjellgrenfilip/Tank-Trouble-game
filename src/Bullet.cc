#include "Bullet.h"
#include <cmath>

Bullet::Bullet(sf::Vector2f pos, float rot) : lifetime{3}, velocity{ static_cast<float>(3*std::cos(rot*M_PI/180.0)), static_cast<float>(3*std::sin(rot*M_PI/180.0))}, sprite{5.0}
{
    sprite.setPosition(pos + velocity*static_cast<float>(10.0));
    sprite.setOrigin (5, 5);
    sprite.setFillColor(sf::Color(120, 120, 120));
}

void Bullet::update()
{
    sprite.move(velocity);
}

void Bullet::render(sf::RenderTarget &target)
{
    target.draw(sprite);
}

sf::FloatRect Bullet::getBounds()
{
    return sprite.getGlobalBounds();
}

void Bullet::reverse_x()
{
    velocity.x = velocity.x * (-1.0);
}

void Bullet::reverse_y()
{
    velocity.y = velocity.y * (-1.0);
}