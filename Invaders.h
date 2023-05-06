#include <SFML/Graphics.hpp>
#include<string.h>
#include <iostream>
#include "Enemy.h"
using namespace std;
using namespace sf;

class Invader : public Enemy
{
public:
 
  
};

class AlphaInvader : public Invader
{
    public:
	Texture tex;
	Sprite sprite;
    Texture Bomb;
    Sprite bSprite;
	float speed=0.1;
	int x,y;
	float t_x, t_y;
    bool max_y;
    int lane_y;


    

    AlphaInvader()
    {
        tex.loadFromFile("img/enemy_1.png");
        sprite.setTexture(tex);
        sprite.setPosition(0, -200);
        sprite.setScale(0.75, 0.75);
        t_x = 0; t_y = -200, lane_y = 0;
        x = 340; y = 700;
        max_y = false;

        Bomb.loadFromFile("img/enemy_laser.png");
        bSprite.setTexture(Bomb);
        bSprite.setPosition(getX(), lane_y);

      
    }

    virtual void dropBomb()
    {
        if (getY() >= lane_y) {
            bSprite.move(getX(), 1);
        }
        //cout << getY()<<" ";
    }

	void fire(int size)
    {

    }
	
	void move(int y, int i)
    {
        lane_y=0;
        switch(y){
            case 1: lane_y=20;
        }
        if (t_y < lane_y) {
            //cout << i << endl;
            float delta_x = 0, delta_y = 0;

            delta_y = 1;
            //delta_x*=speed;
            //delta_y*=speed;

            //cout<<delta_y<<endl;
            t_y += delta_y;
            //t_x+=delta_x;

            //cout<<t_y<<" "<<t_x<<endl;

            sprite.move(delta_x, delta_y);
        }
        else
            max_y-true;
        
    }

	float getX() const 
    {
        return t_x;
    }

	float getY() const
    {
        return t_y;
    }
    void setX(int x) {
        t_x = x;
    }
    virtual void setTexture(string path){
        tex.loadFromFile(path);
        sprite.setTexture(tex);
       // sprite.setPosition(0,0);
    }

    void draw(RenderWindow &window)
    {
        window.draw(sprite);
    }

   
};

class BetaInvader : public Invader
{
    public:
	Texture tex;
	Sprite sprite;
	float speed=0.1;
	int x,y;
	float t_x, t_y;

    BetaInvader()
    {
        tex.loadFromFile("img/enemy_2.png");
        sprite.setTexture(tex);
        sprite.setPosition(0,-200);
        sprite.setScale(0.75, 0.75);
        t_x=0; t_y=-200;
        x=340; y=700;
        //sprite.setScale(0.75, 0.75);
       // delta_x=0;
        //delta_y=0;

        
        //Laser1.play();
    }

	void fire(int size)
    {

    }
	
	void move(int y)
    {
        int lane_y=0;
        switch(y){
            case 1: lane_y=20;
        }
        if (t_y<lane_y){
        float delta_x=0,delta_y=0;

        delta_y=1;
		//delta_x*=speed;
		//delta_y*=speed;

        cout<<delta_y<<endl;
		t_y+=delta_y;
		t_x+=delta_x;

        cout<<t_y<<" "<<t_x<<endl;

		sprite.move(delta_x, delta_y);
        }
        
    }

	float getX() const 
    {
        return t_x;
    }

	float getY() const
    {
        return t_y;
    }

    void setX(int x) {
        t_x = x;
    }

    virtual void setTexture(string path){
        tex.loadFromFile(path);
        sprite.setTexture(tex);
        sprite.setPosition(0,0);
    }

    void draw(RenderWindow &window)
    {
        window.draw(sprite);
    }
};

class GammaInvader : public Invader
{
    public:
	Texture tex;
	Sprite sprite;
	float speed=0.1;
	int x,y;
	float t_x, t_y;

    GammaInvader()
    {
        tex.loadFromFile("img/enemy_3.png");
        sprite.setTexture(tex);
        sprite.setPosition(0,-200);
        sprite.setScale(0.75, 0.75);
        t_x=0; t_y=-200;
        x=340; y=700;
        //sprite.setScale(0.75, 0.75);
       // delta_x=0;
        //delta_y=0;

        
        //Laser1.play();
    }

	void fire(int size)
    {

    }
	
	void move(int y)
    {
        int lane_y=0;
        switch(y){
            case 1: lane_y=20;
        }
        if (t_y<lane_y){
        float delta_x=0,delta_y=0;

        delta_y=1;
		//delta_x*=speed;
		//delta_y*=speed;

        cout<<delta_y<<endl;
		t_y+=delta_y;
		t_x+=delta_x;

        cout<<t_y<<" "<<t_x<<endl;

		sprite.move(delta_x, delta_y);
        }
        
    }

	float getX() const 
    {
        return t_x;
    }

	float getY() const
    {
        return t_y;
    }

    void setX(int x) {
        t_x = x;
    }

    virtual void setTexture(string path){
        tex.loadFromFile(path);
        sprite.setTexture(tex);
        sprite.setPosition(0,0);
    }

    void draw(RenderWindow &window)
    {
        window.draw(sprite);
    }
};
