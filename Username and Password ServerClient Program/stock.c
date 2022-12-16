
#include "csapp.h"
#include <stdbool.h>
void stock(int connfd) 
{
    FILE *in_file=fopen("StockFile.txt","r");//opens the file into in_file
    
    //char array or string variables
    //char buf[MAXLINE]; 
    char user[MAXLINE]; 
    char pass[MAXLINE]; 
    char s[MAXLINE]; 
    rio_t rio;
    char * ack = "Incorrect User or Password";

    int i = 0;

    Rio_readinitb(&rio, connfd);
    //reads the username and passwrod send from client in variable user and pass
    Rio_readlineb(&rio, user, MAXLINE); 
    Rio_readlineb(&rio, pass, MAXLINE);
    //removes the last newline character from both variables since 
    strtok(user, "\n");
    strtok(pass, "\n");
    
    
    //while each word from the file this loop runs
     while (fscanf(in_file,"%s", s) && i <19)
          {
               //compares the user to the string word from the file and if its true scans another word which would be a password
               if(strcmp(s, user)==0) {
                    fscanf(in_file,"%s", s);
                   //if password matches than scan another word and we write the stock value back to the client
                       if(strcmp(s, pass)==0) {
                          printf("USER FOUND\n");
                          fscanf(in_file,"%s", s); 
                            Rio_writen(connfd, s, strlen(s)); 
                            Close(connfd);//flose the server end of socket connection to client
                           break;//breaks out of the loop
                       }
                }
                
                i+=1;
         }
      if ( i>= 19){
      Rio_writen(connfd, ack, strlen(ack)); 
      Close(connfd);
      }
    fclose(in_file);//flose the file
}



