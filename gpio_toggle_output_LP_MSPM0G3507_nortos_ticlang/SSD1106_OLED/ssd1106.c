#include "ti_msp_dl_config.h"
#include "delay.h"
#include "ssd1106.h"
#include "ssd1106_oledfont.h"

//向SSD1106写入一个字节。
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;
void SSD1106_WR_Byte(u8 dat,u8 cmd)
{ 
 u8 i;     
 if(cmd)
   SSD1106_DC_Set();
 else 
   SSD1106_DC_Clr();    
 SSD1106_CS_Clr();
 for(i=0;i<8;i++)
 {     
  SSD1106_SCLK_Clr();
  if(dat&0x80)
     SSD1106_SDIN_Set();
  else 
     SSD1106_SDIN_Clr();
  SSD1106_SCLK_Set();
  dat<<=1;   
 }         
 SSD1106_CS_Set();
 SSD1106_DC_Set();      
} 

void SSD1106_Set_Pos(unsigned char x, unsigned char y) 
{ 
 SSD1106_WR_Byte(0xb0+y,SSD1106_CMD);
 SSD1106_WR_Byte(((x&0xf0)>>4)|0x10,SSD1106_CMD);
 SSD1106_WR_Byte((x&0x0f)|0x01,SSD1106_CMD); 
}      
//开启SSD1106显示    
void SSD1106_Display_On(void)
{
 SSD1106_WR_Byte(0X8D,SSD1106_CMD);  //SET DCDC命令
 SSD1106_WR_Byte(0X14,SSD1106_CMD);  //DCDC ON
 SSD1106_WR_Byte(0XAF,SSD1106_CMD);  //DISPLAY ON
}
//关闭SSD1106显示     
void SSD1106_Display_Off(void)
{
 SSD1106_WR_Byte(0X8D,SSD1106_CMD);  //SET DCDC命令
 SSD1106_WR_Byte(0X10,SSD1106_CMD);  //DCDC OFF
 SSD1106_WR_Byte(0XAE,SSD1106_CMD);  //DISPLAY OFF
}         
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!   
void SSD1106_Clear(void)  
{  
 u8 i,n;      
 for(i=0;i<8;i++)  
 {  
  SSD1106_WR_Byte (0xb0+i,SSD1106_CMD);    //设置页地址（0~7）
  SSD1106_WR_Byte (0x00,SSD1106_CMD);      //设置显示位置—列低地址
  SSD1106_WR_Byte (0x10,SSD1106_CMD);      //设置显示位置—列高地址   
  for(n=0;n<128;n++)SSD1106_WR_Byte(0,SSD1106_DATA); 
 } //更新显示
}

//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示     
//size:选择字体 16/12 
void SSD1106_ShowChar(u8 x,u8 y,u8 chr,u8 size)
{       
 unsigned char c=0,i=0; 
  c=chr-' ';//得到偏移后的值   
  if(x>Max_Column-1){x=0;y=y+2;}
  if(size ==16)
   {
   SSD1106_Set_Pos(x,y); 
   for(i=0;i<8;i++)
   SSD1106_WR_Byte(F8X16[c*16+i],SSD1106_DATA);
   SSD1106_Set_Pos(x,y+1);
   for(i=0;i<8;i++)
   SSD1106_WR_Byte(F8X16[c*16+i+8],SSD1106_DATA);
   }
   else { 
    SSD1106_Set_Pos(x,y+1);
    for(i=0;i<6;i++)
    SSD1106_WR_Byte(F6x8[c][i],SSD1106_DATA);   
   }
}
//m^n函数
u32 SSD1106_pow(u8 m,u8 n)
{
 u32 result=1;  
 while(n--)result*=m;    
 return result;
}      
//显示2个数字
//x,y :起点坐标  
//len :数字的位数
//size:字体大小 16/12
//mode:模式 0,填充模式;1,叠加模式
//num:数值(0~4294967295);      
void SSD1106_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
{          
 u8 t,temp;
 u8 enshow=0;         
 for(t=0;t<len;t++)
 {
  temp=(num/SSD1106_pow(10,len-t-1))%10;
  if(enshow==0&&t<(len-1))
  {
   if(temp==0)
   {
    SSD1106_ShowChar(x+(size/2)*t,y,' ',size);
    continue;
   }else enshow=1; 
     
  }
   SSD1106_ShowChar(x+(size/2)*t,y,temp+'0',size); 
 }
} 
//显示一个字符号串
void SSD1106_ShowString(u8 x,u8 y,u8 *chr, u8 size)
{
 unsigned char j=0;
 while (chr[j]!='\0')
 {  SSD1106_ShowChar(x,y,chr[j], size);
   x+=8;
  if(x>120){x=0;y+=2;}
   j++;
 }
}

//初始化SSD1106         
void SSD1106_Init(void)
{    
  /*
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);  //使能E端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 |GPIO_Pin_3 ;  
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;            //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
  GPIO_Init(GPIOE, &GPIO_InitStructure);   //初始化GPIOE3,6
  GPIO_SetBits(GPIOE,GPIO_Pin_2 |GPIO_Pin_3);  
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); //使能E端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;            //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
  GPIO_Init(GPIOE, &GPIO_InitStructure);   //初始化GPIOD3,6
  GPIO_SetBits(GPIOE,GPIO_Pin_4|GPIO_Pin_5);  
  */    
  
  SSD1106_WR_Byte(0xAE,SSD1106_CMD);//--turn off SSD1106 panel
  SSD1106_WR_Byte(0x00,SSD1106_CMD);//---set low column address
  SSD1106_WR_Byte(0x10,SSD1106_CMD);//---set high column address
  SSD1106_WR_Byte(0x40,SSD1106_CMD);//--set start line address  Set Mapping RAM     Display Start Line (0x00~0x3F)
 SSD1106_WR_Byte(0x81,SSD1106_CMD);//--set contrast control register
 SSD1106_WR_Byte(0xCF,SSD1106_CMD); // Set SEG Output Current Brightness
 SSD1106_WR_Byte(0xA1,SSD1106_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
 SSD1106_WR_Byte(0xC8,SSD1106_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
 SSD1106_WR_Byte(0xA6,SSD1106_CMD);//--set normal display
 SSD1106_WR_Byte(0xA8,SSD1106_CMD);//--set multiplex ratio(1 to 64)
 SSD1106_WR_Byte(0x3f,SSD1106_CMD);//--1/64 duty
 SSD1106_WR_Byte(0xD3,SSD1106_CMD);//-set display offset Shift Mapping RAM Counter (0x00~0x3F)
 SSD1106_WR_Byte(0x00,SSD1106_CMD);//-not offset
 SSD1106_WR_Byte(0xd5,SSD1106_CMD);//--set display clock divide ratio/oscillator frequency
 SSD1106_WR_Byte(0x80,SSD1106_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
 SSD1106_WR_Byte(0xD9,SSD1106_CMD);//--set pre-charge period
 SSD1106_WR_Byte(0xF1,SSD1106_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
 SSD1106_WR_Byte(0xDA,SSD1106_CMD);//--set com pins hardware configuration
 SSD1106_WR_Byte(0x12,SSD1106_CMD);
 SSD1106_WR_Byte(0xDB,SSD1106_CMD);//--set vcomh
 SSD1106_WR_Byte(0x40,SSD1106_CMD);//Set VCOM Deselect Level
 SSD1106_WR_Byte(0x20,SSD1106_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
 SSD1106_WR_Byte(0x02,SSD1106_CMD);//
 SSD1106_WR_Byte(0x8D,SSD1106_CMD);//--set Charge Pump enable/disable
 SSD1106_WR_Byte(0x14,SSD1106_CMD);//--set(0x10) disable
 SSD1106_WR_Byte(0xA4,SSD1106_CMD);// Disable Entire Display On (0xa4/0xa5)
 SSD1106_WR_Byte(0xA6,SSD1106_CMD);// Disable Inverse Display On (0xa6/a7) 
 SSD1106_WR_Byte(0xAF,SSD1106_CMD);//--turn on SSD1106 panel
 SSD1106_WR_Byte(0xAF,SSD1106_CMD); /*display ON*/ 
 SSD1106_Clear();
 SSD1106_Set_Pos(0,0);  
}  

/**
  * @brief  OLED显示数字（十六进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~0xFFFFFFFF
  * @param  Length 要显示数字的长度，范围：1~8
  * @retval 无
  */
void SSD1106_ShowHexNum(uint8_t x, uint8_t y, uint32_t Number, uint8_t Length , u8 size)
{
    uint8_t i, SingleNumber;
    for (i = 0; i < Length; i++)                            
    {
        SingleNumber = Number / SSD1106_pow(16, Length - i - 1) % 16;
        if (SingleNumber < 10)
        {
            SSD1106_ShowChar(x + i*size/2, y, SingleNumber + '0', size);
        }
        else
        {
            SSD1106_ShowChar(x + i*size/2, y, SingleNumber - 10 + 'A', size);
        }
    }
}

/**
  * @brief  OLED显示浮点数字（十进制，带符号数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字
  * @param  Length 要显示数字的长度，范围：1~10
  * @param  Flength 要显示的小数点后几位
  */
void SSD1106_ShowFNum(uint8_t x, uint8_t y, float Number, uint8_t Length, uint8_t Flength)
{
    uint8_t i;
    uint8_t flag = 1;
    float Number1;
    uint32_t Number2;
    if (Number >= 0)
    {
        SSD1106_ShowChar(x, y, '+', 16);
        Number1 = Number;
    }
    else
    {
        SSD1106_ShowChar(x, y, '-', 16);
        Number1 = -Number;
    }
    //将浮点数转换成整数然后显示
    Number2 = (int)(Number1 * SSD1106_pow(10,Flength));
    
    
    for (i = Length; i > 0; i--)                            
    {
        if(i == (Length - Flength))
        {
            SSD1106_ShowChar(x + i*8 + flag*8, y, '.', 16);
            flag = 0;
            SSD1106_ShowChar(x + i*8 + flag*8, y, Number2 / SSD1106_pow(10, Length - i) % 10 + '0', 16);
        }
        else
        {
            SSD1106_ShowChar(x + i*8 + flag*8, y, Number2 / SSD1106_pow(10, Length - i) % 10 + '0', 16);
        }
        
    }    
        
}