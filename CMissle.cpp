#include "stdafx.h"
#include "CMissle.h"

CMissle::CMissle(cv::Point pos)
{
   _lives = 1;
   _radius = 2;
   _velocity = cv::Point (0,30);
   _Position = pos;
}

CMissle::~CMissle()
{
}