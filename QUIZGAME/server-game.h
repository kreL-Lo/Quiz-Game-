#include<stdio.h>
#include<sqlite3.h>
#include<string>
#include<vector>
#include<iostream>
#define nr_rounds 10
//just sends and gets information
#define seconds 20
#define goodAnswer 1

void sendScore(int capacity, sqlite3 *db,mydata &records,int sd){
    char sql[1000];
    records.clear();
    bzero(sql,sizeof(sql));
    sprintf(sql,"select nume,score,id from player where id is not null order by score desc limit %d;",capacity);
    sqlite3_exec(db,sql,selectcalback,&records,&Zerrmsg);
    int size;
    char buff[10000];
    for(auto i :records){
        bzero(buff,sizeof(buff));
        for(auto j : i)
        {
            strcat(buff,j.c_str());
            strcat(buff,"::");
        }
        size= strlen( buff);
        write(sd,&size,sizeof(int));
        write(sd,buff,size);
    }
}
void insert_score(sqlite3 *db, mydata &records, int client, int score){
    char sql[1000];
    bzero(sql,sizeof(sql));
    records.clear();
    sprintf(sql,"update player set score=%d where client=%d;",score,client);
    sqlite3_exec(db,sql,callback,&records,&Zerrmsg);
}
char getAns(sqlite3 *db, mydata & records,int index){
    char answer;
    char sql[1000];
    records.clear();
    bzero(sql,sizeof(sql));
    sprintf(sql,"select answer from questions where id=%d",index);
    sqlite3_exec(db,sql,selectcalback,&records,&Zerrmsg);
    answer = records[0][0][0];
    answer = answer + 'A'-'a';
    return answer;
}
int getRecords(sqlite3 *db,mydata & records,int index){
    int nrSet;
    char sql[1000];
    bzero(sql,sizeof(sql));
    records.clear();
    //get nr of answer
    sprintf(sql,"select nr from questions where id=%i",index);
    sqlite3_exec(db,sql,selectcalback,&records,&Zerrmsg);
    nrSet=atoi(records[0][0].c_str());
    bzero(sql,sizeof(sql));
    records.clear();
    switch(nrSet)
    {
        case 1: 
            sprintf(sql,"select Q,A from questions where id=%i;",index);
            break;
        case 2: 
            sprintf(sql,"select Q,A,B from questions where id=%i;",index);
            break;
        case 3: 
            sprintf(sql,"select Q,A,B,C from questions where id=%i;",index);
            break;
        case 4: 
            sprintf(sql,"select Q,A,B,C,D from questions where id=%i;",index);
            break;
    }
    sqlite3_exec(db,sql,selectcalback,&records,&Zerrmsg);
    return nrSet;
}  
void *game(void * arg){
    int localFinish;
    printf("created thread bro\n");
    pthread_detach(pthread_self());
    struct thData tdL; 
    tdL= *((struct thData*)arg);
    int fd=tdL.cl;
    char buff[100];
    int size ;
    fd_set rfds;
    int nrSet;
    char sql[10000];
    int score =0;
    struct timeval tv;
    int timePast;
    //send the client the seconds per question
    int seco = seconds;
    write(fd,&seco,sizeof(int));
    int nrQ=nr_rounds;
    write(fd,&nrQ,sizeof(int));
    mydata records;//retine momentan setul de valori
    for(int k =1;k<=nr_rounds;k++){// k -nr cheii in baza de date
        nrSet=getRecords(tdL.db,records,k);
        write(fd,&nrSet,sizeof(int));
        for(auto i:records){
            for(auto j:i ){
                size = j.size();
                write(fd,&size,sizeof(int));//trimite dimensiunea
                write(fd,j.c_str(),size);//trimite continutul in ordinea in care am selectat in interogare
            }
        }  
        tv.tv_sec=seconds;
        tv.tv_usec=0;
        FD_ZERO(&rfds);
        FD_SET(fd,&rfds);
        int retval =select(fd+1, &rfds,NULL,NULL,&tv);//aici astept cele n secunde
         if (retval == -1){
               perror("select()");
               break;
               }
           else if (retval){
        
               bzero(buff,sizeof(buff));
               read(fd,buff,1);//get answer from client
                if(buff[0]=='0'){
                    printf("Client has left\n");
                    close(fd);
                    fflush(stdout);
                    break;}
                //CHECK ANSWER
                if(getAns(tdL.db,records,k)==buff[0]){
                    ///CHECK TIME INTERVAL  and update score accordingly
                    timePast = seconds-tv.tv_sec;     
                    if(timePast<=5){
                        score+=3;
                    }
                    else if(timePast <=10){
                        score+=2;
                    }
                    else 
                    {score +=1; }
                    printf("%d %d \n",tdL.cl, score);
                    fflush(stdout);
                    insert_score(tdL.db,records,tdL.cl,score);
                }
            }
           else
               {
                   printf("No data sent.\n");
               }
    }
    //SHOW SCORE
    ++globalFinish;
    localFinish=globalFinish;
    int capacity ;
    read(fd,&size,sizeof(int));
    read(fd,buff,size);
    capacity=atoi(buff);
    
    while(1){//pana cand jocul e gata practic

        if(localFinish!=globalFinish)
        {  
            // update the user
            sendScore(capacity,tdL.db,records,fd);   
        }

    }


    return NULL;
}
