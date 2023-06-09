#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>

#include "State.h"
#include "Game_Map.h"
#include "Player.h"
#include "Collision_Handler.h"
#include "Bullet.h"

class Game_State : public State
{
public:
    Game_State();
    
    virtual void update() override;
    virtual void event_handler(sf::Event event) override;
    virtual void game_event_handler(sf::Event event) override;
    virtual void render(sf::RenderTarget & target) override;
    virtual int get_next_state() override;
    
    static int get_winner();
private:
    
    bool paus;
    bool endgame;
	
    sf::Sound destroyed_sound;
	
    static inline int winner;                //Static för att kunna komma åt inten i Win_State utan ett game_State object
	std::vector<Player> players;
    Game_Map & game_map;                    //Referens till game_map i GameMap_Manager
    Collision_Handler collision_handler;    //Sköter all kollision
};

#endif
