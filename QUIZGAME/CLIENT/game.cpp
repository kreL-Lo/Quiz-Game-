#include <SFML/Graphics.hpp>
#include<sqlite3.h> 
#include<iostream>
#include"grafici.h"
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<math.h>
#include<cstdio>
#include "results.cpp"
int fd;
float to_decimalPlaces(float val, int decimal_places){
    return(floor(val*pow(10,decimal_places))/pow(10,decimal_places));
}
void sigHandler( int sig_num){

    signal(SIGINT,sigHandler);
    write(fd,"0",1);
    printf("Client has aborted\n");
    close(fd);
    fflush(stdout);
    exit(1);
}
#define WI 800
#define HE 800
void drawStuff(int wS,sf::RenderWindow &window){
    for(int i =0;i<5;i++)
                pressButtons[i].setOutlineColor(sf::Color(118, 215, 196));
            pressButtons[wS].setOutlineColor(sf::Color::Green);
            for(int i =0 ;i<4;i++){
                        window.draw(pressButtons[i]);
                        window.draw(texts_default[i]);
                    }
            //window.draw(eraser);
            for(int i =0;i<5;i++){
                if(i!=4)
                    window.draw(pressButtons[i]);
                window.draw(texts_default[i]);
                window.draw(texts[i]);
            }
}
bool receive;

int nrSet;

void *timer (void * arg){


    return NULL;
}
bool over;
void * receiving(void *arg){
            pthread_detach(pthread_self());
            char container[1000];
            sf::String editting;
            int size;
            char clr[]="";
            int nrquestions;
            read(fd,&nrquestions,sizeof(int));
            for(int j =0;j<nrquestions;j++){
                read(fd,&nrSet,sizeof(int));
                for(int i =0 ;i<=nrSet;i++){
                    bzero(container,sizeof(container));//memset(container,0,sizeof(container));
                    bzero(&size,sizeof(size));
                    read(fd,&size,sizeof(int));
                    read(fd,container,size);
                    //write(1,container,strlen(container));
                    //write(1,"\n",1);
                    editting=edit(container,i);
                    texts[i].setString(editting);
                    //clean the background
                }
                for(int i = nrSet+1;i<=4;i++){
                    texts[i].setString(clr);
                }
                    receive=true;
        }
        over = true;
    return NULL;
}
//each user would look like this ORDER-NUMBER NAME 
void game(sf::RenderWindow & window,int sd){
    window.clear();
    fd= sd;
    over = false;
    font.loadFromFile("Arial.ttf");
    float x,y;
    signal(SIGINT,sigHandler);
    pthread_t p ;
    int sec;
    //get here time per round
    bzero(&sec,sizeof(int));
    read(fd,&sec,sizeof(int));
    float nrSec = (float)sec;
    pthread_create(&p,NULL,&receiving,NULL);
    receive=false;
    window.display();
    int wS=0;   
    nrSet=4;
    questionInterface(window);
    char letter[]="ABCD";
    int size;
    char container[1000];
    int k ;
    //acest ceas in interfata client este defapt o reprezentare vizuala a timpului trecut pentru jucator
    //acesta nu este tot deauna corect findca exista acel delay intre client si server
    //deoarece lucram pe un server local acest delay nu are vreun impact cu jocul
    //serverul se ocupa defapt si de retinerea timpului pentru fiecare jucator, nu clientul, 
    // 
    sf::Clock clock;
    float f;
    char number[10];
    
    bool lastSend = false;
    while(window.isOpen())
    {
        //receive data
        bzero(number,sizeof(number));
        sprintf(number,"%.1f",nrSec-clock.getElapsedTime().asSeconds());
        clocker.setString(number);
        window.clear();
        drawStuff(wS,window);
        window.draw(clocker);
        window.display();
        if(over == true){
            f= nrSec-clock.getElapsedTime().asSeconds();
            if(f<0||lastSend){
                results(window,sd);
                window.close();
                exit(1);
            }
        }
        if(receive == true){
            wS=0;
        
            clock.restart();
            for(int i =0;i<5;i++)
                pressButtons[i].setOutlineColor(sf::Color(118, 215, 196));
            pressButtons[wS].setOutlineColor(sf::Color::Green);
            for(int i =0 ;i<4;i++){
                        window.draw(pressButtons[i]);
                        window.draw(texts_default[i]);
                    }
            window.draw(eraser);
            for(int i =0;i<5;i++){
                if(i!=4)
                    window.draw(pressButtons[i]);
                window.draw(texts_default[i]);
                window.draw(texts[i]);
            }
            window.display();
            receive=false;
        }
        
        sf::Event event; 
        while(window.pollEvent(event)){
            switch(event.type){
            case sf::Event::Closed:
                window.close();
                printf("Closed the windown\n");
                write(fd,"0",1);
                close(fd);
                exit(1);
                break;      
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button==sf::Mouse::Left){
                    x =(float)event.mouseButton.x; 
                    y =(float)event.mouseButton.y;
                    }
                break;
             case sf::Event::KeyPressed:
                    if(event.key.code==sf::Keyboard::Up || event.key.code==sf::Keyboard::Down){
                        pressButtons[wS].setOutlineColor(sf::Color(118, 215, 196));
                        switch (event.key.code)
                        {
                            case sf::Keyboard::Up:
                                --wS;
                                if(wS<0){
                                    wS=nrSet-1;
                                }
                            break;
                            case sf::Keyboard::Down:
                                ++wS;
                               
                                if(wS>nrSet-1){
                                    wS=0;
                                }
                            break;
                        }
                        pressButtons[wS].setOutlineColor(sf::Color::Green);
                        for(int i =0 ;i<4;i++){
                            window.draw(pressButtons[i]);
                            window.draw(texts_default[i]);
                        }
                        window.display();
                    }
                    if(event.key.code==sf::Keyboard::Enter){
                        std::cout<<letter[wS]<<std::endl;
                        //send answer to server
                        char a[1];
                        a[0]=letter[wS];
                        write(fd,a,1);
                        if(over==true){
                            lastSend = true;
                        }
                        break; 
                    }
                break;
            
        }
    }
    }
}