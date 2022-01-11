#pragma once

#include "stdafx.h"
#include "CBase4618.h"

/** @brief Enum for drawing colours, holds pin numbers for RGB LED's
*
*/
enum Colours{BLUE = 37, GREEN, RED};


/**
*
* @brief Allows ananlog inputs to be used to 'sketch' on a canvas.
*
*
* This class inherits from the CBase4618 class and overloads functions to implement an 'Etch-A-Sketch' game.
*
*
* @author Grant Howard
*
*/
class CSketch : public CBase4618
{
private:
	int _colourState = BLUE;
	int _reset;
	int time = GetTickCount();

	Point NewPoint = Point(XSIZE / 2, YSIZE / 2);
	Point LastPoint;

public:
	/** @brief Constructor to initiallize comport and size of canvas.
	*
	* @param comport The desired port to be used ("COMx")
	* @param Mat_size Dimensions of canvas (width, height)
	* 
	*
	* @return No return value
	*
	*/
	CSketch(std::string comport, Size Mat_size);

	/** @brief Reads joystick inputs and updates point coordinates.
	*
	* @return No return value
	*
	*/
	void update();

	/** @brief Uses updated point to draw connecting lines and displays image.
	*
	* @return No return value
	*
	*/
	void draw();

	/** @brief Runs program by calling update() and draw() in a loop. Exits on 'q' keypress.
	*
	* @return No return value
	*
	*/
	void run();
};