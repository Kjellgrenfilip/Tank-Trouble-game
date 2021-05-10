#include "Game.h"
#include "Game_State.h"
#include "Menu_State.h"
#include "Pause_State.h"
//#include "Win_State.h"
#include "Constants.h"

#include <SFML/Graphics.hpp>
#include <map>
#include <utility>

#include <iostream>

Game::Game( std::string const& title,
            unsigned width,
            unsigned height)
        :   window{sf::VideoMode{width, height},
            title,
            sf::Style::Titlebar | sf::Style::Close},
            current_state{MENU_STATE},
            running{true},
            states{}
{
    states.insert(  std::pair<int,
                    std::unique_ptr<State>>(
                        {   MENU_STATE, 
                            std::make_unique<Menu_State>()})
                );
    states.insert(  std::pair<int,
                    std::unique_ptr<State>>(
                        {   GAME_STATE, 
                            std::make_unique<Game_State>()})
                );
    states.insert(  std::pair<int,
                    std::unique_ptr<State>>(
                        {   PAUSE_STATE, 
                            std::make_unique<Pause_State>()})
                );
    // states.insert(  std::pair<int,
    //                 std::unique_ptr<State>>(
    //                     {   WIN_STATE, 
    //                         std::make_unique<Win_State>()})
    //             );
}

void Game::start()
{
    sf::Clock clock { };
    while ( running )
    {
        event_handler();

        states.at(current_state) -> update();

        window.clear ();

        states.at(current_state) -> render(window);

        window.display ();

        current_state = states.at(current_state) -> get_next_state();
        if(current_state == EXIT_STATE)
            running = false;  

        delay (clock);
    }
}

void Game::event_handler()
{
    sf::Event event;
    while ( window.pollEvent (event) )
    {
        if ( event.type == sf::Event::Closed )
        {
            running = false;
        }
        states.at(current_state)->event_handler(event);
    }
    states.at(current_state)->game_event_handler(event);
}

void Game::delay(sf::Clock & clock)
{
    sf::sleep(sf::milliseconds(1000.0 / fps) - clock.getElapsedTime());
    clock.restart();
}


