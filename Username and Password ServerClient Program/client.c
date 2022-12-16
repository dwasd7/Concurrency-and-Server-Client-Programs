
#include "csapp.h"
#include<stdio.h>
//takes in arguements ./client , host, and port then stores it in argv
int main(int argc, char **argv) 
{
    int clientfd;
    char *host, *port, buf[100];
    rio_t rio;
    char user[MAXLINE], pass[MAXLINE];

    //of the arguements more than 3 then prints this
    if (argc != 3) {
	fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
	exit(0);
    }
    //argv[0] = "./echoclient"
    host = argv[1];
    port = argv[2];

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);//connect to client
    
    
    //User Input for Username   
    printf("WELCOME! \n");
    printf("Enter UserName: ");
    Fgets(user, MAXLINE, stdin);
    //Writes to the server passing in user variable
    Rio_writen(clientfd, user, strlen(user));
    
    
    //User Input for Password
    printf("Enter PassWord: ");
    Fgets(pass, MAXLINE, stdin);
    //Writes to the server passing in pass variable
    Rio_writen(clientfd, pass, strlen(pass));
    
  //  while (Rio_readlineb(&rio, buf, MAXLINE)){
 //       puts(buf);
  //  }
    
    //Reads what server sends in the buf variable
    Rio_readlineb(&rio, buf, MAXLINE);
    puts(buf); //prints output on the screne
    Close(clientfd); //closes the clinet end of socket
     //line:netp:echoclient:close
    exit(0);
}

