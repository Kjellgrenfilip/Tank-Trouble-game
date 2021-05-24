#include "Constants.h"
#include "Game_State.h"
//#include "Game_Map.h"
#include "Resource_Manager.h"
#include "Collision_Handler.h"
#include <SFML/Graphics.hpp>
#include <iostream>
Game_State::Game_State()
    :   paus{false}, endgame{false}, destroyed_sound{}, players{}, game_map{Resource_Manager::get_game_map()}, 
        collision_handler{}
{
	players.push_back(Player(1, sf::Vector2f{screen_width/10, screen_height/10}));
	players.push_back(Player(2, sf::Vector2f{(screen_width/10)*9, (screen_height/10)*9}));
    
    destroyed_sound.setBuffer(Resource_Manager::get_soundbuffer_destroyed());
}

void Game_State::event_handler(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Escape)
        {
            paus = true;
        }
    }
}

void Game_State::game_event_handler(sf::Event event)
{
    players[0].event_handler(event);
    players[1].event_handler(event);
}

void Game_State::update()
{
    collision_handler.bullet_wall_collision(players);
    collision_handler.tank_wall_collision(players);
    collision_handler.tank_tank_collision(players);
    collision_handler.tank_powerup_collision(players);
    collision_handler.bullet_tank_collision(players.at(0), players.at(1));
    collision_handler.bullet_tank_collision(players.at(1), players.at(0));

    players[0].update();
    players[1].update();
    if (players[0].is_destroyed())
	{
		destroyed_sound.play();
		winner = 2;
		endgame = true;
	}
	else if(players[1].is_destroyed())
	{
		destroyed_sound.play();
		winner = 1;
		endgame = true;
	}
    game_map.update();
}

void Game_State::render(sf::RenderTarget & target)
{
    game_map.render(target);
    players[0].render(target);
    players[1].render(target);
	
}

int Game_State::get_next_state()
{
    if(endgame)
    {
        endgame = false;
        return WIN_STATE;
    }
    else if(paus)
    {
        paus = false;
        return PAUSE_STATE;
    }
    else
    {
        return GAME_STATE;
    }
}

int Game_State::get_winner()
{
	if (winner == 1)
	{
		winner = 0;
		return 1;
	}
	else if (winner == 2)
	{
		winner = 0;
		return 2;
	}
  return 0;
}







