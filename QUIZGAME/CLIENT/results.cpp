#include<SFML/Graphics.hpp>
#include<iostream>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#define HE 800
#define WI 800
int width;
int height;
int capacity;
int listObj;//o sa fie mereu ma mic decat HE/height-1
int fde;
bool rcv;
#include"grafici-results.h"

void rcvScore(int sd){
    char buf[1000];
    int size;
    int listObj;

         read(fde,&listObj,sizeof(int));
        for(int i = 0;i<listObj;i++){
            bzero(buf,sizeof(buf));
            bzero(&size,sizeof(int));
            read(fde,&size,sizeof(int));
            read(fde,buf,size);
            text[i].setString(buf); 
            }	
}
void rcvPosition(int sd){
    int size;
    char buf[1000];
    bzero(buf,sizeof(buf));
    bzero(&size,sizeof(int));
    read(fde,&size,sizeof(int));
    read(fde,buf,size);
    curPosition[1].setString(buf);
}

void rcvWinner(int sd){
    char buf[1000];
    int size;
     bzero(buf,sizeof(buf));
    bzero(&size,sizeof(int));
    read(fde,&size,sizeof(int));
    read(fde,buf,size);
    Winner[1].setString(buf);
}
void * rcvData( void *arg){
    write(fde,&capacity,sizeof(int));
    char ch[1];
     while(1){
        //read bitul de schimb
        bzero(ch,1);
        read(fde,ch,1);
        if(ch[0]=='0'){
            rcvScore(fde);
            rcvPosition(fde);
            rcvWinner(fde);
            rcv=true;
            break;
        }else if(ch[0]=='1'){
            rcvScore(fde);
            rcvPosition(fde);
            rcv = true;
        }
    }
    
    curStatus.setString("Game Over");
    printf("FINISHED \n");
    fflush(stdout); 
    return NULL;
}
using namespace std;
void results(sf::RenderWindow & window, int sd){
    fde=sd;
    height=HE/20;
    width=500;
    pthread_t p;
    capacity = ker;
    pthread_create(&p,NULL,&rcvData,NULL);
    grafici_init(window);
    int wS =1;
    window.clear();
    drawAll(window);
    while(window.isOpen())
    {
        if(rcv==true){
            rcv = false;
            window.clear();
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