#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <time.h>
#include"conio.h"
#include "CBase4618.h"
#include <stdlib.h>

class CBall 
{
public:
   enum { STOP = 0, UpRight = 1, Right = 2, DownRight = 3, DownLeft = 4, Left = 5, UpLeft = 6 };

   CBall();
   ~CBall();

   void reset(void);
   cv::Point GetPos(void) { return _position; }
   int GetDirection(void) { return direction; }
   void move(int speed);
   int rand_dir(void);
   void changeDir(int newDir) { direction = newDir; }

private:
   cv::Point _pos;
   cv::Point _position;
   int direction;

};

