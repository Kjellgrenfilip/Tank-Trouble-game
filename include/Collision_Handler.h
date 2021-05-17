#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class CollisionBox
{
public:
    CollisionBox(sf::Sprite const& object)   
    {
        sf::Transform transform = object.getTransform();
        sf::IntRect bounds = object.getTextureRect();
        points[0] = transform.transformPoint(0.f, 0.f);                             // Upper left point
        points[1] = transform.transformPoint(bounds.width, 0.f);                    // Upper right point
        points[2] = transform.transformPoint(bounds.width, bounds.height);          // Lower right point
        points[3] = transform.transformPoint(0.f, bounds.height);                   // Lower Left point
    }
    sf::Vector2f points[4];

    void project(sf::Vector2f const& Axis, float & min, float & max)
    {
        sf::Vector2f projection;
        projection.x = ((points[0].x * Axis.x + points[0].y * Axis.y) / (Axis.x * Axis.x + Axis.y * Axis.y)) * Axis.x;  
        projection.y = ((points[0].x * Axis.x + points[0].y * Axis.y) / (Axis.x * Axis.x + Axis.y * Axis.y)) * Axis.y;
        min = (projection.x * Axis.x + projection.y * Axis.y);
        max = min;
        for(int j = 1; j < 4; j++)
        {
            projection.x = ((points[j].x * Axis.x + points[j].y * Axis.y) / (Axis.x * Axis.x + Axis.y * Axis.y)) * Axis.x;  
            projection.y = ((points[j].x * Axis.x + points[j].y * Axis.y) / (Axis.x * Axis.x + Axis.y * Axis.y)) * Axis.y;
            float dot_product = (projection.x * Axis.x + projection.y * Axis.y);
            if(dot_product<min)
                min = dot_product;
            if(dot_product>max)
                max = dot_product;
        }
    }
};

bool check_collision(sf::Sprite const& object1, sf::Sprite const& object2)
{
    sf::Vector2f obj1pos = object1.getPosition();
    sf::Vector2f obj2pos = object2.getPosition();
    float x = obj1pos.x - obj2pos.x;
    float y = obj1pos.y - obj2pos.y;
    if(sqrt(pow(x, 2) + pow(y, 2)) > 100)
    {
        //std::cout << "No collision, distance is X: " << x << " Y: "<< y << std::endl;
        return false;
    }
    
    CollisionBox obj1(object1);
    CollisionBox obj2(object2);

    sf::Vector2f Axes[4] =
    {
        sf::Vector2f(   obj1.points[1].x - obj1.points[0].x, 
                        obj1.points[1].y - obj1.points[0].y),
        sf::Vector2f(   obj1.points[1].x - obj1.points[2].x, 
                        obj1.points[1].y - obj1.points[2].y),
        sf::Vector2f(   obj2.points[0].x - obj2.points[3].x, 
                        obj2.points[0].y - obj2.points[3].y),
        sf::Vector2f(   obj2.points[0].x - obj2.points[1].x, 
                        obj2.points[0].y - obj2.points[1].y),
    };
    for(int i{0}; i < 4; i++)
    {
        float min1, max1, min2, max2;
        obj1.project(Axes[i], min1, max1);
        obj2.project(Axes[i], min2, max2);
        if(!((min2 <= max1) && (max2 >= min1)))
        {
            return false;
        }
    }
    return true;
}

#endif
