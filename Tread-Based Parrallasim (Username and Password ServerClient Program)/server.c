/* 
 * server.c - An iterative project4 server 
 */ 
/* $begin server main */
#include "csapp.h"
//#include <pthread>
void StockService(int connfd);
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
    pthread_t tid;//thread id
    listenfd = Open_listenfd(argv[1]);
    while (1) {
	clientlen = sizeof(struct sockaddr_storage); 
    connfd =Malloc(sizeof(int));   
    // wait for the connection from the client. 
	*connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
    Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE,client_port, MAXLINE, 0);
    
    printf("Connected to (%s, %s)\n", client_hostname, client_port);
        
    //this creats a thread where it intracts with the given client effectively though the thread function call with connfd passed in
    Pthread_create(&tid, NULL, thread, connfd);
    //Close(connfd);
    printf("(%s, %s) disconnected\n", client_hostname, client_port);
    }
    exit(0);
}

//function taht is called when a thread is made for diffrent clients, where the file descriptor is passed in
void *thread(void *vargp){
    
    int connfd = *((int*)vargp);
    Pthread_detach(pthread_self());//mades each thread individual
    Free(vargp);//frees the memory space of vargp
    StockService(connfd);//calls the fucntion where it commmunicates between client and server
    Close(connfd);//closes the socket
    return NULL;  
}
/* $end server main */
