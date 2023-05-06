#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>
#include <iostream>
using namespace std;
using namespace sf;

class Bullet
{
    public:
    Texture texture;
    Sprite sprite;
    
    float t_x, t_y;
    float speed=0.5;
    float delta_x, delta_y;
    Bullet()
    {
        texture.loadFromFile("img/PNG/Lasers/laserBlue01.png");
        sprite.setTexture(texture);
        sprite.setPosition(0,0);
        //sprite.setScale(0.75, 0.75);
        t_x = 0;
        t_y = 0;
        delta_x=0;
        delta_y=0;

        
        //Laser1.play();
    }
    Bullet(std::string path)
    {
        texture.loadFromFile(path);
        sprite.setTexture(texture);
        sprite.setPosition(0,0);
        //sprite.setScale(0.75, 0.75);
        delta_x=0;
        delta_y=0;

        //Laser1Buffer.loadFromFile("sounds/effects/laser3.ogg");
        //Laser1.setBuffer(Laser1Buffer);
        //Laser1.play();
    }

    void setPos(float x, float y){
        sprite.setPosition(x,y);
        
    }

    void setTexture(string path){
        texture.loadFromFile(path);
        sprite.setTexture(texture);
        sprite.setPosition(0,0);
    }
    void draw(sf::RenderWindow &window){
        window.draw(sprite);
    }

    float getY() {
        return t_y+700;
    }
    float getX() {
        return t_x;
    }
};