#include "Setting_State.h"
#include "Constants.h"
#include "Resource_Manager.h"

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
    text[0] = sf::Text{"Return", font, 52 };
    text[0].setFillColor(sf::Color(255,0,0));
    text[0].setPosition(screen_width / 2 - text[0].getGlobalBounds().width / 2, screen_height / SETTING_ITEMS - (text[0].getGlobalBounds().height + 10));
    for(int i{1}; i < SETTING_ITEMS; i++)
    {
        std::string temp{"Load Map "};
        temp += std::to_string(i);
        text[i] = sf::Text{temp, font, 52 };
        text[i].setFillColor(sf::Color(255,0,0));
        text[i].setPosition(screen_width / 2 - text[i].getGlobalBounds().width / 2, screen_height / SETTING_ITEMS + (text[i].getGlobalBounds().height + 10) * (i - 1));
    }
}

void Setting_State::event_handler(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Return)
        {
            if(menu_select == 1)
            {
                    Resource_Manager::load_game_map(1);
            }
            else if(menu_select == 2)
            {
                    Resource_Manager::load_game_map(2);
            }
            else if(menu_select == 3)
            {
                    Resource_Manager::load_game_map(3);
            }
            else if(menu_select == 4)
            {
                    Resource_Manager::load_game_map(4);
            }
            else if(menu_select == 5)
            {
                    Resource_Manager::load_game_map(5);
            }
            exit = true;
        }
        if(event.key.code == sf::Keyboard::Up)
        {
            if(menu_select == 0)
            {
                menu_select = SETTING_ITEMS;
            }
            else
            {
                menu_select--;
            }
        }
        if(event.key.code == sf::Keyboard::Down)
        {
            if(menu_select == SETTING_ITEMS)
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
    for(int i{}; i < SETTING_ITEMS; i++)
    {
        text[i].setFillColor(sf::Color(255,255,255));
    }
    text[menu_select].setFillColor(sf::Color(255,0,0));
}

void Setting_State::render(sf::RenderTarget & target)
{
    for(int i{}; i < SETTING_ITEMS; i++)
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

