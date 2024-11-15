#pragma once
#include "CGameobject.h"


/**
*
*@brief A class of an missle.
*
*  @author Alex Weir
*
* @version 1. -- Febuary 24, 2023
*
*/
class CMissle : public CGameObject
{
public:
   /**
	* @brief Construct a new missle
	*
	* @param pos the point where the missle is to start
	*/
	CMissle(cv::Point pos);

	/**
	* @brief destruction of a missle
	*
	*/
	~CMissle();

private:

};
