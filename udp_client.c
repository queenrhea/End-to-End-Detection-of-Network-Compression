#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     9876
#define MAXLINE 1100

#define PCKT_LEN 16

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
    servaddr.sin_addr.s_addr = inet_addr("192.168.1.19");

    // buffer to hold the packet
    //char buffer_p[PCKT_LEN];

    // set the buffer to 0 for all bytes
    memset(buffer, 0, MAXLINE);
    
    int n, rc;
    unsigned int len;
    int i;
    for(i=0; i<2; i++){
        sendto(sockfd, (char *)buffer, MAXLINE,
            0, (const struct sockaddr *) &servaddr,
            sizeof(servaddr));
        printf("Hello message sent.\n");
    }
    

    for(;;){
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                MSG_WAITALL, (struct sockaddr *) &servaddr,
                &len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);
    }

    close(sockfd);
    return 0;
}
