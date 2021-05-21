#include "Menu_State.h"
#include "Constants.h"
#include "Resource_Manager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
Menu_State::Menu_State()
    :   font{}, menu_background{}, control_background{}, startgame{false}, settings{false}, exit{false}, controls{false}, menu_select{0}, menu_song{}  
{
    std::string file{"resources/fonts/Amatic-Bold.ttf"};
    if(!font.loadFromFile(file))
    {
        throw std::invalid_argument("No font at location: " + file);
    }
    text[0] = sf::Text{"Play", font, 52 };
    text[0].setFillColor(sf::Color(255,0,0));
    text[0].setPosition(screen_width / 2 - text[0].getGlobalBounds().width / 2, screen_height / MENU_ITEMS - (text[0].getGlobalBounds().height + 10));
    text[1] = sf::Text{"Settings", font, 52 };
    text[1].setFillColor(sf::Color(255,255,255));
    text[1].setPosition(screen_width / 2 - text[1].getGlobalBounds().width / 2, screen_height / MENU_ITEMS );
    text[2] = sf::Text{"Controls", font, 52 };
    text[2].setFillColor(sf::Color(255,255,255));
    text[2].setPosition(screen_width / 2 - text[2].getGlobalBounds().width / 2, screen_height / MENU_ITEMS + (text[2].getGlobalBounds().height + 10));
    text[3] = sf::Text{"Quit to desktop", font, 52 };
    text[3].setFillColor(sf::Color(255,255,255));
    text[3].setPosition(screen_width / 2 - text[3].getGlobalBounds().width / 2, screen_height / MENU_ITEMS + (text[3].getGlobalBounds().height + 10)*2);
	
	menu_background.setTexture(Resource_Manager::get_texture_background());
	control_background.setTexture(Resource_Manager::get_texture_controls());
	if(!menu_song.openFromFile("resources/sounds/menu_music.ogg"))
    {
        throw std::logic_error("Can't open menu_music");
    }
	
	menu_song.setLoop(true);
	menu_song.play();
	
}

void Menu_State::event_handler(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Return)
        {
            if(menu_select == 0)
            {
                startgame = true;
            }
            else if(menu_select == 1)
            {
                settings = true;
            }
            else if(menu_select == 2)
            {
                if (controls == false)
				{
					controls = true;
				}
				else if(controls == true)
                {
					controls = false;
                }
            }
            else if(menu_select == 3)
            {
				exit = true;
			}
        }
        if(event.key.code == sf::Keyboard::Up)
        {
            if(menu_select == 0)
            {
                menu_select = MENU_ITEMS;
            }
            else
            {
                menu_select--;
            }
        }
        if(event.key.code == sf::Keyboard::Down)
        {
            if(menu_select == MENU_ITEMS)
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
void Menu_State::game_event_handler(sf::Event)
{
}

void Menu_State::update()
{
    for(int i{}; i < MENU_ITEMS; i++)
    {
        text[i].setFillColor(sf::Color(255,255,255));
    }
    text[menu_select].setFillColor(sf::Color(255,0,0));
}

void Menu_State::render(sf::RenderTarget & target)
{
	
	if (!controls)
	{
	target.draw(menu_background);
    
		for(int i{}; i < MENU_ITEMS; i++)
		{
        target.draw(text[i]);
		}
	}
	else
    {
		target.draw(control_background);
    }
}

int Menu_State::get_next_state()
{
    if(startgame)
    {
		menu_song.setVolume(40);
        startgame = false;
        return RESTART_GAME;
    }
    else if(settings)
    {
        settings = false;
        return SETTING_STATE;
    }
    else if(exit)
    {
        return EXIT_STATE;
    }
    else
    {
        return MENU_STATE;
    }
}

