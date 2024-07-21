/*****************************************************************************
* | File        : LCD_Driver.h
* | Author      :   Waveshare team
* | Function    :   LCD driver
* | Info        :
*----------------
* | This version:   V1.0
* | Date        :   2018-12-18
*      
*   
*    This program is Free Software and has ABSOLUTELY NO WARRANTY.
*
******************************************************************************/
#ifndef __LCD_DRIVER_H
#define __LCD_DRIVER_H

#include "DEV_Config.h"

#define LCD_WIDTH   240 //LCD width
#define LCD_HEIGHT  320 //LCD height

void dataTransfer(uint8_t data);

/*
 *  The ILI commands used by this sketch (in numerical order):
 *  
 *  Page numbers refer to the ILI9341 data sheet version 1.11.
 */

#define ILI9341_SLPOUT      0x11      // Sleep Out                           (page 101) - initialization command 1
#define ILI9341_PTLON       0x12      // Partial Mode ON                     (page 103) - not currently used
#define ILI9341_NORON       0x13      // Normal Display Mode ON              (page 104) - not currently used
#define ILI9341_GAMMASET    0x26      // Gamma Set                           (page 107) - initialization command 18
#define ILI9341_DISPON      0x29      // Display ON                          (page 109) - initialization command 21
#define ILI9341_CASET       0x2A      // Column Address Set                  (page 110) - used during writes
#define ILI9341_PASET       0x2B      // Page Address Set                    (page 112) - used during writes
#define ILI9341_RAMWR       0x2C      // Memory Write / Write Frame Memory   (page 114) - used during writes
#define ILI9341_PTLAR       0x30      // Set Partial Area                    (page 118) - not currently used
#define ILI9341_MADCTL      0x36      // Memory Access Control               (page 127) - initialization command 13
#define ILI9341_PIXFMT      0x3A      // COLMOD: Pixel Format Set            (page 134) - initialization command 12
#define ILI9341_FRMCTR1     0xB1      // Frame Rate Control for normal mode  (page 155) - initialization command 14
#define ILI9341_DFUNCTR     0xB6      // Display Function Control            (page 164) - initialization command 15
#define ILI9341_PWCTR1      0xC0      // Power Control 1                     (page 178) - initialization command 8
#define ILI9341_PWCTR2      0xC1      // Power Control 2                     (page 179) - initialization command 9
#define ILI9341_VMCTR1      0xC5      // VCOM Control 1                      (page 180) - initialization command 10
#define ILI9341_VMCTR2      0xC7      // VCOM Control 2                      (page 182) - initialization command 11
#define ILI9341_GMCTRP1     0xE0      // Positive Gamma Correction           (page 188) - initialization command 19
#define ILI9341_GMCTRN1     0xE1      // Negative Gamma Correction           (page 189) - initialization command 20

/*
 *    We also use the following commands which are not in the Adafruit ILI9341 header:
 */

#define ILI9341_STS         0x44      // Set tear scanline                    (page 139) - initialization command 16
#define ILI9341_PCA         0xCB      // Power Control A                      (page 195) - initialization command 5
#define ILI9341_PCB         0xCF      // Power Control B                      (page 196) - initialization command 2
#define ILI9341_DTCA        0xE8      // Driver Timing Control A              (page 197) - initialization command 4
#define ILI9341_DTCB        0xEA      // Driver Timing Control B              (page 199) - initialization command 7
#define ILI9341_POSC        0xED      // Power On Sequence Control            (page 200) - initialization command 3
#define ILI9341_GAMMA3SET   0xF2      // 3 Gamma Control (set 0 to Disable)   (page 201) - initialization command 17
#define ILI9341_PRC         0xF7      // Pump Ratio Control                   (page 202) - initialization command 6


void LCD_Write_Command(uint8_t data);
//void LCD_WriteData_Byte(uint8_t data);
void LCD_WriteData_Word(uint16_t da);

void LCD_SetCursor(uint16_t X, uint16_t Y);
void LCD_SetWindow(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t  Yend);

void LCD_Init(void);
void LCD_SetBackLight(uint16_t Value);

void LCD_Clear(uint16_t Color);
void LCD_ClearWindow(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend,uint16_t color);


// Utility routines

void LCD_turnOnPartialDisplayMode();
void LCD_turnOnNormalDisplayMode();
void LCD_setPartialArea(uint16_t x, uint16_t y);
void LCD_setColumnAddress(uint16_t firstCol, uint16_t lastCol);
void LCD_setPageAddress(uint16_t firstRow, uint16_t lastRow);
void LCD_writeFrameMemory();

// Specify names for some colors

#define WHITE         0xFFFF
#define BLACK         0x0000    
#define BLUE          0x001F  
#define BRED          0XF81F
#define GRED          0XFFE0
#define GBLUE         0X07FF
#define RED           0xF800
#define MAGENTA       0xF81F
#define GREEN         0x07E0
#define CYAN          0x7FFF
#define YELLOW        0xFFE0
#define BROWN         0XBC40 
#define BRRED         0XFC07 
#define GRAY          0X8430 
#define DARKBLUE      0X01CF  
#define LIGHTBLUE     0X7D7C   
#define GRAYBLUE      0X5458 
#define LIGHTGREEN    0X841F 
#define LGRAY         0XC618 
#define LGRAYBLUE     0XA651
#define LBBLUE        0X2B12 


#endif
