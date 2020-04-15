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
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // buffer to hold the packet
    char buffer_p[PCKT_LEN];

    // set the buffer to 0 for all bytes
    memset(buffer_p, 0, PCKT_LEN);
    
    int n, rc;
    unsigned int len;
    int i;
    
    for(i=0; i<20; i++){
        sendto(sockfd, (const char *)hello, strlen(hello),
            0, (const struct sockaddr *) &servaddr,
                sizeof(servaddr));
    printf("Hello message sent.\n");
    }
    

    //sendto(sockfd, buffer_p, len, unsigned int flags,
//const struct sockaddr *to, socklen_t tolen);

    //if( rc == sendto(sockfd, buffer_p, sizeof(buffer_p),0,(const struct sockaddr *) &servaddr,sizeof(//servaddr)) != 0 ) {
             //buffers aren't available locally at the moment,
             //* try again.
             
            // if (errno == ENOBUFS)
            //     continue;
            //perror("sending datagram");
            //exit(1);
        //}
    //for(;;){
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                MSG_WAITALL, (struct sockaddr *) &servaddr,
                &len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);
    //}


    //******AFTER LOW ENTROPY DATA

    //**********15 SEC. WAIT
    int number_of_seconds = 15;
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds) {
        ; 
    }

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

    // char ch;
    //int j = 0; 
    //while(j < 3) {
        //printf("Hi2");
    fscanf(fp, "%u", randval);
    write(sockfd, randval, 255);
        //ch = fgetc(fp);
        //printf("Hi3");
        //j++;
    //}


    //***********COPY BUFFER OF RANDOM BITS TO PAYLOAD
    // int *payload = malloc(3*sizeof(int));   // allocated memory has no effective type
    // int arr[3] = {1,2,3};
    // memcpy(p,arr,3*sizeof(int));      // allocated memory now has an effective type

    //copy the random bits into the buffer*
    memcpy(&randval, &buffer, sizeof(buffer)); //copying src to dest, with sizeof(dest)

    //*****SEND THIS TO SERVER?
    



    printf("%u\n", randval);
    printf("File has been successfully sent.\n");

    close(sockfd);
    fclose(fp);
    return 0;
}
