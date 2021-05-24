#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bullet.h"
#include "Power_Up.h"
#include <memory>
#include <vector>

class Player
{
public:
    Player(int ID, sf::Vector2f const& pos);
    ~Player();
    void update();
    void render(sf::RenderTarget & target);
    void event_handler(sf::Event event);

    std::vector<Projectile*> & get_projectiles();
    sf::Vector2f get_position();                                // returnerar spelarens position    
    sf::Vector2f get_old_position();                            // returnerar spelaren position på bilden innan
    void set_tank_pos(sf::Vector2f new_pos);                    // flyttar spelaren
    bool set_power_up(std::shared_ptr<Power_Up> &new_power);    // ny pointer till power_up
    sf::Sprite const& getPlayerSprite() const;                  // returnerar spelarens sprite
	bool is_destroyed();
    int get_hp();
    void set_hp(int);	

    std::shared_ptr<Power_Up> get_mypower();							

private:	
	int hp;       				//Spelarens liv - spel startar med 3. Bullet skadar -1
	int player_ID;				//Spelarens ID, spelare 1, 2, 3 osv..
    sf::Vector2f pos;			//Spelarens position
    sf::Vector2f old_pos{};     //spelarens gammla position, används vid kollision.
    float rot;					//Spelarens rotation
	sf::Vector2f movement;		//Spelarens rörelseriktning i x och y led. Uppdateras i event_handlern inför varje knapptryck
	
	sf::Sound shot_sound;		//Ljud vid avfyrning av skott
	sf::Sound rocket_sound;		//Ljud vid avfyrning av rocket powerup
	sf::Sound shotgun_sound;	//Ljud vid avfyrning av shotgun powerup
	sf::Sound shield_sound;
	
	sf::Keyboard::Key up;
	sf::Keyboard::Key down;
	sf::Keyboard::Key left;
	sf::Keyboard::Key right;
	sf::Keyboard::Key fire;
	sf::Keyboard::Key activate_powerup;
	
    std::vector<sf::Sprite> hearts;//Behållare för spelaren hjärtan
	
    std::vector<Projectile*> projectiles;	//Vektor med projektiler, dvs rockets och bullets
    sf::CircleShape shield_circle;
    sf::Sprite tank;						//tankens sprite
    sf::Sprite explosion;					//Sprite för explosionsanimationen om en tank förlorar
    
    sf::RectangleShape textsquare;				//Vita rutan vid spelarens text
    sf::Text player_text;						//Spelartexten, "player 1:", "Player 2:"
    std::shared_ptr<Power_Up> my_power{nullptr};
    sf::Vector2f power_print_pos;				//Positionen som powerupen ska skrivas ut bredvid spelartexten när man tar upp en powerup
    bool destroyed;				//Boolean som håller koll på om spelarens har "dött"
	float speed;				//"Hastigheten" som tanken ska förflyttas vid knapptrycks
    int explosion_counter;		//Håller koll på tiden när explosionsspriten skalas upp
    float explosion_scale;

	void set_hearts(sf::Texture& h);	//Fyller på hearts-vektorn med hjärtan
};
#endif
