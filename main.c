#include "oled.h"
int i;
/*
 �û����������main()������ʾ�����򣬸õ�Ƭ���ĵײ��ļ���oled.c�а��������ŵĶ�����޸���oled.c

*/
void main()
{
	OLED_Init();
	Draw_Circle(64,64,50,0xfff0,100,0);
	for(i=0;i<30;i++)
	{
		Draw_Circle(64,64,50-i+1,0x0000,20,0);
		Draw_Circle(64,64,50-i,0xff00,20,0);
	}
	for(i=0;i<=40;i++)
	{
		Draw_Circle(64+i-1,64,21,0x0000,1,0);
		Draw_Circle(64+i,64,21,0xff00,1,0);
		uDelay(300);
	}
	for(i=0;i<=40;i++)
	{
		Draw_Circle(104-i+1,64,21,0x0000,1,0);
		Draw_Circle(104-i,64,21,0xff00,1,0);
		uDelay(255);
	}
	for(i=0;i<=40;i++)
	{
		Draw_Circle(64,64,20+i-1,0x0000,1,0);
		Draw_Circle(64,64,20+i,0xff00+i*2,1,0);
		uDelay(255);
	}
	for(i=0;i<30;i++)
	{
		Draw_Circle(64,64,60-i+1,0x0000,20,0);
		Draw_Circle(64,64,60-i,0xff00,20,0);
	}
	while(1);
}
