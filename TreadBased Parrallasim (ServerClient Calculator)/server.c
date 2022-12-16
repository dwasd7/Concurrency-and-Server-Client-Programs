
#include "csapp.h"
//#include <pthread>
void Solve(int connfd);
void *thread(void *vargp);
int main(int argc, char **argv) 
{
    int listenfd, *connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;  /* Enough space for any address */                //line:netp:echoserveri:sockaddrstorage
    char client_hostname[MAXLINE], client_port[MAXLINE];
    
    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(0);
    }
    pthread_t tid;
    listenfd = Open_listenfd(argv[1]);
    while (1) {
	clientlen = sizeof(struct sockaddr_storage); 
    connfd =Malloc(sizeof(int));   
    // wait for the connection from the client. 
	*connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
    Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE,client_port, MAXLINE, 0);
    
    printf("Connected to (%s, %s)\n", client_hostname, client_port);
        
        
    Pthread_create(&tid, NULL, thread, connfd);
    //Close(connfd);
    printf("(%s, %s) disconnected\n", client_hostname, client_port);
    }
    exit(0);
}

void *thread(void *vargp){
    int connfd = *((int*)vargp);
    Pthread_detach(pthread_self());
    Free(vargp);
    Solve(connfd);
    Close(connfd);
    return NULL;  
}
/* $end server main */
