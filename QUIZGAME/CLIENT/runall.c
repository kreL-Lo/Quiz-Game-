#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include <sys/types.h>
//mic script de a rula mai multe executii a jocului 
int main(){
    char path[1000];
    getcwd(path,sizeof(path));
    strcat(path,"/game");
    for(int i =0 ;i<4;i++){
        pid_t p=fork();
        if(p==0)
        {
            static char * argv[]={"./game",NULL};
            execv(path,argv);
            printf("child nr %d \n",i);
            exit(1);
        }
        else{
           //exit(1);
        }
    }
       
}