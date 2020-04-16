#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include "json-c/json.h"

#define PORT     9876
#define DESTPORT 8765
#define MAXLINE 1100

#define MAXBUF  10 * 1024
#define ACK 'z'

int main(int argc, char **argv) {
    
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

    char *serverip2 = json_object_get_string(serverip);
    //printf("Server IP: %s\n",serverip2);

    int srcportudp2 = json_object_get_int(srcportudp);
    //printf("Source Port UDP: %d\n", srcportudp2);

    int destportudp2 = json_object_get_int(destportudp);
    //printf("Destination Port UDP: %d\n", destportudp2);

    char *destporttcphead2 = json_object_get_string(destporttcphead);
    //printf("Destination Port TCP Head: %s\n",destporttcphead2);

    char *destporttcptail2 = json_object_get_string(destporttcptail);
    //printf("Destination Port TCP Tail: %s\n",destporttcptail2);

    char *portnumtcp2 = json_object_get_string(portnumtcp);
    //printf("Port Number TCP: %s\n",portnumtcp2);

    int payload2 = json_object_get_int(payload);
    //printf("Payload: %d\n", payload2);

    int intermtime2 = json_object_get_int(intermtime);
    //printf("Inter-Measurement Time: %d\n", intermtime2);

    int numudppackets2 = json_object_get_int(numudppackets);
    //printf("The Number of UDP Packets in the UDP Pakcet Train: %d\n", numudppackets2);

    int ttl2 = json_object_get_int(ttl);
    //printf("TTL for the UDP Packets: %d\n", ttl2);
    /* JSON PARSING ENDS */


    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;
    extern int errno;
    int ackvar = ACK;

    //char buf[MAXBUF];
    
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    
    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = inet_addr("192.168.1.19");
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

    for(;;){
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);
 
    int i;
    for(i=0; i<n; i++){
    printf("%x",buffer[i]);
    }
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    printf("n:%d\n",n);
    sendto(sockfd, (const char *)hello, strlen(hello),
        0, (const struct sockaddr *) &cliaddr,
            len);
    printf("Hello message sent.\n");
    }





    /*int rc, current = 0;

    if (rc==recvfrom(sockfd, buf, MAXBUF, MSG_WAITALL, (const struct sockaddr *)&cliaddr, &len) != 0) {
        printf("server error: errno %d\n",errno);
        //printf("server error: errno %d\n",errno);
        perror("reading datagram");
        exit(1);
    }

    printf("udpserver: got packet %d\n", current); */

    // if(sendto(sockfd,&ackvar,sizeof(long), 0, (const struct sockaddr *) &cliaddr, &len) != 0) {
        
    //     perror("sendto");

    //     // if (errno == ENOBUFS)
    //     //     continue;
    //     exit(1);
    // }
    // current++;


    //printf("Client : %s\n", buf);

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
