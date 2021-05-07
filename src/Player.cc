#include <Player.h>
#include <Constants.h>
#include <cmath>
Player::Player(sf::Texture & t, sf::Vector2f const& p)
	: hp{3}, player_ID{}, pos{p}, rot{}, bullets{}, tank{t}, destroyed{false}, speed{4.0}
{

}

void Player::update()
{
	//Uppdatera alla bullets	
	for (auto & bullet : bullets)
	{
		bullet.update();
	}
	
	pos = tank.getPosition();
	rot = tank.getRotation();
	
}


void Player::render(sf::RenderTarget & window)
{
	//Skriva ut, alla skott samt tanken
	for (auto & bullet : bullets)
	{
		bullet.render(window);
	}
	window.draw(tank);
}

void Player::event_handler(sf::Event event)
{
	sf::Vector2f forward_direction;
	forward_direction.x = cos((pi/180)*(tank.getRotation()-90));
	forward_direction.y = sin((pi/180)*(tank.getRotation()-90));
	sf::Vector2f forward_movement = forward_direction * speed;

		if ( sf::Keyboard::isKeyPressed (sf::Keyboard::Key::W) )
        {
			tank.move(forward_movement);
        }
        if ( sf::Keyboard::isKeyPressed (sf::Keyboard::Key::S) )
        {
			tank.move (-forward_movement);
        }
        if ( sf::Keyboard::isKeyPressed (sf::Keyboard::Key::A) )
        {
            tank.rotate (-3);    
        }
        if ( sf::Keyboard::isKeyPressed (sf::Keyboard::Key::D) )
        {
            tank.rotate (3);
        }
		
		if(event.KeyPressed == sf::Event::KeyPressed)
		{
			if ( event.key.code == sf::Keyboard::Key::F)
			{
				
				bullets.push_back(Bullet(pos, tank.getRotation()));
			}
    }

}



sf::FloatRect Player::get_hitbox(sf::Sprite & t)
{
	return t.getGlobalBounds();

}

std::vector<Bullet>& Player::get_bullets()
{
	
}
	
	
	
	
	
	
	 
