CC=g++

CFLAGS=-Wall `pkg-config --cflags opencv` -std=c++11 -c

LDFLAGS=-Wall `pkg-config --libs opencv` -o

all: do_video

do_video: do_video.o 
	$(CC) $(LDFLAGS) do_video do_video.o -lwiringPi -lpigpio 
	
do_video.o: do_video.cpp
	$(CC) $(CFLAGS) do_video.cpp  
	
clean:
	rm *o do_video