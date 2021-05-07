#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

#include "Bullet.h"


#include <vector>

class Player
{
public:
    Player(sf::Texture & t, sf::Vector2f const& p/*sf::Texture & bullet*/);

    void update();
    void render(sf::RenderTarget & target);
    void event_handler(sf::Event event);
	
	sf::FloatRect get_hitbox(sf::Sprite&);     //Returnar playerns hitbox
	std::vector<Bullet>& get_bullets();	//Hämtar en vector med bullets
    
   

private:
	
	int hp;       				//Spelarens liv - spel startar med 3. Bullet skadar -1
	int player_ID;				//Spelarens ID, spelare 1, 2, 3 osv..
    sf::Vector2f pos;			//Spelarens position
    float rot;					//Spelarens rotation
    std::vector<Bullet> bullets;//Behållare för bullets
    sf::Sprite tank;			
    bool destroyed;				//Boolean som håller koll på om spelarens har "dött"

	float speed;
   

    //float const scale{.2};
};
#endif
