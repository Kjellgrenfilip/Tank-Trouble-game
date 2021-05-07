#include "Pause_State.h"
#include "Constants.h"

#include <SFML/Graphics.hpp>
#include <iostream>

Pause_State::Pause_State()
    :   font{}, end_paus{false}, menu{false}, exit{false}, menu_select{0}    
{
    std::string file{"resources/fonts/font.ttf"};
    if(!font.loadFromFile(file))
    {
        throw std::invalid_argument("No font at location: " + file);
    }
    text[0] = sf::Text{"Resume", font, 32 };
    text[0].setColor(sf::Color(255,0,0));
    text[0].setPosition(screen_width / 2 - text[0].getGlobalBounds().width / 2, screen_height / MENU_ITEMS - (text[0].getGlobalBounds().height + 15));
    text[1] = sf::Text{"Return to Menu", font, 32 };
    text[1].setColor(sf::Color(255,255,255));
    text[1].setPosition(screen_width / 2 - text[1].getGlobalBounds().width / 2, screen_height / MENU_ITEMS);
    text[2] = sf::Text{"Quit to desktop", font, 32 };
    text[2].setColor(sf::Color(255,255,255));
    text[2].setPosition(screen_width / 2 - text[2].getGlobalBounds().width / 2, screen_height / MENU_ITEMS + (text[2].getGlobalBounds().height + 10));
}

void Pause_State::event_handler(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Enter)
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

void Pause_State::update()
{
    for(int i{}; i < MENU_ITEMS; i++)
    {
        text[i].setColor(sf::Color(255,255,255));
    }
    text[menu_select].setColor(sf::Color(255,0,0));
}

void Pause_State::render(sf::RenderTarget & target)
{
    for(int i{}; i < MENU_ITEMS; i++)
    {
        target.draw(text[i]);
    }

    // auto bounds { text.getGlobalBounds () };
    // auto size   { target.getSize () };

    // text.setPosition ((size.x - bounds.width) / 2,
    //                   (size.y - bounds.height) / 2);

    // target.draw (text);
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

