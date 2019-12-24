#include<stdio.h>
#include<sqlite3.h>
#include<iostream>
#include<vector>
#include<string>
char str[1000];

void clear_playerTable(sqlite3 *db){
    const char * sql= "delete from player";
    sqlite3_exec(db,sql,callback,0,&Zerrmsg);
}
void insert_PlayerTable(sqlite3 *db, int index, int client, char nume[]){
    bzero(str,sizeof(str));
    sprintf(str,"insert into player(id,client,nume,score) values(%d,%d,'%s',%d);",index,client,nume,0);
    sqlite3_exec(db,str,callback,0,&Zerrmsg);
}



    