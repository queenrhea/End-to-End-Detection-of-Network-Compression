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
    servaddr.sin_addr.s_addr = inet_addr("192.168.1.19");

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

/*
    //******AFTER LOW ENTROPY DATA

    //**********15 SEC. WAIT
    int number_of_seconds = 15;
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    printf("Waiting...\n");
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds) {
        ; 
    }
    printf("Done waiting\n");
    //********* HIGH ENTROPY

    unsigned int randval;

    FILE *fp;


    fp = fopen("/dev/random", "r");

    if(fp == NULL) {
        printf("File not found.");
        exit(0);
    }

    fread(&randval, sizeof(randval), 1, fp);

    //write(buffer, &randval, sizeof(int));
    //rewind(fp);

    printf("Hi1");

  
    //***********COPY BUFFER OF RANDOM BITS TO PAYLOAD

    memcpy(&randval, &buffer, sizeof(buffer)); //copying src to dest, with sizeof(dest)

    int y;
    int z = sizeof(buffer);
    for(y=0; y<z; y++){
        printf("%d",buffer[z]);
    }

    //*****SEND THIS TO SERVER?
    int x;
    for(x=0; x<2; x++){
        sendto(sockfd, (char *)buffer, sizeof(buffer),
            0, (const struct sockaddr *) &servaddr,
            sizeof(servaddr));
        printf("Hello message sent.\n");
    }



    printf("%u\n", randval);
    printf("File has been successfully sent.\n");
*/

    close(sockfd);
    //fclose(fp);
    return 0;
}
