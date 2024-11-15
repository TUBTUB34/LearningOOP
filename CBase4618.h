#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include"conio.h"
#include"CControl.h"


#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

/** CSketch.h
 *
 * @brief A parent class for Pong and Etch a sketch
 *
 * @author Alex Weir
 *
 * @version 0.1 -- Febuary 10, 2023
 */

class CBase4618
{
public:

	bool _thread_exit;
	/**
	* @brief empty constructor
	*
	*/
	CBase4618();

	/**
	* @brief empty constructor
	*
	*/
	~CBase4618();

	/**
	* @brief Control object to comunicate with the microcontroller
	*
	*/
	CControl Control;

	/**
	* @brief Mat object that will be used to draw on in all the labs
	*
	*/
	cv::Mat _canvas;

	/**
	* @brief Method to loop through the draw and Update methods
	*
	* main methode that will be used as the main loop to draw and update the mat object
	* 
	* @return nothing to return
	*/
	void run(void);

	void run_thread();

	/**
	* @brief Virtual methed used with both the pong and etch a sketch
	*
	* Is the methed that gets the updated point from the program. 
	* is used in both the pong and etch a sketch classes
	* 
	* @return nothing to return
	*/
	virtual void update(void) = 0;

	/**
	* @brief Virtual method used to draw on the mat object
	* 
	* @return bool returns true if the exit button is clicked
	*
	*/
	virtual bool draw() = 0;

	bool do_exit;    ///< is only true when the program is to be exited

private:

};

