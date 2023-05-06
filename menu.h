#include "game.h"
#include "option_menu.h"
#include "Instructions.h"
#include <iostream>
using namespace std;
using namespace sf;


/// ADD A TITLE SCREEN AT THE END
class Menu
{
private:
    int selected;
public:
    Options optionMenu;
    Instructions InstructionsMenu;
    Sprite menu;
    Texture menu_tx;
    Music music;
    Font font;
    Text *main_menu=new Text[6];
    bool music_pause;
    SoundBuffer hoverbuffer;
    SoundBuffer selectbuffer;
    Sound hoversound;
    Sound selectsound;

    bool musicIS;
    //add menu attributes here
    Menu()
    {
        menu_tx.loadFromFile("img/menu.jpg");
        menu.setTexture(menu_tx);
        menu.setScale(1.09, 0.73);

        music.openFromFile("sounds/Menu_Theme.ogg");
        music.setVolume(20);
        music.setLoop(true);
        music_pause=false;
        
        hoverbuffer.loadFromFile("sounds/effects/zap1.ogg");
        hoversound.setBuffer(hoverbuffer);
        hoversound.setVolume(100);

        selectbuffer.loadFromFile("sounds/effects/zap2.ogg");
        selectsound.setBuffer(selectbuffer);
        selectsound.setVolume(100);
        

        selected=-1; //default

        if(!font.loadFromFile("texture/fonts/Space_Theme.ttf"))
        cout<<"could not load"<<endl;

        main_menu[0].setFont(font);
        main_menu[0].setFillColor(Color::White);
        main_menu[0].setString("PLAY"); 
        main_menu[0].setCharacterSize(30);
        main_menu[0].setPosition(330,300);

        main_menu[1].setFont(font);
        main_menu[1].setFillColor(Color::White);
        main_menu[1].setString("LEVELS"); 
        main_menu[1].setCharacterSize(30);
        main_menu[1].setPosition(310,360);

        main_menu[2].setFont(font);
        main_menu[2].setFillColor(Color::White);
        main_menu[2].setString("HIGH SCORE"); 
        main_menu[2].setCharacterSize(30);
        main_menu[2].setPosition(280,420);

        main_menu[3].setFont(font);
        main_menu[3].setFillColor(Color::White);
        main_menu[3].setString("OPTIONS"); 
        main_menu[3].setCharacterSize(30);
        main_menu[3].setPosition(300,480);

        main_menu[4].setFont(font);
        main_menu[4].setFillColor(Color::White);
        main_menu[4].setString("INSTRUCTIONS"); 
        main_menu[4].setCharacterSize(30);  
        main_menu[4].setPosition(240,540);

        main_menu[5].setFont(font);
        main_menu[5].setFillColor(Color::White);
        main_menu[5].setString("EXIT"); 
        main_menu[5].setCharacterSize(30);  
        main_menu[5].setPosition(330,600);


        music.play();
        musicIS=true;




    //constructors body
    }

    void display_menu()
    {
        RenderWindow window(VideoMode(780, 780), title);
        Event s;

        
        while(window.isOpen())
        {
            if(!musicIS)
            music.play();
            if (optionMenu.musicFlag==false){
            music.stop();
            music_pause=true;
            }
            if (optionMenu.musicFlag==true){
                if(music_pause){
                    music.play();
                    music_pause=false;
                }
            }
            
            while (window.pollEvent(s))
            { 
                if (s.type == Event::Closed) // If cross/close is clicked/pressed
                        window.close();
            
                if (s.type == s.KeyReleased){
                    hoversound.play();
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
                            Game g;
                            music.stop();
                            window.close();
                            g.start_game();
                            display_menu();
                            music.play();
                            musicIS=false;
                            
                        }
                        if(x==1){

                        }
                        if (x==2){

                        }
                        if (x==3){
                            window.close();
                            optionMenu.display_menu();
                            display_menu();
                        }
                        if (x==4){
                            window.close();
                            InstructionsMenu.display_menu();
                            display_menu();
                        }
                        if (x==5){
                            window.close();
                        }
                    }
                }
            }
             
            window.clear(Color::Black); //clears the screen
            window.draw(menu);  // setting background
            for (int i=0; i<6; i++)
                window.draw(main_menu[i]);
           
            window.display();

            
            
        }
    }

    
    void moveup(){
        if (selected-1>=0){
            main_menu[selected].setFillColor(Color::White); //the color turns back to white
            selected--;
            if (selected==-1)
            selected=2;

            main_menu[selected].setFillColor(Color::Red);


        }
    }

    void movedown(){
        if (selected+1<6){
            main_menu[selected].setFillColor(Color::White); //the color turns back to white
            selected++;
            if (selected==6)
            selected=0;

            main_menu[selected].setFillColor(Color::Red);
            

        }
    }

    int getSelected(){
        return selected;
    }
};
