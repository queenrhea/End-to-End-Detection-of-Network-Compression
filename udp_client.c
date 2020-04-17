#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>

#define SRC_PORT 9876
#define DST_PORT 8765
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
    servaddr.sin_port = htons(DST_PORT);
    servaddr.sin_addr.s_addr = inet_addr("192.168.1.4");

    // set the buffer to 0 for all bytes
    memset(buffer, 0, MAXLINE);
    
    int n;
    unsigned int len;
    int i;
    for(i=0; i<10; i++){
        sendto(sockfd, (char *)buffer, MAXLINE,
            0, (const struct sockaddr *) &servaddr,
            sizeof(servaddr));
        printf("Hello message sent.\n");
    }
    

    //for(;;){
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                MSG_WAITALL, (struct sockaddr *) &servaddr,
                &len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);
    //}


    //******AFTER LOW ENTROPY DATA

    //**********5 SEC. WAIT
    printf("Waiting...\n");
    sleep(5);
    printf("Done waiting\n");
    //********* HIGH ENTROPY

    unsigned int randval;

    FILE *fp;


    fp = fopen("/dev/urandom", "r");

    if(fp == NULL) {
        printf("File not found.\n");
        exit(0);
    }

    fread(&randval, sizeof(randval), 1, fp);

    printf("Hi1\n");

  
    //***********COPY BUFFER OF RANDOM BITS TO PAYLOAD

    memcpy(&buffer, &randval, sizeof(buffer)); //copying src to dest, with sizeof(dest)

    printf("Buffer: ");
    int y;
    int z = sizeof(buffer);
    for(y=0; y<z; y++){
        printf("%u",buffer[z]);
    }

    //*****SEND THIS TO SERVER?
    int x;
    //for(x=0; x<2; x++){
        sendto(sockfd, (char *)buffer, sizeof(buffer),
            0, (const struct sockaddr *) &servaddr,
            sizeof(servaddr));
        printf("\nBuffer sent.\n");
    //}


    printf("Random value: %u\n", randval);
    printf("Bye.\n");


    close(sockfd);
    fclose(fp);
    return 0;
}
