#include<iostream>
#include <sys/types.h>
#include<sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <sqlite3.h>
#include <list>
int globalFinish;
#define alarm_time 10
#include "server-heads.h"//data for sever-lobby and server-sql and server-game
#include "server-sql.h"
#include "server-lobby.h"
#include "server-game.h"
/* portul folosit */
#define PORT 2908
int timer;
void alarm_handler(int s ){
  timer = 0;
}
bool isInList(std::list<int>q,int value){
  for(auto i : q){
    if(i==value)
    {return true;}
  }
  return false;
}
/* codul de eroare returnat de anumite apeluri */

int main()
{
  globalFinish=0;
    //open database
    sqlite3 *db;
    sqlite3_open("Database/questions.db",&db);
    //

  struct sockaddr_in server;	// structura folosita de server
  struct sockaddr_in from;	
  int nr;		//mesajul primit de trimis la client 
  int sd;		//descriptorul de socket 
  int pid;
	int i=0;
  /* crearea unui socket */
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("[server]Eroare la socket().\n");
      return errno;
    }
  /* utilizarea optiunii SO_REUSEADDR */
  int on=1;
  setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
  /* pregatirea structurilor de date */
  bzero (&server, sizeof (server));
  bzero (&from, sizeof (from));
  /* umplem structura folosita de server */
  /* stabilirea familiei de socket-uri */
    server.sin_family = AF_INET;	
  /* acceptam orice adresa */
    server.sin_addr.s_addr = htonl (INADDR_ANY);
  /* utilizam un port utilizator */
    server.sin_port = htons (PORT);
  
  /* atasam socketul */
  if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
    {
      perror ("[server]Eroare la bind().\n");
      return errno;
    }

  /* punem serverul sa asculte daca vin clienti sa se conecteze */
  if (listen (sd, 2) == -1)
    {
      perror ("[server]Eroare la listen().\n");
      return errno;
    }
    //folosit pentru a stoca descriptori clientilor
  /* servim in mod concurent clientii...folosind thread-uri */

  //clear baza de date care se ocupa cu stocatul clientilor
    clear_playerTable(db);
    int index =0;
    struct sigaction sa;
    sa.sa_handler = alarm_handler;
    sigemptyset(&sa.sa_mask);
    //sa.sa_flags = SA_RESTART;
    if(sigaction(SIGALRM, &sa, NULL) == -1){
        perror("sigaction");
        exit(1);
    }
  alarm(alarm_time);
  timer = 1;
  //global timer to log in to the game
  fd_set rdfds;
  FD_ZERO(&rdfds);
  int j =0;
  int nfds=sd;
while (timer)
{
    int client;
    socklen_t length = sizeof (from);
    client = accept (sd, (struct sockaddr *) &from, &length);  
    if(client<=0){ 
      //timer ended or some error
      break;
    }
    //insert1_PlayerTable(db,index,client);
    if(nfds<client){
      nfds=client;
    }
    thData * td; 
    td=(struct thData*)malloc(sizeof(struct thData));	
    td->idThread=index++;
    td->cl=client;
    td->db = db;
    FD_SET(client,&rdfds);
    printf("connected\n");
    pthread_t p;
    pthread_create(&p,NULL,&login_thread,td);
}
sleep(login_time);//astept pentru inca login_time unitati de timp , pentru a fi sigur ca toti jucatorii au terminat cu logarea
//in total de la login la joc va fi de asteptat un total de
// login_time + alarm_time : adica 20 de secunde
thData * td; 
index = 0;
  for(int i = 0; i<=nfds;i++){
    if(i!=sd&&FD_ISSET(i,&rdfds)){
        td=(struct thData*)malloc(sizeof(struct thData));	
        td->idThread=index++;
        td->cl=i;
        td->db = db;
        pthread_t p;
        pthread_create(&p,NULL,&game,td);
    }
  }
  while(1);
    //later
    //the game

  return 0;
};				

