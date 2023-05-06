#include <SFML/Graphics.hpp>
#include<string.h>
#include <iostream>
using namespace std;
using namespace sf;

class Enemy
{
	
	public:


	virtual void fire(float timer)=0;
	
	virtual void move(int y, int i)=0;

	virtual float getX() const =0;

	virtual float getY() const=0;

    virtual void setTexture(string path)=0;

    virtual void draw(RenderWindow &window)=0;

	virtual void setX(int x) = 0;

	virtual bool getMaxY() = 0;

	virtual bool getenmDisp() = 0;

	virtual void displayBomb(RenderWindow& r) = 0;

	virtual bool IsBomb() = 0;

	virtual void resetBomb() = 0;

	virtual void setBombDisp(bool flag) = 0;

	virtual float getTimer() = 0;

	virtual void setTimer(float time) = 0;
};
