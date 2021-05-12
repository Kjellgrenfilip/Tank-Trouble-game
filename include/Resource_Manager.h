#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <SFML/Graphics.hpp>
#include <stdexcept>
class Resource_Manager
{

    private:
        static inline sf::Texture player1_texture;
		static inline sf::Texture player2_texture;
		static inline sf::Texture heart_texture;
        /*static inline sf::Texture shotgun_texture;
        static inline sf::Texture rocket_texture;
        static inline sf::Texture shield_texture;
        static inline sf::Texture speedboost_texture;*/
    public:
        static sf::Texture& get_texture_player(int player_id);
        static sf::Texture& get_texture_heart();
        static sf::Texture& get_texture_shotgun();
        static sf::Texture& get_texture_rocket();
        static sf::Texture& get_texture_shield();
        static sf::Texture& get_texture_speedboost();
        static void get_texture();


};
#endif
