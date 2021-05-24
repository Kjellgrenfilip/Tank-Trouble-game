#include <Player.h>
#include <Constants.h>
#include "Resource_Manager.h"
#include <cmath>
#include <algorithm>

Player::Player(int ID, sf::Vector2f const& p)
	: 	hp{3}, player_ID{ID}, 
		pos{p}, rot{}, movement{}, hit_sound{Resource_Manager::get_soundbuffer_hit()}, 
		shot_sound{Resource_Manager::get_soundbuffer_shot()}, rocket_sound{Resource_Manager::get_soundbuffer_rocket()},
		shotgun_sound{Resource_Manager::get_soundbuffer_shotgun()}, shield_sound{Resource_Manager::get_soundbuffer_shield()},
		up{}, down{}, left{}, right{}, fire{}, activate_powerup{}, hearts{}, projectiles{}, shield_circle{40},
		tank{Resource_Manager::get_texture_player(ID)}, explosion{Resource_Manager::get_texture_explosion()}, textsquare{},
		player_text{"Player " + std::to_string(ID) + ':', Resource_Manager::get_font_mandala(), 32}, power_print_pos{},
		destroyed{false}, speed{4.0}, explosion_counter{20}, explosion_scale{0.2}
{
	tank.setPosition(pos);
    tank.setScale(0.1, 0.1);
    auto size {Resource_Manager::get_texture_player(ID).getSize()};
    tank.setOrigin(size.x / 2, size.y / 2); 
	set_hearts(Resource_Manager::get_texture_heart());
	
	auto size2{Resource_Manager::get_texture_explosion().getSize()};
	explosion.setOrigin(size2.x/2, size2.y/2);
	shield_circle.setOrigin(shield_circle.getRadius(), shield_circle.getRadius());
	textsquare.setFillColor(sf::Color{255,255,255,100});
	textsquare.setSize(sf::Vector2f{gridsize_x*6, gridsize_y});
	if (ID == 1)
	{
		up = sf::Keyboard::Key::W;
		down = sf::Keyboard::Key::S;
		left = sf::Keyboard::Key::A;
		right = sf::Keyboard::Key::D;
		fire = sf::Keyboard::Key::F;
		activate_powerup = sf::Keyboard::Key::G;
		tank.setRotation(180);
		textsquare.setPosition(0,0);
		player_text.setFillColor(sf::Color::Red);
		player_text.setPosition(10,0);
		power_print_pos = sf::Vector2f{textsquare.getPosition().x+textsquare.getGlobalBounds().width,0};
		shield_circle.setFillColor(sf::Color{255,0,0,100});
	}
	else if (ID == 2)
	{
		up = sf::Keyboard::Key::Up;
		down = sf::Keyboard::Key::Down;
		left = sf::Keyboard::Key::Left;
		right = sf::Keyboard::Key::Right;
		fire = sf::Keyboard::Key::RControl;
		activate_powerup = sf::Keyboard::Key::RShift;
		tank.setRotation(rot);
		textsquare.setPosition(screen_width-textsquare.getGlobalBounds().width, 0);
		player_text.setFillColor(sf::Color::Blue);
		player_text.setPosition(screen_width-220, 0);
		power_print_pos = sf::Vector2f{textsquare.getPosition().x-gridsize_x,0};
		shield_circle.setFillColor(sf::Color{0,0,255,100});
	}
}

Player::~Player()
{
    for(auto & projectile : projectiles)
    {
        delete projectile;
    }
}

void Player::update()
{
    if(hp == 0)
	{
		destroyed = true;
	}
	 //Kolla eventuella power ups som är aktiva	
	if(dynamic_cast<Speed_Boost*>(my_power.get()) != nullptr && my_power->is_active_on_player())
    {
        if(my_power->get_active_time() <= 0)
        {
            speed = 4.0;
            my_power.reset();
        }
        else
            my_power->dec_active_timer();
    }

    //Uppdatera alla projektiler

    for(auto projectile : projectiles)
    {
        projectile->update();
    }
	
	pos = tank.getPosition();
	rot = tank.getRotation();
	
}


void Player::render(sf::RenderTarget & window)
{
	//Skriva ut, alla skott samt tanken
    for(auto projectile : projectiles)
    {
        projectile->render(window);
    }

	if (!destroyed)
	{
		window.draw(tank);
		if(dynamic_cast<Shield*>(my_power.get()) != nullptr && my_power->is_active_on_player())
		{
			shield_circle.setPosition(get_position());
			window.draw(shield_circle);
		}	
	}
	else
	{
		explosion.setPosition(pos);
		explosion_scale *= 1.1;
		explosion.setScale(explosion_scale, explosion_scale);
		window.draw(explosion);
		explosion_counter--;
	}
	window.draw(textsquare);
	window.draw(player_text);
	//print_player_text(window);   //skriver ut "Player1: --hjärtan--. Antalet hjärtan justeras med hjälp av players hp
	if(my_power!=nullptr)
	{
		my_power->get_sprite().setPosition(power_print_pos);
		window.draw(my_power->get_sprite());
	}

	for (int i{0}; i < hp; i++)
	{
		window.draw(hearts[i]);
	}
}

void Player::event_handler(sf::Event event)
{
	old_pos = pos;
	movement.x = cos((pi/180)*(tank.getRotation()-90)); //Riktningen som tanken ska röra sig i x-led sett från tankens "framdel"
	movement.y = sin((pi/180)*(tank.getRotation()-90));	//Riktningen som tanken ska röra sig i y-led 		-||-
	
		if ( sf::Keyboard::isKeyPressed (up) )
        {
			tank.move(movement*speed);
        }
       	if ( sf::Keyboard::isKeyPressed (down) )
        {
			tank.move (-(movement*speed));		//Eftersom movement är beräknat i riktningen framåt, så blir det en negativ rörelse i motsatt riktning
        }
        if ( sf::Keyboard::isKeyPressed (left) )
        {
            tank.rotate (-3);    
        }
       	if ( sf::Keyboard::isKeyPressed (right) )
        {
            tank.rotate (3);
		}
		
	if(event.type == sf::Event::KeyReleased)
		{
			if ( event.key.code == fire)
			{
				if (projectiles.size() < 4)
				{
					projectiles.push_back(new Bullet(pos, rot-90));
					shot_sound.play();
				}
			}

            if(event.key.code == activate_powerup && my_power != nullptr)
			{
                if(dynamic_cast<Shotgun*>(my_power.get()) != nullptr)
                {   
                    //Skicka iväg tre kulor med olika vinkel
                    shotgun_sound.play();
                    projectiles.push_back(new Bullet(pos, rot-85));
                    projectiles.push_back(new Bullet(pos, rot-90));
                    projectiles.push_back(new Bullet(pos, rot-95));
                    my_power.reset();
                }
                if(dynamic_cast<Rocket*>(my_power.get()) != nullptr)
                {
                    //Skicka iväg en raket
                    rocket_sound.play();
                    projectiles.push_back(new Rocket_Projectile(pos, rot-90));
                    my_power.reset();
                }
                if(dynamic_cast<Speed_Boost*>(my_power.get()) != nullptr)
                {
                    if(!my_power->is_active_on_player())
                    {
                        my_power->set_active_on_player(true);
                        my_power->set_active_time(180);   //3 sekunder i 60 FPS
                        speed = 8.0;                    //Dubbla hastigheten
                    }
                }
                if(dynamic_cast<Shield*>(my_power.get()) != nullptr)
                {
                    //Aktivera sköld
                    if(!my_power->is_active_on_player())
                    {
						shield_sound.play();
						my_power->set_active_on_player(true);
                    }
                }
			}
		}   
}
	
std::vector<Projectile*> & Player::get_projectiles()
{
    return projectiles;
}

sf::Sprite const& Player::getPlayerSprite() const
{
	return tank;
}


sf::FloatRect Player::get_hitbox() const
{
	return tank.getGlobalBounds();

}

sf::Vector2f Player::get_position()
{
	return pos;
}

sf::Vector2f Player::get_old_position()
{
	return old_pos;
}

void Player::set_tank_pos(sf::Vector2f new_pos)
{
	tank.setPosition(new_pos);
}

void Player::set_hearts(sf::Texture& h)
{
	sf::Sprite heart{h};
	heart.setScale(0.08, 0.08);
	
	if (player_ID == 1)
	{
		heart.setPosition(120, 5);
		for (int i{hp}; i > 0; i--)
			{
				hearts.push_back(heart);
				sf::Vector2f old_pos{heart.getPosition()};
				heart.setPosition(old_pos.x + heart.getGlobalBounds().width+2, old_pos.y);
			}
	}
	else
	{	
		heart.setPosition(screen_width- heart.getGlobalBounds().width*3 -10, 5);
		for (int i{hp}; i > 0; i--)
			{
				hearts.push_back(heart);
				sf::Vector2f old_pos{heart.getPosition()};
				heart.setPosition(old_pos.x + heart.getGlobalBounds().width+2, old_pos.y);
			}
	}
}

bool Player::is_destroyed()
{
	if(destroyed && explosion_counter == 0)
		return true;
	else
		return false;
}

bool Player::set_power_up(std::shared_ptr<Power_Up> &new_power)
{
    if(my_power == nullptr)
    {
        my_power = new_power;
        return true;
    }
    else
    {
        return false;
    }
}

int Player::get_hp()
{
	return hp;
}

void Player::set_hp(int x)
{
	hp = x;
}

std::shared_ptr<Power_Up> Player::get_mypower()
{
	return my_power;
}