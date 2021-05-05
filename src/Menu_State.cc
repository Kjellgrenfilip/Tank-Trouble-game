#include "Menu_State.h"
#include "Constants.h"

#include <SFML/Graphics.hpp>

Menu_State::Menu_State()
    :   text{}, font{}, startgame{false}    
{
    std::string file{"resources/fonts/font.ttf"};
    if(!font.loadFromFile(file))
    {
        throw std::invalid_argument("No font at location: " + file);
    }
    text = sf::Text{"Press <Enter> to start", font, 16 };
}

void Menu_State::event_handler(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Enter)
        {
            startgame = true;
        }
    }
}

void Menu_State::update()
{

}

void Menu_State::render(sf::RenderTarget & target)
{
    auto bounds { text.getGlobalBounds () };
    auto size   { target.getSize () };

    text.setPosition ((size.x - bounds.width) / 2,
                      (size.y - bounds.height) / 2);

    target.draw (text);
}

int Menu_State::get_next_state()
{
    if(startgame)
    {
        startgame = false;
        return GAME_STATE;
    }
    else
    {
        return MENU_STATE;
    }
}

