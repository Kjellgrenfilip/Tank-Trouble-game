#include "Win_State.h"
#include "Constants.h"
#include "Game_State.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "GameMap_Manager.h"
Win_State::Win_State()
    :   font{}, play_again{false}, menu{false}, exit{false}, player1wins{0}, player2wins{0}, winner{0}, menu_select{0}    
{
    std::string file{"resources/fonts/Amatic-Bold.ttf"};
    if(!font.loadFromFile(file))
    {
        throw std::invalid_argument("No font at location: " + file);
    }
    
    menu_text[0] = sf::Text{"Play new round!", font, 52 };
    menu_text[0].setPosition(screen_width / 2 - menu_text[0].getGlobalBounds().width / 2, screen_height / PAUSE_ITEMS - (menu_text[0].getGlobalBounds().height + 15));
    menu_text[1] = sf::Text{"Return to Menu", font, 52 };
    menu_text[1].setPosition(screen_width / 2 - menu_text[1].getGlobalBounds().width / 2, screen_height / PAUSE_ITEMS);
    menu_text[2] = sf::Text{"Quit to desktop", font, 52 };
    menu_text[2].setPosition(screen_width / 2 - menu_text[2].getGlobalBounds().width / 2, screen_height / PAUSE_ITEMS + (menu_text[2].getGlobalBounds().height + 10));
}

void Win_State::event_handler(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Return)
        {
            if(menu_select == 0)
            {
                play_again = true;
            }
            else if(menu_select == 1)
            {
                menu = true;
            }
            else if(menu_select == 2)
            {
                exit = true;
            }
            GameMap_Manager::load_game_map();
        }
        if(event.key.code == sf::Keyboard::Up)
        {
            if(menu_select == 0)
            {
                menu_select = 2;
            }
            else
            {
                menu_select--;
            }
        }
        if(event.key.code == sf::Keyboard::Down)
        {
            if(menu_select == 2)
            {
                menu_select = 0;
            }
            else
            {
                menu_select++;
            }
        }    
    }
}

void Win_State::game_event_handler(sf::Event)
{
}

void Win_State::update()
{
    for(int i{}; i < PAUSE_ITEMS; i++)
    {
        menu_text[i].setFillColor(sf::Color(255,255,255));
    }
    menu_text[menu_select].setFillColor(sf::Color(255,0,0));

	winner = Game_State::get_winner();
		
    if (winner == 1)
	{
		++player1wins;
		win_text[0] = sf::Text{"Player " + std::to_string(winner) + " WON!", font, 100};
	}
	else if (winner == 2)
	{
		++player2wins;
		win_text[0] = sf::Text{"Player " + std::to_string(winner) + " WON!", font, 100};
	}
	
    win_text[0].setFillColor(sf::Color::Yellow);
    win_text[0].setPosition(screen_width/2 - win_text[0].getGlobalBounds().width / 2, 0);
    win_text[1] = sf::Text{"Player 1: " + std::to_string(player1wins) + " wins.", font, 36};
    win_text[1].setFillColor(sf::Color{175,40,40});
    win_text[1].setPosition(screen_width*0.25 - win_text[1].getGlobalBounds().width / 2, screen_height/2);
    win_text[2] = sf::Text{"Player 2: " + std::to_string(player2wins) + " wins.", font, 36};
    win_text[2].setFillColor(sf::Color{28,24,128});
    win_text[2].setPosition(screen_width*0.75 - win_text[2].getGlobalBounds().width / 2, screen_height/2);
}

void Win_State::render(sf::RenderTarget & target)
{
	for (int i{}; i < PAUSE_ITEMS; i++)
	{
		target.draw(win_text[i]);
	}
	for(int i{}; i < PAUSE_ITEMS; i++)
    {
        target.draw(menu_text[i]);
    }
}

int Win_State::get_next_state()
{
    if(play_again)
    {
        play_again = false;
        return RESTART_GAME;
    }
    else if(menu)
    {
        menu = false;
        player1wins = 0;
        player2wins = 0;
        return MENU_STATE;
    }
    else if(exit)
    {
        exit = false;
        return EXIT_STATE;
    }
    else
    {
        return WIN_STATE;
    }
}
