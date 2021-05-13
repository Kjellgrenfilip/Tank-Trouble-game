#ifndef SETTINGSTATE_H
#define SETTINGSTATE_H

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Constants.h"

class Setting_State : public State
{
public:
    Setting_State();

    virtual void update() override;
    virtual void event_handler(sf::Event event) override;
    virtual void game_event_handler(sf::Event) override;
    virtual void render(sf::RenderTarget & target) override;
    virtual int get_next_state() override;

private:
    sf::Text text[MENU_ITEMS];
    sf::Font font;

    bool exit;

    int menu_select;
};

#endif