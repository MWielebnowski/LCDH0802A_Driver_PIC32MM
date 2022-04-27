/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */
#ifndef _LCDH0802A_H    /* Guard against multiple inclusion */
#define _LCDH0802A_H

#include <stdint.h>

/*
    typedef struct LCD_GPIO {
        uint16_t D4_PIN;
        uint16_t D5_PIN;
        uint16_t D6_PIN;
        uint16_t D7_PIN;
        uint16_t EN_PIN;
        uint16_t RS_PIN;
    } LCD_PIN;
*/

/*Prototypes of all functions*/    
    void LCD_Data(unsigned char);
    void LCD_CMD(unsigned char);
    void LCD_Send(void);
    void LCD_Clear(void);
    void LCD_Home(void);
    void LCD_Init(int,int); /* number of lines 1/2, font 5x11/5x8 */
    void LCD_SetCursor(int,int); // x,y position
    void LCD_WriteChar(char); // char to be written
    void LCD_WriteString(char*); // string to be written
    void LCD_RightShift(void);
    void LCD_LeftShift(void);
    void CoreTimer_DelayUs(uint32_t);
    



#endif /* LCDH0802A_H.h */

/* *****************************************************************************
 End of File
 */
