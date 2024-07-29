#ifndef __ST7789_H
#define __ST7789_H

#include "ti_msp_dl_config.h"

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

//SDA PB8
//SCL PB9
//RST PA27
//A0 PA26
//CS PA25
//BL PA24

#define ST7789_RST_reset() DL_GPIO_clearPins(GPIO_LCD_PORT, GPIO_LCD_ST7789_RST_PIN)
#define ST7789_RST_set() DL_GPIO_setPins(GPIO_LCD_PORT, GPIO_LCD_ST7789_RST_PIN)
#define ST7789_A0_reset() DL_GPIO_clearPins(GPIO_LCD_PORT, GPIO_LCD_ST7789_A0_PIN)
#define ST7789_A0_set() DL_GPIO_setPins(GPIO_LCD_PORT, GPIO_LCD_ST7789_A0_PIN)
#define ST7789_CS_reset() DL_GPIO_clearPins(GPIO_LCD_PORT, GPIO_LCD_ST7789_CS_PIN)
#define ST7789_CS_set() DL_GPIO_setPins(GPIO_LCD_PORT, GPIO_LCD_ST7789_CS_PIN)
#define ST7789_BL_reset() DL_GPIO_clearPins(GPIO_LCD_PORT, GPIO_LCD_ST7789_BL_PIN)
#define ST7789_BL_set() DL_GPIO_setPins(GPIO_LCD_PORT, GPIO_LCD_ST7789_BL_PIN)

#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F
#define GRED 		0XFFE0
#define GBLUE	    0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 		0XBC40 //棕色
#define BRRED 		0XFC07 //棕红色
#define GRAY  		0X8430 //灰色

#define LCD_WIDTH   320
#define LCD_HIGH    240

void ST7789_Init(void);
void ST7789_SPI_WriteByte(SPI_Regs *spi,uint8_t data);

void LCD_SetDirection(uint8_t dir);
void LCD_WR_REG(uint8_t data);
void LCD_WR_DATA(uint8_t data);
void LCD_WR_DATA_16Bit(uint16_t data);
void LCD_SetWindows(uint16_t x,uint16_t y,uint16_t width,uint16_t high);
void LCD_SetCursor(uint16_t x, uint16_t y);
void LCD_Clear(uint16_t color);
void LCD_Fill(uint16_t x,uint16_t y,uint16_t width,uint16_t high,uint16_t color);
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);
void LCD_DrawFillRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);
void LCD_Draw_Circle_8(int xc, int yc, int x, int y, uint16_t color);
void LCD_DrawCircle(int xc, int yc,int r, uint16_t color, int fill);
void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint16_t font_color,uint16_t background_color,uint8_t size,uint8_t *p);
void LCD_ShowNum(uint16_t x,uint16_t y,uint16_t font_color,uint16_t background_color,uint32_t num,uint8_t len,uint8_t size, uint8_t mode);
//void Gui_DrawFont_GBK16(u16 x, u16 y, u16 fc, u16 bc, u8 *s);
void LCD_DrawBMP(uint16_t x,uint16_t y, uint16_t width, uint16_t high, const unsigned char *p);


#endif