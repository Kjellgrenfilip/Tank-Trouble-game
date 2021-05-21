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
        bounce_sound{}, powerup_sound{}
{
    bounce_sound.setBuffer(Resource_Manager::get_soundbuffer_bounce());
    powerup_sound.setBuffer(Resource_Manager::get_soundbuffer_powerup());
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
    axes.push_back(sf::Vector2f(obj2.points[0].x - obj2.points[1].x,obj2.points[0].y - obj2.points[1].y));

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
            if(!tile.passable && check_collision(player.getPlayerSprite(), tile.get_sprite()))
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
        for(auto & bullet : player.get_bullets())
        {   
            for(auto & tile : game_map.get_tiles())
            {
                sf::FloatRect tile_rect{tile.get_position(), sf::Vector2f{gridsize_x, gridsize_y}};
                if(!tile.passable && bullet.getBounds().intersects(tile_rect))
                {
                    //Testa ändra hastigheten på kulan i x- och y-led för att se om den kommer befinna sig i samma tile
                    sf::FloatRect try_x{bullet.getBounds()};
                    try_x.left = try_x.left - bullet.get_velocity().x;
                    try_x.top = try_x.top + bullet.get_velocity().y;
                    sf::FloatRect try_y{bullet.getBounds()};
                    try_y.left = try_y.left + 2.0*bullet.get_velocity().x;
                    try_y.top = try_y.top - 2.0*bullet.get_velocity().y;

                    if(!try_x.intersects(tile_rect))
                    {
                        bullet.reverse_x();
                    }
                    else if(!try_y.intersects(tile_rect))
                    {
                        bullet.reverse_y();
                    }
                    else
                    {
                        bullet.reverse_x();
                        bullet.reverse_y();
                    }
					if (bullet.lifetime > 1)
						{
						bounce_sound.play();
						}	
                    bullet.lifetime--;
                    break;
                }
            }
        }
        for(auto & rocket : player.get_rockets())
        {
            for(auto & tile : game_map.get_tiles())
            {
                sf::FloatRect tile_rect{tile.get_position(), sf::Vector2f{gridsize_x, gridsize_y}};
                if(!tile.passable && rocket.getBounds().intersects(tile_rect))
                {
                    rocket.lifetime = 0;
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
