CC = gcc
CFLAGS = -g -Wall -Wextra 
SOURCES = UDPserver_01.c
OBJECTS =  UDPserver_01.o UDPserver_01 
EXECUTABLE = UDPserver_01 
RUN = ./UDPserver_01
ARG= 5150
sh = server/udpsvr.sh

all: $(OBJECTS) 
	
UDPserver_01: UDPserver_01.o ###to get executable file from object file 
	$(CC) -o exe UDPserver_01.o

UDPserver_01.o: UDPserver_01.c
	$(CC) $(CFLAGS) -c -o $@ $< #other version  $(CC) $(CFLAGS) -c $< 


clean:
	rm -f $(EXECUTABLE) *.o



