#include <SFML/Graphics.hpp>
#include<string.h>
#include <iostream>
#include "Bullet.h"
using namespace std;
using namespace sf;


class Player
{

public:
	Bullet* bullet;
	Texture tex;
	Sprite sprite;
	Sprite DiagL;
	Sprite DiagR;
	Sprite Dest;

	int lives = 3;

	bool DESTROY;

	float speed = 0.3;
	float x, y;
	float t_x, t_y;
	bool isFire;
	bool diagonal;
	Texture TexL, TexR, des;
	int bulletspeed;
	Sound Laser1;
	SoundBuffer Laser1Buffer;

	Sound DestroySound;
	SoundBuffer DestroyBuffer;

	Player(std::string png_path)
	{
		//cout<<"called"<<endl;
		isFire = false;
		tex.loadFromFile(png_path);
		TexL.loadFromFile("img/player_ship_diagonal_left.png");
		TexR.loadFromFile("img/player_ship_diagonal_right.png");
		sprite.setTexture(tex);
		x = 340; y = 700;
		t_x = 0; t_y = 0;
		sprite.setPosition(x, y);  //y = -75 ~ the top grid
		sprite.setScale(0.75, 0.75);
		diagonal = false;
		bulletspeed = 1;
		Laser1Buffer.loadFromFile("sounds/effects/laser3.ogg");
		Laser1.setBuffer(Laser1Buffer);
		Laser1.setVolume(100);

		des.loadFromFile("img/player_explosion.png");
		Dest.setTexture(des);
		Dest.setScale(0.75, 0.75);

		DestroyBuffer.loadFromFile("sounds/effects/ship_destroyed.ogg");
		DestroySound.setBuffer(DestroyBuffer);
		DestroySound.setVolume(100);

		DESTROY = false;
	}

	void fire(int size)
	{
		//cout<<"move"<<endl;
		for (int i = 0; i < size; i++) {
			
			bullet[i].delta_y = -1;
			bullet[i].delta_y *= bulletspeed;
			bullet[i].t_x = t_x;
			bullet[i].t_y += bullet[i].delta_y;
			//cout << bullet[0].t_y << endl;
			bullet[i].sprite.move(0, bullet[i].delta_y);
			if (bullet[i].t_y > 0) {
				bullet[i].work = false;
			}
		}
	}

	void AddBullet(int size) {
		Laser1.play();
		Bullet* Temp = new Bullet[size - 1];
		if (size - 1) {
			for (int i = 0; i < size - 1; i++) {
				Temp[i]=bullet[i]; //this causes a little error (warnings, fix later)
			}

		}
		//delete [] bullet;
		bullet = new Bullet[size];
		if (size - 1) {
			for (int i = 0; i < size - 1; i++)
				bullet[i] = Temp[i];
		}

		bullet[size - 1].setTexture("img/PNG/Lasers/laserBlue01.png");
		bullet[size - 1].setPos(getX() + 35, getY());
		delete[] Temp;
	}

	void bulletSort(int size) {
		Bullet* Temp = new Bullet[size];
		for (int i = 0; i < size; i++) {
			Temp[i] = bullet[i];
			//Temp[i].setTexture("img/PNG/Lasers/laserBlue01.png");
		}
		delete[] bullet;

		bullet = new Bullet[size - 5];
		for (int i = 0, j = 5; i < size - 5; i++, j++) {
			bullet[i] = Temp[j];
		}

		//delete[] Temp;

	}

	void pushBack(int n) {
		//	cout<<"pushing back"<<endl;
		bullet[n].setTexture("img/PNG/Lasers/laserBlue01.png");
		bullet[n].setPos(getX() + 35, getY());

	}
	void move(std::string s) {

		if (diagonal) {
			tex.loadFromFile("img/player_ship.png");
			sprite.setTexture(tex);
			diagonal = false;
		}
		float delta_x = 0, delta_y = 0;
		if (s == "l")
			delta_x = -1;

		else if (s == "r")
			delta_x = 1;
		if (s == "u")
			delta_y = -1;
		else if (s == "d")
			delta_y = 1;
		else if (s == "dl") { // diagonal left movement
			sprite.setTexture(TexL);
			diagonal = true;
		}
		else if (s == "dr") { //diagonal right movement
			
			sprite.setTexture(TexR);
			diagonal = true;
		}



		delta_x *= speed;
		delta_y *= speed;

		t_y += delta_y;
		t_x += delta_x;

		//wrap screen
		if (t_y <= -700) {
			sprite.move(sf::Vector2f(0, y));
			t_y = 0;
		}
		else if (t_y > 0) {
			t_y = 0;
			return;
		}
		else if (t_x > 340) {
			sprite.move(-2 * x, 0);
			t_x = -340;
		}
		else if (t_x < -340) {
			sprite.move(2 * x, 0);
			t_x = 340;
		}

		//cout<<t_x<<endl;

		sprite.move(delta_x, delta_y);
	}

	float getX() const
	{
		return t_x + x;
	}

	float getY() const
	{
		return t_y + y;
	}

	void Destroy() {
		Dest.setPosition(getX(), getY());
		DestroySound.play();
	}

	void DrawDest(RenderWindow& window) {
		window.draw(Dest);
	}

	void reset() {
		DESTROY = false;
		t_x = t_y = 0;
	}

	~Player() {
		delete[] bullet;
	}
};

