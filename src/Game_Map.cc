#include <SFML/Graphics.hpp>
#include "Game_Map.h"
#include <fstream>
#include <exception>
#include "Tile.h"
#include "Constants.h"
#include "Shield.h"
#include "Rocket.h"
#include "Shotgun.h"
#include <memory>

#include <iostream>
Game_Map::Game_Map()
    : power_ups{}
{
    generate();
}
void Game_Map::generate()
{
    //temporärt, finns bara en map just nu som har rätt format.
    std::ifstream map_text{"resources/maps/map1.txt"}; //random_map()};
    
    if(map_text.fail())
    {
        //throw error here.
    }
    std::string temp_string;
    float pos_x{};
    float pos_y{};
    while(map_text>>temp_string)
    {
        sf::Vector2f pos{pos_x*gridsize_x,pos_y*gridsize_y};
        if(temp_string == "1")
        {
            //tilen är en vägg
            Tile temp_tile(pos,false,"wall");
            this->tiles.push_back(temp_tile);
        }
        else
        {
            Tile temp_tile(pos,true,"blank");
            this->tiles.push_back(temp_tile);
        }
        if(pos_x>=pixel_resolution_x-1)
        {
            pos_x = 0;
            pos_y += 1;
        }
        else
        {
            pos_x += 1;
        }
    }
}

void Game_Map::update()
{
    srand(time(0));
    int t = rand() % tiles.size();
    int chance = rand() % 10;

    //std::cout << power_ups.size() << std::endl;

    if(tiles.at(t).passable && chance == 0 && tiles.at(t).available_power == nullptr)
    {
        srand(time(0));
        int rand_num = rand() % 3;
        switch(rand_num)
        {
            case 0:
                    power_ups.push_back(std::make_shared<Shield>(tiles.at(t).get_position()));
                    break;
            case 1:
                    power_ups.push_back(std::make_shared<Rocket>(tiles.at(t).get_position()));
                    break;
            case 2:
                    power_ups.push_back(std::make_shared<Shotgun>(tiles.at(t).get_position()));
                    break;
            default:
                    std::cout << "da fuq? random numer not 0-2" << std::endl;
        }
        //power_ups.push_back(std::make_shared<Shield>(tiles.at(t).get_position()));
        tiles.at(t).setPowerUp(power_ups.back());
    }
}

void Game_Map::render(sf::RenderTarget &window)
{
        sf::RectangleShape wall(sf::Vector2f(gridsize_x,gridsize_y));
        wall.setFillColor(sf::Color::White);
        for(auto i : tiles)
        {
            if(i.get_name() == "wall")
            {
                wall.setPosition(i.get_position());
                window.draw(wall);
            }
        }
        for(auto & i : power_ups)
        {
            i->render(window);
        }
}


std::string Game_Map::random_map()
{
    srand(time(0));
    int rnd_val = rand()%3;
    std::string rand_map;
    switch(rnd_val)
    {
        case 0:
                rand_map = "resources/maps/map1.txt";
                break;
        case 1:
                rand_map = "resources/maps/map2.txt";
                break;
        case 2:
                rand_map = "resources/maps/map3.txt";
                break;
        default:
                rand_map = "no such map";
                break;
    }
    return rand_map;
}
