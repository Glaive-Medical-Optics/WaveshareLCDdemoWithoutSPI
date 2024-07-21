 /*****************************************************************************
* | Author      :   Glaive Software team
* | Function    :   Create a window within a window (i.e. a Picture in Picture)
* | Version     :   V1.0
* | Date        :   3-June-2024
*
*    This program is Free Software and has ABSOLUTELY NO WARRANTY.
*
******************************************************************************/


void quickMoveG()
{
  const unsigned short *image = G_70x70;
  unsigned short *imagePtr;
  unsigned long row, col;
  unsigned long dur;
  unsigned long i, j;
  int numberOfFrames = 120;
  unsigned long startX = 100;
  unsigned long startY = 30;
  unsigned long width = G70x70_WIDTH;
  unsigned long height = G70x70_HEIGHT;
  unsigned long time1, time2;
  double dif;
  char buf[10];

// quickly paint the display white.

  LCD_SetWindow(0, 0, LCD_WIDTH, LCD_HEIGHT);
  digitalWrite(DEV_DC_PIN, 1); // sets interface to data mode so we can send a sequence of bits
    for (j=1; j<=LCD_WIDTH*LCD_HEIGHT; j++)
    {
      LCD_WriteData_Word(WHITE);      
    }

  time1=micros();

  // Draw a 70x70 stylized G image 120 times

  for (i=1; i<=numberOfFrames; i++)
  {
    imagePtr = (unsigned short *)image;
    LCD_SetCursor(startX,startY);  
    //setPartialArea(startY, startY+height-1);
    LCD_SetWindow(startX, startY+i, startX+width-1, startY+i+height-1);
    digitalWrite(DEV_DC_PIN, 1); // sets interface to data mode so we can send a sequence of bits
    for (j=1; j<=width*height; j++)
    {
        LCD_WriteData_Word(*imagePtr++);      
    }
  }

  time2=micros();
  dur=time2-time1;
  dif=dur/1000000.0;   // convert to seconds
  sprintf(buf,"%-7.3f",dif);
  Serial.print("duration=");
  Serial.print(buf);
  Serial.print(" sec  (");
  sprintf(buf,"%-4.1f",numberOfFrames/dif);
  Serial.print(buf);
  Serial.print(" FPS)\n");

}
