#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAX 1024 
#define PORT 9876 
 
int main() 
{ 
    int sockfd, connfd; 
    char buffer[MAX]; 
    struct sockaddr_in servaddr, cli; 
  
    //Socket creation
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    //bzero(&servaddr, sizeof(servaddr)); 
  
    //Assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(PORT);

    //read(sockfd, buffer, sizeof(buffer)); 
  
    //Connect the client socket to server socket 
    if (connect(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) { 
        printf("Connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("Connected to the server.\n"); 
  

    // close the socket 
    close(sockfd); 
}
