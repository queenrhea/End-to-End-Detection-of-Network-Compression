
#include<stdio.h> //For standard things
#include<stdlib.h>    //malloc
#include<string.h>    //memset
#include<netinet/ip_icmp.h>   //Provides declarations for icmp header
#include<netinet/udp.h>   //Provides declarations for udp header
#include<netinet/tcp.h>   //Provides declarations for tcp header
#include<netinet/ip.h>    //Provides declarations for ip header
#include<sys/socket.h>
#include<arpa/inet.h>
#define PORT 6343


void print_udp_packet(unsigned char*, int);
void ProcessPacket(unsigned char*, int);
void PrintData (unsigned char* , int);

int sockt;
int i,j;

struct sockaddr_in source,dest; 

int main()
{
    int saddr_size,data_size;
    struct sockaddr_in saddr;
    struct sockaddr_in daddr;

    //struct in_addr in;
    unsigned char *buffer = (unsigned char *)malloc(65536); // Its Big ! Malloc allocates a block of size bytes of memory,returning a pointer to the begining of the block

    struct udphdr *udph = (struct udphdr*)(buffer + sizeof(struct iphdr));
    struct iphdr *iph = (struct iphdr *)buffer;
    memset(&source,0,sizeof(source));
    source.sin_addr.s_addr = iph ->saddr;
    memset(&dest,0,sizeof(dest));
    dest.sin_addr.s_addr = iph->daddr;
    unsigned short iphdrlen = iph->ihl*4;


    printf("Starting...\n");
    //Create a socket
    sockt = socket(AF_INET ,SOCK_DGRAM ,0);
    if(sockt < 0)
    {
        printf("Socket Error\n");
        return 1;
    }
    memset((char *)&daddr,0,sizeof(daddr));

    //prepare the sockaddr_in structure
    daddr.sin_family = AF_INET;
    daddr.sin_addr.s_addr = htonl(INADDR_ANY);
    daddr.sin_port = htons(PORT);

    //Bind
    if(bind(sockt,(struct sockaddr *)&daddr, sizeof(daddr))<0)
    {
      printf("bind failed");
      return 1;
    }
    printf("bind done");

    while(1)
    {
    saddr_size = sizeof saddr;
    printf("waiting for data...");

    //Receive a packet
    data_size = recvfrom(sockt , buffer ,65536 , 0 , (struct sockaddr*) &saddr , (socklen_t*)&saddr_size);
    if(data_size <0)
    {
      printf("Packets not recieved \n");
      return 1;
    }

    printf("Packets arrived from %d \n",ntohs(daddr.sin_port));
    printf("\t Source Port : %d , Destination Port : %d, UDP Length : %d,Protocol : %d, total length : %d \n", ntohs(udph->source), ntohs(udph->dest), ntohs(data_size), (unsigned int)iph->protocol, ntohs(iph->tot_len)); 
    ProcessPacket(buffer,data_size);
    }
    close(sockt);
    printf("Finished");
    return 0;
}

void ProcessPacket(unsigned char* buffer, int size)
{

    print_udp_packet(buffer ,size);

}

void print_udp_packet(unsigned char *buffer , int size)
{

    unsigned short iphdrlen;

    struct iphdr *iph = (struct iphdr *)buffer;
    iphdrlen = iph->ihl*4;

    struct udphdr *udph = (struct udphdr*)(buffer + iphdrlen);

    printf("Data Payload\n");  
    PrintData(buffer + iphdrlen + sizeof udph ,( size - sizeof udph - iph->ihl * 4 ));

    printf("\n");
}

void PrintData (unsigned char* data , int size)
{

    for(i=0 ; i < size ; i++)
    {
        if( i!=0 && i%16==0)   //if one line of hex printing is complete...
        {
            printf("         ");
            for(j=i-16 ; j<i ; j++)
            {
                if(data[j]>=32 && data[j]<=128)
                    printf("%c",(unsigned char)data[j]); //if its a number or alphabet

                else printf("."); //otherwise print a dot
            }
            printf("\n");
        } 

        if(i%16==0) printf("   ");
            printf(" %02X",(unsigned int)data[i]);

        if( i==size-1)  //print the last spaces
        {
            for(j=0;j<15-i%16;j++) printf("   "); //extra spaces

            printf("   ");

            for(j=i-i%16 ; j<=i ; j++)
            {
                if(data[j]>=32 && data[j]<=128) printf("%c",(unsigned char)data[j]);
                else printf(".");
            }
            printf("\n");
        }
    }
}
