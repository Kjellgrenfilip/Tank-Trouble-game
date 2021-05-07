#ifndef PAUSSTATE_H
#define PAUSSTATE_H

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Constants.h"

class Pause_State : public State  // Kanske ska ärva från Menu_State
{
public:
    Pause_State();

    virtual void update() override;
    virtual void event_handler(sf::Event event) override;
    virtual void render(sf::RenderTarget & target) override;
    virtual int get_next_state() override;

private:
    sf::Text text[MENU_ITEMS];
    sf::Font font;

    bool end_paus;
    bool menu;
    bool exit;

    int menu_select;
};

#endif