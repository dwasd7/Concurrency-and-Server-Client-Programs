
#include "csapp.h"

int main(int argc, char **argv) 
{
    int clientfd;
    char *host, *port, num1[MAXLINE], num2[MAXLINE], op[MAXLINE], result[MAXLINE];
    rio_t rio;
    char * Instructions = "CLIENT-SERVER CALCULATOR\n\nFirst Choose a number. \nSecond Choose a Operator within (+, -, /, *).\nFinally Choose the Second Number\n";
    if (argc != 3) {
	fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
	exit(0);
    }
    host = argv[1];
    port = argv[2];
    
    clientfd = Open_clientfd(host, port);
    puts(Instructions);
    printf("First Number: ");
    Fgets(num1, MAXLINE, stdin);
	Rio_writen(clientfd, num1, strlen(num1));

    printf("Operation: ");
    Fgets(op, MAXLINE, stdin);
    Rio_writen(clientfd, op, strlen(op));
       
    printf("Second Number: ");
    Fgets(num2, MAXLINE, stdin);
    Rio_writen(clientfd, num2, strlen(num2));

    Rio_readinitb(&rio, clientfd);

	Rio_readlineb(&rio, result, MAXLINE); 

    puts(result);

    Close(clientfd); 
    exit(0);
}
/* $end clientmain */
