#ifndef __SH1106_H
#define __SH1106_H

#include "ti_msp_dl_config.h"

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

#define SSD1106_MODE 0
#define SIZE 16
#define XLevelL  0x00
#define XLevelH  0x10
#define Max_Column 128
#define Max_Row  64
#define Brightness 0xFF 
#define X_WIDTH  128
#define Y_WIDTH  64    

//采用软件SPI方式
//PA14 CLK
//PA15 SDA
//PA16 CS
//PA17 DC

//-----------------OLED端口定义----------------          
#define SSD1106_SCLK_Clr() DL_GPIO_clearPins(GPIO_SPI_OLED_PORT, GPIO_SPI_OLED_CLK_PIN)//CLK
#define SSD1106_SCLK_Set() DL_GPIO_setPins(GPIO_SPI_OLED_PORT, GPIO_SPI_OLED_CLK_PIN)

#define SSD1106_SDIN_Clr() DL_GPIO_clearPins(GPIO_SPI_OLED_PORT, GPIO_SPI_OLED_SDA_PIN)//DIN
#define SSD1106_SDIN_Set() DL_GPIO_setPins(GPIO_SPI_OLED_PORT, GPIO_SPI_OLED_SDA_PIN)

#define SSD1106_DC_Clr() DL_GPIO_clearPins(GPIO_SPI_OLED_PORT, GPIO_SPI_OLED_DC_PIN)//DC
#define SSD1106_DC_Set() DL_GPIO_setPins(GPIO_SPI_OLED_PORT, GPIO_SPI_OLED_DC_PIN)     

#define SSD1106_CS_Clr()  DL_GPIO_clearPins(GPIO_SPI_OLED_PORT, GPIO_SPI_OLED_CS_PIN)//CS
#define SSD1106_CS_Set()  DL_GPIO_setPins(GPIO_SPI_OLED_PORT, GPIO_SPI_OLED_CS_PIN)

#define SSD1106_CMD  0 //写命令
#define SSD1106_DATA 1 //写数据

//OLED控制用函数
void SSD1106_WR_Byte(u8 dat,u8 cmd);     
void SSD1106_Display_On(void);
void SSD1106_Display_Off(void);                    
void SSD1106_Init(void);
void SSD1106_Clear(void);
void SSD1106_DrawPoint(u8 x,u8 y,u8 t);
void SSD1106_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void SSD1106_ShowChar(u8 x,u8 y,u8 chr, u8 size);
void SSD1106_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void SSD1106_ShowString(u8 x,u8 y, u8 *p, u8 size);  
void SSD1106_Set_Pos(unsigned char x, unsigned char y);
void SSD1106_ShowHexNum(uint8_t x, uint8_t y, uint32_t Number, uint8_t Length , u8 size);
void SSD1106_ShowFNum(uint8_t x, uint8_t y, float Number, uint8_t Length,uint8_t Flength);
#endif