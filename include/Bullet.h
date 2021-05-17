#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "Resource_Manager.h"


class Bullet
{
    public:
        Bullet(sf::Vector2f pos, float rot);    //Koordinater för spelaren, rotationen för spelaren (just nu i radianer)
        void update();
        void render(sf::RenderTarget&);

        sf::FloatRect getBounds();              //Returnerar GlobalBounds för sprite
        sf::Vector2f get_velocity();            //Returnera hastigheten (pixlar per frame)
        void reverse_x();                       //Byt riktning i x-led
        void reverse_y();                       //Byt riktning i y-led
        int lifetime;                           //Antal studs kulan har kvar att leva
    protected:                       
        sf::Vector2f velocity;                  //Hastighet
        
    private:
        sf::CircleShape sprite;
};

class Rocket_Projectile
{
    public:
        Rocket_Projectile(sf::Vector2f pos, float rot);    //Koordinater för spelaren, rotationen för spelaren (just nu i radianer)
        void update();
        void render(sf::RenderTarget&);

        sf::FloatRect getBounds();              //Returnerar GlobalBounds för sprite
        sf::Vector2f get_velocity();            //Returnera hastigheten (pixlar per frame)
        void reverse_x();                       //Byt riktning i x-led
        void reverse_y();                       //Byt riktning i y-led
        int lifetime;                           //Antal studs kulan har kvar att leva
    protected:                       
        sf::Vector2f velocity;                  //Hastighet
        
    private:
        sf::Sprite sprite;
};

#endif