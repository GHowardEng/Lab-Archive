CC=g++

CFLAGS=-Wall `pkg-config --cflags opencv` -std=c++11 -c

LDFLAGS=-Wall `pkg-config --libs opencv` -o

all: Sockets

Sockets: Sockets.o server.o CBase4618.o CControlPi.o CBlueSort.o
	$(CC) $(LDFLAGS) Sockets Sockets.o server.o CBase4618.o CControlPi.o CBlueSort.o -lwiringPi -lpigpio -lpthread -lraspicam -lraspicam_cv
	
Sockets.o: Sockets.cpp
	$(CC) $(CFLAGS) Sockets.cpp 

server.o: server.cpp
	$(CC) $(CFLAGS) server.cpp 

CBase4618.o: CBase4618.cpp
	$(CC) $(CFLAGS) CBase4618.cpp  
	
CControlPi.o: CControlPi.cpp
	$(CC) $(CFLAGS) CControlPi.cpp 

CBlueSort.o: CBlueSort.cpp
	$(CC) $(CFLAGS) CBlueSort.cpp 