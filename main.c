#include "oled.h"
/*
 �û����������main()������ʾ�����򣬸õ�Ƭ���ĵײ��ļ���oled.c�а��������ŵĶ�����޸���oled.c

*/
void main()
{
	OLED_Init();
	Display_String(1,1,"Welcome to MCU",0xf0f0);
	Display_String(1,17,"2020,2,3",0x0ff00);
	while(1);
}
