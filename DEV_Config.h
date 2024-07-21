/*****************************************************************************
* | File        :   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master 
*                and enhance portability
*----------------
* | This version:   V1.0
* | Date        :   2018-11-22
* | Info        :
* 
*    This program is Free Software and has ABSOLUTELY NO WARRANTY.
*
******************************************************************************/
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

#include <Arduino.h>
#include <stdint.h>
#include <stdio.h>

#define DISPLAY_CLK_PIN D3    // Display CLK -- orange wire
#define DISPLAY_DIN_PIN D2    // Display DIN -- green wire
#define DISPLAY_CMD_PIN D7    // Display DC  -- blue wire
#define DISPLAY_CS_PIN  D10   // Display CS  -- yellow wire, can also hook to ground
#define DEV_CS_PIN  D10       // yellow wire
#define DEV_DC_PIN  D7        // blue wire
#define DEV_RST_PIN D8        // brown wire
#define DEV_BL_PIN  D9        // gray wire (back light)

void pinSetup();

  
#define DEV_DATA_WRITE(_dat)   dataTransfer(_dat)


/*-----------------------------------------------------------------------------*/
 void Config_Init();
#endif
