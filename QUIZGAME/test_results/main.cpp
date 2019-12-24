#include<SFML/Graphics.hpp>
#include<iostream>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sqlite3.h>
#include<string.h>
#define HE 800
#define WI 800
int width;
int height;
int capacity;
int listObj;//o sa fie mereu ma mic decat HE/height-1
int fd;
bool rcv;
#include"grafici-results.h"
void * rcvData( void *arg){
    write(fd,&capacity,sizeof(int));
    int size;
    char buf[1000];
    while(1){
        read(fd,&listObj,sizeof(int ));
        for(int i = 0;i<listObj;i++){
            bzero(buf,sizeof(buf));
            read(fd,&size,sizeof(int));
            read(fd,buf,size);
            text[i].setString(buf);
        }
        rcv = true;
    }
    return NULL;
}
using namespace std;
int main(){
    sf::RenderWindow window (sf::VideoMode(HE,WI),"Quizz Game");
    height=HE/10;
    width=500;
    capacity = HE/height-1;
    grafici_init(window);
    int wS =1;
    window.clear();
    arrows[wS].setFillColor(sf::Color::Yellow);
    tails[wS].setFillColor(sf::Color::Yellow);
    drawAll(window);
    while(window.isOpen())
    {
        window.clear();
        if(rcv==true){
            rcv = false;
            for(int i =listObj;i<capacity;i++){
                text[i].setString("");
            }
            drawAll(window);
        }
            sf::Event event;
            while (window.pollEvent(event))
            {
                switch(event.type){
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::KeyPressed:
                    if(event.key.code==sf::Keyboard::Right  || event.key.code == sf::Keyboard::Left){
                        window.clear();
                        arrows[wS].setFillColor(sf::Color::Yellow);
                        tails[wS].setFillColor(sf::Color::Yellow);
                        drawAll(window);
                        if(event.key.code==sf::Keyboard::Left){
                            wS=1;
                            write(fd,"L",1);//sending left page to return from server
                        }
                    
                        if(event.key.code==sf::Keyboard::Right){
                            wS=0;
                            write(fd,"R",1);//sending right page to rcv from server
                        }
                        arrows[wS].setFillColor(sf::Color::Green);
                        tails[wS].setFillColor(sf::Color::Green);
                        drawAll(window);
                    }
                        break;
                }
            }
    }
    return 0;   
}