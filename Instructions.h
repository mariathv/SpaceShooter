#ifndef HEADER_H_
#define HEADER_H_


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class Instructions
{
    int selected;
    public:
    Sprite ins;
    Font font;
    Texture tex;
    int size=1;
    Text *Ins=new Text[size];
    bool music_flag;

    SoundBuffer hoverbuffer;
    SoundBuffer selectbuffer;
    Sound hoversound;
    Sound selectsound;

    Instructions(){
        selected=-1;
        music_flag=false;
        tex.loadFromFile("img/instruction.jpg");
        ins.setTexture(tex);
        ins.setScale(1.08,0.73);

        if(!font.loadFromFile("texture/fonts/Space_Theme.ttf"))
        cout<<"could not load"<<endl;

        Ins[0].setFont(font);
        Ins[0].setFillColor(Color::White);
        Ins[0].setString("BACK"); 
        Ins[0].setCharacterSize(30);
        Ins[0].setPosition(340,650);


        hoverbuffer.loadFromFile("sounds/effects/zap1.ogg");
        hoversound.setBuffer(hoverbuffer);
        hoversound.setVolume(100);

        selectbuffer.loadFromFile("sounds/effects/zap2.ogg");
        selectsound.setBuffer(selectbuffer);
        selectsound.setVolume(100);
    }

    void display_menu()
    {
        RenderWindow window(VideoMode(780, 780), "Instructions");
        Event s;
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
                            window.close();
                        }
                    }
                }
            }

                
            window.clear(Color::Black); //clears the screen
            window.draw(ins);  // setting background
            for (int i=0; i<size; i++)
                window.draw(Ins[i]);
            
            window.display();
        }
    }

    void moveup(){
        if (selected-1>=0){
            Ins[selected].setFillColor(Color::White); //the color turns back to white
            selected--;
            if (selected==-1)
            selected=1;

            Ins[selected].setFillColor(Color::Red);


        }
    }

    void movedown(){
        if (selected+1<size){
            Ins[selected].setFillColor(Color::White); //the color turns back to white
            selected++;
            if (selected==size)
            selected=0;

            Ins[selected].setFillColor(Color::Red);
            

        }
    }

    int getSelected(){
        return selected;
    }
};





#endif