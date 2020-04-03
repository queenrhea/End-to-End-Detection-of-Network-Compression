#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 22
#define MAXLINE 1025

int main() {
    int server_socket, new_socket;
    struct sockaddr_in servaddr, new_servaddr;

    char *hello = "Hello from server";

    socklen_t addr_size;
    char buffer[MAXLINE];



    // Creating socket file descriptor
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

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

    //Put the server socket in a passive mode, where it waits for the client to approach //the server to make a connection
    listen(server_socket, 1);
    addr_size = sizeof(new_servaddr);

    //Connection is established between client and server, and they are ready to transfer data
    new_socket = accept(server_socket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    send(new_socket, buffer, strlen(buffer), 0);

    recvfrom(server_socket, buffer, MAXLINE, 0);
    
    printf("Client : %s\n", buffer);

    sendto(new_socket, (const char *)hello, strlen(hello), 0, (const struct sockaddr *) &new_servaddr, sizeof(new_servaddr));

    printf("Hello message sent.\n");

   

    
    //FILE* fp = fopen("myconfig.json", "w"); 

    //total=0; 
    
    //if(fp != NULL){ 
     //   while((b = recv(, buffer, 1024,0))> 0 ) { 
     //       total += b; 
     //       fwrite(buffer, 1, b, fp); 
   // } 
   // else {
     //   perror("File not found");
   // }
    
   // printf("Received bytes: %d\n",total); 
    
    //fclose(fp); 
   
    close(server_socket);
    return 0;
}
