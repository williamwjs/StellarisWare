#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "GPIODriverConfigure.h"

void GPIOInitial(void)
{	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);					//UART0
  	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);  					//KEY RIGHT | KEY LEFT
	//SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);					//UART1-RS232
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);					//KEY PRESS | KEY UP
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);					//KEY DOWN  | LED1 | LED0
		
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinConfigure(GPIO_PB2_I2C0SCL);
	GPIOPinConfigure(GPIO_PB3_I2C0SDA);
	//GPIOPinConfigure(GPIO_PD0_U1RX);
	//GPIOPinConfigure(GPIO_PD1_U1TX);
	GPIOPinConfigure(GPIO_PF2_LED1);
	GPIOPinConfigure(GPIO_PF3_LED0);
	
	GPIOPinTypeGPIOOutput(LED0_BASE,LED0_PIN);						//Set LED0
	GPIOPinTypeGPIOOutput(LED1_BASE,LED1_PIN);						//Set LED1
	LEDOff(LED_ALL);

	GPIOPinTypeGPIOInput(KEY_PRESS_BASE, KEY_PRESS_PIN);			//Set Key Press
	GPIOPinTypeGPIOInput(KEY_LEFT_BASE,  KEY_LEFT_PIN);				//Set Key Left
	GPIOPinTypeGPIOInput(KEY_RIGHT_BASE, KEY_RIGHT_PIN);			//Set Key Right
	GPIOPinTypeGPIOInput(KEY_UP_BASE,    KEY_UP_PIN);				//Set Key Up
	GPIOPinTypeGPIOInput(KEY_DOWN_BASE,  KEY_DOWN_PIN);				//Set Key Down

	GPIOPinTypeUART(UART0_PIN_BASE, UART0RX_PIN | UART0TX_PIN);		//Set UART0
	//GPIOPinTypeUART(UART1_PIN_BASE, UART1RX_PIN | UART1TX_PIN);	//Set UART1-RS232
	
	GPIOPinTypeI2C(I2C0_PIN_BASE, I2C0SCL_PIN | I2C0SDA_PIN);		//Set I2C0

	//�ж�����
	/*
	GPIOIntTypeSet(KEY_PRESS_BASE,KEY_PRESS_PIN,GPIO_FALLING_EDGE);	//Press�ж�
	GPIOPinIntEnable(KEY_PRESS_BASE,KEY_PRESS_PIN);
	
	GPIOIntTypeSet(KEY_LEFT_BASE,KEY_LEFT_PIN,GPIO_FALLING_EDGE);	//Left�ж�
	GPIOPinIntEnable(KEY_LEFT_BASE, KEY_LEFT_PIN);
	GPIOIntTypeSet(KEY_RIGHT_BASE,KEY_RIGHT_PIN,GPIO_FALLING_EDGE);	//Right�ж�
	GPIOPinIntEnable(KEY_RIGHT_BASE,KEY_RIGHT_PIN);	
	GPIOIntTypeSet(KEY_UP_BASE,KEY_UP_PIN,GPIO_FALLING_EDGE);		//Up�ж�
	GPIOPinIntEnable(KEY_UP_BASE,KEY_UP_PIN);	
	GPIOIntTypeSet(KEY_DOWN_BASE,KEY_DOWN_PIN,GPIO_FALLING_EDGE);	//Down�ж�
	GPIOPinIntEnable(KEY_DOWN_BASE,KEY_DOWN_PIN);
	
	IntEnable(INT_GPIOE);											//KEY_PRESS | KEY_UP INTS
	IntEnable(INT_GPIOB);											//KEY_LEFT | KEY_RIGHT INTS
	IntEnable(INT_GPIOF);											//KEY_DOWN INT
	*/
}

void LEDOn(unsigned char LEDNum)
{
	switch (LEDNum)
	{
		case	LED_0:	HWREG(LED0_BASE+GPIO_O_DATA+(LED0_PIN<<2))=~LED0_PIN;break;
		case	LED_1:	HWREG(LED1_BASE+GPIO_O_DATA+(LED1_PIN<<2))=~LED1_PIN;break;
		case	LED_ALL:
		{
			HWREG(LED0_BASE+GPIO_O_DATA+(LED0_PIN<<2))=~LED0_PIN;
			HWREG(LED1_BASE+GPIO_O_DATA+(LED1_PIN<<2))=~LED1_PIN;
			break;
		}
		default:	break;
	}
}

void LEDOff(unsigned char LEDNum)
{
	switch (LEDNum)
	{
		case	LED_0:	HWREG(LED0_BASE+GPIO_O_DATA+(LED0_PIN<<2))=LED0_PIN;break;
		case	LED_1:	HWREG(LED1_BASE+GPIO_O_DATA+(LED1_PIN<<2))=LED1_PIN;break;
		case	LED_ALL:
		{
			HWREG(LED0_BASE+GPIO_O_DATA+(LED0_PIN<<2))=LED0_PIN;
			HWREG(LED1_BASE+GPIO_O_DATA+(LED1_PIN<<2))=LED1_PIN;
			break;
		}
		default:	break;
	}
}

void LEDOverturn(unsigned char LEDNum)
{
	switch (LEDNum)
	{
		case	LED_0:	HWREG(LED0_BASE+GPIO_O_DATA+(LED0_PIN<<2)) =
						~HWREG(LED0_BASE+GPIO_O_DATA+(LED0_PIN<<2));
						break;
		case	LED_1:	HWREG(LED1_BASE+GPIO_O_DATA+(LED1_PIN<<2)) =
						~HWREG(LED1_BASE+GPIO_O_DATA+(LED1_PIN<<2));
						break;
		case	LED_ALL:
		{
			HWREG(LED0_BASE+GPIO_O_DATA+(LED0_PIN<<2)) =
			~HWREG(LED0_BASE+GPIO_O_DATA+(LED0_PIN<<2));
			HWREG(LED1_BASE+GPIO_O_DATA+(LED1_PIN<<2)) =
			~HWREG(LED1_BASE+GPIO_O_DATA+(LED1_PIN<<2));
			break;
		}
		default:	break;
	}
}	

unsigned char GetKeyNumber(void)
{
	if (!HWREG(KEY_PRESS_BASE+GPIO_O_DATA+(KEY_PRESS_PIN<<2)))	return KEY_PRESS;
	if (!HWREG(KEY_LEFT_BASE+GPIO_O_DATA+(KEY_LEFT_PIN<<2)))	return KEY_LEFT;
	if (!HWREG(KEY_RIGHT_BASE+GPIO_O_DATA+(KEY_RIGHT_PIN<<2)))	return KEY_RIGHT;
	if (!HWREG(KEY_UP_BASE+GPIO_O_DATA+(KEY_UP_PIN<<2)))		return KEY_UP;
	if (!HWREG(KEY_DOWN_BASE+GPIO_O_DATA+(KEY_DOWN_PIN<<2)))	return KEY_DOWN;
	return 0;
}

unsigned char I2C0PullUpTest(void)
{
/****************************Put your code here!!************************************/
	GPIOPinTypeGPIOInput(I2C0_PIN_BASE, I2C0SCL_PIN | I2C0SDA_PIN);	  	//����I2C0�õ�����������ΪGPIO����ģʽ
	//����������������Ϊ����������ģʽ����������8MA
	GPIOPadConfigSet(I2C0_PIN_BASE, I2C0SCL_PIN | I2C0SDA_PIN, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPD);
/************************************************************************************/
	SysCtlDelay(SysCtlClockGet()/1500);
	if (GPIOPinRead(I2C0_PIN_BASE, 
		I2C0SCL_PIN | I2C0SDA_PIN) !=
		(I2C0SCL_PIN | I2C0SDA_PIN))
		return 1;	
	GPIOPinTypeI2C(I2C0_PIN_BASE, I2C0SCL_PIN | I2C0SDA_PIN);
	return 0;
}

