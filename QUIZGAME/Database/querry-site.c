//code inspired from  
//https://stackoverflow.com/questions/9766313/how-to-use-libxml2-to-parse-dirty-html-in-c-programing
//by Pankaj Vavadiya
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/HTMLparser.h>
#include<sqlite3.h>
#include"insert-db.h"
#define nr_questions 10
int nrset;

int countAns;
int count;
int isQuestion(char *str){
    char * a = (char * )malloc(4);
    a[0]=str[0];
    a[1]=str[1];
    a[2]=str[2];
    a[3]='\0';
    char *b = (char *)malloc(3);
    b[0]=str[0];
    b[1]=str[1];
    b[2]='\0';
    char tmp[5];
    for(int i =1 ;i<=nr_questions+1;i++){
        bzero(tmp,sizeof(tmp));
        sprintf(tmp,"%d.",i);
        if(strcmp(a,tmp)==0||
            strcmp(b,tmp)==0){
            return 1;
        }
    }
    return 0;
}
int isAnswer( const char * str )
{
    char ans[]= "Answer:";
    if(strlen(str)<strlen(ans))
    {
        return 0;
    }
    int flag ;
    for(int j =0 ;j<strlen(str)-strlen(ans)+1;j++){
        flag = 1;
        for(int i =0 ;i<strlen(ans);i++){
            if(str[i+j]!=ans[i]){
                flag = 0;
                break;
            }
        }
        if(flag == 1){
            return 1;
        }
    }
    return 0;
}
int bginwrite;
void traverse_dom_trees(xmlNode * a_node,sqlite3 *db)
{
    xmlNode *cur_node = NULL;
    if(NULL == a_node)
    {
        return;
    }

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) 
    {   
        if(cur_node->type == XML_TEXT_NODE)
        {
            //procces
            if(count<nr_questions+2){
                if(bginwrite==1){
                           //write in db nr of questions
                        //printf("%d %d\n",count-1,nrset);
                        sql_insert_nrQuestions(db,count-1,nrset);
                        
                    } 
                if( strlen((char*)cur_node->content)>0&&
                    strcmp((char *)cur_node->parent->name,"p")==0&&
                    isQuestion((char *) cur_node->content)
                )
                {

                    bginwrite=1;
                    //write in db questions
                    if(count<nr_questions+1)
                        {
                        //printf("%d %s\n ",count, (char *)cur_node->content);

                        sql_insert_question(db,count,(char *)cur_node->content);
                        //GET QUESTIONS
                        nrset=0;
                        }                        
                    count ++;
                }
                else {
                     if(count<=11){
                         char * str=  (char*)cur_node->content;
                        if(str[2]==')'){
                            ++nrset;
                            //printf("%d %s\n",count-1, str);
                            sql_insert_set(db,str[1]+'A'-'a',str,count-1);
                            
                            //GET SET ANS
                        }
                    }
                }
            }
            if(countAns<=nr_questions&&strcmp((char *)cur_node->parent->name,"div")==0 &&
                isAnswer((char*) cur_node->content))
                    {
                        char * str = (char * ) cur_node->content;
                        printf("%s %d \n",(char *)cur_node->content,countAns);
                        sql_answer(db,countAns,str[strlen(str)-1]);
                        ++countAns;
                    }
        }
            
        traverse_dom_trees(cur_node->children,db);
    }
}

int main() 
{ 
    nrset=0;
    count = 1;
    htmlDocPtr doc;
    xmlNode *roo_element = NULL;
    countAns= 1;
  
    char * fileName = "site-out.txt";
    doc = htmlReadFile(fileName, NULL, HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
    if (doc == NULL) 
    {
        fprintf(stderr, "Document not parsed successfully.\n");
        return 0;
    }

    roo_element = xmlDocGetRootElement(doc);

    if (roo_element == NULL) 
    {
        fprintf(stderr, "empty document\n");
        xmlFreeDoc(doc);
        return 0;
    }

    sqlite3 *db ;
    sqlite3_open("questions.db",&db);
    delete_questions(db);//clear db
    set_questions(db);//reset questions id 
    traverse_dom_trees(roo_element,db);//traverse

    sqlite3_close(db);
    xmlFreeDoc(doc);       // free document
    xmlCleanupParser();    // Free globals
    return 0;
}