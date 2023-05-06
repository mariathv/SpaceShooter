#ifndef OPTIONS_H_
#define OPTIONS_H_


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;
using namespace sf;


class Options
{
    int selected;
    public:
    Sprite menu;
    Texture menu_tx;
    Font font;
    int size=2;
    Text *options_menu=new Text[size];
    bool musicFlag;

    SoundBuffer hoverbuffer;
    SoundBuffer selectbuffer;
    Sound hoversound;
    Sound selectsound;

    //add menu attributes here
    Options()
    {
        menu_tx.loadFromFile("img/options.jpg");
        menu.setTexture(menu_tx);
        menu.setScale(1.09, 0.73);

        musicFlag=true;

        selected=-1; //default

        if(!font.loadFromFile("texture/fonts/Space_Theme.ttf"))
        cout<<"could not load"<<endl;

        options_menu[0].setFont(font);
        options_menu[0].setFillColor(Color::White);
        options_menu[0].setString("Music : ON"); 
        options_menu[0].setCharacterSize(30);
        options_menu[0].setPosition(300,300);

        options_menu[1].setFont(font);
        options_menu[1].setFillColor(Color::White);
        options_menu[1].setString("BACK"); 
        options_menu[1].setCharacterSize(30);
        options_menu[1].setPosition(300,375);

        hoverbuffer.loadFromFile("sounds/effects/zap1.ogg");
        hoversound.setBuffer(hoverbuffer);
        hoversound.setVolume(100);

        selectbuffer.loadFromFile("sounds/effects/zap2.ogg");
        selectsound.setBuffer(selectbuffer);
        selectsound.setVolume(100);
    //constructors body
    }

    void display_menu()
    {

        RenderWindow window(VideoMode(780, 780), "options");
        Event s;
        cout<<"optios"<<endl;
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
                            if(musicFlag){
                            options_menu[0].setString("Music : OFF");  musicFlag=false;
                            }
                            else{
                            options_menu[0].setString("Music : ON"); musicFlag=true;
                            }
                        }
                        if(x==1){
                            window.close();
                        }
                    }
                }
            }

             
            window.clear(Color::Black); //clears the screen
            window.draw(menu);  // setting background
            for (int i=0; i<size; i++)
                window.draw(options_menu[i]);
           
            window.display();

            
            
        }
    }

    void moveup(){
        if (selected-1>=0){
            options_menu[selected].setFillColor(Color::White); //the color turns back to white
            selected--;
            if (selected==-1)
            selected=2;

            options_menu[selected].setFillColor(Color::Red);


        }
    }

    void movedown(){
        if (selected+1<size){
            options_menu[selected].setFillColor(Color::White); //the color turns back to white
            selected++;
            if (selected==size)
            selected=0;

            options_menu[selected].setFillColor(Color::Red);
            

        }
    }

    int getSelected(){
        return selected;
    }

};
#endif







