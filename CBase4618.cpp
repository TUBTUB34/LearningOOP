
#include "stdafx.h"
#include "CControl.h"
#include "CSketch.h"
#include "CBase4618.h"
#include "CPong.h"


CBase4618::CBase4618()
{
   _thread_exit = false;
}

CBase4618::~CBase4618()
{

}


void CBase4618::run_thread()
{
   do_exit = false;

   std::thread t1(&CPong::update_thread, this);
   std::thread t2(&CPong::draw_thread, this);
   t1.detach();
   t2.detach();
   while ('q' != cv::waitKey(1) && do_exit == false);

   Sleep(1000);
   
   return;
}

void CBase4618::run()
{
   do_exit = false;

   do
   {
      update();
      do_exit = draw();
      }while ('q' != cv::waitKey(1) && do_exit == false);

   return;
}
