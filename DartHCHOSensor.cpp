/*
  DartHCHOSensor.cpp - DartHCHOSensor library
  Developed by JZ - 2020/04/04
  (Based on DartHCHOSensor library developed by Jason Ling for Dart Gravity: HCHO Sensor)

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3.0 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  Version 1.0: Apr 4th 2020 by JZ<zijing.zhang@gmail.com>
*/

#include "DartHCHOSensor.h"

DartHCHOSensor::DartHCHOSensor(HardwareSerial* Serial)	//read the uart signal by hardware uart, such as GPIO3
{
    mySerial = Serial;
    receivedFlag = 0;
}

byte DartHCHOSensor::checkSum(byte array[],byte length)	
{
    byte sum = 0;
    for(int i = 1; i < length-1; i ++)
    {
		sum += array[i];
    }
    sum = (~sum) + 1;
    return sum;
}

boolean DartHCHOSensor::available()		//new data was recevied
{
    while(mySerial->available()>0)
    {
		for(byte index = 0; index < MAXLENGTH-1; index++)
		{
			receivedCommandStack[index] = receivedCommandStack[index+1];
		}
		receivedCommandStack[MAXLENGTH-1] = mySerial->read();

		byte sumNum = checkSum(receivedCommandStack, MAXLENGTH);
		if( (receivedCommandStack[0] == 0xFF) && (receivedCommandStack[1] == 0x17) && (receivedCommandStack[2] == 0x04) && (receivedCommandStack[MAXLENGTH-1] == sumNum) )	//head bits and sum are all right
		{
			receivedFlag = 1;			//new data received
			return receivedFlag;
		}else{
			receivedFlag = 0;			//data loss or error
			return receivedFlag;
		}  
    }
    return receivedFlag;
}

float DartHCHOSensor::uartReadPPM()
{
    receivedFlag = 0;
    float ppb = (unsigned int)receivedCommandStack[4]<<8 | receivedCommandStack[5];		// bit 4: ppm high 8-bit; bit 5: ppm low 8-bit
    float ppm = ppb / 1000.0;	//1ppb = 1000ppm
    return ppm;
}
 
