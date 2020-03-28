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
