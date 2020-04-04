/***************************************************
 This example reads the concentration of HCHO in air via hardware UART interface.
 
 Modified by JZ<zijing.zhang@gmail.com> - Apr 4th, 2020
 (Based on DFRobotHCHOSensor library developed by Jason Ling for DFRobot Gravity: HCHO Sensor
 Version 1.0: 15 Dec 2016 by Jason<jason.ling@dfrobot.com@dfrobot.com>)
 
 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution
 ****************************************************/
 
 /***********Notice and Trouble shooting***************
 1. This code is tested on ESP8266/ESP32 with Arduino IDE 1.8.12.
 2. In order to protect the sensor, do not touch the white sensor film on the sensor module. 
 Also high concentration of hydrogen sulfide, hydrogen, methanol, ethanol, carbon monoxide should be avoided. 
 3. Please do not use the sensors in systems which may impair human being’s safety.
 ****************************************************/

#include <DartHCHOSensor.h>

DartHCHOSensor hchoSensor;

void setup()
    Serial.begin(9600);
}

void loop()
{
    if(hchoSensor.available()>0)	
    {
      Serial.print(hchoSensor.uartReadPPM());
      Serial.println("ppm");
    }
}
