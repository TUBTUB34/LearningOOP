#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <time.h>
#include"conio.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "CBase4618.h"
#include "CGameobject.h"
#include "CAstroid.h"
#include "CMissle.h"
#include "CShip.h"


/**
*
*@brief A class for a game of astroids.
*
*  @author Alex Weir
*
* @version 1. -- Febuary 24, 2023
*
*/
class CAstroidGame : public CBase4618
{
public:
	/**
	* @brief construction of the astroid game
	* 
	* @param dim size of the mat to be used
	*
	*/
	CAstroidGame(cv::Size Dim);

	/**
	* @brief destruction of the astroid game
	*
	*/
	~CAstroidGame();

	/**
	* @brief Updates the game state.
	*
	* @return nothing to return
	*
	*/
	void update();

	/**
	* @brief Draws the game to the screen.
	*
	* @return true if the Game is to be exited.
	*/
	bool draw();

	/**
	* @brief Updates the position of the ship
	*
	* @return nothing to return
	*
	*/
	void Ship_position();

	/**
	* @brief resets the whole game
	*
	* @return nothing to return
	*
	*/
	void reset();

	/**
	* @brief resets the position of the ship
	*
	* @return nothing to return
	*
	*/
	void restart();

	CShip Ship; ///< ship object


private:
	
	int _Click_Fire; ///< fires a missle
	int _Click_Reset; ///< resets the game
	int _Num_of_missle; ///<number of missles
	int _lives; ///< number of lives
	int _Score; ///< score

	bool game_over; ///< if the game is over

	double _Start_Time; ///< start time

	cv::Size _Canvis_size; ///< size of the board
	cv::Point2f Temp_ship; ///< temporary ship location
	cv::Point2f Temp_Missle; ///< temp missile location
	cv::Point _Check; ///< checks the analog input
	std::string WindowName; ///< name of the window
	cv::Point gui_position; ///< gui start position

	cv::Scalar _Ship_color; ///< color of the ship
	cv::Scalar _Astroid_color; ///< color of the astroids
	cv::Scalar _Missle_color; ///< color of the missles

	std::vector<CAstroid> Astroides; ///<vactor of astroids
	std::vector<CMissle> Missles; ///< vecrtor of missles

};
