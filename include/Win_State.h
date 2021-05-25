#ifndef WINSTATE_H
#define WINSTATE_H

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Constants.h"


class Win_State : public State  
{
public:
    Win_State();

    virtual void update() override;
    virtual void event_handler(sf::Event event) override;
    virtual void game_event_handler(sf::Event) override;
    virtual void render(sf::RenderTarget & target) override;
    virtual int get_next_state() override;

private:
    sf::Text win_text[PAUSE_ITEMS];  
    sf::Text menu_text[PAUSE_ITEMS];
    sf::Font font;

    bool play_again;
    bool menu;
    bool exit;

	int player1wins;
	int player2wins;
    int winner;
    
    int menu_select;
};

#endif
