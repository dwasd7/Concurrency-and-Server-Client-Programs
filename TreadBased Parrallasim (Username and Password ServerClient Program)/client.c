/*
 * client.c - A client program that
              1. sends username to server
              2. sends password to server
              3. Receives stock value information if the username, password combination 
                is present in server database. 
 */
/* $begin clientmain */
#include "csapp.h"

int main(int argc, char **argv) 
{
    int clientfd;
    char *host, *port, username[MAXLINE], password[MAXLINE], messageFromServer[MAXLINE];
    rio_t rio;

    if (argc != 3) {
	fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
	exit(0);
    }
    host = argv[1];
    port = argv[2];

    clientfd = Open_clientfd(host, port);
    
    printf("Enter the username:");
    Fgets(username, MAXLINE, stdin);
	Rio_writen(clientfd, username, strlen(username));

    Rio_readinitb(&rio, clientfd);
    //waits for server to send username sucessfully recived message.
	Rio_readlineb(&rio, messageFromServer, MAXLINE); 
    Fputs(messageFromServer,stdout);

    printf("Enter the password:");
    Fgets(password, MAXLINE, stdin);
    Rio_writen(clientfd, password, strlen(password));
   
    //waits for server to send username sucessfully recived message.
	Rio_readlineb(&rio, messageFromServer, MAXLINE); 
    Fputs(messageFromServer,stdout);

    //waits for server to send username/password mismatch message or stock value
	Rio_readlineb(&rio, messageFromServer, MAXLINE); 

    Fputs(messageFromServer, stdout);

    Close(clientfd); 
    exit(0);
}
/* $end clientmain */
