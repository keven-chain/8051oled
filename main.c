#include "oled.h"
/*
 用户代码的区域，main()里面是示例程序，该单片机的底层文件在oled.c中包含，引脚的定义和修改在oled.c

*/
void main()
{
	OLED_Init();
	Display_String(1,1,"Welcome to MCU",0xf0f0);
	Display_String(1,17,"2020,2,3",0x0ff00);
	while(1);
}
