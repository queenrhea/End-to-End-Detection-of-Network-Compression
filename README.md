# End-to-End-Detection-of-Network-Compression
Project Description: Implemented two network applications to detect whether network compression is present and locate the compression link on the network path. One application is a client/server application and the other application is a standalone application which works in an uncooperative environment. 

# Instructions for compiling and running

Uses json-c library for parsing the configuration file.

To install json-c, run this command on the the terminal: sudo apt install libjson-c-dev

And follow the instructions here: https://github.com/json-c/json-c/blob/master/README.md#buildunix

TO COMPILE PROGRAMS:

    For client: gcc compdetect_client.c -ljson-c
    
    For server: gcc compdetect_server.c -ljson-c
    
TO RUN PROGRAMS: 
    
    ./a.out myconfig.json

*Run the server first before running the client on two separate vms.*
