struct sentData{
    const char * ip;
    const char *port;
    const char *nume;
};
using namespace std;
int establish_connection(sentData myData){
    struct sockaddr_in server;
    int port = atoi(myData.port);
    int sd = socket (AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
  /* adresa IP a serverului */
    server.sin_addr.s_addr = inet_addr(myData.ip);
  /* portul de conectare */
    server.sin_port = htons (port);
    if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
        perror ("[client]Eroare la connect().\n");
        return -1;
    }   
    return sd;
}

int login(const char * nume, int sd){
    char container[1000];
    int size;
    char ch[1];
    printf("%s",nume);
    bzero(container,sizeof(container));
    //get name
    sprintf(container,"%s",nume);
    //send size
    size = strlen(container);
    write(sd,&size,sizeof(int));
    //send data
    write(sd,container,size);
    //read response
    bzero(ch,sizeof(ch));
    read(sd,ch,1);
    if(ch[0]=='1')
        return 1;    
    else if (ch[0]=='2'){
        return 2;
    }
    return 0;
}

