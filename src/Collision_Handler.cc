#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "Collision_Handler.h"

Collision_Handler::Collision_Handler()
    : obj1pos{}, obj2pos{}
{
}

Collision_Handler::Collision_Box::Collision_Box(sf::Sprite const& sprite)
    : transform{sprite.getTransform()}, boundery{sprite.getTextureRect()}
{
    transform_points();
}

void Collision_Handler::Collision_Box::transform_points()
{
    points[0] = transform.transformPoint(0, 0);                             // Upper left point
    points[1] = transform.transformPoint(boundery.width, 0);                    // Upper right point
    points[2] = transform.transformPoint(boundery.width, boundery.height);          // Lower right point
    points[3] = transform.transformPoint(0, boundery.height);                   // Lower Left point
}

void Collision_Handler::Collision_Box::project(sf::Vector2f const& axis, float & min, float & max)
{
    sf::Vector2f projection;
    projection.x = ((points[0].x * axis.x + points[0].y * axis.y) / (axis.x * axis.x + axis.y * axis.y)) * axis.x;  // Projektionsformel för linje
    projection.y = ((points[0].x * axis.x + points[0].y * axis.y) / (axis.x * axis.x + axis.y * axis.y)) * axis.y;  // Projektionsformel för linje    
    min = (projection.x * axis.x + projection.y * axis.y);                                                          // Projektionsformel för linje
    max = min;
    for(int j = 1; j < 4; j++)
    {
        projection.x = ((points[j].x * axis.x + points[j].y * axis.y) / (axis.x * axis.x + axis.y * axis.y)) * axis.x;  // Projektionsformel för linje
        projection.y = ((points[j].x * axis.x + points[j].y * axis.y) / (axis.x * axis.x + axis.y * axis.y)) * axis.y;  // Projektionsformel för linje
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
    if(sqrt(pow(x, 2) + pow(y, 2)) > 100)
    {
        //std::cout << "No collision, distance is X: " << x << " Y: "<< y << std::endl;
        return false;
    }
    
    Collision_Box obj1(object1);
    Collision_Box obj2(object2);

    sf::Vector2f axes[4];
    axes[0] = sf::Vector2f(obj1.points[1].x - obj1.points[0].x, obj1.points[1].y - obj1.points[0].y);
    axes[1] = sf::Vector2f(obj1.points[1].x - obj1.points[2].x, obj1.points[1].y - obj1.points[2].y);
    axes[2] = sf::Vector2f(obj2.points[0].x - obj2.points[3].x, obj2.points[0].y - obj2.points[3].y);
    axes[3] = sf::Vector2f(obj2.points[0].x - obj2.points[1].x,obj2.points[0].y - obj2.points[1].y);

    for(int i{0}; i < 4; i++)
    {
        float min1, max1, min2, max2;
        obj1.project(axes[i], min1, max1);
        obj2.project(axes[i], min2, max2);
        if(!((min2 <= max1) && (max2 >= min1))) // Separating axis theorem
        {
            return false;
        }
    }
    return true;
}

