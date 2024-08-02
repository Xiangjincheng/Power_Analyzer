#include <My_Oled12864.h>

void IIC_Start()
{   OLED_SDIN_Set();
	OLED_SCLK_Set();    DELAY_US(5);//5
	OLED_SDIN_Clr();    DELAY_US(6);//6
	OLED_SCLK_Clr();
}
/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{   OLED_SCLK_Clr();
	OLED_SDIN_Clr();
	OLED_SCLK_Set() ;   DELAY_US(6);//6
	OLED_SDIN_Set();    DELAY_US(6);//6
}

void IIC_Wait_Ack()
{   OLED_SDIN_Set();
	OLED_SCLK_Set() ;   DELAY_US(3);
	OLED_SCLK_Clr();    DELAY_US(3);
}
/**********************************************
// IIC Write byte
**********************************************/
void Write_IIC_Byte(unsigned char IIC_Byte)
{   unsigned char i;
	unsigned char m,da;
	da=IIC_Byte;
	OLED_SCLK_Clr();
	for(i=0;i<8;i++)
	{
		m=da;
		//	OLED_SCLK_Clr();
		m=m&0x80;
		if(m==0x80)         {OLED_SDIN_Set();}
		else                OLED_SDIN_Clr();
		da=da<<1;           DELAY_US(2);
		OLED_SCLK_Set();    DELAY_US(2);
		OLED_SCLK_Clr();    DELAY_US(2);
}	}
/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{   IIC_Start();
    Write_IIC_Byte(0x78);            //Slave address,SA0=0
    IIC_Wait_Ack();
    Write_IIC_Byte(0x00);			//write command
    IIC_Wait_Ack();
    Write_IIC_Byte(IIC_Command);
    IIC_Wait_Ack();
    IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{   IIC_Start();
    Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
    IIC_Wait_Ack();
    Write_IIC_Byte(0x40);			//write data
    IIC_Wait_Ack();
    Write_IIC_Byte(IIC_Data);
    IIC_Wait_Ack();
    IIC_Stop();
}
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{   if(cmd)Write_IIC_Data(dat);
	else Write_IIC_Command(dat);
}

/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{   unsigned char m,n;
	for(m=0;m<8;m++)
	{   OLED_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_WR_Byte(0x00,0);		//low column start address
		OLED_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++) OLED_WR_Byte(fill_Data,1);
}	}
/***********************Delay****************************************/
void Delay_50ms(unsigned int Del_50ms)
{   unsigned int m;
	for(;Del_50ms>0;Del_50ms--) for(m=12490;m>0;m--);
}
void Delay_1ms(unsigned int Del_1ms)
{   unsigned int m;
    for(;Del_1ms>0;Del_1ms--)   for(m=16500;m>0;m--);
}
void Delay_3us(void)
{   unsigned char j;
	for(j=0;j<33;j++);
}
//坐标设置
void OLED_Set_Pos(unsigned char x, unsigned char y)
{ 	OLED_WR_Byte((0xb0)+y,OLED_CMD);
	OLED_WR_Byte(((x&(0xf0))>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&(0x0f)),OLED_CMD);
}
//开启OLED显示
void OLED_Display_On(void)
{   OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示
void OLED_Display_Off(void)
{   OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!
void CLEAR_Screen(void)
{   u8 i,n;
	for(i=0;i<8;i++)
	{   OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA);
}	} //更新显示
void OLED_On(void)
{   u8 i,n;
	for(i=0;i<8;i++)
	{   OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址
		for(n=0;n<128;n++)OLED_WR_Byte(0xff,OLED_DATA);
}	} //更新显示
//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示
//size:选择字体 16/12
void lcd12864_display_char(unsigned int LINE_start,unsigned char LINE_end,unsigned char ROW_start,unsigned char ROW_end,unsigned int f)
{   unsigned char linecnt,rowcnt,bytecnt;
    for(linecnt=LINE_start;linecnt<=LINE_end;linecnt++)   //讲哪行显示出来
    {   OLED_WR_Byte (0xb0+linecnt,OLED_CMD);    //设置页地址（0~7）
        OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
        OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址
        for(rowcnt=ROW_start;rowcnt<=ROW_end;rowcnt++)  //将哪行的所有字符显示出来
           for (bytecnt=0;bytecnt<7;bytecnt++)     OLED_WR_Byte(LCD_charNumber[LCD_char[f][linecnt][rowcnt]] [bytecnt],OLED_DATA); //
}   }
//m^n函数
u32 oled_pow(u8 m,u8 n)
{   u32 result=1;
	while(n--)result*=m;
	return result;
}

//显示汉字
/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void lcd12864_display_picture(unsigned int LINE_start,unsigned char LINE_end,unsigned char ROW_start,unsigned char ROW_end)
{   unsigned char linecnt,rowcnt;
    for(linecnt=LINE_start;linecnt<=LINE_end;linecnt++)   //讲哪行显示出来
    {   OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
        OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址
        for(rowcnt=ROW_start;rowcnt<=ROW_end;rowcnt++)  OLED_WR_Byte(LCD_picture_char[linecnt][rowcnt],OLED_DATA); //
}    }
//初始化SSD1306
void LCD12864_init(void)
{
 	OLED_WR_Byte(0xAE,OLED_CMD);//--display off
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address
	OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
	OLED_WR_Byte(0x81,OLED_CMD); // contract control
	OLED_WR_Byte(0xCF,OLED_CMD);
	OLED_WR_Byte(0xA1,OLED_CMD);
	OLED_WR_Byte(0xC8,OLED_CMD);
	OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
	OLED_WR_Byte(0x00,OLED_CMD);//
	OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
	OLED_WR_Byte(0x80,OLED_CMD);//
	OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_WR_Byte(0xF1,OLED_CMD);//
	OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_WR_Byte(0x12,OLED_CMD);//
	OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	OLED_WR_Byte(0x30,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	OLED_WR_Byte(0x14,OLED_CMD);//
	OLED_WR_Byte(0xA4,OLED_CMD);
	OLED_WR_Byte(0xA6,OLED_CMD);
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
}
void lcd_display_shuju_deal( int shuju,unsigned int flag,unsigned char line,unsigned char row1,unsigned char row2,unsigned char row3,unsigned char row4)
 {  unsigned int dc_buff;               //把数据的每一位分离出来用于显示
    if (shuju>0)                            //若数据大于零则直接分离
    {   LCD_char[flag][line][row1]=shuju/1000;      dc_buff=shuju%1000;
        LCD_char[flag][line][row2]=dc_buff/100;     dc_buff=dc_buff%100;
        LCD_char[flag][line][row3]=dc_buff/10;      LCD_char[flag][line][row4]=dc_buff%10;
    }
    if  (shuju<0)                       //若数据小于零则取反后再分离
    {   shuju=-shuju;
        LCD_char[flag][line][row1]=shuju/1000;      dc_buff=shuju%1000;
        LCD_char[flag][line][row2]=dc_buff/100;     dc_buff=dc_buff%100;
        LCD_char[flag][line][row3]=dc_buff/10;      LCD_char[flag][line][row4]=dc_buff%10;
    }
    if (shuju==0)                   //若数据等于零，则每一位都为零
    {   LCD_char[flag][line][row1]=0;           LCD_char[flag][line][row2]=0;
        LCD_char[flag][line][row3]=0;       LCD_char[flag][line][row4]=0;
    }
}
void lcd_display_shuju_deal2( int shuju,unsigned int flag,unsigned char line,unsigned char row1,unsigned char row2)
{   if (shuju>0)                        //若数据大于零则直接分离
    {   LCD_char[flag][line][row1]=shuju/10;        LCD_char[flag][line][row2]=shuju%10;    }
    if (shuju<0)                        //若数据小于零则取反后再分离
    {   shuju=-shuju;
        LCD_char[flag][line][row1]=shuju/10;        LCD_char[flag][line][row2]=shuju%10;    }
    if (shuju==0)                       //若数据等于零，则每一位都为零
    {   LCD_char[flag][line][row1]=0;               LCD_char[flag][line][row2]=0;           }
}
void lcd_display_shuju_deal3( int shuju,unsigned int flag,unsigned char line,unsigned char row1,unsigned char row2,unsigned char row3)
 {  unsigned int dc_buff;               //把数据的每一位分离出来用于显示
    if (shuju>0)                            //若数据大于零则直接分离
    {   LCD_char[flag][line][row1]=shuju/100;       dc_buff=shuju%100;
        LCD_char[flag][line][row2]=dc_buff/10;  LCD_char[flag][line][row3]=dc_buff%10;
    }
    if (shuju<0)                            //若数据小于零则取反后再分离
    {   shuju=-shuju;
        LCD_char[flag][line][row1]=shuju/100;       dc_buff=shuju%100;
        LCD_char[flag][line][row2]=dc_buff/10;  LCD_char[flag][line][row3]=dc_buff%10;
    }
    if (shuju==0)                           //若数据等于零，则每一位都为零
    {   LCD_char[flag][line][row1]=0;   LCD_char[flag][line][row2]=0;   LCD_char[flag][line][row3]=0;
    }
}
