#include "ST7789.h"
#include "ti_msp_dl_config.h"
#include "delay.h"
#include "font.h"

void ST7789_SPI_WriteByte(SPI_Regs *spi,uint8_t data)
{
    DL_SPI_transmitData8(spi, data);
    while(DL_SPI_isBusy(spi));
}

//初始化
void ST7789_Init(void)
{  					 
	ST7789_BL_reset();
	ST7789_RST_reset();
	delay_ms(100);	
	ST7789_RST_set();
	delay_ms(50);
	
	LCD_WR_REG(0x01);//Software Reset
	delay_ms(120);

    LCD_WR_REG(0x11); 			//Sleep Out
	delay_ms(120);               //DELAY120ms
//-----------------------ST7789V Frame rate setting-----------------//
//************************************************
	LCD_WR_REG(0x3A);        //65k mode
	LCD_WR_DATA(0x05);
	
	LCD_WR_REG(0xC5); 		//VCOM
	LCD_WR_DATA(0x1A);
	
	LCD_WR_REG(0x36);                 // 屏幕显示方向设置
	LCD_WR_DATA(0xA0);
	//-------------ST7789V Frame rate setting-----------//
	LCD_WR_REG(0xb2);		//Porch Setting
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x33);
	LCD_WR_DATA(0x33);

	LCD_WR_REG(0xb7);			//Gate Control
	LCD_WR_DATA(0x05);			//12.2v   -10.43v
	//--------------ST7789V Power setting---------------//
	LCD_WR_REG(0xBB);//VCOM
	LCD_WR_DATA(0x3F);

	LCD_WR_REG(0xC0); //Power control
	LCD_WR_DATA(0x2c);

	LCD_WR_REG(0xC2);		//VDV and VRH Command Enable
	LCD_WR_DATA(0x01);

	LCD_WR_REG(0xC3);			//VRH Set
	LCD_WR_DATA(0x0F);		//4.3+( vcom+vcom offset+vdv)

	LCD_WR_REG(0xC4);			//VDV Set
	LCD_WR_DATA(0x20);				//0v

	LCD_WR_REG(0xC6);				//Frame Rate Control in Normal Mode
	LCD_WR_DATA(0X01);			//111Hz

	LCD_WR_REG(0xd0);				//Power Control 1
	LCD_WR_DATA(0xa4);
	LCD_WR_DATA(0xa1);

	LCD_WR_REG(0xE8);				//Power Control 1
	LCD_WR_DATA(0x03);

	LCD_WR_REG(0xE9);				//Equalize time control
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x08);
	//---------------ST7789V gamma setting-------------//
	LCD_WR_REG(0xE0); //Set Gamma
	LCD_WR_DATA(0xD0);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x14);
	LCD_WR_DATA(0x28);
	LCD_WR_DATA(0x33);
	LCD_WR_DATA(0x3F);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x13);
	LCD_WR_DATA(0x14);
	LCD_WR_DATA(0x28);
	LCD_WR_DATA(0x30);

	LCD_WR_REG(0XE1); //Set Gamma
	LCD_WR_DATA(0xD0);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x24);
	LCD_WR_DATA(0x32);
	LCD_WR_DATA(0x32);
	LCD_WR_DATA(0x3B);
	LCD_WR_DATA(0x14);
	LCD_WR_DATA(0x13);
	LCD_WR_DATA(0x28);
	LCD_WR_DATA(0x2F);

	LCD_WR_REG(0x20); 		    //反显
	delay_ms(120); 
	LCD_WR_REG(0x29);         //开启显示
	LCD_Clear(WHITE);         //清屏
	ST7789_BL_set();            
}

void LCD_SetDirection(uint8_t dir)
{
	LCD_WR_REG(0x36);    // Memory Access Control 
	LCD_WR_DATA(dir);     //0x00,0x20,0x40,0x60,0x80,0xa0,0xc0,0xe0
}

void LCD_WR_REG(uint8_t data)
{ 
   ST7789_CS_reset();
   ST7789_A0_reset();
   ST7789_SPI_WriteByte(SPI1,data);
   ST7789_CS_set();
}

void LCD_WR_DATA(uint8_t data)
{
   ST7789_CS_reset();
   ST7789_A0_set();
   ST7789_SPI_WriteByte(SPI1,data);
   ST7789_CS_set();
}

void LCD_WR_DATA_16Bit(uint16_t data)
{	
   ST7789_CS_reset();
   ST7789_A0_set();  
   ST7789_SPI_WriteByte(SPI1,data>>8);
   ST7789_SPI_WriteByte(SPI1,data);
   ST7789_CS_set();
}

void LCD_SetWindows(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{	     
	LCD_WR_REG(0X2A); 
	LCD_WR_DATA(x1 >> 8); 
	LCD_WR_DATA(x1 & 0XFF);
	LCD_WR_DATA(x2 >> 8); 
	LCD_WR_DATA(x2 & 0XFF);

	LCD_WR_REG(0X2B); 
	LCD_WR_DATA(y1 >> 8); 
	LCD_WR_DATA(y1 & 0XFF);
	LCD_WR_DATA(y2 >> 8); 
	LCD_WR_DATA(y2 & 0XFF);
	LCD_WR_REG(0X2C);      //开始写入GRAM
}

void LCD_SetCursor(uint16_t x, uint16_t y)
{	  	    			
	LCD_SetWindows(x,y,x,y);
} 

void LCD_Clear(uint16_t color)
{
	uint16_t i;
	uint16_t j;
	LCD_SetWindows(0,0,LCD_WIDTH,LCD_HIGH);
  for(j = 0; j < LCD_HIGH; j++)
  {
		for(i = 0; i < LCD_WIDTH; i++)
		{
			LCD_WR_DATA_16Bit(color);
		}
	}
} 

void LCD_Fill(uint16_t x,uint16_t y,uint16_t width,uint16_t high,uint16_t color)
{  	
	uint16_t i;
	uint16_t j;
	LCD_SetWindows(x,y,width-1,high-1);       //设置显示窗口
	for(i = 0; i < high; i++)
	{
		for(j = 0; j < width; j++)
		LCD_WR_DATA_16Bit(color);	              //写入数据 	 
	}
	LCD_SetWindows(0,0,LCD_WIDTH,LCD_HIGH);    //恢复窗口设置为全屏
}

void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
	LCD_SetCursor(x,y);                //设置光标位置 
	LCD_WR_DATA_16Bit(color); 
}

void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		LCD_DrawPoint(uRow,uCol,color);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	LCD_DrawLine(x1,y1,x2,y1,color);
	LCD_DrawLine(x1,y1,x1,y2,color);
	LCD_DrawLine(x1,y2,x2,y2,color);
	LCD_DrawLine(x2,y1,x2,y2,color);
}  

void LCD_DrawFillRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	LCD_Fill(x1,y1,x2,y2,color);
}

void LCD_Draw_Circle_8(int xc, int yc, int x, int y, uint16_t color)
{
	LCD_DrawPoint(xc + x, yc + y, color);
	LCD_DrawPoint(xc - x, yc + y, color);
	LCD_DrawPoint(xc + x, yc - y, color);
	LCD_DrawPoint(xc - x, yc - y, color);
	LCD_DrawPoint(xc + y, yc + x, color);
	LCD_DrawPoint(xc - y, yc + x, color);
	LCD_DrawPoint(xc + y, yc - x, color);
	LCD_DrawPoint(xc - y, yc - x, color);
}

void LCD_DrawCircle(int xc, int yc,int r, uint16_t color, int fill)
{
	int x = 0, y = r, yi, d;
	d = 3 - 2 * r;
	if (fill) 
	{
		// 如果填充（画实心圆）
		while (x <= y) {
			for (yi = x; yi <= y; yi++)
				LCD_Draw_Circle_8(xc, yc, x, yi, color);
			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	} else 
	{
		// 如果不填充（画空心圆）
		while (x <= y) {
			LCD_Draw_Circle_8(xc, yc, x, y, color);
			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	}
}

void LCD_ShowChar(uint16_t x,uint16_t y,uint16_t font_color,uint16_t background_color,uint8_t num,uint8_t size,uint8_t mode)
{  							  
  uint8_t temp,t1,t;
	uint16_t y0 = y;
	uint8_t csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数	
 	num=num-' ';//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	
//	Address_set(x,y,x+size-1,y+size-1);
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=lcd_asc2_1206[num][t]; 	 	//调用1206字体
		else if(size==16)temp=lcd_asc2_1608[num][t];	//调用1608字体
		else if(size==24)temp=lcd_asc2_2412[num][t];	//调用2412字体
		else return;								//没有的字库
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_DrawPoint(x,y,font_color);
			else if(mode==0)LCD_DrawPoint(x,y,background_color);
			temp<<=1;
			y++;
			if(y>=240)return;		//超区域了
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=320)return;	//超区域了
				break;
			}
		}  	 
	}  	    	   	 	  
}   

void LCD_ShowString(uint16_t x,
										uint16_t y,
										uint16_t width,
										uint16_t height,
										uint16_t font_color,
										uint16_t background_color,
										uint8_t size,
										uint8_t *p)
{         
	uint8_t x0=x;
	width+=x;
	height+=y;
	while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
	{       
			if(x>=width){x=x0;y+=size;}
			if(y>=height)break;//退出
			LCD_ShowChar(x,y,font_color,background_color,*p,size,0);
			x+=size/2;
			p++;
	}  
}

uint32_t mypow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}

/*
size 12  16
mode 0: 带背景
mode 1: 不带背景
*/
void LCD_ShowNum(uint16_t x,uint16_t y,uint16_t font_color,uint16_t background_color,uint32_t num,uint8_t len,uint8_t size, uint8_t mode)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,font_color,background_color,' ',size, mode);
				continue;
			}else enshow=1; 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,font_color,background_color,temp+'0',size, mode); 
	}
} 

/*
void Gui_DrawFont_GBK16(u16 x, u16 y, u16 fc, u16 bc, u8 *s)
{
	unsigned char i,j;
	unsigned short k,x0;
	x0=x;

	while(*s) 
	{	
		if((*s) < 128) 
		{
			k=*s;
			if (k==13) 
			{
				x=x0;
				y+=16;
			}
			else 
			{
				if (k>32) k-=32; else k=0;
	
			    for(i=0;i<16;i++)
				for(j=0;j<8;j++) 
					{
				    	if(asc16[k*16+i]&(0x80>>j))	LCD_DrawPoint(x+j,y+i,fc);
						else 
						{
							if (fc!=bc) LCD_DrawPoint(x+j,y+i,bc);
						}
					}
				x+=8;
			}
			s++;
		}
			
		else 
		{

			for (k=0;k<hz16_num;k++) 
			{
			  if ((hz16[k].Index[0]==*(s))&&(hz16[k].Index[1]==*(s+1)))
			  { 
				    for(i=0;i<16;i++)
				    {
						for(j=0;j<8;j++) 
							{
						    	if(hz16[k].Msk[i*2]&(0x80>>j))	LCD_DrawPoint(x+j,y+i,fc);
								else {
									if (fc!=bc) LCD_DrawPoint(x+j,y+i,bc);
								}
							}
						for(j=0;j<8;j++) 
							{
						    	if(hz16[k].Msk[i*2+1]&(0x80>>j))	LCD_DrawPoint(x+j+8,y+i,fc);
								else 
								{
									if (fc!=bc) LCD_DrawPoint(x+j+8,y+i,bc);
								}
							}
				    }
				}
			  }
			s+=2;x+=16;
		} 
	}
}
*/

void LCD_DrawBMP(uint16_t x,uint16_t y, uint16_t width, uint16_t high, const unsigned char *p) 
{
  uint32_t i; 
	uint16_t picH,picL; 
	LCD_SetWindows(x,y,width-1,high-1);        //窗口设置
  for(i = 0; i < (width - x)*(high - y); i++)
	{	
			picL=*(p+i*2);	                         //数据低位在前
			picH=*(p+i*2+1);				
			LCD_WR_DATA_16Bit(picH<<8|picL);  				
	}	
	LCD_SetWindows(0,0,LCD_WIDTH,LCD_HIGH);           //恢复显示窗口为全屏	
}