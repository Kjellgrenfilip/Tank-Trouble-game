#include "Constants.h"
#include "Game_State.h"
//#include "Game_Map.h"
#include "Resource_Manager.h"
#include <SFML/Graphics.hpp>

Game_State::Game_State()
    :   paus{false}, endgame{false}, players{}, game_map{}   // Initiera game_map här   
{
    //man måste skriva klassen före get_texture
    //ändrade även width och height till det rätta värdena från constant
	players.push_back(Player(Resource_Manager::get_texture_player(1), sf::Vector2f{screen_width/2, screen_height/2}));

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

void Game_State::update()
{
    //game_map.update();
}

void Game_State::render(sf::RenderTarget & target)
{
    game_map.render(target);
}

int Game_State::get_next_state()
{
    if(endgame)
    {
        endgame = false;
        return MENU_STATE; // Ska egentligen gå vidare till Win_State
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

