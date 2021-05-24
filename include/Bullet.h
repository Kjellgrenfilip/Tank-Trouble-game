#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Projectile
{
    public:
        Projectile() = default;
        Projectile(float rot, int life, sf::Texture & texture);                  //Tar in spelarens rotaion för att bestämma riktning på projektil
        virtual ~Projectile() = default;

        void update();
        void render(sf::RenderTarget&);
        sf::Sprite & get_sprite();

        sf::Vector2f & get_velocity();            //Returnera hastigheten (pixlar per frame)
        void reverse_x();                       //Byt riktning i x-led
        void reverse_y();                       //Byt riktning i y-led

        int lifetime;                           //Antal studs kulan har kvar att leva
    protected:                       
        sf::Vector2f velocity;                  //Hastighet
        sf::Sprite sprite;
};

class Bullet : public Projectile
{
    public:
        Bullet(sf::Vector2f const & pos, float rot);    
};

class Rocket_Projectile : public Projectile
{
    public:
        Rocket_Projectile(sf::Vector2f const & pos, float rot);
};

#endif