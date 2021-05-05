#include "Constants.h"
#include "Game_State.h"
//#include "Game_Map.h"

#include <SFML/Graphics.hpp>

Game_State::Game_State()
    :   paus{false}, endgame{false}  // Initiera game_map här   
{
}

void Game_State::event_handler(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Escape)
        {
            endgame = true;
        }
    }
}

void Game_State::update()
{
    //game_map.update();
}

void Game_State::render(sf::RenderTarget & target)
{
    //game_map.render(target);
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
        return MENU_STATE; // Ska egentligen gå vidare till Paus_State
    }
    else
    {
        return GAME_STATE;
    }
}

