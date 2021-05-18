#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game_Map.h"
#include "Player.h"
#include "Resource_Manager.h"
#include "Collision_Handler.h"
class Game_State : public State
{
public:
    Game_State();
    
    virtual void update() override;
    virtual void event_handler(sf::Event event) override;
    virtual void game_event_handler(sf::Event event) override;
    virtual void render(sf::RenderTarget & target) override;
    virtual int get_next_state() override;

    void bullet_wall_collision_handler();
    void tank_wall_collision_handler();
    void tank_tank_collision_handler();
    void tank_powerup_collision_handler();
    
    static int get_winner();
private:
    
    bool paus;
    bool endgame;

	static inline int winner;
	std::vector<Player> players;
    Game_Map game_map;   // Döpte den till game_map för att 
                         // inte skapa förvirring med std::map
    Collision_Handler collision_handler;
};

#endif
