#include "Bullet.h"
#include <cmath>

Projectile::Projectile(float rot, int life) 
    :   lifetime{life}, velocity{   static_cast<float>(5*std::cos(rot*M_PI/180.0)), 
                                    static_cast<float>(5*std::sin(rot*M_PI/180.0))}
{
}

sf::Vector2f & Projectile::get_velocity()
{
    return velocity;
}

void Projectile::reverse_x()
{
    velocity.x = velocity.x * (-1.0);
}

void Projectile::reverse_y()
{
    velocity.y = velocity.y * (-1.0);
}

Bullet::Bullet(sf::Vector2f const & pos, float rot) 
    :   Projectile{rot, 4}, sprite{5.0}
{
    sprite.setPosition(pos + velocity*static_cast<float>(6.0));
    sprite.setOrigin (5, 5);
    sprite.setFillColor(sf::Color(80, 80, 80));
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

Rocket_Projectile::Rocket_Projectile(sf::Vector2f const & pos, float rot) 
    :   Projectile{rot, 1}, sprite{Resource_Manager::get_texture_rocket_projectile()}
{
    sprite.setPosition(pos + velocity*static_cast<float>(6.0));
    sprite.setOrigin (10, 10);
    sprite.setRotation(rot + 45.0);
}

void Rocket_Projectile::update()
{
    sprite.move(velocity);
}

void Rocket_Projectile::render(sf::RenderTarget &target)
{
    target.draw(sprite);
}

sf::FloatRect Rocket_Projectile::getBounds()
{
    return sprite.getGlobalBounds();
}

