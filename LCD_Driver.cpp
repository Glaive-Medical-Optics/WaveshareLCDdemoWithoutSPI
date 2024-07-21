/*****************************************************************************
* | File        : LCD_Driver.c
* | Author      :   Waveshare team
* | Function    :   LCD driver
* | Info        :
*----------------
* | This version:   V1.0
* | Date        :   2018-12-18
* | Info        :   
*
*    This program is Free Software and has ABSOLUTELY NO WARRANTY.
*
******************************************************************************/
#include "LCD_Driver.h"
/*******************************************************************************
function:
  Hardware reset
*******************************************************************************/


  unsigned long time1, time2;
  long dif;
  unsigned long count=0;

static void LCD_Reset(void)
{
  delay(200); // ms
  digitalWrite(DEV_RST_PIN, 0);
  delay(200);
  digitalWrite(DEV_RST_PIN, 1);
  delay(200);
}

/*******************************************************************************
function:
    Write data and commands
*******************************************************************************/


void LCD_Write_Command(byte data)
{
  digitalWrite(DISPLAY_CS_PIN, 0);
  digitalWrite(DISPLAY_CMD_PIN, 0);
  DEV_DATA_WRITE(data);
  digitalWrite(DISPLAY_CLK_PIN, 1);
}

static void LCD_WriteData_Byte(byte data)
{
  digitalWrite(DISPLAY_CS_PIN, 0);
  digitalWrite(DISPLAY_CMD_PIN, 1);
  DEV_DATA_WRITE(data);
  digitalWrite(DISPLAY_CLK_PIN, 1);
}

void LCD_WriteData_Word(uint16_t data)
{
  digitalWrite(DISPLAY_CS_PIN, 0);
  digitalWrite(DISPLAY_CMD_PIN, 1);
  DEV_DATA_WRITE((data>>8) & 0xff);
  DEV_DATA_WRITE(data & 0xff);
  digitalWrite(DISPLAY_CS_PIN, 1);
}

void pinSetup()
{
  pinMode(DISPLAY_CLK_PIN, OUTPUT);
  pinMode(DISPLAY_DIN_PIN, OUTPUT);
  pinMode(DISPLAY_CS_PIN, OUTPUT);
  pinMode(DISPLAY_CMD_PIN, OUTPUT);
  digitalWrite(DISPLAY_CLK_PIN, 1);
  digitalWrite(DISPLAY_DIN_PIN, 1);
  digitalWrite(DISPLAY_CS_PIN, HIGH);
  digitalWrite(DISPLAY_CMD_PIN, 1);
}

/*
 *  This routine sends the data bits to the LCD most significant bit first (high order bit to low order bit).
 */

void dataTransfer(uint8_t data)
{
  uint8_t mask = 0x80;

  for (int i = 0; i < 8; i++) {
    digitalWrite(DISPLAY_CLK_PIN, 0);
    digitalWrite(DISPLAY_DIN_PIN, data & mask);
    digitalWrite(DISPLAY_CLK_PIN, 1);
    mask = mask>>1;
  }
}


/******************************************************************************
function: 
    Common register initialization
******************************************************************************/
void LCD_Init(void)
{
  LCD_Reset();

  LCD_Write_Command(ILI9341_SLPOUT); //Sleep out, turns on display

  LCD_Write_Command(ILI9341_PCB);  // Power Control B
  LCD_WriteData_Byte(0x00);
  LCD_WriteData_Byte(0xC1);
  LCD_WriteData_Byte(0X30);
  LCD_Write_Command(ILI9341_POSC);  // Power On Sequence Control
  LCD_WriteData_Byte(0x64);
  LCD_WriteData_Byte(0x03);
  LCD_WriteData_Byte(0X12);
  LCD_WriteData_Byte(0X81);
  LCD_Write_Command(ILI9341_DTCA);  // Driver Timing Control A
  LCD_WriteData_Byte(0x85);
  LCD_WriteData_Byte(0x00);
  LCD_WriteData_Byte(0x79);
  LCD_Write_Command(ILI9341_PCA);  // Power Control A
  LCD_WriteData_Byte(0x39);
  LCD_WriteData_Byte(0x2C);
  LCD_WriteData_Byte(0x00);
  LCD_WriteData_Byte(0x34);
  LCD_WriteData_Byte(0x02);
  LCD_Write_Command(ILI9341_PRC);  // Pump Ratio Control
  LCD_WriteData_Byte(0x20);
  LCD_Write_Command(ILI9341_DTCB); // Driver Timing Control B
  LCD_WriteData_Byte(0x00);
  LCD_WriteData_Byte(0x00);
  LCD_Write_Command(ILI9341_PWCTR1); //Power control 1 --- command list starts on page 83
  LCD_WriteData_Byte(0x1D);         //VRH[5:0] --- 4.30 volt (page 178 of ILI spec)
  LCD_Write_Command(ILI9341_PWCTR2); //Power control 2
  LCD_WriteData_Byte(0x12); //SAP[2:0];BT[3:0], --- confused on page 179
  LCD_Write_Command(ILI9341_VMCTR1); //VCM control, --- VCOM Control 1 on page 180
  LCD_WriteData_Byte(0x33); // --- 0110011 sets VCOMH voltage to 3.975 volts
  LCD_WriteData_Byte(0x3F); // --- 0111111 sets VCOML voltage to 4.275 volts
  LCD_Write_Command(ILI9341_VMCTR2); //VCM control --- VCOM Control 2 (page 182)
  LCD_WriteData_Byte(0x92); // --- VMF[6:0] 1010010 sets VCOM offset voltage to +18 (VMH and VML)
  LCD_Write_Command(ILI9341_PIXFMT); // Memory Access Control -- Pixel Format Set (page 134)
  LCD_WriteData_Byte(0x55); // --- DPI[2:0]+DBI[2:0] 101+101 = 16 bits/px RGB interface + 16 bits/px MCU
  LCD_Write_Command(ILI9341_MADCTL); // Memory Access Control --- page 127
  LCD_WriteData_Byte(0x08); // --- Seems to be setting the BGR bit, i.e. BGR color filter panel (as opposed to RGB)
  LCD_Write_Command(ILI9341_FRMCTR1); // Frame Control (normal mode) page 155.
  LCD_WriteData_Byte(0x00); // --- DIVA[1:0]=00, division ratio fosc/1
  LCD_WriteData_Byte(0x12); // --- RTNA[4:0]=10010 frame rate of 106 Hz
  LCD_Write_Command(ILI9341_DFUNCTR); // Display Function Control --- page 164
  LCD_WriteData_Byte(0x0A); // --- supposed to have 4 parameters, I only see 2 parameters here
  LCD_WriteData_Byte(0xA2); // blank line means parameter definitions are truncated

  LCD_Write_Command(ILI9341_STS);  // --- Set tear scanline (page 139)
  LCD_WriteData_Byte(0x02);

  LCD_Write_Command(ILI9341_GAMMA3SET); // 3Gamma Function Disable
  LCD_WriteData_Byte(0x00);
  LCD_Write_Command(ILI9341_GAMMASET); //Gamma curve selected --- Gamma set (page 107)
  LCD_WriteData_Byte(0x01); // --- Gamma curve 1
  LCD_Write_Command(ILI9341_GMCTRP1); //Set Gamma --- Positive Gamma Correction (page 188)
  LCD_WriteData_Byte(0x0F); // --- 15 parameters
  LCD_WriteData_Byte(0x22);
  LCD_WriteData_Byte(0x1C);
  LCD_WriteData_Byte(0x1B);
  LCD_WriteData_Byte(0x08);
  LCD_WriteData_Byte(0x0F);
  LCD_WriteData_Byte(0x48);
  LCD_WriteData_Byte(0xB8);
  LCD_WriteData_Byte(0x34);
  LCD_WriteData_Byte(0x05);
  LCD_WriteData_Byte(0x0C);
  LCD_WriteData_Byte(0x09);
  LCD_WriteData_Byte(0x0F);
  LCD_WriteData_Byte(0x07);
  LCD_WriteData_Byte(0x00);
  LCD_Write_Command(ILI9341_GMCTRN1); //Set Gamma
  LCD_WriteData_Byte(0x00);
  LCD_WriteData_Byte(0x23);
  LCD_WriteData_Byte(0x24);
  LCD_WriteData_Byte(0x07);
  LCD_WriteData_Byte(0x10);
  LCD_WriteData_Byte(0x07);
  LCD_WriteData_Byte(0x38);
  LCD_WriteData_Byte(0x47);
  LCD_WriteData_Byte(0x4B);
  LCD_WriteData_Byte(0x0A);
  LCD_WriteData_Byte(0x13);
  LCD_WriteData_Byte(0x06);
  LCD_WriteData_Byte(0x30);
  LCD_WriteData_Byte(0x38);
  LCD_WriteData_Byte(0x0F);
  LCD_Write_Command(ILI9341_DISPON); //Display on --- page 109.
}

/*
 *  Some utility routines
 */

void LCD_turnOnPartialDisplayMode()
{
  LCD_Write_Command(ILI9341_PTLON);
}

void LCD_turnOnNormalDisplayMode()
{
  LCD_Write_Command(ILI9341_NORON);
}

void LCD_setPartialArea(uint16_t x, uint16_t y)
{
    LCD_Write_Command(ILI9341_PTLAR);
    LCD_WriteData_Word(x);
    LCD_WriteData_Word(y);
}

void LCD_setColumnAddress(uint16_t firstCol, uint16_t lastCol)
{
    LCD_Write_Command(ILI9341_CASET);
    LCD_WriteData_Word(firstCol);
    LCD_WriteData_Word(lastCol);
}

void LCD_setPageAddress(uint16_t firstRow, uint16_t lastRow)
{
    LCD_Write_Command(ILI9341_PASET);
    LCD_WriteData_Word(firstRow);
    LCD_WriteData_Word(lastRow);
}

void LCD_writeFrameMemory()
{
    LCD_Write_Command(ILI9341_RAMWR);
}

/******************************************************************************
function: Set the window to draw to
parameter :
    Xstart: Start uint16_t x coordinate
    Ystart: Start uint16_t y coordinate
    Xend  : End uint16_t coordinates
    Yend  : End uint16_t coordinatesen
******************************************************************************/
void LCD_SetWindow(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t  Yend)
{ 
    LCD_setColumnAddress(Xstart, Xend);
    LCD_setPageAddress(Ystart, Yend);
    LCD_writeFrameMemory();
}

/******************************************************************************
function: Set the cursor position
parameter :
    Xstart: Start uint16_t x coordinate
    Ystart: Start uint16_t y coordinate

******************************************************************************/
void LCD_SetCursor(uint16_t X, uint16_t Y)
{ 
  LCD_Write_Command(ILI9341_CASET);
  LCD_WriteData_Byte(X >> 8);
  LCD_WriteData_Byte(X);
  LCD_WriteData_Byte(X >> 8);
  LCD_WriteData_Byte(X);

  LCD_Write_Command(ILI9341_PASET);
  LCD_WriteData_Byte(Y >> 8);
  LCD_WriteData_Byte(Y);
  LCD_WriteData_Byte(Y >> 8);
  LCD_WriteData_Byte(Y);

  LCD_Write_Command(ILI9341_RAMWR);
}

/******************************************************************************
function: Clear screen function, refresh the screen to a certain color
parameter :
    Color :   The color you want to clear all the screen
******************************************************************************/
void LCD_Clear(uint16_t Color)
{
  unsigned int i,j;   
  LCD_SetWindow(0, 0, LCD_WIDTH, LCD_HEIGHT);
  digitalWrite(DEV_DC_PIN, 1);
  for(i = 0; i < LCD_WIDTH; i++){
    for(j = 0; j < LCD_HEIGHT; j++){
      DEV_DATA_WRITE((Color>>8)&0xff);
      DEV_DATA_WRITE(Color);
    }
   }
}

/******************************************************************************
function: Refresh a certain area to the same color
parameter :
    Xstart: Start uint16_t x coordinate
    Ystart: Start uint16_t y coordinate
    Xend  : End uint16_t coordinates
    Yend  : End uint16_t coordinates
    color : Set the color
******************************************************************************/
void LCD_ClearWindow(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend,uint16_t color)
{          
  uint16_t i,j; 
  LCD_SetWindow(Xstart, Ystart, Xend-1,Yend-1);
  for(i = Ystart; i <= Yend-1; i++){                                
    for(j = Xstart; j <= Xend-1; j++){
      LCD_WriteData_Word(color);
    }
  }                   
}
