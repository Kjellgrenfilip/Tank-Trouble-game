#include "Pause_State.h"
#include "Constants.h"

#include <SFML/Graphics.hpp>
#include <iostream>

Pause_State::Pause_State()
    :   font{}, end_paus{false}, menu{false}, exit{false}, menu_select{0}    
{
    std::string file{"resources/fonts/Amatic-Bold.ttf"};
    if(!font.loadFromFile(file))
    {
        throw std::invalid_argument("No font at location: " + file);
    }
    text[0] = sf::Text{"Resume", font, 52 };
    text[0].setPosition(screen_width / 2 - text[0].getGlobalBounds().width / 2, screen_height / PAUSE_ITEMS - (text[0].getGlobalBounds().height + 15));
    text[1] = sf::Text{"Return to Menu", font, 52 };
    text[1].setPosition(screen_width / 2 - text[1].getGlobalBounds().width / 2, screen_height / PAUSE_ITEMS);
    text[2] = sf::Text{"Quit to desktop", font, 52 };
    text[2].setPosition(screen_width / 2 - text[2].getGlobalBounds().width / 2, screen_height / PAUSE_ITEMS + (text[2].getGlobalBounds().height + 10));
}

void Pause_State::event_handler(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Return)
        {
            if(menu_select == 0)
            {
                end_paus = true;
            }
            else if(menu_select == 1)
            {
                menu = true;
            }
            else if(menu_select == 2)
            {
                exit = true;
            }
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

void Pause_State::game_event_handler(sf::Event)
{
}

void Pause_State::update()
{
    for(int i{}; i < PAUSE_ITEMS; i++)
    {
        text[i].setFillColor(sf::Color(255,255,255));
    }
    text[menu_select].setFillColor(sf::Color(255,0,0));
}

void Pause_State::render(sf::RenderTarget & target)
{
    for(int i{}; i < PAUSE_ITEMS; i++)
    {
        target.draw(text[i]);
    }
}

int Pause_State::get_next_state()
{
    if(end_paus)
    {
        end_paus = false;
        return GAME_STATE;
    }
    else if(menu)
    {
        menu = false;
        return MENU_STATE;
    }
    else if(exit)
    {
        exit = false;
        return EXIT_STATE;
    }
    else
    {
        return PAUSE_STATE;
    }
}

