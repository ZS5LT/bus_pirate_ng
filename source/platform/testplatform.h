

// development test platform

// SPI hardware (HW-SPI)
#define BPSPIPORT	SPI1
#define BPSPICLK	RCC_SPI1
#define BPSPIMISOPORT	GPIOA
#define BPSPIMOSIPORT	GPIOA
#define BPSPICSPORT	GPIOA
#define BPSPICLKPORT	GPIOA
#define BPSPIMISOPIN	GPIO6
#define BPSPIMOSIPIN	GPIO7
#define BPSPICSPIN	GPIO4
#define BPSPICLKPIN	GPIO5

// AUX
#define BPAUXPORT	GPIOC
#define BPAUXPIN	GPIO13

// ADC's
#define BPADC		ADC1
#define BPADCCLK	RCC_ADC1
#define BPADCCHAN	0		//pa0
#define BP3V3CHAN	0
#define BP5V0CHAN	0
#define BPVPUCHAN	0

// debug USART
#define DEBUGTXPORT	GPIOA
#define DEBUGTXPIN	GPIO_USART1_TX
#define DEBUGUSART	USART1
#define DEBUGUSARTCLK	RCC_USART1

// regular USART (HW-USART)
#define BPUSARTTXPORT	GPIOA
#define BPUSARTRXPORT	GPIOA
#define BPUSARTTXPIN	GPIO2
#define BPUSARTRXPIN	GPIO3
#define BPUSARTCLK	RCC_USART2
#define BPUSART		USART2

// hw-i2c
#define BPI2C		I2C2
#define BPI2CCLK	RCC_I2C2




// voltage regulators and pullupvoltages
#define BPPSUENPORT	GPIOC
#define BPPSUENPIN	GPIO13
#define BPVPUENPORT	GPIOC
#define BPVPUENPIN	GPIO13
#define BPVPU33ENPORT	GPIOC
#define BPVPU33ENPIN	GPIO13
#define BPVPU50ENPORT	GPIOC
#define BPVPU50ENPIN	GPIO13




