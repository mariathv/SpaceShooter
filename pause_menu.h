
#include "option_menu.h"
#include <iostream>
using namespace std;
using namespace sf;

class Pause
{
    int selected;
    public:
    Options optionMenu;
    Sprite menu;
    Texture menu_tx;
    Font font;
    int size=3;
    Text *pause_menu=new Text[size];
    bool musicFlag;
    bool exit;

    SoundBuffer hoverbuffer;
    SoundBuffer selectbuffer;
    Sound hoversound;
    Sound selectsound;
    Music music;

    //add menu attributes here
    Pause()
    {
        menu_tx.loadFromFile("img/pause_menu.jpg");
        menu.setTexture(menu_tx);
        menu.setScale(1.09, 0.72);

        musicFlag=true; exit=false;

        selected=-1; //default

        if(!font.loadFromFile("texture/fonts/Space_Theme.ttf"))
        cout<<"could not load"<<endl;

        pause_menu[0].setFont(font);
        pause_menu[0].setFillColor(Color::White);
        pause_menu[0].setString("Resume"); 
        pause_menu[0].setCharacterSize(30);
        pause_menu[0].setPosition(300,380);

        pause_menu[1].setFont(font);
        pause_menu[1].setFillColor(Color::White);
        pause_menu[1].setString("Options"); 
        pause_menu[1].setCharacterSize(30);
        pause_menu[1].setPosition(300,485);

        pause_menu[2].setFont(font);
        pause_menu[2].setFillColor(Color::White);
        pause_menu[2].setString("Quit"); 
        pause_menu[2].setCharacterSize(30);
        pause_menu[2].setPosition(300,590);

        hoverbuffer.loadFromFile("sounds/effects/zap1.ogg");
        hoversound.setBuffer(hoverbuffer);
        hoversound.setVolume(100);

        selectbuffer.loadFromFile("sounds/effects/zap2.ogg");
        selectsound.setBuffer(selectbuffer);
        selectsound.setVolume(100);

        music.openFromFile("sounds/Title_Screen.ogg");
        music.setVolume(20);
        music.setLoop(true);
        
    //constructors body
    }

    void display_menu()
    {
        if(musicFlag)
        music.play();
        RenderWindow window(VideoMode(780, 780), "pause");
        Event s;
        //cout<<"optios"<<endl;
        while(window.isOpen())
        {
            while (window.pollEvent(s))
            { 
                hoversound.play();
                if (s.type == Event::Closed) // If cross/close is clicked/pressed
                        window.close();
            
                if (s.type == s.KeyReleased){
                    if (s.key.code == Keyboard::Up){
                        moveup();
                        break;
                    }
                    if (s.key.code == Keyboard::Down){
                        movedown();
                        break;
                    }
                    if (s.key.code == Keyboard::Return){
                        selectsound.play();
                        int x=getSelected();
                        if (x==0){
                            music.stop();
                            musicFlag=true;
                            window.close();
                        }
                        if(x==1){
                            window.close();
                            optionMenu.display_menu();
                            musicFlag=false;
                            display_menu();
                        }
                        if (x==2){
                            music.stop();
                            musicFlag=false;
                            exit=true;
                            window.close();
                        }
                    }
                }
            }

             
            window.clear(Color::Black); //clears the screen
            window.draw(menu);  // setting background
            for (int i=0; i<size; i++)
                window.draw(pause_menu[i]);
           
            window.display();

            
            
        }
    }

    void moveup(){
        if (selected-1>=0){
            pause_menu[selected].setFillColor(Color::White); //the color turns back to white
            selected--;
            if (selected==-1)
            selected=2;

            pause_menu[selected].setFillColor(Color::Red);


        }
    }

    void movedown(){
        if (selected+1<size){
            pause_menu[selected].setFillColor(Color::White); //the color turns back to white
            selected++;
            if (selected==size)
            selected=0;

            pause_menu[selected].setFillColor(Color::Red);
            

        }
    }

    int getSelected(){
        return selected;
    }

};







