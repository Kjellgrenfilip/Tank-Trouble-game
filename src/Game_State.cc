#include "Constants.h"
#include "Game_State.h"
//#include "Game_Map.h"
#include "Resource_Manager.h"
#include "Collision_Handler.h"
#include <SFML/Graphics.hpp>
#include <iostream>
Game_State::Game_State()
    :   paus{false}, endgame{false}, players{}, game_map{Resource_Manager::get_game_map()}, collision_handler{}   // Initiera game_map här   
{
    //man måste skriva klassen före get_texture
    //ändrade även width och height till det rätta värdena från constant
	players.push_back(Player(Resource_Manager::get_texture_player(1), sf::Vector2f{screen_width/10, screen_height/10}, 1, Resource_Manager::get_texture_heart(), Resource_Manager::get_texture_explosion()));
	players.push_back(Player(Resource_Manager::get_texture_player(2), sf::Vector2f{(screen_width/10)*9, (screen_height/10)*9}, 2, Resource_Manager::get_texture_heart(), Resource_Manager::get_texture_explosion() ));
    
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
    //players[0].event_handler(event);
    //players[1].event_handler(event);
}

void Game_State::game_event_handler(sf::Event event)
{
    
    players[0].event_handler(event);
    players[1].event_handler(event);
}

void Game_State::update()
{
    //game_map.update();
    bullet_wall_collision_handler();
    tank_wall_collision_handler();
    tank_tank_collision_handler();
    tank_powerup_collision_handler();
    players[0].update(players[1]);
    players[1].update(players[0]);
    if (players[0].is_destroyed())
		{
			winner = 2;
			endgame = true;
		}
	else if(players[1].is_destroyed())
		{
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

void Game_State::bullet_wall_collision_handler()
{
    for(auto & player: players)
    {
        for(auto & bullet : player.get_bullets())
        {   
            for(auto & tile : game_map.tiles)
            {
                sf::FloatRect tile_rect{tile.get_position(), sf::Vector2f{gridsize_x, gridsize_y}};
                if(!tile.passable && bullet.getBounds().intersects(tile_rect))
                {
                    //Testa ändra hastigheten på kulan i x- och y-led för att se om den kommer befinna sig i samma tile
                    sf::FloatRect try_x{bullet.getBounds()};
                    try_x.left = try_x.left - bullet.get_velocity().x;
                    try_x.top = try_x.top + bullet.get_velocity().y;
                    sf::FloatRect try_y{bullet.getBounds()};
                    try_y.left = try_y.left + 2.0*bullet.get_velocity().x;
                    try_y.top = try_y.top - 2.0*bullet.get_velocity().y;

                    if(!try_x.intersects(tile_rect))
                    {
                        bullet.reverse_x();
                    }
                    else if(!try_y.intersects(tile_rect))
                    {
                        bullet.reverse_y();
                    }
                    else
                    {
                        bullet.reverse_x();
                        bullet.reverse_y();
                    }
                    bullet.lifetime--;
                    break;
                }
            }
        }
    }
}

void Game_State::tank_wall_collision_handler()
{
    for(auto & player : players)
    {
        for(auto & tile : game_map.tiles)
        {
            //sf::FloatRect tile_rect{tile.get_position(),sf::Vector2f{gridsize_x,gridsize_y}};
            if(!tile.passable && collision_handler.check_collision(player.getPlayerSprite(), tile.tile))
            {
                player.set_tank_pos(player.get_old_position());
            }
        }
    }
}

void Game_State::tank_tank_collision_handler()
{
    if(collision_handler.check_collision(players.at(0).getPlayerSprite(), players.at(1).getPlayerSprite()))
    {
        players.at(0).set_tank_pos(players.at(0).get_old_position());
        players.at(1).set_tank_pos(players.at(1).get_old_position());
    }
}

void Game_State::tank_powerup_collision_handler()
{
    for(auto & player : players)
    {
        for(size_t i{};i<game_map.power_ups.size();i++)
        {
            if(collision_handler.check_collision(player.getPlayerSprite(),game_map.power_ups.at(i)->get_sprite()))
            //(player.get_hitbox().intersects(game_map.power_ups.at(i)->get_hitbox()))
            {
                if(player.set_power_up(game_map.power_ups.at(i)))   //Returnerar false om spelaren redan har en power up
                {
                    game_map.power_ups.at(i).reset();
                    game_map.power_ups.erase(game_map.power_ups.begin()+i);
                } 
            }
        }
    }
}

int Game_State::get_next_state()
{
    if(endgame)
    {
		sf::Time delay = sf::seconds(2);
        endgame = false;
        sf::sleep(delay);
        return WIN_STATE; // Ska egentligen gå vidare till Win_State
    }
    else if(paus)
    {
        paus = false;
        return PAUSE_STATE; // Ska egentligen gå vidare till Paus_State
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







