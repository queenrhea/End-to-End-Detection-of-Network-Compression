#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     9876
#define MAXLINE 65536

int main() {
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from client";
    struct sockaddr_in     servaddr;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    int n, len;
    
    sendto(sockfd, (const char *)hello, strlen(hello),
        0, (const struct sockaddr *) &servaddr,
            sizeof(servaddr));
    printf("Hello message sent.\n");
        
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                MSG_WAITALL, (struct sockaddr *) &servaddr,
                &len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);

    int bytes_read = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (bytes_read==-1) {
        perror("Connect");
        return 1;
    }

    FILE *fp = fopen("myconfig.json", "r"); 
    
    if(fp == NULL){ 
        perror("File not found"); 
        return 0; 
    } 

    while((bytes_read = fread(buffer, sizeof(buffer), 1, fp))>0){ 
        //Include checks for if cannot read file
        send(sockfd, buffer, bytes_read, 0);  //send config. file contents to server
    } 

    fclose(fp);

    close(sockfd);
    return 0;
}
