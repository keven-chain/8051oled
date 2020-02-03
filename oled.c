#include "oled.h"
#include "STC8.h"
#include "font.h"
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
//引脚定义
sbit SCLK=	P2^4;
sbit SDIN=	P2^5;	
sbit RES=	P3^4	;	
sbit CS	=P3^5		;
sbit DC=	P3^6	;	
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 延迟函数
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void uDelay(long l)
{
	while(l--);
}


void Delay(unsigned char n)
{
unsigned char i,j,k;

	for(k=0;k<n;k++)
	{
		for(i=0;i<131;i++)
		{
			for(j=0;j<15;j++)
			{
				uDelay(203);	
			}
		}
	}
}
//******************************************************************************//
//函数功能：写命令
//无返回值
//*******************************************************************************//
void Write_Command(unsigned char Data)
{
unsigned char i;

	CS=0;
	DC=0;
	for (i=0; i<8; i++)
	{
		SCLK=0;
		SDIN=(Data&0x80)>>7;
		Data = Data << 1;
//		uDelay(1);
		SCLK=1;
//		uDelay(1);
	}
//	SCLK=0;
	DC=1;
	CS=1;
}

void Write_Data(unsigned char Data)
{
unsigned char i;

	CS=0;
	DC=1;
	for (i=0; i<8; i++)
	{
		SCLK=0;
		SDIN=(Data&0x80)>>7;
		Data = Data << 1;
//		uDelay(1);
		SCLK=1;
//		uDelay(1);
	}
//	SCLK=0;
	DC=1;
	CS=1;
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//初始化的一些函数
//不用处理
//不用管，除非要处理底层
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Set_Column_Address(unsigned char a, unsigned char b)
{
	Write_Command(0x15);
	Write_Data(a);	
	Write_Data(b);	
}

void Set_Row_Address(unsigned char a, unsigned char b)
{
	Write_Command(0x75);
	Write_Data(a);				
	Write_Data(b);				
}

void Set_Write_RAM()
{
	Write_Command(0x5C);
}

void Set_Read_RAM()
{
	Write_Command(0x5D);
}

void Set_Remap_Format(unsigned char d)
{
	Write_Command(0xA0);
	Write_Data(d);
}

void Set_Start_Line(unsigned char d)
{
	Write_Command(0xA1);			
	Write_Data(d);				
}

void Set_Display_Offset(unsigned char d)
{
	Write_Command(0xA2);
	Write_Data(d);
}

void Set_Display_Mode(unsigned char d)
{
	Write_Command(0xA4|d);
}

void Set_Function_Selection(unsigned char d)
{
	Write_Command(0xAB);			
	Write_Data(d);			
}

void Set_Display_On_Off(unsigned char d)
{
	Write_Command(0xAE|d);
}

void Set_Phase_Length(unsigned char d)
{
	Write_Command(0xB1);			
	Write_Data(d);						
}


void Set_Display_Enhancement(unsigned char d)
{
	Write_Command(0xB2);			
	Write_Data(d);				
	Write_Data(0x00);
	Write_Data(0x00);
}

void Set_Display_Clock(unsigned char d)
{
	Write_Command(0xB3);			
	Write_Data(d);				
}

void Set_VSL(unsigned char d)
{
	Write_Command(0xB4);			
	Write_Data(0xA0|d);			
	Write_Data(0xB5);
	Write_Data(0x55);
}

void Set_GPIO(unsigned char d)
{
	Write_Command(0xB5);			
	Write_Data(d);				
}

void Set_Precharge_Period(unsigned char d)
{
	Write_Command(0xB6);			
	Write_Data(d);				
}

void Set_Precharge_Voltage(unsigned char d)
{
	Write_Command(0xBB);			
	Write_Data(d);				
}

void Set_VCOMH(unsigned char d)
{
	Write_Command(0xBE);			
	Write_Data(d);				
}

void Set_Contrast_Color(unsigned char a, unsigned char b, unsigned char c)
{
	Write_Command(0xC1);			
	Write_Data(a);				
	Write_Data(b);				
	Write_Data(c);				
}

void Set_Master_Current(unsigned char d)
{
	Write_Command(0xC7);			
	Write_Data(d);			
}

void Set_Multiplex_Ratio(unsigned char d)
{
	Write_Command(0xCA);		
	Write_Data(d);				
}

void Set_Command_Lock(unsigned char d)
{
	Write_Command(0xFD);			
	Write_Data(d);				
}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Global Variables
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define Max_Column	0x7f			// 128-1
#define Max_Row		0x7f			// 128-1
#define	Brightness	0x0F
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Show Regular Pattern (Full Screen)
//    a: RRRRRGGG
//    b: GGGBBBBB
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Fill_RAM(unsigned char a, unsigned char b)
{
unsigned char i,j;

	Set_Column_Address(0x00,0x7F);
	Set_Row_Address(0x00,0x7F);
	Set_Write_RAM();

	for(i=0;i<128;i++)
	{
		for(j=0;j<128;j++)
		{
			Write_Data(a);
			Write_Data(b);
		}
	}
}

void Fill_Block(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e, unsigned char f)
{
unsigned char i,j;

	Set_Column_Address(a,b);
	Set_Row_Address(c,d);
	Set_Write_RAM();

	for(i=0;i<(d-c+1);i++)
	{
		for(j=0;j<(b-a+1);j++)
		{
			Write_Data(e);
			Write_Data(f);
		}
	}
}

void Rainbow()
{

		Fill_Block(0x20,0x2F,0x00,Max_Row,0xF8,0x1F);
		Fill_Block(0x30,0x3F,0x00,Max_Row,0x07,0x9F);
		Fill_Block(0x40,0x4F,0x00,Max_Row,0xF8,0x00);
		Fill_Block(0x50,0x5F,0x00,Max_Row,0x07,0xE0);
		Fill_Block(0x60,0x6F,0x00,Max_Row,0x00,0x1F);
		Fill_Block(0x70,Max_Column,0x00,Max_Row,0x00,0x00);
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  垂直滚动
//
//    a: 滚动方向
//       "0x00" (Upward)
//       "0x01" (Downward)
//    b: 滚动行数
//    c:滚动时间间隔
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Vertical_Scroll(unsigned char a, unsigned char b, unsigned char c)
{
unsigned int i,j;	

	switch(a)
	{
		case 0:
			for(i=0;i<128;i+=b)
			{
				Set_Start_Line(i);
				for(j=0;j<c;j++)
				{
					uDelay(200);
				}
			}
			break;
		case 1:
			for(i=0;i<128;i+=b)
			{
				Set_Start_Line(128-i);
				for(j=0;j<c;j++)
				{
					uDelay(200);
				}
			}
			break;
	}
	Set_Start_Line(0x00);
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 水平滚动
//
//    a: 滚动方向
//       "0x00" (Rightward)
//       "0x01" (Leftward)
//    b: 滚动间隔长度
//    c：起始列
//    d: 起始行
//    e: 滚动频率
//    f: 延迟
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Horizontal_Scroll(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e, unsigned char f)
{
	Write_Command(0x96);			// Horizontal Scroll Setup
	Write_Data((a<<7)|b);
	Write_Data(c);
	Write_Data(d);
	Write_Data(0x00);
	Write_Data(e);
	Write_Command(0x9F);			// Activate Horizontal Scroll
	Delay(f);
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  停止滚动
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Deactivate_Scroll()
{
	Write_Command(0x9E);			// Deactivate Scrolling
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 淡入
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Fade_In()
{
unsigned int i;	

	Set_Display_On_Off(0x01);
	for(i=0;i<(Brightness+1);i++)
	{
		Set_Master_Current(i);
		uDelay(200);
		uDelay(200);
		uDelay(200);
	}
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  淡出
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Fade_Out()
{
unsigned int i;	

	for(i=(Brightness+1);i>0;i--)
	{
		Set_Master_Current(i-1);
		uDelay(200);
		uDelay(200);
		uDelay(200);
	}
	Set_Display_On_Off(0x00);
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  	睡眠模式
//		0x00,进入睡眠
//		0x01 退出睡眠
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Sleep(unsigned char a)
{
	switch(a)
	{
		case 0:
			Set_Display_On_Off(0x00);
			Set_Display_Mode(0x01);
			break;
		case 1:
			Set_Display_Mode(0x02);
			Set_Display_On_Off(0x01);
			break;
	}
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// 灰阶设置
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Set_Gray_Scale_Table()
{
	Write_Command(0xB8);
	Write_Data(0x02);			// Gray Scale Level 1
	Write_Data(0x03);			// Gray Scale Level 2
	Write_Data(0x04);			// Gray Scale Level 3
	Write_Data(0x05);			// Gray Scale Level 4
	Write_Data(0x06);			// Gray Scale Level 5
	Write_Data(0x07);			// Gray Scale Level 6
	Write_Data(0x08);			// Gray Scale Level 7
	Write_Data(0x09);			// Gray Scale Level 8
	Write_Data(0x0A);			// Gray Scale Level 9
	Write_Data(0x0B);			// Gray Scale Level 10
	Write_Data(0x0C);			// Gray Scale Level 11
	Write_Data(0x0D);			// Gray Scale Level 12
	Write_Data(0x0E);			// Gray Scale Level 13
	Write_Data(0x0F);			// Gray Scale Level 14
	Write_Data(0x10);			// Gray Scale Level 15
	Write_Data(0x11);			// Gray Scale Level 16
	Write_Data(0x12);			// Gray Scale Level 17
	Write_Data(0x13);			// Gray Scale Level 18
	Write_Data(0x15);			// Gray Scale Level 19
	Write_Data(0x17);			// Gray Scale Level 20
	Write_Data(0x19);			// Gray Scale Level 21
	Write_Data(0x1B);			// Gray Scale Level 22
	Write_Data(0x1D);			// Gray Scale Level 23
	Write_Data(0x1F);			// Gray Scale Level 24
	Write_Data(0x21);			// Gray Scale Level 25
	Write_Data(0x23);			// Gray Scale Level 26
	Write_Data(0x25);			// Gray Scale Level 27
	Write_Data(0x27);			// Gray Scale Level 28
	Write_Data(0x2A);			// Gray Scale Level 29
	Write_Data(0x2D);			// Gray Scale Level 30
	Write_Data(0x30);			// Gray Scale Level 31
	Write_Data(0x33);			// Gray Scale Level 32
	Write_Data(0x36);			// Gray Scale Level 33
	Write_Data(0x39);			// Gray Scale Level 34
	Write_Data(0x3C);			// Gray Scale Level 35
	Write_Data(0x3F);			// Gray Scale Level 36
	Write_Data(0x42);			// Gray Scale Level 37
	Write_Data(0x45);			// Gray Scale Level 38
	Write_Data(0x48);			// Gray Scale Level 39
	Write_Data(0x4C);			// Gray Scale Level 40
	Write_Data(0x50);			// Gray Scale Level 41
	Write_Data(0x54);			// Gray Scale Level 42
	Write_Data(0x58);			// Gray Scale Level 43
	Write_Data(0x5C);			// Gray Scale Level 44
	Write_Data(0x60);			// Gray Scale Level 45
	Write_Data(0x64);			// Gray Scale Level 46
	Write_Data(0x68);			// Gray Scale Level 47
	Write_Data(0x6C);			// Gray Scale Level 48
	Write_Data(0x70);			// Gray Scale Level 49
	Write_Data(0x74);			// Gray Scale Level 50
	Write_Data(0x78);			// Gray Scale Level 51
	Write_Data(0x7D);			// Gray Scale Level 52
	Write_Data(0x82);			// Gray Scale Level 53
	Write_Data(0x87);			// Gray Scale Level 54
	Write_Data(0x8C);			// Gray Scale Level 55
	Write_Data(0x91);			// Gray Scale Level 56
	Write_Data(0x96);			// Gray Scale Level 57
	Write_Data(0x9B);			// Gray Scale Level 58
	Write_Data(0xA0);			// Gray Scale Level 59
	Write_Data(0xA5);			// Gray Scale Level 60
	Write_Data(0xAA);			// Gray Scale Level 61
	Write_Data(0xAF);			// Gray Scale Level 62
	Write_Data(0xB4);			// Gray Scale Level 63
}

void Set_Linear_Gray_Scale_Table()
{
	Write_Command(0xB9);
}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//oled初始化
//在main()里面是要引入
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void OLED_Init()
{
	unsigned char i;
	RES=0;
	for(i=0;i<200;i++)
	{
		uDelay(200);
	}
	RES=1;
	Set_Command_Lock(0x12);
	Set_Command_Lock(0xB1);
	Set_Display_On_Off(0x00);	
	Set_Display_Clock(0xF1);	
	Set_Multiplex_Ratio(0x7F);	
	Set_Display_Offset(0x00);
	Set_Start_Line(0x00);	
	Set_Remap_Format(0x74);
	Set_GPIO(0x00);	
	Set_Function_Selection(0x01);	
	Set_VSL(0xA0);
	Set_Contrast_Color(0xC8,0x80,0xC8);	
	Set_Master_Current(Brightness);	
	Set_Gray_Scale_Table();		
	Set_Phase_Length(0x32);	
	Set_Precharge_Voltage(0x17);	
	Set_Display_Enhancement(0xA4);
	Set_Precharge_Period(0x01);	
	Set_VCOMH(0x05);	
	Set_Display_Mode(0x02);		
	Fill_RAM(0x00,0x00);	
	Set_Display_On_Off(0x01);
}
//一些画画的函数
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//函数功能：画矩形
//    a:开始列
//    b:结束列
//    c: 开始行
//    d:结束行
//    e:线的宽度
//    d:设颜色
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Draw_Rectangle(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e, int Colour_RGB)
{
unsigned char i,j;

	Set_Column_Address(a,b);
	Set_Row_Address(c,(c+e-1));
	Set_Write_RAM();
	for(i=0;i<(b-a+1);i++)
	{
		for(j=0;j<e;j++)
		{
	Write_Data(Colour_RGB >> 8); //写入填充颜色高字节
  Write_Data(Colour_RGB);  //写入填充颜色低字节
		}
	}

	Set_Column_Address((b-e+1),b);
	Set_Row_Address(c,d);
	Set_Write_RAM();
	for(i=0;i<(d-c+1);i++)
	{
		for(j=0;j<e;j++)
		{
		Write_Data(Colour_RGB >> 8); //写入填充颜色高字节
		Write_Data(Colour_RGB);  //写入填充颜色低字节
		}
	}

	Set_Column_Address(a,b);
	Set_Row_Address((d-e+1),d);
	Set_Write_RAM();
	for(i=0;i<(b-a+1);i++)
	{
		for(j=0;j<e;j++)
		{
		Write_Data(Colour_RGB >> 8); //写入填充颜色高字节
  Write_Data(Colour_RGB);  //写入填充颜色低字节
		}
	}

	Set_Column_Address(a,(a+e-1));
	Set_Row_Address(c,d);
	Set_Write_RAM();
	for(i=0;i<(d-c+1);i++)
	{
		for(j=0;j<e;j++)
		{
			Write_Data(Colour_RGB >> 8); //写入填充颜色高字节
			Write_Data(Colour_RGB);  //写入填充颜色低字节		
		}
	}
}
//***********************************************//
//画点的算法
//x确定x轴上坐标，y确定y轴上坐标
//***********************************************//
void Draw_Point(unsigned char x, unsigned char y, int Colour_RGB)
{
  Write_Command(0x15);  // 设置列地址
  Write_Data(x);    

  Write_Command(0x75);  // 设置行地址
  Write_Data(y);    

  Set_Write_RAM();  //使能MCU写RAM

  Write_Data(Colour_RGB >> 8); //写入填充颜色高字节
  Write_Data(Colour_RGB);  //写入填充颜色低字节
}
//**************************************************//
//x0，y0：圆心的坐标
//r为半径
//colur可采用16进制数构成的颜色
//time形成园的时间
//time_mode时间延迟的选择
//*************************************************//
void Draw_Circle(char x0,char y0,char r,int colour,char time,bit time_mode)
{
	int a,b;
	a=0;b=r;	  
	while(a<=b)
	{
		Draw_Point(x0-b,y0-a,colour);             //3           
		Draw_Point(x0+b,y0-a,colour);             //0           
		Draw_Point(x0-a,y0+b,colour);             //1                
		Draw_Point(x0-a,y0-b,colour);             //2             
		Draw_Point(x0+b,y0+a,colour);             //4               
		Draw_Point(x0+a,y0-b,colour);             //5
		Draw_Point(x0+a,y0+b,colour);             //6 
		Draw_Point(x0-b,y0+a,colour);             //7
		a++;
		if((a*a+b*b)>(r*r))//判断要画的点是否过远
		{
			b--;
		}
	 if(time_mode) Delay(time);
		else uDelay(time);
	}
}
//**********************************//
//画线
//x1,y1:起始点的坐标
//x2,y2:终点的坐标
//**********************************//
void Draw_Line(int x1,int y1,int x2,int y2,int color)
{
	int t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1;
	uRow=x1;//画线起点坐标
	uCol=y1;
	if(delta_x>0)incx=1; //设置单步方向 
	else if (delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;//水平线 
	else {incy=-1;delta_y=-delta_x;}
	if(delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		Draw_Point(uRow,uCol,color);//画点
		xerr+=delta_x;
		yerr+=delta_y;
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
/******************************************************************************
      函数说明：画正三角形
      入口数据：x,y   中心点坐标
                r   终止坐标
      返回值：  无
******************************************************************************/
void Draw_Triangle(int x,int y,int r,int color)
{
	Draw_Line(x,y-r,x-r,y,color);
	Draw_Line(x,y-r,x+r,y,color);
	Draw_Line(x+r,y,x-r,y,color);
}/**
  * @函数名       Display_Pattern
  * @功  能       显示图片
  * @参  数       *Pattern_Data：图片数组；Start_x：x方向起点；End_x：x方向终点；Start_y：y方向起点；End_y：y方向终点
  * @返回值       无
  */
void Display_Pattern(unsigned char *Pattern_Data, unsigned char Start_x, unsigned char End_x, unsigned char Start_y, unsigned char End_y)
{
	unsigned char *Data_Pointer;	//定义指针变量
	unsigned char i, j;		//定义变量

	Data_Pointer = Pattern_Data;	//获取数组首地址
	Set_Column_Address(Start_x, End_x);	//设置列范围
	Set_Row_Address(Start_y, End_y);	//设置行范围
	Set_Write_RAM();	//设置MCU写RAM

	for(i = 0; i < (End_y - Start_y + 1); i++)	//y方向(End_y - Start_y + 1)
	{
		for(j = 0; j < (End_x - Start_x + 1); j++)	//x方向(End_x - Start_x + 1)
		{
			Write_Data(*Data_Pointer);	//写入数据（一个点需要写入16位数据：RRRRRGGGGGGBBBBB）
			Data_Pointer++;
			Write_Data(*Data_Pointer);
			Data_Pointer++;
		}
	}
}
/**
  * @函数名       display_char
  * @功  能       指定坐标画一个字符（逐行式），字符大小固定为8*16
  * @参  数       x：列起始地址；y：行起始地址；Var_Char：写入的字符；Colour_RGB：填充颜色：RRRRRGGGGGGBBBBB
  * @返回值       无
  */
void Display_Char(unsigned char x, unsigned char y, unsigned char Var_Char, int Colour_RGB)
{
  unsigned char i, j; //定义变量
  unsigned char Var_Temp, x_Temp; //定义变量

  x_Temp = x; //获取x起始坐标
  for (i = 0; i < 16; i++)
  {
    Var_Temp = ACSII_Font[Var_Char - 0x20][i];  //获取字符在数组的偏移量
    for ( j = 0; j < 8; j++)
    {
      if (Var_Temp & 0x80)  //先画最高位的点，为1则画对应的颜色
        Draw_Point(x, y, Colour_RGB);
      //else
        //Draw_Point(x, y, 0x0000); //为0则黑色（都不亮），可作为背景色

      Var_Temp <<= 1; //移位，准备画下一个点
      x++;  //x坐标加1

      if((x - x_Temp) == 8)
      { 
        x = x_Temp; //x坐标回到起始位置
        y++;  //y坐标加1
        break;  //退出当前循环
      }
    }
  }
}


/**
  * @函数名       Display_String
  * @功  能       显示字符串
  * @参  数       x：列起始地址；y：行起始地址；*chr：显示的字符串；Colour_RGB：填充颜色：RRRRRGGGGGGBBBBB
  * @返回值       无
  */
void Display_String(unsigned char x, unsigned char y, unsigned char *chr, int Colour_RGB)
{
  unsigned char i = 0;  //定义变量

  while(chr[i] != '\0') //判断是否结束
  {
    Display_Char(x, y, chr[i], Colour_RGB); //显示字符
    x += 8; //x坐标加8（一个字符x方向占8个点，Y方向占16个点）
    i++;  //下一个字符
  }
}