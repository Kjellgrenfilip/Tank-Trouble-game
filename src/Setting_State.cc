#include "Setting_State.h"
#include "Constants.h"

#include <SFML/Graphics.hpp>
#include <iostream>

Setting_State::Setting_State()
    :   font{}, exit{false}, menu_select{0}    
{
    std::string file{"resources/fonts/Amatic-Bold.ttf"};
    if(!font.loadFromFile(file))
    {
        throw std::invalid_argument("No font at location: " + file);
    }
    text[0] = sf::Text{"Return", font, 32 };
    text[0].setFillColor(sf::Color(255,0,0));
    text[0].setPosition(screen_width / 2 - text[0].getGlobalBounds().width / 2, screen_height / MENU_ITEMS - (text[0].getGlobalBounds().height + 10));
    text[1] = sf::Text{"Load Map 1 (inte implementerad)", font, 32 };
    text[1].setFillColor(sf::Color(255,255,255));
    text[1].setPosition(screen_width / 2 - text[1].getGlobalBounds().width / 2, screen_height / MENU_ITEMS);
    text[2] = sf::Text{"Load Map 2 (inte implementerad)", font, 32 };
    text[2].setFillColor(sf::Color(255,255,255));
    text[2].setPosition(screen_width / 2 - text[2].getGlobalBounds().width / 2, screen_height / MENU_ITEMS + (text[2].getGlobalBounds().height + 10));
}

void Setting_State::event_handler(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Return)
        {
            if(menu_select == 0)
            {
                exit = true;
            }
            else if(menu_select == 1)
            {
                    // Ladda om map
            }
            else if(menu_select == 2)
            {
                    // Ladda om map
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

void Setting_State::game_event_handler(sf::Event)
{
}

void Setting_State::update()
{
    for(int i{}; i < MENU_ITEMS; i++)
    {
        text[i].setFillColor(sf::Color(255,255,255));
    }
    text[menu_select].setFillColor(sf::Color(255,0,0));
}

void Setting_State::render(sf::RenderTarget & target)
{
    for(int i{}; i < MENU_ITEMS; i++)
    {
        target.draw(text[i]);
    }
}

int Setting_State::get_next_state()
{
    if(exit)
    {
        exit = false;
        return MENU_STATE;
    }
    else
    {
        return SETTING_STATE;
    }
}

