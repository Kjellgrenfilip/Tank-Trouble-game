#include <Player.h>

Player::Player(sf::Texture & t, sf::Vector2f const& p)
	: hp{3}, player_ID{}, pos{p}, rot{},bullets{get_bullets()}, tank{t}, destroyed{false}, speed{4.0}
{

}

void Player::update()
{
	//Uppdatera alla bullets	
	/*for (auto & bullet : bullets)
	{
		bullet.update(w);
	}*/

	
}


void Player::render(sf::RenderTarget & window)
{
	//Skriva ut, alla skott samt tanken
	/*for (auto & bullet : bullets)
	{
		bullet.render(window);
	}*/
	//window.draw(tank);
}

void Player::event_handler(sf::Event event)
{
	sf::Vector2f forward_direction;
	forward_direction.x = cos((pi/180)*(tank.getRotation()-90));
	forward_direction.y = sin((pi/180)*(tank.getRotation()-90));
	sf::Vector2f forward_movement = forward_direction * speed;

		if ( Keyboard::isKeyPressed (Keyboard::Key::W) )
        {
			tank.move(forward_movement);
        }
        if ( Keyboard::isKeyPressed (Keyboard::Key::S) )
        {
			tank.move (-forward_movement);
        }
        if ( Keyboard::isKeyPressed (Keyboard::Key::A) )
        {
            tank.rotate (-3);    
        }
        if ( Keyboard::isKeyPressed (Keyboard::Key::D) )
        {
            tank.rotate (3);
        }
		
		if (Keyboard::isKeyPressed (Keyboard::Key::Space))
		{
			//fire bullet
		}

}



sf::FloatRect get_hitbox()
{
	return tank.getGlobalBounds();

}

std::Vector<Bullet>& get_bullets()
{
	
}
	
	
	
	
	
	
	 
