#pragma once
#include "stdafx.h"

/**
*
* @brief A base class for creating a game object.
*
*
* This class is meant to allow simple creation, tracking and control of an object in a video game.
*
*
* @author Grant Howard
*
*/
class CGameObject
{
protected:
	Point2f _position;
	Point2f _velocity;
	Scalar _colour;

	int _radius;
	int _lives;

public:
	/** @brief Function to update the position of the object.
	*
	* @param pos The new position coordinates for the object.
	*
	* @return No return value.
	*
	*/
	void move(Point2f pos);

	/** @brief Tests for collisions with other game objects.
	*
	* @param &obj The external object to test against.
	*
	* @return Returns true if collision detected, otherwise returns false.
	*
	*/
	bool collide(CGameObject &obj);

	/** @brief Tests for collisions with walls of game window.
	*
	* @param &obj The external object to test against.
	*
	* @return Returns true if collision detected, otherwise returns false.
	*
	*/
	bool collide_wall(Size mat);

	/** @brief Decrements object life count.
	*
	* @return No return value.
	*
	*/
	void hit();

	/** @brief Getter for object lives.
	*
	* @return Returns the number of lives remaining as an int.
	*
	*/
	int get_lives() { return _lives; }

	/** @brief Setter for object lives.
	*
	* @param lives The value to be set.
	*
	* @return No return value.
	*
	*/
	void set_lives(int lives) { _lives = lives; }

	/** @brief Getter for current object position.
	*
	*
	* @return Returns position as a cv::Point2f.
	*
	*/
	Point2f get_pos() { return _position; }

	/** @brief Setter for object radius.
	*
	* @param rad The value to be set.
	*
	* @return No return value.
	*
	*/
	void set_rad(int rad) {_radius = rad;}

	/** @brief Getter for object radius.
	*
	* @return Returns object radius as an int.
	*
	*/
	int get_rad() { return _radius; }

	/** @brief Setter for object colour.
	*
	* @param colour The Scalar colour value to be set.
	*
	* @return No return value.
	*
	*/
	void set_colour(Scalar colour) { _colour = colour; }

	/** @brief Setter for object velocity.
	*
	* @param vel The value to be set.
	*
	* @return No return value.
	*
	*/
	void set_vel(Point2f vel) { _velocity = vel; }

	/** @brief Get for current object velocity.
	*
	* @return Returns velocity as a cv::Point2f.
	*
	*/
	Point2f get_vel() { return _velocity; }

	/** @brief Function to draw object on game image.
	*
	* @param &im The Mat image to be drawn on.
	*
	* @return No return value.
	*
	*/
	void draw(Mat &im);
};