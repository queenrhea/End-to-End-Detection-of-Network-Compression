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
    
    sendto(sockfd, (const char *)hello, strlen(hello),
        0, (const struct sockaddr *) &servaddr,
            sizeof(servaddr));
    printf("Hello message sent.\n");

    //sendto(sockfd, buffer_p, len, unsigned int flags,
//const struct sockaddr *to, socklen_t tolen);

    if( rc == sendto(sockfd, buffer_p, sizeof(buffer_p),0,(const struct sockaddr *) &servaddr,sizeof(servaddr)) != 0 ) {
			/* buffers aren't available locally at the moment,
			 * try again.
			 */
			// if (errno == ENOBUFS)
			// 	continue;
			perror("sending datagram");
			exit(1);
		}
        
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                MSG_WAITALL, (struct sockaddr *) &servaddr,
                &len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);

    close(sockfd);
    return 0;
}
