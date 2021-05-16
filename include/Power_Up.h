#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>

class Power_Up
{
public:
    Power_Up();

    virtual ~Power_Up() = default; 
    //virtual Power_up(sf::Vector2f pos) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderTarget & target) = 0; 

    bool expired;

protected:
    int lifetime;
};

#endif