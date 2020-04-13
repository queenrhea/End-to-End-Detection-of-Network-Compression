#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>

#define PORT     9876
#define MAXLINE 65536

#define MAXBUF  10 * 1024

int main() {
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;
    extern int errno;

    char buf[MAXBUF];
    
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    
    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    
    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    
    int n;
    unsigned int len;

    len = sizeof(cliaddr); //len is value/resuslt

    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    sendto(sockfd, (const char *)hello, strlen(hello),
        0, (const struct sockaddr *) &cliaddr,
            len);
    printf("Hello message sent.\n");


   /* do forever */
    int rc;

    if (rc==recvfrom(sockfd, buf, MAXBUF, 0, (const struct sockaddr *)&cliaddr, &len) < 0) {
        printf("server error: errno %d\n",errno); 
        //printf("server error: errno %d\n",errno);
        perror("reading datagram");
        exit(1);
    }

    //printf("udpserver: got packet");

    // int data_size, saddr_size;

    
    // saddr_size = sizeof(servaddr);
    // printf("waiting for data...");
    // data_size = recvfrom(sockfd, buf, MAXBUF, 0, (struct sockaddr*) &servaddr, (socklen_t*)&saddr_size);

    // if(data_size<0)
    // {
    //   printf("Packets not recieved \n");
    //   return 1;
    // }
    
    
    close(sockfd);
    return 0;
}
