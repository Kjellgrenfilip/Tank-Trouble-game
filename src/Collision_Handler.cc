#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Game_Map.h"
#include "Resource_Manager.h"
#include "Player.h"
#include "Bullet.h"

#include "Constants.h"

#include "Collision_Handler.h"

Collision_Handler::Collision_Handler()
    :   game_map{Resource_Manager::get_game_map()}, obj1pos{}, obj2pos{}, 
        bounce_sound{}, powerup_sound{}, hit_sound{}
{
    bounce_sound.setBuffer(Resource_Manager::get_soundbuffer_bounce());
    powerup_sound.setBuffer(Resource_Manager::get_soundbuffer_powerup());
    hit_sound.setBuffer(Resource_Manager::get_soundbuffer_hit());
}

Collision_Handler::Collision_Box::Collision_Box(sf::Sprite const& sprite)
    : points{}, transform{sprite.getTransform()}, boundery{sprite.getTextureRect()}
{
    transform_points();
}

void Collision_Handler::Collision_Box::transform_points()
{
    points.push_back(transform.transformPoint(0, 0));                                 // Upper left point
    points.push_back(transform.transformPoint(boundery.width, 0));                    // Upper right point
    points.push_back(transform.transformPoint(boundery.width, boundery.height));      // Lower right point
    points.push_back(transform.transformPoint(0, boundery.height));                   // Lower Left point
}

void Collision_Handler::Collision_Box::project(sf::Vector2f const& axis, float & min, float & max)
{
    sf::Vector2f projection;
    projection.x = ((points.at(0).x * axis.x + points.at(0).y * axis.y) / (axis.x * axis.x + axis.y * axis.y)) * axis.x;  // Projektionsformel för linje
    projection.y = ((points.at(0).x * axis.x + points.at(0).y * axis.y) / (axis.x * axis.x + axis.y * axis.y)) * axis.y;  // Projektionsformel för linje    
    min = (projection.x * axis.x + projection.y * axis.y);                                                          // Projektionsformel för linje
    max = min;
    for(size_t i = 1; i < points.size(); i++)
    {
        projection.x = ((points.at(i).x * axis.x + points.at(i).y * axis.y) / (axis.x * axis.x + axis.y * axis.y)) * axis.x;  // Projektionsformel för linje
        projection.y = ((points.at(i).x * axis.x + points.at(i).y * axis.y) / (axis.x * axis.x + axis.y * axis.y)) * axis.y;  // Projektionsformel för linje
        float dot_product = (projection.x * axis.x + projection.y * axis.y);                                            // Projektionsformel för linje
        if(dot_product<min)     // Spara undan max/min värde 
        {
            min = dot_product;
        }
        if(dot_product>max)
        {
            max = dot_product;
        }
    }
}

bool Collision_Handler::check_collision(sf::Sprite const& object1, sf::Sprite const& object2)
{
    obj1pos = object1.getPosition();
    obj2pos = object2.getPosition();
    float x = obj1pos.x - obj2pos.x;
    float y = obj1pos.y - obj2pos.y;
    if(sqrt(pow(x, 2) + pow(y, 2)) > 100) // Kolla om det fysiskt är möjligt för kollision
    {                                     
        return false;
    }
    
    Collision_Box obj1(object1);
    Collision_Box obj2(object2);

    std::vector<sf::Vector2f> axes;
    axes.push_back(sf::Vector2f(obj1.points[1].x - obj1.points[0].x, obj1.points[1].y - obj1.points[0].y));
    axes.push_back(sf::Vector2f(obj1.points[1].x - obj1.points[2].x, obj1.points[1].y - obj1.points[2].y));
    axes.push_back(sf::Vector2f(obj2.points[0].x - obj2.points[3].x, obj2.points[0].y - obj2.points[3].y));
    axes.push_back(sf::Vector2f(obj2.points[0].x - obj2.points[1].x, obj2.points[0].y - obj2.points[1].y));

    for(size_t i{0}; i < axes.size(); i++)
    {
        float min1, max1, min2, max2;
        obj1.project(axes.at(i), min1, max1);
        obj2.project(axes.at(i), min2, max2);
        if(!((min2 <= max1) && (max2 >= min1)))     // Separating axis theorem
        {
            return false;
        }
    }
    return true;
}

void Collision_Handler::tank_wall_collision(std::vector<Player> & players)
{
    for(auto & player : players)
    {
        for(auto & tile : game_map.get_tiles())
        {
            if(!tile.is_passable() && check_collision(player.getPlayerSprite(), tile.get_sprite()))
            {
                player.set_tank_pos(player.get_old_position());
            }
        }
    }
}

void Collision_Handler::bullet_wall_collision(std::vector<Player> & players)
{
    for(auto & player : players)
    {
        for(auto projectile : player.get_projectiles())
        {   
            for(auto & tile : game_map.get_tiles())
            {
                if(!tile.is_passable() && check_collision(projectile->get_sprite(), tile.get_sprite()))
                {
                    if(dynamic_cast<Rocket_Projectile*>(projectile) != nullptr)
                    {
                        projectile->lifetime = 0;
                        break;
                    }

                    sf::Sprite try_x{projectile->get_sprite()};
                    try_x.setPosition(try_x.getPosition().x - projectile->get_velocity().x, 
                                      try_x.getPosition().y + projectile->get_velocity().y);
                    sf::Sprite try_y{projectile->get_sprite()};
                    try_y.setPosition(try_y.getPosition().x + projectile->get_velocity().x, 
                                      try_y.getPosition().y - projectile->get_velocity().y);

                    if(!check_collision(try_x, tile.get_sprite()))
                    {
                        projectile->reverse_x();
                    }
                    else if(!check_collision(try_y, tile.get_sprite()))
                    {
                        projectile->reverse_y();
                    }
                    else
                    {
                        projectile->reverse_x();
                        projectile->reverse_y();
                    }
					if (projectile->lifetime > 1)
					{
						bounce_sound.play();
					}	
                    projectile->lifetime--;
                    break;
                }
            }
        }
    }
}

void Collision_Handler::tank_tank_collision(std::vector<Player> & players)
{
    if(check_collision(players.at(0).getPlayerSprite(), players.at(1).getPlayerSprite()))
    {
        players.at(0).set_tank_pos(players.at(0).get_old_position());
        players.at(1).set_tank_pos(players.at(1).get_old_position());
    }
}

void Collision_Handler::tank_powerup_collision(std::vector<Player> & players)
{
    for(auto & player : players)
    {
        for(size_t i{}; i < game_map.get_powerups().size(); i++)
        {
            if(check_collision(player.getPlayerSprite(), game_map.get_powerups().at(i)->get_sprite()))
            {
                if(player.set_power_up(game_map.get_powerups().at(i)))   //Returnerar false om spelaren redan har en power up
                {
                    game_map.get_powerups().at(i).reset();
                    game_map.get_powerups().erase(game_map.get_powerups().begin() + i);
					powerup_sound.play();
                } 
            }
        }
    }
}

void Collision_Handler::bullet_tank_collision(Player & player1, Player & player2)
{
    for (auto & projectile : player1.get_projectiles())
    {
        if (check_collision(projectile->get_sprite(), player2.getPlayerSprite()))
        {   
            //Kolla om spelaren har aktiv sköld
            if(dynamic_cast<Shield*>(player2.get_mypower().get()) != nullptr && player2.get_mypower()->is_active_on_player())
            {
                std::cout << "pang" << std::endl;
                player2.reset_power_up();
                //player2.get_mypower().reset();
            }
            else if(dynamic_cast<Bullet*>(projectile) != nullptr)
            {
                player2.set_hp(player2.get_hp()-1);
            }
            else if(dynamic_cast<Rocket_Projectile*>(projectile) != nullptr)
            {
                player2.set_hp(0);
            }
			hit_sound.play();
            projectile->lifetime = 0;
        }

        if(projectile->lifetime <= 0)
        {
            delete projectile;
            projectile = nullptr;
        }
    }
    player1.get_projectiles().erase(remove(begin(player1.get_projectiles()), end(player1.get_projectiles()), nullptr), end(player1.get_projectiles()));
}
