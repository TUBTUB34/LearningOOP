#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


#include <windows.h>
#include"Serial.h"

/** CControl.h
 *
 * A Control class to send and receive data through via a serial port.
 *
 * @author Alex Weir
 *
 * @version 0.1 -- January 20 2023
 */

class CControl {
private:

   int result;                ///< Result of the analog conversion
   bool error;                ///< To detect if the controler has been disconnected
   int pressed;               ///< returns one if the button is pressed
   bool current_state;        ///< the current state of the pushbutton
   bool Previous_state;       ///< the last state of the pushbutton
   bool is_count;             ///< if there is a 20 ms clock counting
   double start_time;         ///< the state of the 20 ms timer

   enum MyEnum                ///< The three ch of the of the microcontroller
   {
      DIGITAL,
      ANALOG,
      SERVO,
   };

   int DPB[3] = { 5,32,33 };  ///< the three different channles of the pushbuttons 

   Serial _com;               ///< Comport data

public:

   /**
   * Empty constructor
   *
   */
   CControl();

   /**
   * Empty destructor
   *
   */
   ~CControl();

   /** Sends and initiates the comport that is to be used by the program.
  *
  */
   void init_com(void);

   /** recives the value from the desired channel.
  *
  * @param type is what type of data you want to receive (Digital, Analog, or Servo)
  * @param Channel is the channel you want the data from
  * @param result is passed by refference and it the rusulting data
  *
  * @return bool returns false if the devices is not communicating properly
  */
   bool get_data(int type, int channel, int& result);

   /** sets the value to the desired channel.
  *
  * @param type is what type of data you want set (Digital or Servo)
  * @param Channel is the channel you want to set
  * @param val is what value you want to set to the channel
  *
  * @return bool returns false if the devices is not communicating properly
  */
   bool set_data(int type, int channel, int val);

   /** gets the Precentage of the total analog channel.
  *
  * @param type is what type of data you want get Analog
  * @param Channel is the channel you want to get
  *
  * @return float returns the percentage
  */
   float get_analog(int channel);

   /** gets a button press with debounce.
   *
   * @param Channel is the channel you want to get
   *
   * @return int returns 1 for a single cycle when the button is pressed
   */
   int get_button(int Channel);

   /** Tests to see if the device is still connected or not.
   *
   * @return bool returns 1 fif the device is disconnected
   */
   bool CControl::test(void);

};