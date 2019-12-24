#include<SFML/Graphics.hpp>
#include<iostream>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#define HE 800
#define WI 800
int width;
int height;
int capacity;
int listObj;//o sa fie mereu ma mic decat HE/height-1
int fde;
bool rcv;
#include"grafici-results.h"
void * rcvData( void *arg){
    write(fde,&capacity,sizeof(int));
    int size;
    char buf[1000];
    while(1){
        read(fde,&listObj,sizeof(int ));
        for(int i = 0;i<listObj;i++){
            bzero(buf,sizeof(buf));
            read(fde,&size,sizeof(int));
            read(fde,buf,size);
            text[i].setString(buf); 
        }
        rcv = true;
    }
    return NULL;
}
using namespace std;
void results(sf::RenderWindow & window, int sd){
    fde=sd;
    height=HE/20;
    width=500;
    capacity = ker;
    grafici_init(window);
    int wS =1;
    window.clear();
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

                }
            }
    }

}