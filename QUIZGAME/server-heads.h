#include<stdio.h>
#include<sqlite3.h>
#include<string>
#include<vector>
#include<iostream>
struct thData{
	int idThread; //id-ul thread-ului tinut in evidenta de acest program
	int cl; //descriptorul intors de accept
    sqlite3 *db;
};
char * Zerrmsg=0;
//code inspired by https://stackoverflow.com/questions/18839799/retrieve-sqlite-table-data-in-c/18840064
#define mydata std::vector<std::vector<std::string>> 
static int selectcalback(void * NotUsed,int argc,char **argv,char **azColName){
        mydata * records =(mydata*)NotUsed;
        records->emplace_back(argv,argv+argc);
        return 0;
}

////////////////////////////////////////////////////////////////////////////////////
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}