#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game_Map.h"
#include "Player.h"
#include "Resource_Manager.h"
class Game_State : public State
{
public:
    Game_State();
    
    virtual void update() override;
    virtual void event_handler(sf::Event event) override;
    virtual void game_event_handler(sf::Event event) override;
    virtual void render(sf::RenderTarget & target) override;
    virtual int get_next_state() override;

    void collision_handler();
    void tank_wall_collision_handler();
private:
    
    bool paus;
    bool endgame;

	std::vector<Player> players;
    Game_Map game_map;   // Döpte den till game_map för att 
                         // inte skapa förvirring med std::map
};

#endif
