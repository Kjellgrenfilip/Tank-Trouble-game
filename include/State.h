#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

class State
{
public:
    virtual ~State() = default; 
    virtual void update() = 0;
    virtual void event_handler(sf::Event event) = 0;
    virtual void render(sf::RenderTarget & target) = 0;
    virtual int get_next_state() = 0;
};

#endif