#ifndef RESOURCE_MANAGER.H
#define RESOURCE_MANAGER.H
#include <SFML/Graphics.hpp>
#include <stdexcept>
class Resource_Manager
{

    private:
    static sf::Texture player1_texture;
    static sf::Texture player2_texture;
    static sf::Texture shotgun_texture;
    static sf::Texture rocket_texture;
    static sf::Texture shield_texture;
    static sf::Texture speedboost_texture;
    public:
    static sf::Texture& get_texture_player(int player_id)
    {
        if (player_id == 1)
        {
            return player1_texture;
        }
        else
        {
            return player2_texture;
        }
    }
    static sf::Texture& get_texture_shotgun()
    {
        return shotgun_texture;
    }
    static sf::Texture& get_texture_rocket()
    {
        return rocket_texture;
    }
    static sf::Texture& get_texture_shield()
    {
        return shield_texture;
    }
    static sf::Texture& get_texture_speedboost()
    {
        return speedboost_texture;
    }
    static void get_textures()
    {
        if(!player1_texture.loadFromFile("resources/textures/player1_texture.png"))
        {
            throw std::invalid_argument("cannot open player1_texture");
        }
        if(!player2_texture.loadFromFile("resources/textures/player2_texture.png"))
        {
            throw std::invalid_argument("cannot open player2_texture");
        }
        if(!shotgun_texture.loadFromFile("resources/textures/shotgun_texture.png"))
        {
            throw std::invalid_argument("cannot open shotgun_texture");
        }
        if(!rocket_texture.loadFromFile("resources/textures/rocket_texture.png"))
        {
            throw std::invalid_argument("cannot open rocket_texture");
        }
        if(!shield_texture.loadFromFile("resources/textures/shield_texture.png"))
        {
            throw std::invalid_argument("cannot open shield_texture");
        }
         if(!speedboost_texture.loadFromFile("resources/textures/speedboost_texture.png"))
        {
            throw std::invalid_argument("cannot open speedboost_texture");
        }
    }
    


};
#endif