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
    unsigned int len;
    char buffer[MAX]; 
    struct sockaddr_in servaddr, client; 
  
    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    //bzero(&servaddr, sizeof(servaddr)); 
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT); 

    //read(sockfd, buffer, sizeof(buffer)); 
  
    // Binding newly created socket to given IP and verification 
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
  
    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server is listening..\n"); 
    len = sizeof(client); 
  
    // Accept the data from client 
    connfd = accept(sockfd, &client, &len); 
    if (connfd < 0) { 
        printf("Server accept failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server accepted the client.\n"); 

    FILE *fp;

    int ch = 0;
    fp = fopen("myconfig2.ini", "a");
    int words;

    read(connfd, &words, sizeof(int));

    while(ch != words) {
        read(connfd, buffer, 255);
        fprintf(fp, "%s", buffer);
        ch++;
    }

    strtok(words, "=");

    printf("File has been received successfully.\n");
  
    close(connfd);
    close(sockfd); 

    }
