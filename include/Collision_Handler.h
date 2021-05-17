#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class Collision_Handler
{
public:
    Collision_Handler();

    bool check_collision(sf::Sprite const& object1, sf::Sprite const& object2);

private:

    class Collision_Box
    {
    public:
        Collision_Box(sf::Sprite const& sprite);

        void project(sf::Vector2f const& axis, float & min, float & max);

        sf::Vector2f points[4];

    private:    

        void transform_points();

        sf::Transform transform;
        sf::IntRect boundery;
    };

    sf::Vector2f obj1pos;
    sf::Vector2f obj2pos;

    sf::Vector2f axes[4];

};
#endif
