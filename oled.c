#include "oled.h"
#include "STC8.h"
#include "font.h"
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
//���Ŷ���
sbit SCLK=	P2^4;
sbit SDIN=	P2^5;	
sbit RES=	P3^4	;	
sbit CS	=P3^5		;
sbit DC=	P3^6	;	
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// �ӳٺ���
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
//�������ܣ�д����
//�޷���ֵ
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
//��ʼ����һЩ����
//���ô���
//���ùܣ�����Ҫ����ײ�
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
//  ��ֱ����
//
//    a: ��������
//       "0x00" (Upward)
//       "0x01" (Downward)
//    b: ��������
//    c:����ʱ����
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
// ˮƽ����
//
//    a: ��������
//       "0x00" (Rightward)
//       "0x01" (Leftward)
//    b: �����������
//    c����ʼ��
//    d: ��ʼ��
//    e: ����Ƶ��
//    f: �ӳ�
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
//  ֹͣ����
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Deactivate_Scroll()
{
	Write_Command(0x9E);			// Deactivate Scrolling
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// ����
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
//  ����
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
//  	˯��ģʽ
//		0x00,����˯��
//		0x01 �˳�˯��
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
// �ҽ�����
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
//oled��ʼ��
//��main()������Ҫ����
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
//һЩ�����ĺ���
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//�������ܣ�������
//    a:��ʼ��
//    b:������
//    c: ��ʼ��
//    d:������
//    e:�ߵĿ��
//    d:����ɫ
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
	Write_Data(Colour_RGB >> 8); //д�������ɫ���ֽ�
  Write_Data(Colour_RGB);  //д�������ɫ���ֽ�
		}
	}

	Set_Column_Address((b-e+1),b);
	Set_Row_Address(c,d);
	Set_Write_RAM();
	for(i=0;i<(d-c+1);i++)
	{
		for(j=0;j<e;j++)
		{
		Write_Data(Colour_RGB >> 8); //д�������ɫ���ֽ�
		Write_Data(Colour_RGB);  //д�������ɫ���ֽ�
		}
	}

	Set_Column_Address(a,b);
	Set_Row_Address((d-e+1),d);
	Set_Write_RAM();
	for(i=0;i<(b-a+1);i++)
	{
		for(j=0;j<e;j++)
		{
		Write_Data(Colour_RGB >> 8); //д�������ɫ���ֽ�
  Write_Data(Colour_RGB);  //д�������ɫ���ֽ�
		}
	}

	Set_Column_Address(a,(a+e-1));
	Set_Row_Address(c,d);
	Set_Write_RAM();
	for(i=0;i<(d-c+1);i++)
	{
		for(j=0;j<e;j++)
		{
			Write_Data(Colour_RGB >> 8); //д�������ɫ���ֽ�
			Write_Data(Colour_RGB);  //д�������ɫ���ֽ�		
		}
	}
}
//***********************************************//
//������㷨
//xȷ��x�������꣬yȷ��y��������
//***********************************************//
void Draw_Point(unsigned char x, unsigned char y, int Colour_RGB)
{
  Write_Command(0x15);  // �����е�ַ
  Write_Data(x);    

  Write_Command(0x75);  // �����е�ַ
  Write_Data(y);    

  Set_Write_RAM();  //ʹ��MCUдRAM

  Write_Data(Colour_RGB >> 8); //д�������ɫ���ֽ�
  Write_Data(Colour_RGB);  //д�������ɫ���ֽ�
}
//**************************************************//
//x0��y0��Բ�ĵ�����
//rΪ�뾶
//colur�ɲ���16���������ɵ���ɫ
//time�γ�԰��ʱ��
//time_modeʱ���ӳٵ�ѡ��
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
		if((a*a+b*b)>(r*r))//�ж�Ҫ���ĵ��Ƿ��Զ
		{
			b--;
		}
	 if(time_mode) Delay(time);
		else uDelay(time);
	}
}
//**********************************//
//����
//x1,y1:��ʼ�������
//x2,y2:�յ������
//**********************************//
void Draw_Line(int x1,int y1,int x2,int y2,int color)
{
	int t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1;
	uRow=x1;//�����������
	uCol=y1;
	if(delta_x>0)incx=1; //���õ������� 
	else if (delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;//ˮƽ�� 
	else {incy=-1;delta_y=-delta_x;}
	if(delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		Draw_Point(uRow,uCol,color);//����
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
      ����˵��������������
      ������ݣ�x,y   ���ĵ�����
                r   ��ֹ����
      ����ֵ��  ��
******************************************************************************/
void Draw_Triangle(int x,int y,int r,int color)
{
	Draw_Line(x,y-r,x-r,y,color);
	Draw_Line(x,y-r,x+r,y,color);
	Draw_Line(x+r,y,x-r,y,color);
}/**
  * @������       Display_Pattern
  * @��  ��       ��ʾͼƬ
  * @��  ��       *Pattern_Data��ͼƬ���飻Start_x��x������㣻End_x��x�����յ㣻Start_y��y������㣻End_y��y�����յ�
  * @����ֵ       ��
  */
void Display_Pattern(unsigned char *Pattern_Data, unsigned char Start_x, unsigned char End_x, unsigned char Start_y, unsigned char End_y)
{
	unsigned char *Data_Pointer;	//����ָ�����
	unsigned char i, j;		//�������

	Data_Pointer = Pattern_Data;	//��ȡ�����׵�ַ
	Set_Column_Address(Start_x, End_x);	//�����з�Χ
	Set_Row_Address(Start_y, End_y);	//�����з�Χ
	Set_Write_RAM();	//����MCUдRAM

	for(i = 0; i < (End_y - Start_y + 1); i++)	//y����(End_y - Start_y + 1)
	{
		for(j = 0; j < (End_x - Start_x + 1); j++)	//x����(End_x - Start_x + 1)
		{
			Write_Data(*Data_Pointer);	//д�����ݣ�һ������Ҫд��16λ���ݣ�RRRRRGGGGGGBBBBB��
			Data_Pointer++;
			Write_Data(*Data_Pointer);
			Data_Pointer++;
		}
	}
}
/**
  * @������       display_char
  * @��  ��       ָ�����껭һ���ַ�������ʽ�����ַ���С�̶�Ϊ8*16
  * @��  ��       x������ʼ��ַ��y������ʼ��ַ��Var_Char��д����ַ���Colour_RGB�������ɫ��RRRRRGGGGGGBBBBB
  * @����ֵ       ��
  */
void Display_Char(unsigned char x, unsigned char y, unsigned char Var_Char, int Colour_RGB)
{
  unsigned char i, j; //�������
  unsigned char Var_Temp, x_Temp; //�������

  x_Temp = x; //��ȡx��ʼ����
  for (i = 0; i < 16; i++)
  {
    Var_Temp = ACSII_Font[Var_Char - 0x20][i];  //��ȡ�ַ��������ƫ����
    for ( j = 0; j < 8; j++)
    {
      if (Var_Temp & 0x80)  //�Ȼ����λ�ĵ㣬Ϊ1�򻭶�Ӧ����ɫ
        Draw_Point(x, y, Colour_RGB);
      //else
        //Draw_Point(x, y, 0x0000); //Ϊ0���ɫ����������������Ϊ����ɫ

      Var_Temp <<= 1; //��λ��׼������һ����
      x++;  //x�����1

      if((x - x_Temp) == 8)
      { 
        x = x_Temp; //x����ص���ʼλ��
        y++;  //y�����1
        break;  //�˳���ǰѭ��
      }
    }
  }
}


/**
  * @������       Display_String
  * @��  ��       ��ʾ�ַ���
  * @��  ��       x������ʼ��ַ��y������ʼ��ַ��*chr����ʾ���ַ�����Colour_RGB�������ɫ��RRRRRGGGGGGBBBBB
  * @����ֵ       ��
  */
void Display_String(unsigned char x, unsigned char y, unsigned char *chr, int Colour_RGB)
{
  unsigned char i = 0;  //�������

  while(chr[i] != '\0') //�ж��Ƿ����
  {
    Display_Char(x, y, chr[i], Colour_RGB); //��ʾ�ַ�
    x += 8; //x�����8��һ���ַ�x����ռ8���㣬Y����ռ16���㣩
    i++;  //��һ���ַ�
  }
}