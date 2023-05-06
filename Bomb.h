#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>
#include <iostream>
using namespace std;
using namespace sf;

class Bomb {
public:
	Texture Tex;
	Sprite bomb;

	float speed, t_x, t_y, delta_y, delta_x, org_y;
	int x, y;
	bool max_y, bomb_disp;

	Bomb() {
		Tex.loadFromFile("img/enemy_laser.png");
		bomb.setTexture(Tex);

		speed = 0.35, t_x = 0, t_y = 0, x = 340, y = 700, delta_y = 0, delta_x=0, org_y=0;
		max_y = false; bomb_disp = false;
	}

	void setPos(double x, double y) {
		bomb.setPosition(x+30, y);
		delta_y = org_y = y;
		delta_x = x + 30;
	}

	void Draw(RenderWindow& win) {
		win.draw(bomb);
	}

	void dropBomb() {
		bomb_disp = true;
		delta_y += speed;
		bomb.move(0, 1*speed); 
		//reset();
	}

	void reset() {
		if (delta_y >= 700) {
			
			setPos(delta_x, org_y);
		}
	}
};
