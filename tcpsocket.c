//
//  tcpsocket.c
//  client-angie
//
//  Created by Angie Preciado on 3/27/20.
//  Copyright © 2020 Angie Preciado. All rights reserved.
//

//just creates a tcp socket and prints out if it was successful
#include <stdio.h>
#include <sys/socket.h>

int main(int argc , char *argv[])
{
    int tcpsocket;
    tcpsocket = socket(AF_INET , SOCK_STREAM , 0);
    
    if (tcpsocket == -1)
    {
        printf("Could not create socket\n");
    }
    else
    {
        printf("Socket successfully created\n");
    }
    return 0;
}

//-----------------------------------------------

//Socket creation

int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
//ip4 domain, UDP communication type, protocol IP 0

//Setsockopt(): helps in reuse of address and port; prevents error such as "address already in use"
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);

// Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 


address.sin_family = AF_INET; 
address.sin_addr.s_addr = INADDR_ANY; 
address.sin_port = htons( PORT );


// IPv4 AF_INET sockets:
struct sockaddr_in {
    short            sin_family;   // e.g. AF_INET, AF_INET6
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
};

struct in_addr {
    unsigned long s_addr;          // load with inet_pton()
};

struct sockaddr {
    unsigned short    sa_family;    // address family, AF_xxx
    char              sa_data[14];  // 14 bytes of protocol address
};

//Bind function: Bind socket(node) to address and port #
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

// Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    }

//Arguments:
// sockfd – File descriptor of socket to be binded
// addr – Structure in which address to be binded to is specified
// addrlen – Size of addr structure


//BUFFER for sendto() and recvfrom()
char buffer[MAXLINE]; 

ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
               const struct sockaddr *dest_addr, socklen_t addrlen)
//Send a message on the socket

//Arguments:
// sockfd – File descriptor of socket
// buf – Application buffer containing the data to be sent
// len – Size of buf application buffer
// flags – Bitwise OR of flags to modify socket behaviour
// dest_addr – Structure containing address of destination
// addrlen – Size of dest_addr structure

buffer[n] = '\0'; 
    printf("Client : %s\n", buffer); 
    sendto(sockfd, (const char *)hello, strlen(hello),  
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
            len); 
    printf("Hello message sent.\n");  


//recvfrom()
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                 struct sockaddr *src_addr, socklen_t *addrlen)
//Receive a message from the socket.

//Arguments:
// sockfd – (same as sendto())
// buf – (same as sendto())
// len – (same as sendto())
// flags – Bitwise OR of flags to modify socket behaviour
// src_addr – Structure containing source address is returned
// addrlen – Variable in which size of src_addr structure is returned

n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                &len);

                //this line comes before sendto() and before buffer[n] = '\0'
