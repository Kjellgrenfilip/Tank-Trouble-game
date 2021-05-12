#include "Resource_Manager.h"

sf::Texture& Resource_Manager::get_texture_player(int player_id)
    {
        sf::Vector2u empty {0,0};
        if (player_id == 1)
        {
            if(player1_texture.getSize() == empty)
            {
                get_texture();
            }
            return player1_texture;
        }
	
        else
        {
            if(player2_texture.getSize() == empty)
            {
                get_texture();
            }
            return player2_texture;
        }
    }
sf::Texture& Resource_Manager::get_texture_heart()
{
	if (heart_texture.getSize() == sf::Vector2u{0,0})
		{
			get_texture();
		}
		return heart_texture;
}
			
  /*  sf::Texture& Resource_Manager::get_texture_shotgun()
    {
        if(shotgun_texture.getSize() == sf::Vector2u(0,0))
        {
            get_texture();
        }
        return shotgun_texture;
    }
    sf::Texture& Resource_Manager::get_texture_rocket()
    {
        if(rocket_texture.getSize() == sf::Vector2u(0,0))
        {
            get_texture();
        }
        return rocket_texture;
    }
    sf::Texture& Resource_Manager::get_texture_shield()
    {
        if(shield_texture.getSize() == sf::Vector2u(0,0))
        {
            get_texture();
        }
        return shield_texture;
    }
    sf::Texture& Resource_Manager::get_texture_speedboost()
    {
        if(speedboost_texture.getSize() == sf::Vector2u(0,0))
        {
            get_texture();
        }
        return speedboost_texture;
    }*/
    void Resource_Manager::get_texture()
    {
        if(!player1_texture.loadFromFile("resources/textures/player1_texture.png"))
        {
            throw std::invalid_argument("cannot open player1_texture");
        }
        if(!player2_texture.loadFromFile("resources/textures/player2_texture.png"))
        {
            throw std::invalid_argument("cannot open player2_texture");
        }
        if(!heart_texture.loadFromFile("resources/textures/heart.png"))
        {
            throw std::invalid_argument("cannot open heart_texture");
        }
       
       
        /*if(!shotgun_texture.loadFromFile("resources/textures/shotgun_texture.png"))
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
        }*/
    }
