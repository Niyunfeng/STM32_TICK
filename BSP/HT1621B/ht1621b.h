#ifndef _HT1621B_H
#define _HT1621B_H

#include "pub.h"

void GPIO_LcdInit(void);					
void lcd_init(void);						
void lcd_show_num(unsigned char data[]);	
void lcd_clr(void);							
void lcd_test(void);						

#endif
