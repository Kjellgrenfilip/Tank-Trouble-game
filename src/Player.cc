#include <Player.h>
#include <Constants.h>
#include <cmath>
Player::Player(sf::Texture & t, sf::Vector2f const& p, int ID)
	: hp{3}, player_ID{ID}, pos{p}, rot{}, bullets{}, tank{t}, destroyed{false}, speed{4.0}
{
	tank.setPosition(pos);
    tank.setRotation(rot);
    tank.setScale(0.1, 0.1);
    auto size {t.getSize()};
    tank.setOrigin(size.x / 2, size.y / 2); 
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

		if (player_ID == 1)
	{
		
		
		if ( sf::Keyboard::isKeyPressed (sf::Keyboard::Key::W) )
        {
			tank.move(forward_movement);
			//pos = tank.getPosition();
        }
       if ( sf::Keyboard::isKeyPressed (sf::Keyboard::Key::S) )
        {
			tank.move (-forward_movement);
			//pos = tank.getPosition();
        }
        if ( sf::Keyboard::isKeyPressed (sf::Keyboard::Key::A) )
        {
            tank.rotate (-3);    
			//rot = tank.getRotation();
        }
       if ( sf::Keyboard::isKeyPressed (sf::Keyboard::Key::D) )
        {
            tank.rotate (3);
			//rot = tank.getRotation();
		}
		
	if(event.type == sf::Event::KeyReleased)
		{
			if ( event.key.code == sf::Keyboard::Key::F)
			{
				if (bullets.size() < 4)
				bullets.push_back(Bullet(pos, rot-90));
			}
		}
	}
	if (player_ID == 2)
	{
		if ( sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Up) )
        {
			
			tank.move(forward_movement);
			//pos = tank.getPosition();
        }
       if ( sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Down) )
        {
			
			tank.move (-forward_movement);
			//pos = tank.getPosition();
        }
        if ( sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Left) )
        {
            tank.rotate (-3);    
			//rot = tank.getRotation();
        }
       if ( sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Right) )
        {
            tank.rotate (3);
			//rot = tank.getRotation();
		}
		
		if(event.type == sf::Event::KeyReleased)
		{
			if ( event.key.code == sf::Keyboard::Key::Numpad0)
			{
				if (bullets.size() < 4)
				bullets.push_back(Bullet(pos, rot-90));
			}
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
	
	
	
	
	
	
	 
