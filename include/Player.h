#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bullet.h"
#include "Power_Up.h"
#include <memory>
#include <vector>
#include "Shotgun.h"
#include "Rocket.h"
#include "Speed_Boost.h"
#include "Shield.h"

class Player
{
public:
    Player(int ID, sf::Vector2f const& pos);

    void update(Player&);
    void render(sf::RenderTarget & target);
    void event_handler(sf::Event event);
	
	sf::FloatRect get_hitbox() const;                           // Returnar playerns hitbox
	std::vector<Bullet>& get_bullets();                        	// Hämtar en vector med bullets
    std::vector<Rocket_Projectile>& get_rockets();
    sf::Vector2f get_position();                                // returnerar spelarens position    
    sf::Vector2f get_old_position();                            // returnerar spelaren position på bilden innan
    void set_tank_pos(sf::Vector2f new_pos);                    // flyttar spelaren
    bool set_power_up(std::shared_ptr<Power_Up> &new_power);    // ny pointer till power_up
    sf::Sprite const& getPlayerSprite() const;                  // returnerar spelarens sprite
	bool is_destroyed();
private:
	
	int hp;       				//Spelarens liv - spel startar med 3. Bullet skadar -1
	int player_ID;				//Spelarens ID, spelare 1, 2, 3 osv..
    sf::Vector2f pos;			//Spelarens position
    sf::Vector2f old_pos{};     //spelarens gammla position, används vid kollision.
    float rot;					//Spelarens rotation
	
	sf::Sound hit_sound;
	sf::Sound shot_sound;
	sf::Sound rocket_sound;
	sf::Sound shotgun_sound;
	
	sf::Keyboard::Key up;
	sf::Keyboard::Key down;
	sf::Keyboard::Key left;
	sf::Keyboard::Key right;
	sf::Keyboard::Key fire;
	sf::Keyboard::Key activate_powerup;
	
    std::vector<sf::Sprite> hearts;//Behållare för spelaren hjärtan
    std::vector<Bullet> bullets;   //Behållare för bullets
    std::vector<Rocket_Projectile> rockets;
    sf::Sprite tank;
    sf::Sprite explosion;
    sf::RectangleShape textsquare;			
    std::shared_ptr<Power_Up> my_power{nullptr};
    bool destroyed;				//Boolean som håller koll på om spelarens har "dött"
	float speed;
    int explosion_counter;
    float explosion_scale;

	void check_bullets(Player&);
	void set_hearts(sf::Texture& h);
	void print_player_text(sf::RenderTarget & target);
};
#endif
