// Lab 5.cpp : Defines the entry point for the console application.
//

#include "CPong.hpp"


int main()
{
	CPong mypong("COM3", Size (XSIZE, YSIZE));

	mypong.run();

    return 0;
}
