
#include<vector>
#include<string>
#include<iostream>
#include <sys/types.h>
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
#define login_time 10


bool isInDb(sqlite3 * db,char nume[] )
{
    mydata records;   
    char sql[1000];
    bzero(sql,sizeof(sql));
    sprintf(sql,"select exists (select 1 from player where nume = '%s');",nume);
    sqlite3_exec(db,sql,selectcalback,&records,&Zerrmsg);
    if(records[0][0][0]=='0'){
        return false;
    }
    return true;
}
void * login_thread(void * arg){
    pthread_detach(pthread_self());
    thData tdL ;
    tdL= *((struct thData*)arg);
    fd_set rfds;
    int fd = tdL.cl;
    struct timeval tv;
    tv.tv_sec=login_time;
    tv.tv_usec=0;
    FD_ZERO(&rfds);
    FD_SET(fd,&rfds);
    char container[1000];
    int size;
    std::cout<<"login thread\n";
    int time = login_time;// time to end
    bool isIn =false;
    while(time>0&&isIn==false){// while  ca sa-i tot dau jucatorului incercari de a se loga cu un nume care nu-i in baza de date
        int retval =select(fd+1, &rfds,NULL,NULL,&tv);//astept un raspuns in n secunde ;
        if(retval==-1){
            perror("select()");
            break;
        }
        else if(retval){
            //get answer
            printf("something has been sent\n");
            bzero(container,sizeof(container));
            int r= read(fd,&size,sizeof(int));
            if(r==0){
                break;
            }
            read(fd,container,size);
            std::cout<<container<<std::endl;
            if(isInDb(tdL.db,container)){
                write(fd,"0",1);// este deja in baza de date
                std::cout<<"trying again\n";
            }
            else{
                write(fd,"1",1);// nu este in baza de date
                //adaug in baza de date
                insert_PlayerTable(tdL.db,tdL.idThread,tdL.cl,container);
                isIn = true;
            }
        }
        else{
            //
            printf("no data was send bruh\n");
        }
            std::cout<<time<<std::endl;
            time = tv.tv_sec;
            tv.tv_sec=time;
            tv.tv_usec=0;
            FD_ZERO(&rfds);
            FD_SET(fd,&rfds);
    }
    if(isIn == false){//trimit ca nu mai are timp de raspuns si inchid conexiunea
        read(fd,&size,sizeof(int));
        read(fd,container,size);
        write(fd,"2",1);//time has expired
        close(fd);
    }

    return NULL;
}

//thread that sends the client data about the state of server
//later 