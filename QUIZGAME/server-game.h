#include<stdio.h>
#include<sqlite3.h>
#include<string>
#include<vector>
#include<iostream>
#define nr_rounds nrQues
//just sends and gets information
#define seconds 10
#define goodAnswer 1

int nrQuestions(sqlite3 *db ){
    mydata records;
    char sql[1000];
    bzero(sql,sizeof(sql));
    sprintf(sql,"select count(*) from questions;");
    sqlite3_exec(db,sql,selectcalback,&records,&Zerrmsg); 
    return atoi(records[0][0].c_str());
}

void sendScore(int capacity, sqlite3 *db,mydata &records,int sd){
    char sql[1000];
    records.clear();
    bzero(sql,sizeof(sql));
    sprintf(sql,"select nume,score,id from player where id is not null order by score desc limit %d;",capacity);
    sqlite3_exec(db,sql,selectcalback,&records,&Zerrmsg);
    int size=records.size();
    write(sd,&size,sizeof(int));
    char buff[10000];
    int index =1;
    int curScore = atoi(records[0][1].c_str());
    for(auto i :records){
        int score = atoi(i[1].c_str());
        if(curScore>score){
            index++;
            curScore=score;
        }
        bzero(buff,sizeof(buff));
        sprintf(buff,"Loc %d ::Nume %s ::Scor %s::ID %s ",index,i[0].c_str(),i[1].c_str(),i[2].c_str());
        bzero(&size,sizeof(int));
        size= strlen( buff);
        write(sd,&size,sizeof(int));
        write(sd,buff,size);
    }
}


const char * getNume(sqlite3 *db , int client){
    mydata records;
    char sql[1000];
    sprintf(sql,"select nume from player where client='%d';",client);
    sqlite3_exec(db,sql,selectcalback,&records,&Zerrmsg);
    return records[0][0].c_str();
}
void sendPlacement(const char * nume, sqlite3 *db,mydata &records,int sd){
    char sql[1000];
    records.clear();
    bzero(sql,sizeof(sql));
    sprintf(sql,"select nume, score, (select count(*) from (select distinct p3.score from player p3 join player p4 on p3.score!=p4.score) p1 where p.score<p1.score),id from player p where nume ='%s';",nume);
    sqlite3_exec(db,sql,selectcalback,&records,&Zerrmsg);
    char buff[1000];
    int size;
    for(auto i :records){
        bzero(buff,sizeof(buff));
        char tmp[100];
        int d= atoi(i[2].c_str());
        bzero(tmp,sizeof(tmp));
        sprintf(tmp,"%d",d+1);
        printf("%s\n",tmp);
        sprintf(buff,"%s::Scor %s :: Loc %s :: ID %s",i[0].c_str(),i[1].c_str(),tmp,i[3].c_str());
        bzero(&size,sizeof(int));
        size= strlen( buff);
        write(sd,&size,sizeof(int));
        write(sd,buff,size);
    }
}
void sendWinner(sqlite3 *db,mydata &records,int sd){
    char sql[1000];
    records.clear();
    bzero(sql,sizeof(sql));
    sprintf(sql,"select nume,score,id from player where id is not null order by score desc limit 1;");
    sqlite3_exec(db,sql,selectcalback,&records,&Zerrmsg);
    char buff[1000];
    int size;
    for(auto i :records){
        bzero(buff,sizeof(buff));
        sprintf(buff,"%s::Scor %s :: Loc %s :: ID %s",i[0].c_str(),i[1].c_str(),"1",i[2].c_str());
        bzero(&size,sizeof(int));
        printf("%s\n",buff);
        size= strlen(buff);
        write(sd,&size,sizeof(int));
        write(sd,buff,size);
        break;
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
               printf("SOMETHING HAS BEEN SEND.\n");
               bzero(buff,sizeof(buff));
               read(fd,buff,1);//get answer from client
               printf("%s\n",buff);
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
                    insert_score(tdL.db,records,tdL.cl,score);
                }
            }
           else
               {
                   printf("No data sent.\n");
                   fflush(stdout);
               }
    }
    write(fd,"R",1);
    //SHOW SCORE
    localFinish = 0;
    ++globalFinish;
    int capacity ;
    const char * nume = getNume(tdL.db,tdL.cl);
    read(fd,&size,sizeof(int));
    capacity=size;
    while(1){

        if(globalFinish==totalPlayers||endTime==true){
            write(fd,"0",1);
            sendScore(capacity,tdL.db,records,fd);   
            sendPlacement(nume,tdL.db,records,fd);
            sendWinner(tdL.db,records,fd);
            break;
        }
        else if(localFinish!=globalFinish)
        {  
            // update the user
            write(fd,"1",1);
            localFinish=globalFinish;
            sendScore(capacity,tdL.db,records,fd);   
            sendPlacement(nume,tdL.db,records,fd);
        }
    }
    printf("FINISHED\n");
    return NULL;
}
