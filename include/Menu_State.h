#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "Constants.h"

class Menu_State : public State
{
public:
    Menu_State();

    virtual void update() override;
    virtual void event_handler(sf::Event event) override;
    virtual void game_event_handler(sf::Event) override;
    virtual void render(sf::RenderTarget & target) override;
    
    virtual int get_next_state() override;
    

private:
    sf::Text text[MENU_ITEMS];
    sf::Font font;
	sf::Sprite background;
    bool startgame;
    bool settings;
    bool exit;

    int menu_select;
    
    sf::Music menu_song;
};

#endif
