#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>
class Power_Up
{
public:
    Power_Up();

    virtual ~Power_Up() = default; 
    Power_Up(sf::Vector2f &pos,sf::Texture& power_up_texture);
    void update();
    void render(sf::RenderTarget & target); 
    sf::Sprite& get_sprite();
    
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
    sf::Sprite power;
    int time;
    sf::Vector2f pos;
};

#endif