#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include "json-c/json.h"
#include <fcntl.h>
#include <time.h>

 
int main(int argc, char **argv)
{ 

    /* JSON PARSING */

    char buffer1[1024];
    struct json_object *parsed_json;
    struct json_object *serverip;
    struct json_object *srcportudp;
    struct json_object *destportudp;
    struct json_object *destporttcphead;
    struct json_object *destporttcptail;
    struct json_object *portnumtcp;
    struct json_object *payload;
    struct json_object *intermtime;
    struct json_object *numudppackets;
    struct json_object *ttl;

    char *filename;
    FILE *fp;

    // getting file from command-line argument
    if (argc >= 2){
        filename = argv[1];
        printf("File name: %s\n", filename);
        fp = fopen(argv[1], "r");
        fread(buffer1, 1024, 1, fp);
        fclose(fp);
    }
    else {
        perror("fopen");
    }
    
    parsed_json = json_tokener_parse(buffer1);

    json_object_object_get_ex(parsed_json, "serverip", &serverip);
    json_object_object_get_ex(parsed_json, "srcportudp", &srcportudp);
    json_object_object_get_ex(parsed_json, "destportudp", &destportudp);
    json_object_object_get_ex(parsed_json, "destporttcphead", &destporttcphead);
    json_object_object_get_ex(parsed_json, "destporttcptail", &destporttcptail);
    json_object_object_get_ex(parsed_json, "portnumtcp", &portnumtcp);
    json_object_object_get_ex(parsed_json, "payload", &payload);
    json_object_object_get_ex(parsed_json, "intermtime", &intermtime);
    json_object_object_get_ex(parsed_json, "numudppackets", &numudppackets);
    json_object_object_get_ex(parsed_json, "ttl", &ttl);

    //saving json objects
    char *serverip2 = json_object_get_string(serverip);
    int srcportudp2 = json_object_get_int(srcportudp);
    int destportudp2 = json_object_get_int(destportudp);
    char *destporttcphead2 = json_object_get_string(destporttcphead);
    char *destporttcptail2 = json_object_get_string(destporttcptail);
    char *portnumtcp2 = json_object_get_string(portnumtcp);
    int payload2 = json_object_get_int(payload);
    int intermtime2 = json_object_get_int(intermtime);
    int numudppackets2 = json_object_get_int(numudppackets);
    int ttl2 = json_object_get_int(ttl);

    /* JSON PARSING ENDS */


    /* TCP CONNECTION */

    int client_socket, connfd; 
    char buffer[payload2]; 
    struct sockaddr_in cliaddr; 
  
    // Socket creation
    client_socket = socket(AF_INET, SOCK_STREAM, 0); 
    if (client_socket == -1) { 
        printf("Socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
  
    // Assign IP, PORT 
    cliaddr.sin_family = AF_INET; 
    cliaddr.sin_addr.s_addr = inet_addr("192.168.1.17"); 
    cliaddr.sin_port = htons(destportudp2);

  
    // Connect the client socket to server socket 
    if (connect(client_socket, (const struct sockaddr *)&cliaddr, sizeof(cliaddr)) != 0) { 
        printf("Connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("TCP connection from client to the server successful.\n\n");

    /* UDP */

    int sockfd;
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(destportudp2);
    servaddr.sin_addr.s_addr = inet_addr("192.168.1.17");

    /* DON'T FRAGMENT FLAG */
    int val = 1;

    if (setsockopt(sockfd, IPPROTO_IP, IP_MTU_DISCOVER, &val, sizeof(val)) < 0){
        printf("Don't fragment flag not set successfully.\n\n");
    }

    else {
        printf("Don't fragment flag set to 1.\n\n");
    }

    // set the buffer to 0 for all bytes
    memset(buffer, 0, payload2);


    float threshold = 100; // set threshold for compression detection
    
    // measuring time it takes to send the 6000 packets
    clock_t start1, end1;
    start1 = clock();

    
    int packet_id = 0;
    int i;
    
    // sending udp packet train for low entropy
    for(i=0; i<numudppackets2; i++){
        //setting packet id
        memset(buffer, packet_id, 2);
        packet_id += 1;

        sendto(sockfd, (char *)buffer, sizeof(buffer),
            0, (const struct sockaddr *) &servaddr,
            sizeof(servaddr));

    }
    end1 = clock();


    // calculating the difference between arrival time in first and last packets
    float seconds_short_int_low = (float) (end1 - start1) / CLOCKS_PER_SEC;
    float milliseconds_low = seconds_short_int_low * 1000; 

    printf("It took %f milliseconds to complete low entropy.\n", (milliseconds_low));

    /* COMPRESSION DETECTION FOR LOW ENTROPY */
    if(milliseconds_low > threshold) {
        printf("Compression detected!\n\n");
    }
    else {
        printf("No compression was detected.\n\n");
    }
    
    /* END OF LOW ENTROPY */

    // Intermeasurement wait period
    printf("Waiting...\n");
    sleep(intermtime2);
    printf("Done waiting\n\n");

    /* HIGH ENTROPY */

    // measuring time it takes to send the 6000 packets
    clock_t start2, end2;
    start2 = clock();
    
    // sending udp packet train for high entropy
    for(i=0; i<numudppackets2; i++){
        // reading from /dev/urandom and copying contents into buffer
        int fd = open("/dev/urandom", O_RDONLY);
        read(fd, buffer, sizeof(buffer));
        close(fd);

        //setting packet id
        memset(buffer, packet_id, 2);
        packet_id += 1;

        // send buffer contents to server
        sendto(sockfd, (char *)buffer, sizeof(buffer),
            0, (const struct sockaddr *) &servaddr,
            sizeof(servaddr));
    }
    end2 = clock();

    // calculating the difference between arrival time in first and last packets
    float seconds_short_int_high = (float) (end2 - start2) / CLOCKS_PER_SEC;
    float milliseconds_high = seconds_short_int_high * 1000;

    printf("It took %f milliseconds to complete high entropy.\n", (milliseconds_high));

    /* COMPRESSION DETECTION FOR HIGH ENTROPY */
    if(milliseconds_high > threshold) {
        printf("Compression detected!\n");
    }
    else {
        printf("No compression was detected.\n");
    }

    printf("Bye.\n");

    close(client_socket);
    close(sockfd);

    return 0;
}
