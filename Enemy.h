#include <SFML/Graphics.hpp>
#include<string.h>
#include <iostream>
using namespace std;
using namespace sf;

class Enemy
{
	
	public:
	//Texture tex;
	//Sprite sprite;
	//float speed=0.3;
	//int x=340, y=700;
	//float t_x=0, t_y=0;

	virtual void fire(int size)=0;
	
	virtual void move(int y, int i)=0;

	virtual float getX() const =0;

	virtual float getY() const=0;

    virtual void setTexture(string path)=0;

    virtual void draw(RenderWindow &window)=0;

	virtual void setX(int x) = 0;

	virtual void dropBomb() = 0;

};
