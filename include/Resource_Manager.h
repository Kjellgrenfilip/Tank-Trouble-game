#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdexcept>
#include "Game_Map.h"
class Resource_Manager
{

    private:
        static inline sf::Texture player1_texture;
		static inline sf::Texture player2_texture;
		static inline sf::Texture heart_texture;
        static inline sf::Texture shield_texture;
        static inline sf::Texture shotgun_texture;
        static inline sf::Texture rocket_texture;
        static inline sf::Texture speedboost_texture;
        static inline sf::Texture background_texture;
        static inline sf::Texture controls_texture;
        static inline sf::Texture wall_texture;
        static inline sf::Texture floor_texture;
        static inline sf::Texture explosion_texture;
        static inline sf::Font font_mandala;
        
        static inline sf::SoundBuffer hit_sound;
        static inline sf::SoundBuffer shot_sound;
        static inline sf::SoundBuffer powerup_sound;
        static inline sf::SoundBuffer destroyed_sound;
        static inline sf::SoundBuffer bounce_sound;
        static inline sf::SoundBuffer rocket_sound;
        static inline sf::SoundBuffer shotgun_sound;
        static inline sf::SoundBuffer shield_sound;

        static inline Game_Map game_map;
        static inline sf::Texture rocket_projectile_texture;
    public:
        static sf::Texture& get_texture_player(int player_id);
        static sf::Texture& get_texture_heart();
        static sf::Texture& get_texture_shotgun();
        static sf::Texture& get_texture_rocket();
        static sf::Texture& get_texture_shield();
        static sf::Texture& get_texture_speedboost();
        static sf::Texture& get_texture_rocket_projectile();
        static sf::Texture& get_texture_background();
        static sf::Texture& get_texture_controls();
        static sf::Texture& get_texture_wall();
        static sf::Texture& get_texture_floor();
        static sf::Texture& get_texture_explosion();
        static sf::Font& get_font_mandala();
        
        static sf::SoundBuffer& get_soundbuffer_hit();
        static sf::SoundBuffer& get_soundbuffer_shot();
        static sf::SoundBuffer& get_soundbuffer_powerup();
        static sf::SoundBuffer& get_soundbuffer_destroyed();
        static sf::SoundBuffer& get_soundbuffer_bounce();
        static sf::SoundBuffer& get_soundbuffer_rocket();
        static sf::SoundBuffer& get_soundbuffer_shotgun();
        static sf::SoundBuffer& get_soundbuffer_shield();

        static void load_game_map(int mapID = 0);
        static void get_texture();
        static void get_soundbuffer();
        static Game_Map& get_game_map();

        


};
#endif
