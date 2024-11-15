#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include"conio.h"
#include "CBase4618.h"


#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

/** CSketch.h
 *
 * @brief A class to draw on a mat image. The functionalitly of this class is to make a classic etch-a-sketch
 *
 * this class does all the implementation of an etch a sketch
 * @author Alex Weir
 *
 * @version 0.1 -- Febuary 10, 2023
 */


class CSketch : public CBase4618
{
public:
	/**
	* @brief constructor to initalize the mat object to be drawn on
	* 
	* @param Dim The size of the canvis to draw on
	*
	*/
	CSketch(cv::Size Dim);

	/**
	* @brief destructor - closes all the windows open as well as turning off the leds
	*
	*
	*/
	~CSketch();
	
	/**
	* @brief updates the position of where to draw the point on the mat image.
	* 
	* Uses the joysitc to move the point up or down, left or right.
	* uses the accelerometer to cleaar the sreen. 
	* the pushbutton the change the color of the line.
	* 
	* @return nothing to return
	*
	*/
	void update();

	/**
	* @brief Draws the line on the screen as well as the gui
	* 
	* has a reset button that clears the sceen
	* has a exit button the will close the program
	* 
	* @return nothing to return
	*
	*/
	bool draw();

private:

	cv::Point2f _Check;								///<temporay point used to check the joystick
	cv::Point Position;								///<point used for the first point of the line
   cv::Point Prev_position;						///<point used for the last point of the line
	cv::Scalar line_Color;							///<Color of the line
	std::string WindowName;							///<Name of the display window
	cv::Point gui_position;							///<Start position of the GUI

	std::string Color;								///<For displaying the color of the line in the GUI

	int Button_count;									///<for changing the color 
	float clear;										///<Used to clear the screen if the accerometer is above a threashold
	int accelerometer;								///<Used for clearing the screen
	int Real_colorB;									///<used so the program doesnt keep calling the get_data function
	int Real_colorG;									///<used so the program doesnt keep calling the get_data function
	int Real_colorR;									///<used so the program doesnt keep calling the get_data function
};
