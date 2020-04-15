//
//  testconfig.c
//  client-angie
//
//  Created by Angie Preciado on 4/6/20.
//  Copyright © 2020 Angie Preciado. All rights reserved.
//

#include <stdio.h>
#include "json-c/json.h"

int main(int argc, char **argv){

    char buffer[1024];
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
    
    /*fp = fopen("myconfig.json", "r");
    fread(buffer, 1024, 1, fp);
    fclose(fp);*/

    char *filename;
    FILE *fp;

    if (argc >= 2){
        filename = argv[1];
        printf("File name: %s\n", filename);
        fp = fopen(argv[1], "r");
        fread(buffer, 1024, 1, fp);
        fclose(fp);
    }
    else {
        perror("fopen");
    }
    
    parsed_json = json_tokener_parse(buffer);

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
    printf("Server IP: %s\n",serverip2);

    int srcportudp2 = json_object_get_int(srcportudp);
    printf("Source Port UDP: %d\n", srcportudp2);

    int destportudp2 = json_object_get_int(destportudp);
    printf("Destination Port UDP: %d\n", destportudp2);

    char *destporttcphead2 = json_object_get_string(destporttcphead);
    printf("Destination Port TCP Head: %s\n",destporttcphead2);

    char *destporttcptail2 = json_object_get_string(destporttcptail);
    printf("Destination Port TCP Tail: %s\n",destporttcptail2);

    char *portnumtcp2 = json_object_get_string(portnumtcp);
    printf("Port Number TCP: %s\n",portnumtcp2);

    int payload2 = json_object_get_int(payload);
    printf("Payload: %d\n", payload2);

    int intermtime2 = json_object_get_int(intermtime);
    printf("Inter-Measurement Time: %d\n", intermtime2);

    int numudppackets2 = json_object_get_int(numudppackets);
    printf("The Number of UDP Packets in the UDP Pakcet Train: %d\n", numudppackets2);

    int ttl2 = json_object_get_int(ttl);
    printf("TTL for the UDP Packets: %d\n", ttl2);

}

