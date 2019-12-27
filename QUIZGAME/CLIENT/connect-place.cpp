#include <sys/types.h>
#include <arpa/inet.h>  
#include <sys/socket.h> 
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <string>
#include<errno.h>
#include "connection.h"
#include "game.cpp"





void play_connect(sf::RenderWindow & window){
    
    float x,y;
    window.clear();
    button menuButton[4];
    //BUTTON SIZES
    menuButton[0]={30,30,WI-80,HE-80};
    menuButton[1]={2*WI/5,HE/6,WI/2-WI/5,HE/2-2*HE/6};
    menuButton[2]={2*WI/5-100,HE/6,WI/2-WI/5-200,HE/2-2*HE/6};
    menuButton[3]={2*WI/5-100,HE/6,WI/2-WI/2+300,HE/2-2*HE/6};
    button menuTextBox[3];
    menuTextBox[0]={500,100,menuButton[1].x,menuButton[1].y+menuButton[1].heigth+50};
    menuTextBox[1]={500,100,menuButton[1].x,menuButton[1].y+2*menuButton[1].heigth+50};
    menuTextBox[2]={500,100,menuButton[1].x,menuButton[1].y+3*menuButton[1].heigth+50};

    //set text
      sf::Font font;
    font.loadFromFile("Arial.ttf");
    //SET TEXT
    sf::Text text[2];
    text[0].setString("Connect");    
    text[1].setString("Login");
    for(int i = 0;i<2;i++){
        text[i].setFont(font);
        text[i].setCharacterSize(40);
        text[i].setFillColor(sf::Color(50,205,50));
        text[i].setStyle(sf::Text::Bold);
    }
    text[0].setPosition(menuButton[2].x+30,menuButton[2].y);
    text[1].setPosition(menuButton[3].x+30,menuButton[3].y);
    sf::Text textBox[3];
    textBox[0].setString("Ip");
    textBox[1].setString("Port");
    textBox[2].setString("Nume");

    for(int i = 0;i<3;i++){
        textBox[i].setFont(font);
        textBox[i].setCharacterSize(40);
        textBox[i].setFillColor(sf::Color(50,205,50));
        textBox[i].setStyle(sf::Text::Bold);
    }
    
    //
    //BUTTON INIT
    sf::RectangleShape myMenuButtons[3],myMenuTextBox[3];
    //textBoxSetting
    textBox[0].setPosition(menuTextBox[0].x-100,menuTextBox[0].y+30);
    textBox[1].setPosition(menuTextBox[1].x-150,menuTextBox[1].y+30);
    textBox[2].setPosition(menuTextBox[2].x-150,menuTextBox[2].y+30);
    for(int i =0;i<3;i++){
        myMenuTextBox[i]=sf::RectangleShape(sf::Vector2f(menuTextBox[i].width,menuTextBox[i].heigth));
        myMenuTextBox[i].setPosition(menuTextBox[i].x,menuTextBox[i].y);
        myMenuTextBox[i].setOutlineThickness(2);
        myMenuTextBox[i].setOutlineColor(sf::Color(129, 199, 132));
        myMenuTextBox[i].setFillColor(sf::Color::Black);
        
        window.draw(myMenuTextBox[i]);
        window.draw(textBox[i]);
        }
        
    //BUTTON SETTINGS
    for(int i =0;i<3;i++){
        myMenuButtons[i]=sf::RectangleShape(sf::Vector2f(menuButton[i].width,menuButton[i].heigth));
        myMenuButtons[i].setPosition(menuButton[i].x,menuButton[i].y);
        myMenuButtons[i].setOutlineThickness(5);
        myMenuButtons[i].setOutlineColor(sf::Color::Green);
        myMenuButtons[i].setFillColor(sf::Color::Black);
        if(i==1||i==2){
            myMenuButtons[i]=sf::RectangleShape(sf::Vector2f(menuButton[i+1].width,menuButton[i+1].heigth));
            myMenuButtons[i].setPosition(menuButton[i+1].x,menuButton[i+1].y);
            myMenuButtons[i].setOutlineThickness(5);
            myMenuButtons[i].setOutlineColor(sf::Color::Green);
            myMenuButtons[i].setFillColor(sf::Color::Black);
        }
        window.draw(myMenuButtons[i]);
    }
    
    window.draw(text[0]);
    window.draw(text[1]);
    int back= 0;
    sf::String playerInput[3];
    sf::Text playerText[3];
    for(int i = 0;i<3;i++){
        playerText[i].setFillColor(sf::Color::Red);
        playerText[i].setFont(font);
        playerText[i].setPosition(menuTextBox[i].x+10,menuTextBox[i].y+30);
        playerText[i].setCharacterSize(35);
    }
    sf::RectangleShape fillRect(sf::Vector2f(menuTextBox[0].width-1,menuTextBox[0].heigth-1));
    fillRect.setFillColor(sf::Color::Black);
    fillRect.setPosition(menuTextBox[0].x+1,menuTextBox[0].y+1);
    //////////////////////////
    int wS =0;//writing state
    myMenuTextBox[wS].setOutlineColor(sf::Color::Green);
    //defaut parameters
    playerInput[0]="127.0.0.1";
    playerInput[1]="2908";
    srand(time(NULL));
    char words[]="bcdfghjklmnpqrstvwxyzaeiouy";
    int lenght = strlen(words);
    string name="";
    for(int i =0;i<5;i++){
        name+=words[rand()%lenght];
    }
    playerInput[2]=name;
    for(int i =0;i<3;i++){
        playerText[i].setString(playerInput[i]);
        window.draw(playerText[i]);
    }
    //window to display message from server
    button server_display={600,100,199,1};
    sf::Text sv_display,sv_diplayer;
    sv_display.setFont(font);
    sv_display.setString("Status-Sv:");
    sv_display.setFillColor(sf::Color::Green);
    sv_display.setPosition(server_display.x-125,server_display.y+30);
    sv_display.setCharacterSize(25);
    sv_diplayer=sv_display;
    sv_diplayer.setFillColor(sf::Color::Blue);
    sv_diplayer.setPosition(server_display.x+100,server_display.y+30);
    sv_diplayer.setCharacterSize(40);
    sf::RectangleShape myServer_display(sf::Vector2f(server_display.width,server_display.heigth));
    myServer_display.setFillColor(sf::Color::Black);
    myServer_display.setPosition(server_display.x,server_display.y);
    myServer_display.setOutlineColor(sf::Color::Red);
    myServer_display.setOutlineThickness(1);
    window.draw(myServer_display);
    window.draw(sv_display);
    window.display();
    //SERVER ACTIVITIES
    bool connected=0;
    int sd=-1;
    //server console text

    //
    while(window.isOpen()&&back==0)
    {
        sf::Event event; 
        while(window.pollEvent(event)){
            //create a process that 
            //check for user inputs
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button==sf::Mouse::Left){
                        x =(float )event.mouseButton.x; 
                        y =(float )event.mouseButton.y;
                        if(checkButton(x,y,menuButton[0])){
                            back=1;
                        }
                        if(checkButton(x,y,menuButton[3])){//loggin
                        std::cout<<connected<<"\n";
                            if(connected==1){
                                const char * a = playerInput[2].toAnsiString().c_str();
                                int par = login(a,sd);
                                if(par==1){
                                    game(window,sd);//game
                                    sv_diplayer.setString("Logged in");
                                    window.draw(myServer_display);
                                    window.draw(sv_diplayer);
                                    window.display();
                                }
                                else if (par==2){
                                    sv_diplayer.setString("Out of time to login");
                                    window.draw(myServer_display);
                                    window.draw(sv_diplayer);
                                    window.display();                             
                                    connected = 0;
                                    close(sd);       
                                }
                                else
                                {
                                    sv_diplayer.setString("Username-Taken");
                                    window.draw(myServer_display);
                                    window.draw(sv_diplayer);
                                    window.display();                                    
                                }
                            }
                            else{
                                sv_diplayer.setString("User not connected");
                                    window.draw(myServer_display);
                                    window.draw(sv_diplayer);
                                    window.display();
                            }
                        }
                        if(checkButton(x,y,menuButton[2]))//connect
                        {
                            sentData mySend={
                                playerInput[0].toAnsiString().c_str(),
                                playerInput[1].toAnsiString().c_str(),
                                playerInput[2].toAnsiString().c_str(),
                            };
                            if(connected == 0){
                                sd = establish_connection(mySend);
                                if(sd==-1){
                                    //write can't connect
                                    sv_diplayer.setString("Can't connect");
                                    window.draw(myServer_display);
                                    window.draw(sv_diplayer);
                                    window.display();
                                }
                                else{
                                    connected=1;
                                    // write server is connected in sfml console
                                    sv_diplayer.setString("Has connected");
                                    window.draw(myServer_display);
                                    window.draw(sv_diplayer);
                                    window.display();
                                }
                            }
                        }   
                    }
                    break;

                case sf::Event::KeyPressed:
                    if(event.key.code==sf::Keyboard::Up || event.key.code==sf::Keyboard::Down){
                        myMenuTextBox[wS].setOutlineColor(sf::Color(129, 199, 132));
                        switch (event.key.code)
                        {
                            case sf::Keyboard::Up:
                                --wS;
                                if(wS<0){
                                    wS=2;
                                }
                            break;
                            case sf::Keyboard::Down:
                                ++wS;
                                if(wS>2){
                                    wS=0;
                                }
                            break;
                        }
                        
                        myMenuTextBox[wS].setOutlineColor(sf::Color::Green);
                        for(int i =0 ;i<3;i++){
                            window.draw(myMenuTextBox[i]);
                            window.draw(playerText[i]);
                        }
                       window.display();
                    }
                break;
                case sf::Event::TextEntered:
                    switch(wS){
                        case 0:
                            //write max 10 characters
                            if(event.text.unicode>='0'&&event.text.unicode<='9'||event.text.unicode=='.')
                            {   
                                if(playerInput[wS].getSize()<10){
                                    playerInput[wS]+=event.text.unicode;
                                    playerText[wS].setString(playerInput[wS]);
                                    window.draw(playerText[wS]);
                                    window.display();
                                }
                            }
                            else if(event.text.unicode==8){//backspace
                                if(playerInput[wS].getSize()>0){
                                    playerInput[wS].erase(playerInput[wS].getSize()-1,1);
                                    playerText[wS].setString(playerInput[wS]);
                                    fillRect.setPosition(menuTextBox[wS].x+1,menuTextBox[wS].y+1);
                                    window.draw(fillRect);
                                    window.draw(playerText[wS]);
                                    window.display();}
                            }
                            break;
                        case 1:
                            //max 5
                            if(event.text.unicode>='0'&&event.text.unicode<='9')
                            {   
                                if(playerInput[wS].getSize()<5){
                                    playerInput[wS]+=event.text.unicode;
                                    playerText[wS].setString(playerInput[wS]);
                                    window.draw(playerText[wS]);
                                    window.display();
                                }
                            }
                            else if(event.text.unicode==8){//backspace
                                if(playerInput[wS].getSize()>0){
                                    playerInput[wS].erase(playerInput[wS].getSize()-1,1);
                                    playerText[wS].setString(playerInput[wS]);
                                    fillRect.setPosition(menuTextBox[wS].x+1,menuTextBox[wS].y+1);
                                    window.draw(fillRect);
                                    window.draw(playerText[wS]);
                                    window.display();
                                }
                            }
                            break;
                        case 2:
                            if(event.text.unicode>='A'&&event.text.unicode<='z')
                            {
                                if(playerInput[wS].getSize()<8){
                                    playerInput[wS]+=event.text.unicode;
                                    playerText[wS].setString(playerInput[wS]);
                                    window.draw(playerText[wS]);
                                    window.display();
                                }
                            }
                            else if(event.text.unicode==8){//backspace
                                if(playerInput[wS].getSize()>0){
                                    playerInput[wS].erase(playerInput[wS].getSize()-1,1);
                                    playerText[wS].setString(playerInput[wS]);
                                    fillRect.setPosition(menuTextBox[wS].x+1,menuTextBox[wS].y+1);
                                    window.draw(fillRect);
                                    window.draw(playerText[wS]);
                                    window.display();
                                }
                            }
                            break;
                    }
                    break;
                }
    }   

}

}