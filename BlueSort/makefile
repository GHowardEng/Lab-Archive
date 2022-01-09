CC=g++

CFLAGS=-Wall `pkg-config --cflags opencv` -std=c++11 -c

LDFLAGS=-Wall `pkg-config --libs opencv` -o

all: Sorting

Sorting: SortMain.o CBase4618.o CControlPi.o CBlueSort.o
	$(CC) $(LDFLAGS) Sorting SortMain.o CBase4618.o CControlPi.o CBlueSort.o -lwiringPi -lpigpio -lpthread -lraspicam -lraspicam_cv
	
SortMain.o: SortMain.cpp
	$(CC) $(CFLAGS) SortMain.cpp

CBase4618.o: CBase4618.cpp
	$(CC) $(CFLAGS) CBase4618.cpp  
	
CControlPi.o: CControlPi.cpp
	$(CC) $(CFLAGS) CControlPi.cpp 

CBlueSort.o: CBlueSort.cpp
	$(CC) $(CFLAGS) CBlueSort.cpp 
	
clean:
	rm *o TestControl