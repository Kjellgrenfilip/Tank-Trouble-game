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
	
	sf::FloatRect get_hitbox() const;                           // Returnar playerns hitbox
	std::vector<Bullet>& get_bullets();                        	// Hämtar en vector med bullets
    sf::Vector2f get_position();                                // returnerar spelarens position    
    sf::Vector2f get_old_position();                            // returnerar spelaren position på bilden innan
    void set_tank_pos(sf::Vector2f new_pos);                    // flyttar spelaren
    void set_power_up(std::shared_ptr<Power_Up> &new_power);    // ny pointer till power_up
    sf::Sprite const& getPlayerSprite() const;                  // returnerar spelarens sprite
	
	bool is_destroyed();
private:
	
	int hp;       				//Spelarens liv - spel startar med 3. Bullet skadar -1
	int player_ID;				//Spelarens ID, spelare 1, 2, 3 osv..
    sf::Vector2f pos;			//Spelarens position
    sf::Vector2f old_pos{};     //spelarens gammla position, används vid kollision.
    float rot;					//Spelarens rotation
   
    std::vector<sf::Sprite> hearts;//Behållare för spelaren hjärtan
    std::vector<Bullet> bullets;//Behållare för bullets
    sf::Sprite tank;			
    std::shared_ptr<Power_Up> my_power{};
    bool destroyed;				//Boolean som håller koll på om spelarens har "dött"
	float speed;
	void check_bullets(Player&);
	void set_hearts(sf::Texture& h);
	void print_player_text(sf::RenderTarget & target);
};
#endif
