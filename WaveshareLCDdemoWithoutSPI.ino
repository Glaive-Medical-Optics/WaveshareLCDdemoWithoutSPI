/*****************************************************************************
* | File        : WaveshareLCDdemoWithoutSPI
* | Author      : Glaive software team
*----------------
* | This version:   V1.1
* | Date        :   19-July-2024
******************************************************************************/

/*
 *    This is a demo program that shows how to display moving images on 
 *    a Waveshare LCD display attached to an Arduino Giga R1 board
 *    without using the SPI interface.
 *    
 *    This sketch displays a stylized "G" that moves around
 *    on the Waveshare LCD module without using the SPI interface.
 *    
 *    The pin connections must be set up as follows:
 *    
 *    LCD pin     wire color    Arduino pin
 *    -------     ----------    -----------
 *    VCC         purple        5V            required
 *    GND         white         GND           required
 *    DIN         green         D2            optional
 *    CLK         orange        D3            optional
 *    CS          yellow        D10           optional
 *    DC          blue          D7            optional
 *    RST         brown         D8            optional
 *    BL          gray          D9            optional
 *    
 *    This demo is set up to use pins D2, D3, D7, D8, D9, and D10 as shown in the table above.
 *    You can replace these pins by any digital pins.
 *    To do that, specify the pins you are using in the file DEV_Config.h.
 *    
 *    This program is Free Software and has ABSOLUTELY NO WARRANTY.
 */


#include "LCD_Driver.h"

void setup()
{

  Serial.begin(9600);   // for print debugging
  delay(4000);          //delay 4 seconds to give the serial port enough time to initialize
  Serial.print("\nStarting...\n");

  Config_Init();
  Serial.print("Config succeeded.\n");

  LCD_Init();
  Serial.print("LCD_Init succeeded.\n");

  quickMoveG();
  
  Serial.print("exiting setup.\n");

}

void loop()
{

}
