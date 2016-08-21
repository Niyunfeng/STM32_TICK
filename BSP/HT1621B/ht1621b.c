#include <stdio.h>
#include "ht1621b.h"
#include "delay.h"

#define HT1621_CS	GPIO_Pin_12
#define HT1621_WR	GPIO_Pin_13
#define HT1621_DAT	GPIO_Pin_14


#define  DAT   1	
#define  COM   0	

void delay(unsigned int MS);					
void lcd_show_num(unsigned char data[]);
void lcd_clr(void);


//??HT1621 4COM?????,???COM0,?4bit?SEG0,?4bit?SEG1
		//?????	
//  _
// |_|   ???8???? 1--f 2--e 3--d 4--c 5--g 6--b 7--a 
// |_|  
//  
//		
//unsigned char NUM[]={
//	0x60,0x60,0x60,0xe0,0x60,0xe0,0x60,		// 0x60 -- 1
//	0x3e,0xbe,0xbe,0x3e,0xbe,0xbe,0xbe,		// 0x3e -- 2
//	0x7a,0x7a,0xfa,0xfa,0xfa,0xfa,0xfa,		// 0x7a -- 3
//	0xe3,0x63,0x63,0xe3,0xe3,0xe3,0x63,		// 0x63 -- 4
//	0xdb,0x5b,0xdb,0xdb,0xdb,0x5b,0xdb,		// 0x5b -- 5
//	0xdf,0xdf,0xdf,0xdf,0xdf,0x5f,0xdf,		// 0x5f -- 6
//	0x70,0x70,0x70,0xf0,0x70,0xf0,0xf0,		// 0x70 -- 7
//	0xff,0xff,0xff,0xff,0xff,0xff,0xff,		// 0x7f -- 8
//	0xfb,0x7b,0xfb,0xfb,0xfb,0xfb,0xfb,		// 0x7b -- 9
//	0xfd,0xfd,0xfd,0xfd,0x7d,0xfd,0xfd,		// 0x7d -- 0
//};

/*
* fq
* LCD GPIO ???
* ??:void
* ??:void
* ?? GPIOB 4,5,6,7 ????lcd CS RD(????) WR DAT
*/
void GPIO_LcdInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct_LCD;		//GIPOA4~7

	GPIO_InitStruct_LCD.GPIO_Pin 	= GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitStruct_LCD.GPIO_Mode 	= GPIO_Mode_Out_PP;
	GPIO_InitStruct_LCD.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct_LCD);
}

/*
* fq
* LCD ????
* ??:MODE :COM(????) DAT(????)
* ??:void
*
*/

void write_mode(unsigned char MODE)	//????,??or??
{
	GPIO_ResetBits(GPIOB,HT1621_WR);								//	RW = 0;
	Delay_Ms(10);
	GPIO_SetBits(GPIOB,HT1621_DAT);									//	DA = 1;
	GPIO_SetBits(GPIOB,HT1621_WR);									//	RW = 1;
	Delay_Ms(10);
	
	GPIO_ResetBits(GPIOB,HT1621_WR);								//	RW = 0;
	Delay_Ms(10);
	GPIO_ResetBits(GPIOB,HT1621_DAT);								//	DA = 0;
	GPIO_SetBits(GPIOB,HT1621_WR);									//	RW = 1;
	Delay_Ms(10);
	
	GPIO_ResetBits(GPIOB,HT1621_WR);								//	RW = 0;
	Delay_Ms(10);

	if(0==MODE)
	{
		GPIO_ResetBits(GPIOB,HT1621_DAT);							//	DA = 0;
	}
	else
	{
		GPIO_SetBits(GPIOB,HT1621_DAT);								//	DA = 1;
	}
	Delay_Ms(10);
	GPIO_SetBits(GPIOB,HT1621_WR);									//	RW = 1;
	Delay_Ms(10);
}

/*
* fq
* LCD ??????
* ??:cbyte ,?????
* ??:void
*
*/

void write_command(unsigned char Cbyte)								//?????9bit,??1bit??
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		GPIO_ResetBits(GPIOB,HT1621_WR);							//	RW = 0;
		Delay_Ms(10);

		if((Cbyte>>(7-i)) & 0x01)
		{
			GPIO_SetBits(GPIOB,HT1621_DAT);							//	DA = 1;
		}
		else
		{
			GPIO_ResetBits(GPIOB,HT1621_DAT);						//	DA = 0;
		}
		Delay_Ms(10);
		GPIO_SetBits(GPIOB,HT1621_WR);								//	RW = 1;
		Delay_Ms(10);
	}
	GPIO_ResetBits(GPIOB,HT1621_WR);								//	RW = 0;
	Delay_Ms(10);
	GPIO_ResetBits(GPIOB,HT1621_DAT);								//	DA = 0;	?9bit,???,??????
	GPIO_SetBits(GPIOB,HT1621_WR);									//	RW = 1;
	Delay_Ms(10);
}

/*
* fq
* LCD ??????
* ??:cbyte ,??
* ??:void
*
*/
void write_address(unsigned char Abyte)								//???6bit
{
	unsigned char i;
	Abyte = Abyte<<2;
	for(i=0;i<6;i++)
	{
		GPIO_ResetBits(GPIOB,HT1621_WR);							//	RW = 0;
		Delay_Ms(10);

		if((Abyte>>(7-i)) & 0x01)
		{
			GPIO_SetBits(GPIOB,HT1621_DAT);							//	DA = 1;
		}
		else
		{
			GPIO_ResetBits(GPIOB,HT1621_DAT);						//	DA = 0;
		}
		Delay_Ms(10);
		GPIO_SetBits(GPIOB,HT1621_WR);								//	RW = 1;
		Delay_Ms(10);
	}
}
/*
* fq
* LCD ??????
* ??:Dbyte ,??
* ??:void
*
*/
void write_data(unsigned char Dbyte)	//???
{
	int i;
	for(i=0;i<8;i++)
	{
		GPIO_ResetBits(GPIOB,HT1621_WR);							//	RW = 0;
		Delay_Ms(10);

		if((Dbyte>>(7-i)) & 0x01)
		{
			GPIO_SetBits(GPIOB,HT1621_DAT);							//	DA = 1;
		}
		else
		{
			GPIO_ResetBits(GPIOB,HT1621_DAT);						//	DA = 0;
		}
		Delay_Ms(10);
		GPIO_SetBits(GPIOB,HT1621_WR);								//	RW = 1;
		Delay_Ms(10);
	}
}

/*
* fq
* LCD ???,?lcd????????
* ??:void
* ??:void
*
*/
void lcd_init( void )												//???
{
	GPIO_ResetBits(GPIOB,HT1621_CS);								//CS = 0;
	write_mode(COM);		//????
	write_command(0x01);	//Enable System
	write_command(0x03);	//Enable Bias
	write_command(0x04);	//Disable Timer
	write_command(0x05);	//Disable WDT
	write_command(0x08);	//Tone OFF
	write_command(0x18);	//on-chip RC??
	write_command(0x29);	//1/4Duty 1/3Bias
	write_command(0x80);	//Disable IRQ
	write_command(0x40);	//Tone Frequency 4kHZ
	write_command(0xE3);	//Normal Mode
	GPIO_SetBits(GPIOB,HT1621_CS);									//CS = 1;
}
/*
* fq
* LCD ??????
* ??:??????,n ??????
* ??:void
*
*/
void full_ram(unsigned char *puts,unsigned char n)
{
	unsigned char i;
	
	GPIO_ResetBits(GPIOB,HT1621_CS);								// CS = 0;
	write_mode(DAT);
	write_address(0);
	for(i=0;i<7;i++)
	{
		write_data(puts[7*n+i]);
		Delay_Ms(4);
	}	
	GPIO_SetBits(GPIOB,HT1621_CS);									//CS = 1;
}
/*
* fq
* LCD ??????
* ??:puts ,??????,???7,??????,???????;???????,?: "12234567"
* ??:void
*
*/
void lcd_show_data(unsigned char *puts)
{
	unsigned char i ;
	
	GPIO_ResetBits(GPIOB,HT1621_CS);								// CS = 0;
	write_mode(DAT);
	write_address(0);
	
	for(i=0;i<7;i++)
	{
		write_data(puts[i]);
		Delay_Ms(4);
	}
	GPIO_SetBits(GPIOB,HT1621_CS);									//CS = 1;
}

/*
* fq
* LCD ????????
* ??:times
* ??:void
*
*/
void lcd_Delay_Ms(int times)
{
	int i;
	for(i=0;i<20*times;i++) ;
}

/*
* fq
* LCD ????
* ??:times
* ??:void
*
*/

void lcd_clr(void)
{
	unsigned char i;
	
	GPIO_ResetBits(GPIOB,HT1621_CS);								// CS = 0;
	write_mode(DAT);
	write_address(0);
	
	for(i=0;i<7;i++)
	{
		write_data(0x00);
	}	
	GPIO_SetBits(GPIOB,HT1621_CS);									//CS = 1;
}

/*
* fq
* ???????
* ??:void
* ??:void
*
*/
#if 0
	unsigned char HT1621[]={
	
		0x81,0x01,0x01,0x01,0x01,0x01,0x01,
		0x02,0x02,0x02,0x02,0x82,0x02,0x02,
		0x04,0x84,0x04,0x04,0x04,0x04,0x04,
		0x08,0x08,0x88,0x08,0x08,0x08,0x08,
		0x10,0x10,0x10,0x10,0x10,0x10,0x90,
		0x20,0x20,0x20,0x20,0x20,0xa0,0x20,
		0x40,0x40,0x40,0xc0,0x40,0x40,0x40,
		};
	
void test_line(void)
{
	int i ;
	for(i=0;i<7;i++)
	{
		full_ram(HT1621,i);
		lcd_Delay_Ms(1000000);
	}
	GPIO_ResetBits(GPIOB,HT1621_CS);								// CS = 0;

	write_mode(COM);
	GPIO_SetBits(GPIOB,HT1621_CS);									//CS = 1;
}	
#endif

/*
* fq
* LCD ??????,????
* ??:data ,??????,???7,??????,???????;???????,?: "12234567"
* ??:void
*
*/
void lcd_show_num(unsigned char data[])
{
	char i = 0 ;
	unsigned char show_buf[7];
	
	for(i=0;i<7;i++)												//???????
	{
		switch(data[i])
		{
			case '0':
					show_buf[6-i] = 0x7d;
					break;
			case '1':
					show_buf[6-i] = 0x60;
					break;
			case '2':
					show_buf[6-i] = 0x3e;
					break;
			case '3':
					show_buf[6-i] = 0x7a;
					break;
			case '4':
					show_buf[6-i] = 0x63;
					break;
			case '5':
					show_buf[6-i] = 0x5b;
					break;
			case '6':
					show_buf[6-i] = 0x5f;
					break;
			case '7':
					show_buf[6-i] = 0x70;
					break;
			case '8':
					show_buf[6-i] = 0x7f;
					break;
			case '9':
					show_buf[6-i] = 0x7b;
					break;
		}
	}
	switch(data[7])
	{
		case '0':
				show_buf[0] += 0x80;
				show_buf[1] += 0x80;
				show_buf[2] += 0x80;
				show_buf[3] += 0x80;
				show_buf[5] += 0x80;
				show_buf[6] += 0x80;
				break;
		case '1':
				show_buf[3] += 0x80;
				show_buf[5] += 0x80;
				break;
		case '2':
				show_buf[1] += 0x80;
				show_buf[2] += 0x80;
				show_buf[4] += 0x80;
				show_buf[5] += 0x80;
				show_buf[6] += 0x80;
				break;
		case '3':
				show_buf[2] += 0x80;
				show_buf[3] += 0x80;
				show_buf[4] += 0x80;
				show_buf[5] += 0x80;
				show_buf[6] += 0x80;
				break;
		case '4':
				show_buf[0] += 0x80;
				show_buf[3] += 0x80;
				show_buf[4] += 0x80;
				show_buf[5] += 0x80;
				break;
		case '5':
				show_buf[0] += 0x80;
				show_buf[2] += 0x80;
				show_buf[3] += 0x80;
				show_buf[4] += 0x80;
				show_buf[6] += 0x80;
				break;
		case '6':
				show_buf[0] += 0x80;
				show_buf[1] += 0x80;
				show_buf[2] += 0x80;
				show_buf[3] += 0x80;
				show_buf[4] += 0x80;
				show_buf[6] += 0x80;
				break;
		case '7':
				show_buf[3] += 0x80;
				show_buf[5] += 0x80;
				show_buf[6] += 0x80;
				break;
		case '8':
				show_buf[0] += 0x80;
				show_buf[1] += 0x80;
				show_buf[2] += 0x80;
				show_buf[3] += 0x80;
				show_buf[4] += 0x80;			
				show_buf[5] += 0x80;
				show_buf[6] += 0x80;
				break;
		case '9':
				show_buf[0] += 0x80;
				show_buf[2] += 0x80;
				show_buf[3] += 0x80;
				show_buf[4] += 0x80;			
				show_buf[5] += 0x80;
				show_buf[6] += 0x80;
				break;	
	}	
	lcd_show_data(show_buf);
}

/*
* fq
* LCD ?????
* ??:void
* ??:void
*
*/
void lcd_test(void)
{
	Delay_Ms(20);
    GPIO_LcdInit();
	lcd_init();

	while(1)
	{	
        write_data(1);
		lcd_show_num("12345678");
		lcd_Delay_Ms(2000000);

		lcd_show_num("23456789");
		lcd_Delay_Ms(2000000);		

		lcd_show_num("34567890");
		lcd_Delay_Ms(2000000);

		lcd_show_num("45678901");
		lcd_Delay_Ms(2000000);

		lcd_show_num("56789012");
		lcd_Delay_Ms(2000000);

		lcd_show_num("67890123");
		lcd_Delay_Ms(2000000);

		lcd_show_num("78901234");
		lcd_Delay_Ms(2000000);

		lcd_show_num("89012345");
		lcd_Delay_Ms(2000000);

		lcd_show_num("90123456");
		lcd_Delay_Ms(2000000);

		lcd_show_num("01234567");
		lcd_Delay_Ms(2000000);

 		lcd_clr();
		lcd_Delay_Ms(2000000);	
	}
}

/***************************************************end file*************************************************/
