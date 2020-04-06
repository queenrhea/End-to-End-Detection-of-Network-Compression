#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 9876
#define MAXLINE 1025

void main() {
    int server_socket, new_socket;
    int confd = 0;
    struct sockaddr_in servaddr, new_servaddr;

    //char *hello = "Hello from server";

    socklen_t addr_size;
    char buffer[MAXLINE];



    // Creating socket file descriptor
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    printf("Server Socket Created Successfully\n");

    memset(&servaddr, 0, sizeof(servaddr));

    //Server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");


    //Bind the socket with the server address
    if (bind(server_socket, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Bind to Port Number %d\n", 9876);

    //Put the server socket in a passive mode, where it waits for the client to approach //the server to make a connection
    listen(server_socket, 5);
    printf("Listening...\n");

    addr_size = sizeof(new_servaddr);

    //Connection is established between client and server, and they are ready to transfer data
    new_socket = accept(server_socket, (struct sockaddr*)&servaddr, sizeof(servaddr));

    strcpy(buffer, "Hello\n");

    send(new_socket, buffer, strlen(buffer), 0);

    // recv(server_socket, buffer, MAXLINE, 0);
    
    // printf("Client: %s\n", buffer);

    // sendto(new_socket, (const char *)hello, strlen(hello), 0, (const struct sockaddr *) &new_servaddr, sizeof(new_servaddr));

    //printf("Hello message sent.\n");

   
    //FILE* fp = fopen("myconfig.json", "r"); 
    //confd = accept(server_socket, (struct sockaddr*)NULL, NULL);

    //total=0; 
    
    //if(fp != NULL){ 
     //   while((b = recv(confd, buffer, 1024,0))> 0 ) { 
     //       total += b; 
     //       fwrite(buffer, 1, b, fp); 
    //         read(new_socket, buffer, 255);
    //         fprintf(fp, "%s", buffer);
   // } 
   // else {
     //   perror("File not found");
   // }
    
   // printf("Received bytes: %d\n",total); 
    
    //fclose(fp); 
   
    //close(server_socket);
    //return 0;
}
