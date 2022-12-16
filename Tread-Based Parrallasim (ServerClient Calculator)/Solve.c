#include "csapp.h"
#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void Compute(int connfd, int num1, int num2, char* op){
    
    char buffer[MAXLINE]; //used to store the answer as string to send back to client
    long int answer;//stores the answer for +, -, and * operators
    double divans; //stores the answer for the division operation
    
    //removes the newline character from op
    strtok(op, "\n");
    //compares op to + and if its true then this executes
    if(strcmp(op,"+") == 0){
        answer = num1 + num2;//adds num1 and num2
        sprintf(buffer,"%li",answer); //converts long integer to string into buffer
        Rio_writen(connfd, buffer, strlen(buffer));//writes the buffer to client
        return;
    }
    //compares op to - and if its true then this executes
    else if(strcmp(op,"-") == 0){
        answer = num1 - num2;//substract num1 and num2
        sprintf(buffer,"%li",answer);//converts long integer to string into buffer
        Rio_writen(connfd, buffer, strlen(buffer));//writes the buffer to client
        return;
    }
    //compares op to * and if its true then this executes
    else if(strcmp(op,"*") == 0){
        answer = num1 * num2;//multiplies num1 and num2
        sprintf(buffer,"%li",answer);//converts long integer to string into buffer
        Rio_writen(connfd, buffer, strlen(buffer));//writes the buffer to client
        return;
    }
    //compares op to / and if its true then this executes
    else if(strcmp(op,"/") == 0){
        divans = (double)num1 / (double)num2; //divides num1 and num2 by converting it to double for possible decimal answer
        sprintf(buffer,"%f",divans);//converts float to string into buffer
        Rio_writen(connfd, buffer, strlen(buffer));//writes the buffer to client
        return;
    }
    return;
}
void Solve(int connfd) 
{
    size_t n; 
    char num1[MAXLINE], num2[MAXLINE], op[MAXLINE], output[MAXLINE];
    rio_t rio;
    char* failed = "Invalid Input, Locked Out\n"; //message if inputs are invalid
    Rio_readinitb(&rio, connfd);
    //Reads in the all the buffers written from the client side (num1, num2, and op)
    n = Rio_readlineb(&rio, num1, MAXLINE);
	printf("server received num1 with %d bytes\n", (int)n);
    n = Rio_readlineb(&rio, op, MAXLINE);
  	printf("server received Operation with %d bytes\n", (int)n);  
    n = Rio_readlineb(&rio, num2, MAXLINE);
  	printf("server received num2 with %d bytes\n", (int)n);
    
    //removes the nextline character from num1 and num2
    strtok(num1, "\n");
    strtok(num2, "\n");
    
    //Variables to make sure that the inputs are numbers and operations avaliable and I set them originally to zero
    int n1IsDigit = 0;
    int Isop = 0;
    int n2IsDigit = 0;
    
    //Both bool goes through the char array and checks if it is a digit and if a single character is not a digit it sets its apporopriate variable to 1 then breaks out
	for(int i=0;num1[i]!='\0';i++)
	{	
			if(!isdigit(num1[i])){
				n1IsDigit = 1;
                break;
			}
	}
    for(int j=0;num2[j]!='\0';j++)
	{
			if(!isdigit(num2[j])){
				n2IsDigit = 1;
                break;
			}
	}

    
   //checks if the operator is all of these or not and is only one character and if it is then sets the Isop to 0 else 1
   if(strcmp(op,"+\n") == 0 || strcmp(op,"-\n") == 0 || strcmp(op,"*\n") == 0 || strcmp(op,"/\n") == 0) {
       Isop = 0;
   }
       else{
           Isop = 1;
       }
    
    //if All the inputs are valid then it calls the Compute Function otherwise write the failed message to the client
    if(n2IsDigit == 0 && n1IsDigit == 0 && Isop == 0){
        //converts num1 and num2 into int and passes it as an arguement to Compute Function
        int n1 = atoi(num1);
        int n2 = atoi(num2);
        Compute(connfd, n1 , n2, op);   
    }
    else{
        Rio_writen(connfd, failed, strlen(failed)); 
    } 
    
    return;
}


