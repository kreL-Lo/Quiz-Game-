#include<stdio.h>
#include<sqlite3.h>
#include<vector>
#include<string>
#include<iostream>
#include <string.h>
using namespace std;
#define mydata std::vector<std::vector<std::string>> 
static int selectcalback(void * NotUsed,int argc,char **argv,char **azColName){
        mydata * records =(mydata*)NotUsed;
        records->emplace_back(argv,argv+argc);
        return 0;
}


char sql[1000];
char *Zerrmsg;

int getRecords(sqlite3 *db,mydata & records,int index){
    bzero(sql,sizeof(sql));
    int nrSet;
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
            sprintf(sql,"select A,Q from questions where id=%i;",index);
            break;
        case 2: 
            sprintf(sql,"select A,B,Q from questions where id=%i;",index);
            break;
        case 3: 
            sprintf(sql,"select A,B,C,Q from questions where id=%i;",index);
            break;
        case 4: 
            sprintf(sql,"select A,B,C,D,Q from questions where id=%i;",index);
            break;
    }
    sqlite3_exec(db,sql,selectcalback,&records,&Zerrmsg);
    return nrSet;
}  

int main(){
    sqlite3 * db;
    sqlite3_open("questions.db",&db);
    mydata records;
    // do smt
    for(int i =1;i<=10;i++){
        getRecords(db,records,i);
        for(auto i: records){
            for(auto j: i ){
                cout<<j.c_str()<<endl;
            }
            
        }
    //
   
    }
    sqlite3_close(db);
}
