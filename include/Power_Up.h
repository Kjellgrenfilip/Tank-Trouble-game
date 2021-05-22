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
    virtual sf::Sprite& get_sprite() = 0;
    
    bool is_expired(){return expired;};
    bool is_active_on_player(){return active_on_player;};
    void set_active_on_player(bool x){active_on_player = x;};
    int get_active_time(){return active_timer;};
    void set_active_time(int x){active_timer = x;};
    void dec_active_timer(){--active_timer;};
protected:
    bool expired;
    int lifetime;
    bool active_on_player{false};
    int active_timer{};
};

#endif