# End-to-End-Detection-of-Network-Compression
By: Rhea Arora and Angie Preciado

# Introduction

Implemented network compression detection in a client/server application. The purpose of the project is to implement the end-to-end approach which is used to detect compression to save end-host resources by not compressing more data at the intermediate nodes.

# Requirements

This project uses json-c library for parsing the configuration file.

To install json-c, run this command on the the terminal: 

    sudo apt install libjson-c-dev

And follow the instructions here: https://github.com/json-c/json-c/blob/master/README.md#buildunix

# Instructions for compiling and running

TO COMPILE PROGRAMS:

    For client: gcc compdetect_client.c -ljson-c
    
    For server: gcc compdetect_server.c -ljson-c
    
    For standalone: gcc standalone.c -ljson-c
    
TO RUN PROGRAMS: 
    
    ./a.out myconfig.json

*Run the server first before running the client on two separate vms.*
