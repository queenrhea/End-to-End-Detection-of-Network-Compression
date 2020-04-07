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

int main() {
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;
    
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    
    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    
    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    int len, n;

    len = sizeof(cliaddr); //len is value/resuslt

    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    sendto(sockfd, (const char *)hello, strlen(hello),
        0, (const struct sockaddr *) &cliaddr,
            len);
    printf("Hello message sent.\n");


    int confd = 0;

    FILE* fp = fopen("myconfig.json", "r"); 
    confd = accept(sockfd, (struct sockaddr*)NULL, NULL);

    int total=0, b = 0;

    // if(fp != NULL){ 
    //     printf("hewllo1");
    //     while((b = recv(confd, buffer, 1024,0))> 0 ) { 
    //         printf("hewllo2");
    //         total += b; 
    //        //fwrite(buffer, 1, b, fp); 
    //         read(sockfd, buffer, 100);
    //         printf("hewllo3");
    //         fprintf(fp, "%s", buffer);
    //         printf("hewllofinal");
    //     }
    // }

    if(fp != NULL){ 
        printf("hello1");
        while((b=recvfrom(confd, buffer, MAXLINE,
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len)>0)) { 
            printf("hello2");
            total += b; 
           //fwrite(buffer, 1, b, fp); 
            read(sockfd, buffer, 100);
            printf("hello3");
            fprintf(fp, "%s", buffer);
            printf("hellofinal");
        }
    }
       
       else {
        perror("File not found");
    }

    printf("Received bytes: %d\n",total); 

    if (b<0) {
        perror(" ");
        fclose(fp);
    }

    else {
        perror("File");
    }
    close(confd);
    
    fclose(fp); 
    
    return 0;
}
