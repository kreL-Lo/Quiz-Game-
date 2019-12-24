#include "header.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "connect-place.cpp"
// main menu


int main()
{
    float x,y;
    button menuButton[3];
    //BUTTON SIZES & coords
    menuButton[0]={2*WI/5,HE/6,WI/2-WI/5,HE/2-2*HE/6};
    menuButton[1]=menuButton[0];
    menuButton[1].y=menuButton[1].y+2*menuButton[0].heigth; 
    menuButton[2]={30,30,WI-150,HE-100};
     sf::Font font;
    font.loadFromFile("Arial.ttf");
    //SET TEXT
    sf::Text text[2];
    text[0].setString("Play");    
    for(int i = 0;i<1;i++){
        text[i].setFont(font);
        text[i].setCharacterSize(40);
        text[i].setFillColor(sf::Color(50,205,50));
        text[i].setStyle(sf::Text::Bold);
    }
    //txt positions
        point textPosition[2];
    for(int i =0 ;i<1;i++){
         textPosition[i]={menuButton[i].x+menuButton[i].width/2-8*text[i].getString().getSize()
         ,menuButton[i].y+menuButton[i].heigth/2};
         text[i].setPosition(textPosition[i].x,textPosition[i].y-textSize);
    }

    //
    //RENDER WINDOW
    sf::RenderWindow window(sf::VideoMode(WI,HE), "Quizz");
    //BUTTON INIT
    sf::RectangleShape myMenuButtons[3];
    //BUTTON SETTINGS
    for(int i =0;i<3;i++){
        myMenuButtons[i]=sf::RectangleShape(sf::Vector2f(menuButton[i].width,menuButton[i].heigth));
        myMenuButtons[i].setPosition(menuButton[i].x,menuButton[i].y);
        myMenuButtons[i].setOutlineThickness(5);
        myMenuButtons[i].setOutlineColor(sf::Color::Green);
        myMenuButtons[i].setFillColor(sf::Color::Black);
    }
    window.draw(myMenuButtons[0]);
    window.draw(myMenuButtons[2]);
    for(int i =0 ;i<2;i++){
        window.draw(text[i]);}
    int out =0;
    
    window.display();
    while (window.isOpen()||out)
    {
        sf::Event event; 
        while (window.pollEvent(event))
        {
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button==sf::Mouse::Left){
                        x =(float )event.mouseButton.x;
                        y =(float )event.mouseButton.y;
                        //rect.setPosition(x,y)
                        if(checkButton(x,y,menuButton[0])){

                            //play_connect(window);
                            results(window,10);
                            window.clear();
                            window.draw(myMenuButtons[0]);
                            window.draw(myMenuButtons[2]);
                            window.draw(text[0]);
                            
                            window.display();
                        }
                        if(checkButton(x,y,menuButton[2])){
                            window.close();
                        }
                    }
                    break;
                    
            }
        }
    }
    return 0;
}