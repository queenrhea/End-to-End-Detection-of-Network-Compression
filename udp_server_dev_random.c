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
#define DESTPORT 8765
#define MAXLINE 65536 //1100

#define MAXBUF  10 * 1024
#define ACK 'z'

int main() {
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;
    extern int errno;
    int ackvar = ACK;

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

    //for(;;){
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);
 
    int i;
    for(i=0; i<n; i++){
        printf("%02x",buffer[i]);
    }

    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    printf("n:%d\n",n);
    sendto(sockfd, (const char *)hello, strlen(hello),
        0, (const struct sockaddr *) &cliaddr,
            len);
    printf("Hello message sent.\n");
    //}


    //printf("Client : %s\n", buf);


    FILE *fp;

    int ch = 0;
    fp = fopen("random_c.c", "a");

    if(fp == NULL) {
        printf("File not found.");
        exit(0);
    }

    unsigned int randval;

    fread(&randval, sizeof(randval), 1, fp);

    //read(buffer, &randval, sizeof(randval));

    printf("Hi1");

    //int j = 0;
    //while(j < 3) {
        //fprintf("Hi2");
        //read(sockfd, buffer, 255);
    fprintf(fp, "\t%u\t", randval);
        //j++;
        //fprintf("Hi3");
    //}

    printf("%u\n", randval);

    printf("File has been received successfully.\n");
    


    
    
    close(sockfd);
    return 0;
}
