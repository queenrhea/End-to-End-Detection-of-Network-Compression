#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "json-c/json.h"
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

    // saving json objects
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


    /*TCP CONNECTION SERVER SIDE*/

    unsigned int len;
    char buffer[payload2];

    int client_socket, connfd; 
    struct sockaddr_in cliaddr, server; 
  
    // socket create and verification 
    client_socket = socket(AF_INET, SOCK_STREAM, 0); 
    if (client_socket == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
  
    // assign IP, PORT 
    cliaddr.sin_family = AF_INET; // IPv4
    cliaddr.sin_addr.s_addr = inet_addr("192.168.1.17");
    cliaddr.sin_port = htons(destportudp2);  
  
    // Binding newly created socket to given IP 
    if (bind(client_socket, (const struct sockaddr *)&cliaddr,
            sizeof(cliaddr)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
  
    // Server is ready to listen
    if ((listen(client_socket, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server is listening..\n"); 
    len = sizeof(server); 
  
    // Accept the data from client 
    connfd = accept(client_socket, &server, &len); 
    if (connfd < 0) { 
        printf("Server accept failed...\n"); 
        exit(0); 
    } 
    else {
        printf("Server accepted the client.\n"); 
        printf("TCP Connection Successful.\n\n");
    }

    /* UDP SERVER */

    int sockfd;
    struct sockaddr_in servaddr, client;
    
    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&client, 0, sizeof(client));

    //Filling client information
    client.sin_family = AF_INET; // IPv4
    client.sin_addr.s_addr = inet_addr("192.168.1.20");
    client.sin_port = htons(srcportudp2);

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = inet_addr("192.168.1.17");
    servaddr.sin_port = htons(destportudp2);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("UDP Connection Successful.\n");

    int n;
    unsigned int len2;

    len2 = sizeof(client);

    int i;
    for(i=0; i<numudppackets2; i++){
    n = recvfrom(sockfd, (char *)buffer, sizeof(buffer),
                MSG_WAITALL, ( struct sockaddr *) &client,
                &len2);
    }
    printf("Received low entropy packets.\n");
    
    /* END OF LOW ENTROPY */

    // Intermeasurement wait period
    printf("Waiting...\n");
    sleep(intermtime2); // 15 seconds
    printf("Done waiting.\n");

    /* HIGH ENTROPY */
    int m;
    int index;
    for(index=0; index<numudppackets2; index++){
        m = recvfrom(sockfd, (char *)buffer, sizeof(buffer),
                MSG_WAITALL, ( struct sockaddr *) &client,
                &len2);
    }
    printf("Received high entropy packets.\n");
    printf("\nBye.\n");
    
    close(sockfd);
    close(client_socket);

    return 0;
}
