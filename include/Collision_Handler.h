#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

class Collision_Handler
{
public:
    Collision_Handler();

    bool check_collision(sf::Sprite const& object1, sf::Sprite const& object2);
    void tank_wall_collision(std::vector<Player> & players);
    void bullet_wall_collision(std::vector<Player> & players);
    void tank_tank_collision(std::vector<Player> & players);
    void tank_powerup_collision(std::vector<Player> & players);

private:
    class Collision_Box
    {
    public:
        Collision_Box(sf::Sprite const& sprite);

        void project(sf::Vector2f const& axis, float & min, float & max);

        std::vector<sf::Vector2f> points;

    private:    
        void transform_points();

        sf::Transform transform;
        sf::IntRect boundery;
    };

    Game_Map & game_map;

    sf::Vector2f obj1pos;
    sf::Vector2f obj2pos;

    sf::Sound bounce_sound;
    sf::Sound powerup_sound;
};
#endif
