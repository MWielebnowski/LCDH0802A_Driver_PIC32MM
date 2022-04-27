/*
 * File:   LCDH0802A.c
 * Author: user
 *
 * Created on April 13, 2022, 10:51 AM
 */


#include "xc.h"
#include "LCDH0802A.h"
#include <stdint.h>
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/adc1.h"
#include "mcc_generated_files/sccp2_compare.h"
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/coretimer.h"
#include <stdio.h>

#define CPU_FREQUENCY (22000000UL)                  
#define CORE_TIMER_FREQUENCY (CPU_FREQUENCY/2)
#define CORE_TIMER_MILLISECONDS (CORE_TIMER_FREQUENCY/1000)
#define CORE_TIMER_MICROSECONDS (CORE_TIMER_FREQUENCY/1000000)

void CoreTimer_DelayUs(uint32_t delay){
    uint32_t DelayStartTime = CORETIMER_CountGet();
    while((CORETIMER_CountGet() - DelayStartTime) < (delay * CORE_TIMER_MICROSECONDS));
}

void CoreTimer_DelayMs(uint32_t delay){
    uint32_t DelayStartTime = CORETIMER_CountGet();
    while((CORETIMER_CountGet() - DelayStartTime) < (delay * CORE_TIMER_MILLISECONDS));
}

void LCD_Data(unsigned char Data){
    if(Data & 1)
        D4_PIN_SetHigh();
    else
        D4_PIN_SetLow();
    if(Data & 2)
        D5_PIN_SetHigh();
    else
        D5_PIN_SetLow();
    if(Data & 4)
        D6_PIN_SetHigh();
    else
        D6_PIN_SetLow();
    if(Data & 8)
        D7_PIN_SetHigh();
    else
        D7_PIN_SetLow();
}

void LCD_CMD(unsigned char CMD){
    RS_PIN_SetLow();
    LCD_Data(CMD);
    LCD_Send();
}

void LCD_Send(void){
    EN_PIN_SetHigh();
    CoreTimer_DelayUs(20);
    EN_PIN_SetLow();
    CoreTimer_DelayUs(20);  
}

void LCD_Clear(void){
    LCD_CMD(0);
    LCD_CMD(1);
    CoreTimer_DelayUs(70);
}

void LCD_Home(void){
    LCD_CMD(0);
    LCD_CMD(2);
    CoreTimer_DelayUs(35);
}

void LCD_LeftShift(void){
    LCD_CMD(1);
    LCD_CMD(0x08);
    CoreTimer_DelayUs(35);
    }

void LCD_RightShift(void){
    LCD_CMD(1);
    LCD_CMD(0x0C);
    CoreTimer_DelayUs(35);
    }

void LCD_Init(int N,int F){
    LCD_CMD(0x00);
    RS_PIN_SetLow();
    EN_PIN_SetLow();
    CoreTimer_DelayMs(150);
    LCD_CMD(0x03);
    CoreTimer_DelayMs(5);
    LCD_CMD(0x03);
    CoreTimer_DelayMs(160);
    LCD_CMD(0x03);
    LCD_CMD(0x02);
    LCD_CMD(0x02);
    if(N == 1 && F == 0)
        LCD_CMD(0x08);
    if(N == 1 && F == 1)
        LCD_CMD(0x0C);
    if(N == 0 && F == 1)
        LCD_CMD(0x04);
    else
        LCD_CMD(0x00);
    LCD_CMD(0x00);
    LCD_CMD(0x0C); // 0x08
    LCD_CMD(0x00);
    LCD_CMD(0x06);// 0X01
    LCD_CMD(0x00);
    LCD_CMD(0x01); // 0x02
}

void LCD_SetCursor(int x,int y){ // x = kolumna, y = wiersz
    unsigned char Temp, High, Low;
    if(y == 1){
        Temp = 0x80 + x - 1; // 0x14 + c - 1
        High = Temp >> 4;
        Low  = Temp & 0x0F;
        LCD_CMD(High);
        LCD_CMD(Low);
    }
    
    if(y == 2){
        Temp = 0xC0 + x - 1;
        High = Temp >> 4;
        Low  = Temp & 0x0F;
        LCD_CMD(High);
        LCD_CMD(Low);
    }
    CoreTimer_DelayMs(2);
}

void LCD_WriteChar(char Data){
    char Low, High;
    Low = Data & 0x0F;
    High = Data >> 4; //Data & 0xF0;
    
    RS_PIN_SetHigh();
    LCD_Data(High);
    LCD_Send();
    LCD_Data(Low);
    LCD_Send();
    RS_PIN_SetLow();
}

void LCD_WriteString(char *str){
    int i;
    for(i=0;str[i]!='\0';i++)
       LCD_WriteChar(str[i]);
}

