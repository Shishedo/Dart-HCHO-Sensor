/*
  DartHCHOSensor.h - DartHCHOSensor library
  Modified by JZ<zijing.zhang@gmail.com> - Apr 4th, 2020
  (Based on DFRobotHCHOSensor library developed by Jason Ling for DFRobot Gravity: HCHO Sensor
  Version 1.0: 15 Dec 2016 by Jason<jason.ling@dfrobot.com@dfrobot.com>)
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3.0 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
*/


#ifndef __DartHCHOSensor_H_
#define __DartHCHOSensor_H_

#include <arduino.h>

#define MAXLENGTH  9

class DartHCHOSensor
{
  public:
  DartHCHOSensor(HardwareSerial* Serial);	//read the uart signal by hardware uart,such as GPIO3

  boolean available();		//new data was recevied
  float uartReadPPM();		//get the concentration(ppm) by uart signal

  private:
  Stream *mySerial;
  byte receivedCommandStack[MAXLENGTH];
  byte checkSum(byte array[],byte length);
  boolean receivedFlag;
  byte _sensorPin;
};

#endif
