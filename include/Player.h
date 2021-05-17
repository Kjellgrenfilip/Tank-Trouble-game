#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

#include "Bullet.h"
#include "Power_Up.h"
#include <memory>
#include <vector>

class Player
{
public:
    Player(sf::Texture & t, sf::Vector2f const& p, int ID, sf::Texture & h);

    void update(Player&);
    void render(sf::RenderTarget & target);
    void event_handler(sf::Event event);
	
	sf::FloatRect get_hitbox() const;     //Returnar playerns hitbox
	std::vector<Bullet>& get_bullets();	//Hämtar en vector med bullets
    sf::Vector2f get_position();
    sf::Vector2f get_old_position();
    void set_tank_pos(sf::Vector2f new_pos);
    std::shared_ptr<Power_Up> my_power{};
    sf::Sprite const& getPlayerSprite() const;

private:
	
	int hp;       				//Spelarens liv - spel startar med 3. Bullet skadar -1
	int player_ID;				//Spelarens ID, spelare 1, 2, 3 osv..
    sf::Vector2f pos;			//Spelarens position
    sf::Vector2f old_pos{};     //spelarens gammla position, används vid kollision.
    float rot;					//Spelarens rotation
   
    std::vector<sf::Sprite> hearts;
    std::vector<Bullet> bullets;//Behållare för bullets
    sf::Sprite tank;			
    
    bool destroyed;				//Boolean som håller koll på om spelarens har "dött"
	float speed;
	void check_bullets(Player&);
	void set_hearts(sf::Texture& h);
	void print_player_text(sf::RenderTarget & target);
};
#endif
