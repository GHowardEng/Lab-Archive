// Lab 4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CSketch.h"

int main()
{
	CSketch sketch("COM3", Size(XSIZE, YSIZE));
	sketch.run();
	
    return 0;
}
