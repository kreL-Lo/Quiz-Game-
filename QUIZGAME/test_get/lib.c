//code inspired from  
//https://stackoverflow.com/questions/9766313/how-to-use-libxml2-to-parse-dirty-html-in-c-programing
//by Pankaj Vavadiya
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/HTMLparser.h>
#include <pthread.h>
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
    
void traverse_dom_trees(xmlNode * a_node)
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
            /* Process here text node, It is available in cpStr :TODO: */
            if(strlen((char*)cur_node->content)>0&&strcmp((char *)cur_node->parent->name,"p")==0)
                printf("node type: Text, node content: %s,  parent %s\n", (char *)cur_node->content, (char *)cur_node->parent->name);
            if(strcmp((char *)cur_node->parent->name,"div")==0 &&
                isAnswer((char*) cur_node->content))
                    printf("%s,%s \n",(char *)cur_node->content,(char*)cur_node->parent->name);
            
        }
        traverse_dom_trees(cur_node->children);
    }
}

int main(int argc, char **argv) 
{
    htmlDocPtr doc;
    xmlNode *roo_element = NULL;
    if (argc != 2)  
    {
        printf("\nInvalid argument\n");
        return(1);
    }
    

    doc = htmlReadFile(argv[1], NULL, HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
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

    traverse_dom_trees(roo_element);

    xmlFreeDoc(doc);       // free document
    xmlCleanupParser();    // Free globals
    return 0;
}