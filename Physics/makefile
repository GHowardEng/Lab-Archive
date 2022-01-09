CC=g++

CFLAGS=-Wall `pkg-config --cflags opencv` -std=c++11 -c

LDFLAGS=-Wall `pkg-config --libs opencv` -o

all: Physics

Physics: Physics.o CControlPi.o 
	$(CC) $(LDFLAGS) Physics Physics.o CControlPi.o -lwiringPi -lpigpio
	
Physics.o: Physics.cpp
	$(CC) $(CFLAGS) Physics.cpp 
	
CControlPi.o: CControlPi.cpp
	$(CC) $(CFLAGS) CControlPi.cpp 
	
clean:
	rm *o Physics