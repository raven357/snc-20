#!/bin/bash

if [ "$0" = "server/udpsrv.sh" ];then 
    gcc -o UDPserver_01 server/UDPserver_01.c -Wall
else
    gcc -o UDPserver_01 UDPserver_01.c -Wall
fi



