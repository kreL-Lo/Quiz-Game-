#!/bin/bash
gcc -Wall -I/usr/include/libxml2 -o parse_site querry-site.c -lxml2 -l sqlite3 
gcc get-site.c -lcurl -o get-site # to compile curl
./get-site
./parse_site
