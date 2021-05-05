#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "State.h"

class Game
{
public:
    Game(std::string const& title, unsigned width, unsigned height);

    void start();

private:
    sf::RenderWindow window;

    int current_state;
    bool running;
    std::map<int, std::unique_ptr<State>> states;

    void event_handler();
    void delay(sf::Clock & clock);
};

#endif

