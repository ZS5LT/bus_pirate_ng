

#include <stdint.h>
#include <libopencm3/stm32/spi.h>
#include "buspirateNG.h"
#include "HWSPI.h"
#include "cdcacm.h"
#include "UI.h"
#include "LCDSPI.h"


uint32_t LCDSPI_send(uint32_t d)
{
	HD44780_write(1, d);

	return 0;
}

uint32_t LCDSPI_read(void)
{
	return 0;
}

void LCDSPI_macro(uint32_t macro)
{
	cdcprintf("-DUMMY1- macro(%08X)", macro);

	switch(macro)
	{
		case 0:		cdcprintf("No macros available");
				break;
		case 1:		HD44780_init();
				HD44780_initdisp();
				break;
		default:	cdcprintf("Macro not defined");
				modeConfig.error=1;
	}

}

void LCDSPI_setup(void)
{
}

void LCDSPI_setup_exc(void)
{
	HD44780_init();
}

void LCDSPI_cleanup(void)
{
	HD44760_cleanup();
}

void LCDSPI_pins(void)
{
	cdcprintf("pin1\tpin2\tpin3\tpin4");
}

void LCDSPI_settings(void)
{
	cdcprintf("DUMMY ()=()");
}

// hd44780 driver

#define HCT595_LCD_LED		0b00000001
#define HCT595_LCD_RS		0b00000010
#define HCT595_LCD_RW		0b00000100
#define HCT595_LCD_EN		0b00001000
#define HCT595_LCD_D4		0b00010000
#define HCT595_LCD_D5		0b00100000
#define HCT595_LCD_D6		0b01000000
#define HCT595_LCD_D7		0b10000000

#define CMD_CLEARDISPLAY        0b00000001 //82us-1.64ms

#define CMD_RETURNHOME          0b00000010 //40us-1.64ms

#define CMD_ENTRYMODESET        0b00000100 //40us
#define INCREMENT 		0b10
#define DECREMENT 		0b00
#define DISPLAYSHIFTON 		0b1
#define DISPLAYSHIFTOFF 	0

#define CMD_DISPLAYCONTROL      0b00001000 //40us
#define DISPLAYON 		0b100
#define DISPLAYOFF 		0
#define CURSERON 		0b10
#define CURSEROFF 		0
//#define BLINKON 		0b1
//#define BLINKOFF 		0

#define CMD_CURSERDISPLAYSHIFT 0b00010000 //40us
#define DISPLAYSHIFT		0b1000
#define CURSERMOVE 		0
#define SHIFTRIGHT 		0b100
#define SHIFTLEFT 		0

#define CMD_FUNCTIONSET         0b00100000 //40us
#define DATAWIDTH8 		0b10000
#define DATAWIDTH4 		0
#define DISPLAYLINES2 		0b1000
#define DISPLAYLINES1 		0
#define FONT5X10 		0b100
#define FONT5X7 		0


void HD44780_init(void)
{
	// setup SPI
	HWSPI_setcpol(1<<1);
	HWSPI_setcpha(1);
	HWSPI_setbr(5<<3);
	HWSPI_setdff(SPI_CR1_DFF_8BIT);
	HWSPI_setlsbfirst(SPI_CR1_MSBFIRST);
	HWSPI_setcsidle(1);
	HWSPI_setup_exc();

	cdcprintf("This mode uses an external adapter");
}

void HD44760_cleanup(void)
{
	HWSPI_cleanup();
}

void HD44780_initdisp(void)
{
	HWSPI_xfer(0x00);
	HWSPI_setcs(1);
	HWSPI_setcs(0);
	delayms(15);
	HD44780_writenibble(0, 0x03);
	delayms(15);
	HD44780_writenibble(0, 0x03);
	delayms(15);
	HD44780_writenibble(0, 0x03);
	delayms(15);
	HD44780_writenibble(0, 0x02);
	delayms(15);
	
	HD44780_write(0, 0x28);
	delayms(15);
	HD44780_write(0, 0x08);
	delayms(15);
	HD44780_write(0, 0x01);
	delayms(15);
	HD44780_write(0, 0x0f);
	delayms(15);

}

void HD44780_write(uint8_t rs, uint8_t d)
{
	HD44780_writenibble(rs, (d>>4));
	HD44780_writenibble(rs, (d&0x0F));
}	

void HD44780_writenibble(uint8_t rs, uint8_t d)
{
	d&=0x0F;
	d<<=4;

	if(rs) d|=HCT595_LCD_RS;

	HWSPI_xfer(d);
	HWSPI_setcs(1);
	HWSPI_setcs(0);
	HWSPI_xfer(d|HCT595_LCD_EN);
	HWSPI_setcs(1);
	HWSPI_setcs(0);
	HWSPI_xfer(d);
	HWSPI_setcs(1);
	HWSPI_setcs(0);

}



