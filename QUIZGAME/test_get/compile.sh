#!/bin/bash
gcc -Wall -I/usr/include/libxml2 -o parse_site $1.c -lxml2 # to compile the libxml 
gcc test.c -lcurl -o get_site # to compile curl