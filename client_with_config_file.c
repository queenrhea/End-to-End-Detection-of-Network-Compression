#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     22
#define MAXLINE 1025

int main() {
    int client_socket;
    char buffer[MAXLINE];

    struct sockaddr_in servaddr;

    char *hello = "Hello from client";

    //Creating socket file descriptor
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    
    //Server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    int n, len;
    
    sendto(client_socket, (const char *)hello, strlen(hello), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    printf("Hello message sent.\n");

    //Make connection to server
    connect(client_socket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
        
    recv(client_socket, buffer, MAXLINE, 0);
    
    printf("Data Received: %s\n", buffer);

    FILE *fp = fopen("myconfig.json", "r"); 
    
    if(fp == NULL){ 
        perror("File"); 
        return 0; 
    } 

    while((bytes_read = fread(buffer, sizeof(buffer), 1, fp))>0){ 
        //Include checks for if cannot read file
        send(sockfd, buffer, bytes_read, 0); 
    } 

    fclose(fp);


    close(sockfd);
    return 0;
}
