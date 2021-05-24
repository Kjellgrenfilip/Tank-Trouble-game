#include "Bullet.h"
#include "Resource_Manager.h"
#include <cmath>

Projectile::Projectile(float rot, int life, sf::Texture & texture) 
    :   lifetime{life}, 
        velocity{   static_cast<float>(5*std::cos(rot*M_PI/180.0)), 
                    static_cast<float>(5*std::sin(rot*M_PI/180.0))},
        sprite{texture}
{
    auto size = texture.getSize();
    sprite.setOrigin(size.x / 2, size.y / 2);
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

sf::Sprite & Projectile::get_sprite()
{
    return sprite;
}

void Projectile::update()
{
    sprite.move(velocity);
}

void Projectile::render(sf::RenderTarget &target)
{
    target.draw(sprite);
}

Bullet::Bullet(sf::Vector2f const & pos, float rot) 
    :   Projectile{rot, 4, Resource_Manager<sf::Texture>::get_file("resources/textures/bullet.png")}
{
    sprite.setPosition(pos + velocity*static_cast<float>(6.0));
    sprite.setScale(0.1, 0.1);
}

Rocket_Projectile::Rocket_Projectile(sf::Vector2f const & pos, float rot) 
    :   Projectile{rot, 1, Resource_Manager<sf::Texture>::get_file("resources/textures/rocket_projectile.png")}
{
    sprite.setPosition(pos + velocity*static_cast<float>(6.0));
    sprite.setRotation(rot + 45.0);
}
