#include <Player.h>
#include <Constants.h>
#include <cmath>
Player::Player(sf::Texture & t, sf::Vector2f const& p, int ID, sf::Texture & h)
	: hp{3}, player_ID{ID}, pos{p}, rot{}, hearts{}, bullets{}, tank{t}, destroyed{false}, speed{4.0}
{
	tank.setPosition(pos);
    tank.setRotation(rot);
    tank.setScale(0.1, 0.1);
    auto size {t.getSize()};
    tank.setOrigin(size.x / 2, size.y / 2); 
	
	set_hearts(h);
	
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
	
	print_player_text(window);   //skriver ut "Player1: --hjärtan--. Antalet hjärtan justeras med hjälp av players hp
			 
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



sf::FloatRect Player::get_hitbox() const
{
	return tank.getGlobalBounds();

}

std::vector<Bullet>& Player::get_bullets()
{
	return bullets;
}
	
sf::Vector2f Player::get_position()
{
	return pos;
}
	
void Player::set_hearts(sf::Texture& h)
{
	sf::Sprite heart{h};
	heart.setScale(0.05, 0.05);
	
	if (player_ID == 1)
	{
		heart.setPosition(100, 0);
		for (int i{hp}; i > 0; i--)
			{
				hearts.push_back(heart);
				sf::Vector2f old_pos{heart.getPosition()};
				heart.setPosition(old_pos.x + 20.0, old_pos.y);
			}
	}
	else
	{	
		heart.setPosition(screen_width-60, 0);
		for (int i{hp}; i > 0; i--)
			{
				hearts.push_back(heart);
				sf::Vector2f old_pos{heart.getPosition()};
				heart.setPosition(old_pos.x + 20.0, old_pos.y);
			}
	}
}

void Player::print_player_text(sf::RenderTarget & target)
{
	std::string file{"resources/fonts/font.ttf"};
    sf::Font font;
    if(!font.loadFromFile(file))
    {
        throw std::invalid_argument("No font at location: " + file);
    }	
	sf::Text text1{"Player 1:", font, 18};
	sf::Text text2{"Player 2:", font, 18};
	for (int i{1}; i < 3; i++)
	{
		if (i == 1)
		{
			text1.setFillColor(sf::Color::Red);
			target.draw(text1);
		}
		if (i == 2)
		{
			text2.setFillColor(sf::Color::Blue);
			text2.setPosition(screen_width-160, 0);
			target.draw(text2);
		}
	}

for (int i{0}; i < hp; i++)
	{
		target.draw(hearts[i]);
	}



}





