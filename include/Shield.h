#ifndef SHEILD_H
#define SHEILD_H

#include <SFML/Graphics.hpp>

#include "Power_Up.h"

class Shield : public Power_Up
{
public:
    Shield(sf::Vector2f pos);
    // virtual void update() override;
    // virtual void render(sf::RenderTarget & target) override;
    // sf::Sprite& get_sprite();
private:
    // sf::Sprite power;
    // int time;
    // sf::Vector2f pos;
};

#endif