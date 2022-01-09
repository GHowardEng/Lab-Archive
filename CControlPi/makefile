CC=g++

CFLAGS=-Wall `pkg-config --cflags opencv` -std=c++11 -c

LDFLAGS=-Wall `pkg-config --libs opencv` -o

all: TestControl

TestControl: TestMain.o CControlPi.o 
	$(CC) $(LDFLAGS) TestControl TestMain.o CControlPi.o -lwiringPi -lpigpio 
	
TestMain.o: TestMain.cpp
	$(CC) $(CFLAGS) TestMain.cpp 
	
CControlPi.o: CControlPi.cpp
	$(CC) $(CFLAGS) CControlPi.cpp 
	
clean:
	rm *o TestControl