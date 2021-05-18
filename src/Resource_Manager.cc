#include "Resource_Manager.h"
#include "Game_Map.h"

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
        if(!shield_texture.loadFromFile("resources/textures/shield_texture1.png"))
        {
            throw std::invalid_argument("cannot open shield_texture");
        }
       
        if(!shotgun_texture.loadFromFile("resources/textures/shotgun_boost1.png"))
        {
            throw std::invalid_argument("cannot open shotgun_texture");
        }
        if(!rocket_texture.loadFromFile("resources/textures/rocket_boost1.png"))
        {
            throw std::invalid_argument("cannot open rocket_texture");
        }

        if(!speedboost_texture.loadFromFile("resources/textures/speed_texture1.png"))
        {
            throw std::invalid_argument("cannot open speed_texture1");
        }

        if(!rocket_projectile_texture.loadFromFile("resources/textures/rocket_projectile.png"))
        {
            throw std::invalid_argument("cannot open rocket_projectile_texture");
        }
		if(!background_texture.loadFromFile("resources/textures/menu_background.png"))
        {
            throw std::invalid_argument("cannot open background_texture");
        }
        if(!floor_texture.loadFromFile("resources/textures/rusty_texture.png"))
        {
            throw std::invalid_argument("cannot open background_texture");
        }
        if(!wall_texture.loadFromFile("resources/textures/rusty_wall.png"))
        {
            throw std::invalid_argument("cannot open background_texture");
        }
        if(!explosion_texture.loadFromFile("resources/textures/explosion.png"))
        {
            throw std::invalid_argument("cannot open explosion_texture");
        }
		
    }


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
sf::Texture& Resource_Manager::get_texture_shield()
{
    if(shield_texture.getSize() == sf::Vector2u(0,0))
    {
        get_texture();
    }
    return shield_texture;
}
			
    sf::Texture& Resource_Manager::get_texture_shotgun()
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

    sf::Texture& Resource_Manager::get_texture_rocket_projectile()
    {
        if(rocket_projectile_texture.getSize() == sf::Vector2u(0,0))
        {
            get_texture();
        }
        return rocket_projectile_texture;
    }
    
    sf::Texture& Resource_Manager::get_texture_speedboost()
    {
        if(speedboost_texture.getSize() == sf::Vector2u(0,0))
        {
            get_texture();
        }
        return speedboost_texture;
    }
    sf::Texture& Resource_Manager::get_texture_background()
    {
		if(background_texture.getSize() == sf::Vector2u(0,0))
        {
            get_texture();
        }
        return background_texture;
	}
    sf::Texture& Resource_Manager::get_texture_floor()
    {
        if(floor_texture.getSize() == sf::Vector2u(0,0))
        {
            get_texture();
        }
        return floor_texture;
    }
       sf::Texture& Resource_Manager::get_texture_wall()
    {
        if(wall_texture.getSize() == sf::Vector2u(0,0))
        {
            get_texture();
        }
        return wall_texture;
    }
    
      sf::Texture& Resource_Manager::get_texture_explosion()
    {
        if(explosion_texture.getSize() == sf::Vector2u(0,0))
        {
            get_texture();
        }
        return explosion_texture;
    }

    void Resource_Manager::load_game_map(int mapID)
    {
        game_map.generate(mapID);
    }

    Game_Map& Resource_Manager::get_game_map()
    {
        return game_map;
    }
