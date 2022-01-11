#pragma once

#include "stdafx.h"
#include "CControl.h"

/**
*
* @brief Acts as a base class for further projects.
*
*
* This class is meant to be used as a base class for graphics related projects. Empty functions are to be overloaded into a derived class for further development.
*
*
* @author Grant Howard
*
*/
class CBase4618
{
public:
	CControl controller;	///< CControl object to interface with microcontroller
	Mat _canvas;		///< Mat image to be drawn on
	
	/** @brief Will read inputs and update locations once implemented.
	*
	* @return No return value
	*
	*/
	void update();

	/** @brief Will display updated image once implemented.
	*
	* @return No return value
	*
	*/
	void draw();

	/** @brief Runs program by calling update() and draw() in a loop.
	*
	* @return No return value
	*
	*/
	void run();
};