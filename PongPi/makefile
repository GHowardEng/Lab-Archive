CC=g++

CFLAGS=-Wall `pkg-config --cflags opencv` -std=c++11 -c

LDFLAGS=-Wall `pkg-config --libs opencv` -o

all: PongPi

PongPi: Lab5.o CPong.o CBase4618.o CControlPi.o 
	$(CC) $(LDFLAGS) PongPi Lab5.o CPong.o CBase4618.o CControlPi.o -lwiringPi -lpigpio -lpthread
	
Lab5.o: Lab5.cpp
	$(CC) $(CFLAGS) Lab5.cpp 

CPong.o: CPong.cpp
	$(CC) $(CFLAGS) CPong.cpp 

CBase4618.o: CBase4618.cpp
	$(CC) $(CFLAGS) CBase4618.cpp 	
	
CControlPi.o: CControlPi.cpp
	$(CC) $(CFLAGS) CControlPi.cpp 
	
clean:
	rm *o PongPi