
#include "csapp.h"
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
//#include "stock.c"
void stock(int connfd);
//Timer function to be able to read the File Descriptor and return 1 if fd is readable else return -0
int readable_timeo(int fd, int sec)
 {
     fd_set rset;
     struct timeval tv;

     FD_ZERO(&rset);
     FD_SET(fd, &rset);

     tv.tv_sec = sec;
     tv.tv_usec = 0;

     return (select(fd + 1, &rset, NULL, NULL, &tv));
         /* > 0 if descriptor is readable */
 }

//takes in arguement ./server and port  then stores it in argv
int main(int argc, char **argv) 
{
    
    //variables
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;  /* Enough space for any address */  //line:netp:echoserveri:sockaddrstorage
    char client_hostname[MAXLINE], client_port[MAXLINE];
    //if the arguement more than 2 then prints this
    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(0);
    }

    listenfd = Open_listenfd(argv[1]); //listens for port number same as the client's
    
    while (1) { 
	clientlen = sizeof(struct sockaddr_storage); 
    printf("WAITING FOR CLIENT INPUT\n");
    //listens to the client port and checks for infor being sent
	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
         
        Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE, 
                    client_port, MAXLINE, 0);
  
        printf("Connected to (%s, %s)\n", client_hostname, client_port);
        
    //stock fucntion call to get the right stock depending on user input on clinet side
    stock(connfd);
        
    //Timer FUntion Implementation where the socket closes if user does not send any UserName for 30 Sec   
    if (readable_timeo(connfd,30) == 0){ 
          Close(connfd); 
        continue; //goes back up to check and never closes
     }
              
}
}
/* $end echoserverimain */
