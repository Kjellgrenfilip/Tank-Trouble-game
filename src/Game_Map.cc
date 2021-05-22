#include <SFML/Graphics.hpp>
#include <fstream>
#include <stdexcept>
#include <memory>
#include <iostream>

#include "Game_Map.h"
#include "Tile.h"
#include "Constants.h"
#include "Shield.h"
#include "Rocket.h"
#include "Shotgun.h"
#include "Speed_Boost.h"
#include "Resource_Manager.h"

Game_Map::Game_Map()
    : powerups{}, tiles{}
{
    generate();
}
void Game_Map::generate(int mapID)
{
    //temporärt, finns bara en map just nu som har rätt format.
    std::ifstream map_text{random_map(mapID)};
    
    if(map_text.fail())
    {
        throw std::logic_error("No map at file location");
    }

    tiles.clear();

    std::string temp_string;
    float pos_x{};
    float pos_y{};
    while(map_text >> temp_string)
    {
        sf::Vector2f pos{pos_x * gridsize_x, pos_y * gridsize_y};
        if(temp_string == "1")
        {
            //tilen är en vägg
            Tile temp_tile(pos, false, Resource_Manager::get_texture_wall(), "wall");
            this->tiles.push_back(temp_tile);
        }
        else
        {
            Tile temp_tile(pos, true, Resource_Manager::get_texture_floor(), "floor");
            this->tiles.push_back(temp_tile);
        }
        if(pos_x >= pixel_resolution_x - 1)
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

    if(tiles.at(t).passable && chance == 0 && !tiles.at(t).available_power)
    {
        srand(time(0));
        int rand_num = rand() % 4;
        //std::cout << "Added"<< std::endl;
        switch(rand_num)
        {
            case 0:
                    powerups.push_back(std::make_shared<Shield>(tiles.at(t).get_position()));
                    break;
            case 1:
                    powerups.push_back(std::make_shared<Rocket>(tiles.at(t).get_position()));
                    break;
            case 2:
                    powerups.push_back(std::make_shared<Shotgun>(tiles.at(t).get_position()));
                    break;
            case 3:
                    powerups.push_back(std::make_shared<Speed_Boost>(tiles.at(t).get_position()));
                    break;
            default:
                    throw std::logic_error("Random number not 0-3");
        }
        tiles.at(t).setPowerUp();
    }
    // Kolla om power_up har gått ut, ta bort
    for (size_t i{}; i < powerups.size(); i++)
    {
        if(powerups.at(i) -> is_expired())
        {
            powerups.at(i).reset();                        
            powerups.erase(powerups.begin() + i);
            i--;
        }
    }

    for(auto & p : powerups)
    {
        p->update();
    }
}

void Game_Map::render(sf::RenderTarget &window)
{
        for(auto tile : tiles)
        {
            window.draw(tile.get_sprite());
        }
        for(auto & i : powerups)
        {
            i->render(window);
        }
}


std::string Game_Map::random_map(int mapID)
{
    int choice{};
    if(mapID == 0)
    {
        srand(time(0));
        choice = rand()%5 + 1;
    }
    else
    {
        choice = mapID;
    }
    std::string rand_map;
    switch(choice)
    {
        case 1:
                rand_map = "resources/maps/map1.txt";
                break;
        case 2:
                rand_map = "resources/maps/map2.txt";
                break;
        case 3:
                rand_map = "resources/maps/map3.txt";
                break;
        case 4:
                rand_map = "resources/maps/map4.txt";
                break;
        case 5:
                rand_map = "resources/maps/map5.txt";
                break;
        default:
                rand_map = "no such map";
                break;
    }
    return rand_map;
}
    std::vector<Tile>& Game_Map::get_tiles()
    {
        return tiles;
    }
    std::vector<std::shared_ptr<Power_Up>>& Game_Map::get_powerups()
    {
        return powerups;
    }
