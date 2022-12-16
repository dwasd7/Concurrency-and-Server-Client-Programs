#include "csapp.h"

typedef struct{
    char username[MAXLINE];
    char password[MAXLINE];
    char stockValue[MAXLINE];
}Stock;

void CheckStockFile(int connfd, char* username, char* password){
    FILE *fp;
    Stock myStock;
    char* failureMessage = "Error: Username and password did not match!!\n";
    char successMessage[50] = "The stock value is: ";
    char buffer[MAXLINE];
    fp = fopen("StockFile.txt", "rt");
    if (fp == NULL) 
        { 
            printf("File does not exist"); 
            exit(1); 
        }


    while (fgets(buffer,MAXLINE, fp) != NULL) {
        // breaks the buffer sting into 3 string tokens
        sscanf(buffer, "%s %s %s", myStock.username, myStock.password, myStock.stockValue);
        
        if(strcmp(myStock.username,username)==0 && strcmp(myStock.password, password)==0){
            strcat(successMessage,myStock.stockValue);
            strcat(successMessage,"\n");
            Rio_writen(connfd, successMessage, strlen(successMessage)); 
            fclose(fp);
            return;
            }
        }
    
    //in case of failure
    Rio_writen(connfd, failureMessage, strlen(failureMessage)); 
    fclose(fp);
    return;
}
void StockService(int connfd) 
{
    size_t n; 
    char username[MAXLINE]; 
    char password[MAXLINE];
    char* userReceivedMessage = "Username sucessfully received!\n";
    char* passReceivedMessage = "Password sucessfully received!\n";

    rio_t rio;
      
    Rio_readinitb(&rio, connfd);
    n = Rio_readlineb(&rio, username, MAXLINE);
	printf("server received username with %d bytes\n", (int)n);
    
    //removing the extra /n line so that it can be matched with the username from file.
    username[n-1]= '\0';
    
    //sending username sucessfully recieved message to client
    Rio_writen(connfd, userReceivedMessage,strlen(userReceivedMessage));
    n = Rio_readlineb(&rio, password, MAXLINE);
  	printf("server received password with %d bytes\n", (int)n);
    
    //removing the extra /n line so that it can be matched with the prossword from file.
    password[n-1]= '\0';
    
    //sending password sucessfully recieved message to client
    Rio_writen(connfd, passReceivedMessage,strlen(passReceivedMessage));   
    
    //this function opens StockFile.txt and try to match 
    //username and password from client with that provided in the file. 
    //if sucessfully matched, it sends the stock value to the client. 
    CheckStockFile(connfd, username, password);
    
    return;
}


