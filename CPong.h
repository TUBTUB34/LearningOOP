#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <time.h>
#include"conio.h"
#include "CBase4618.h"
#include "CBall.h"
#include "CPaddle.h"


#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


/**
*
*@brief A class that represents a basic Pong game.
* 
*  @author Alex Weir
*
* @version 1. -- Febuary 24, 2023
* 
*/
class CPong : public CBase4618
{
public:

   /**
   * @brief An enum representing the different directions the ball can move.
   *
   */
   enum { STOP = 0, UpRight = 1, Right = 2, DownRight = 3, DownLeft = 4, Left = 5, UpLeft = 6 };

   /**
   * @brief Construct a new Pong Game
   *
   */
   CPong();

   /**
   * @brief Destroy the CPong object
   *
   */
   ~CPong();

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

   bool _thread_exit; ///< A flag that indicates whether the threads should exit. 

   /**
   * @brief The update thread function.
   *
   * @param ptr A pointer to a CBase4618 object.
   */
   static void update_thread(CBase4618* ptr);

   /**
   * @brief The draw thread function.
   *
   * @param ptr A pointer to a CBase4618 object.
   * 
   * @return nothing to return
   */
   static void draw_thread(CBase4618* ptr);

   /**
   * @brief Resets the paddle possition without clearing the scores.
   * 
   * @return nothing to return
   *
   */
   void SoftReset(void);

   /**
   * @brief Resets the game and clears the scores.
   * 
   * @return nothing to return
   *
   */
   void Reset(void);
   
   CBall Ball; ///< The Ball object for the game
   
private:

   cv::Point PPaddle; ///< Player paddle position
   cv::Point CPaddle; ///< Computer paddle position
   cv::Point ball; ///< Ball Position
   cv::Point gui_position; ///< Gui Position
   cv::Size _Dim; ///< Dimension of the window
   std::string WindowName; ///< Name of the widow
   std::string Winner; ///< Winner of the game
   cv::Scalar _BallColor; ///< Color of the ball

   int _Size;  ///< Size of the ball
   int _Speed; ///< Speed of the ball
   int _Click_Reset1; ///< Button press to reset the game

   int _width; ///< width of the window
   int _height; ///< Height of the window
   int _direction; ///< direction of the ball

   int _Player_paddle_variable; ///<temp value for the player paddle
   int _Player_Score; ///< Player score
   int _Cmp_Score; ///< Computer score
   int _BallSlider; ///< For the ball size slider
   int _SpeedSlider; ///< For the ball speed slider

   int _FPS; ///< First FPS
   int _FPS2; ///< Second FPS
   int _FPS3; ///< Third FPS

   int _FPS_AVE; ///< Average of the three fps's

   double start_tic; ///< Star time for the clock
   double freq; ///< Freqency of the clock
   double elapsed_time; ///<time for function to run

   /**
   *
   *@brief Updates the position of the ball.
   * 
   * @return nothing to return
   */
   void UpdateBall(void);

   /**
   *
   *@brief Updates the position of the paddle
   * 
   * @return nothing to return
   */
   void UpdatePaddle(void);

   /**
   *
   *@brief Updates the position of the ball.
   * 
   * @return nothing to return
   */
   void UpdateScore(void);

   bool game_over; ///< when the score reaches 5

};

