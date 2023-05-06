
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "Invaders.h"
#include "player.h"
#include "pause_menu.h"
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{
public:
Enemy *enm[7];
Pause pauseMenu;
Sprite background; //Game background sprite
Texture bg_texture;
Music music;
Player* p; //player 
bool pause, musicpause;
int wave=1;

// add other game attributes


Game()
{
    p=new Player("img/player_ship.png");
    bg_texture.loadFromFile("img/background2.jpg");
    background.setTexture(bg_texture);
    background.setScale(1.6, 2.65);
    music.openFromFile("sounds/Battle_in_the_Stars.ogg");
    music.setVolume(10);
    music.setLoop(true);
    pause=false;
    musicpause=false;
    for (int i=0; i<7; i++)
    enm[i] = NULL;
}

void start_game()
{
    music.play();

    srand(time(0));
    RenderWindow window(VideoMode(780, 780), title);
    Clock clock;
    double timer = 0, firetimer = 0.3, temptimer = 0;
    int bullet_size=0, bulletspeed=2;
    int index_bul=0;
    bool maxbul=false; // limits the bullet array
    bool firing = false;
    bool TOGGLE = false;

    bool enm_disp = false, enm_allot = false, p_disp = true;
    int enm_dist = 0;
    int* seq = new int[7];
    seq[0] = 1, seq[1] = 3, seq[2] = 5, seq[3] = 0, seq[4] = 2, seq[5] = 4, seq[6] = 6;//bombing sequence
    int seqindx = 0;

    AlphaInvader *A= new AlphaInvader[7];
    for (int i = 0; i < 7; i++) {
        A[i].sprite.setPosition(enm_dist, -200);
        A[i].setX(enm_dist);
        enm_dist += 110;
    }

    
    while (window.isOpen())
    {

        if (!pause) {
            if (pauseMenu.exit) {
                music.stop(); window.close();
            }
            if (pauseMenu.optionMenu.musicFlag == false) {
                music.stop();
                musicpause = true;
            }
            if (pauseMenu.optionMenu.musicFlag == true) {
                if (musicpause) {
                    music.play();
                    musicpause = false;
                }
            }
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed) {// If cross/close is clicked/pressed
                    music.stop();
                    window.close(); //close the game  
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
                p->move("l");    // Player will move to left
            if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
                p->move("r");  //player will move to right
            if (Keyboard::isKeyPressed(Keyboard::Up)) { //If up key is pressed
                p->move("u");    //playet will move upwards
                if (Keyboard::isKeyPressed(Keyboard::Left))
                    p->move("dl");
                if (Keyboard::isKeyPressed(Keyboard::Right))
                    p->move("dr");
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
                p->move("d");  //player will move downwards

            ////////////////////////////////////////////////
            /////  Call your functions here            ////
            //////////////////////////////////////////////

            //ENEMIES

            if (timer >= 5) {
                enm_disp = true;
                if (wave == 1) {
                    if (!enm_allot) {
                        for (int i = 0; i < 7; i++)
                            enm[i] = &A[i];
                        enm_allot = true;
                    }
                    for (int i = 0; i < 7; i++) {
                        enm[i]->move(wave, i); // been called evertime
                    }
                    if (!p->DESTROY)
                        for (int i = 0; i < 7; i++)
                            if (p->getY() <= enm[i]->getY() && (p->getX() > enm[i]->getX() && p->getX() < enm[i]->getX() + 110)) {
                                p->DESTROY = true;
                                p->Destroy();
                                p->lives--;
                                TOGGLE = true;
                                temptimer = timer;
                                break;
                            }
                }
            }
            //ENEMY BOMBING
            if (enm_disp) {
                if (enm[seq[seqindx]]->getMaxY()) {

                    enm[seq[seqindx]]->fire(timer);
                }
            }
            if (p->DESTROY) {
                p_disp = false;
                window.draw(p->Dest);

            }


            //FIRING BULLETS
            if (p_disp)
                p->fire(bullet_size); //fires bullets depending upon the size

            if (enm_disp)
                for (int i = 0; i < 7; i++)
                    for (int j = 0; j < bullet_size; j++)
                        if (p->bullet[j].getY() <= enm[i]->getY() && (p->bullet[j].getX()+340 > enm[i]->getX() && p->bullet[j].getX()+340 < enm[i]->getX() + 110)){
                            cout << "destroy enemy" << i << endl;
        }
           


            if (Keyboard::isKeyPressed(Keyboard::P)){  //pause game
            pause=true;
            music.pause();
            pauseMenu.display_menu();
            pause=false;
            music.play();
            }
            window.clear(Color::Black); //clears the screen
            window.draw(background);  // setting background

           if (timer>=firetimer){
                firing=true;
                firetimer=timer+0.25;
           }

           if (enm_disp) {
               for (int i = 0; i < 7; i++)
                   enm[i]->draw(window);

                    
                   if (enm[seq[seqindx]]->IsBomb()) {
                       
                       enm[seq[seqindx]]->displayBomb(window);
                       if (timer >= enm[seq[seqindx]]->getTimer() + 2) {
                           enm[seq[seqindx]]->resetBomb();
                           seqindx++;
                           if (seqindx == 7) {
                               seqindx = 0;
                               for (int i = 0; i < 7; i++)
                                   enm[i]->setBombDisp(false);
                           }
                            
                           cout << seqindx << endl;
                       }
                       
                   }
              
           }
               if (p_disp) {

                   window.draw(p->sprite);   // setting player on screen
                   if (firing || Keyboard::isKeyPressed(Keyboard::Space)) { //player shoots the bullet
                       firing = false;
                       if (!maxbul)
                           bullet_size++;
                       p->AddBullet(bullet_size);
                       if (index_bul == 10) {
                           maxbul = true;
                           index_bul = 0;
                       }
                       p->pushBack(index_bul);
                       index_bul++;
                   }

                   for (int i = 0; i < bullet_size; i++)
                       window.draw(p->bullet[i].sprite);
               }
               else
                   if (TOGGLE) {
                       p->DrawDest(window);
                       if (timer >= temptimer + 0.5) {
                           temptimer = 0;
                           TOGGLE = false;
                           p->sprite.setPosition(340, 700);
                           p_disp = true;
                           p->reset();
                       }
                   }
            window.display();  //Displying all the sprites
            }
    }
}

~Game(){
    delete p;
}

};

//allot multiple enemies
//destroy enemy
//work with wave 1
//work with bullet addon