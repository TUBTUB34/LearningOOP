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
#include "CControl.h"


/**
*
*  @brief A class that is used in a basic astroid game.
*
*  @author Alex Weir
*
* @version 1. -- Febuary 24, 2023
*
*/

class CGameObject 
{
protected:
   cv::Point2f _Position; ///< Position on screen
   cv::Point2f _velocity; ///< velocity of object
   int _radius; ///< Radius of object
   int _lives; ///< number of lives
public:

   /**
   *
   * @brief For moving the individual objects.
   *
   * @return nothing to return
   */
   void move();

   /**
   *
   * @brief For detecting if collision has occured
   *
   * @return true if there is collison
   */
   bool collide(CGameObject& obj); 

   /**
   *
   * @brief For detecting if the ship or astroid has hit the wall
   *
   * @return true if there is collison
   */
   bool collide_wall(cv::Size board);

   /**
   *
   * @brief For detecting and keep track of missle hitting the astroid
   *
   * @param board The dimiensions of the screen
   * 
   * @return true if there is collison
   */
   void hit();

   /**
   *
   * @brief returns the amount of lives
   *
   * @return amount of lives
   */
   int get_lives() { return _lives; }

   /**
   *
   * @brief returns the radius of object
   *  
   * @return radius of object
   */
   int get_radius() { return _radius; }

   /**
   *
   * @brief returns the score
   *
   * @return the score
   */
   int get_score() { return _Score; }

   /**
   *
   * @brief sets the score
   *
   * @param score the socore that is to be set
   * 
   * @return nothing to return 
   */
   void set_score(int score) { _Score = score; }

   /**
   *
   * @brief sets the amount of lives
   *
   * @param lives the amount of lives
   *
   * @return nothing to return
   */
   void set_lives(int lives) { _lives = lives; }

   /**
   *
   * @brief sets the position
   *
   * @param pos the position that is to be set
   *
   * @return nothing to return
   */
   void set_pos(cv::Point2f pos) { _Position = pos; }

   /**
   *
   * @brief gets the current possition of the object
   *
   * @return returns the positon 
   */
   cv::Point2f get_pos() { return _Position; }

   /**
   *
   * @brief draw the object on the screen
   *
   * @param in the canvas to be drawn on
   * 
   * @param color color of the object ot be drawn
   *
   * @return nothing to return
   */
   void draw(cv::Mat& im, cv::Scalar color);

private:
   int _Score = 0; ///< Player score

};
