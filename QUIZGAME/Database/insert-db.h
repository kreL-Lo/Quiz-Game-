#include<sqlite3.h>
char *Zerrmsg;
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

char sql[1000];

void set_questions( sqlite3 * db){
    for(int i = 1;i<=10;i++){
        bzero(sql,sizeof(sql));
        sprintf(sql,"insert into questions (id) values(%d);",i);
        sqlite3_exec(db,sql,callback,0,&Zerrmsg);
    }
}
void delete_questions(sqlite3 * db){
    char pp[] = "delete from questions;";
    sqlite3_exec(db,pp,callback,0,&Zerrmsg);
}

void sql_insert_question(sqlite3 *db,int index ,char *str){
    bzero(sql,sizeof(sql));
    sprintf(sql,"UPDATE questions SET Q='%s' WHERE id=%d;",str,index);
    sqlite3_exec(db,sql,callback,0,&Zerrmsg);
}

void sql_insert_set(sqlite3 *db,char c,char * str, int index){
    bzero(sql,sizeof(sql));
    sprintf(sql,"UPDATE questions SET %c='%s' WHERE id=%d;",c,str,index);
    sqlite3_exec(db,sql,callback,0,&Zerrmsg);
}

void sql_answer(sqlite3 *db, int index,char str){
    bzero(sql,sizeof(sql));
    sprintf(sql,"UPDATE questions SET answer='%c' WHERE id=%d;",str,index);
    sqlite3_exec(db,sql,callback,0,&Zerrmsg);
}

void sql_insert_nrQuestions(sqlite3 *db, int index, int nr ){
    bzero(sql,sizeof(sql));
    sprintf(sql,"UPDATE questions SET nr=%d where id=%d;",nr,index);
    sqlite3_exec(db,sql,callback,0,&Zerrmsg);
}