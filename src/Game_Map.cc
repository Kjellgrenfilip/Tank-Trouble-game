#include <SFML/Graphics.hpp>
#include "Game_Map.h"
#include <fstream>
#include <exception>
#include "Tile.h"
#include "Constants.h"
Game_Map::Game_Map()
{
    generate();
}
void Game_Map::generate()
{
    std::ifstream map_text{random_map()};
    //std::ifstream map_text{"map1.txt"};
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
        if(pos_x>=resolution_gridsize-1)
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
}


std::string Game_Map::random_map()
{
    srand(time(0));
    int rnd_val = rand()%3;
    std::string rand_map;
    // detta kommer inte fungera, vet ej hur man ska hitta till filerna då de ej ligger i samma map.
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
