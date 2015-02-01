#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "UARTConfigure.h"
#include "I2CConfigure.h"

unsigned char LEDSerial=0x01;

void I2C0MasterInitial(void)
{												   
	unsigned char tempCounter;

/****************************Put your code here!!************************************/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);		//SysCtl使能I2C0模块
	I2CMasterInitExpClk(I2C0_MASTER_BASE, SysCtlClockGet(), false);			//设置I2C0主机模块传输速率为100kbps（普通模式）
	I2CMasterEnable(I2C0_MASTER_BASE);				//使能I2C主机模块
/************************************************************************************/
	
	//配置所有PCA9557为输出模式，并关闭所有LED
	I2CMasterTransmit_Burst_2Bytes(I2C0_MASTER_BASE,LED_I2CADDR,PCA9557_REG_CONFIG,0x00);
	I2CMasterTransmit_Burst_2Bytes(I2C0_MASTER_BASE,LED_I2CADDR,PCA9557_REG_OUTPUT,0x00);
	//LED_OnChip启动动画
	for (tempCounter=0;tempCounter<8;tempCounter++)
	{
		LEDSerial<<=1;
		SysCtlDelay(SysCtlClockGet()/60);
		I2CMasterTransmit_Burst_2Bytes(I2C0_MASTER_BASE,LED_I2CADDR,PCA9557_REG_OUTPUT,LEDSerial);
	}
}

//该函数可设置100kbps及400kbps之外的其他速度
void I2CMasterSpeedSet(unsigned long ulBase, unsigned long ulSpeed) 
{ 
	unsigned long ulClk, ulTPR; 
	ulClk = SysCtlClockGet( );         							//获取当前的系统时钟速率 
	ulTPR = (ulClk / (2 * 10)) / ulSpeed; 
	if (ulTPR < 2) ulTPR = 2;        							//防止过高的速率设置请求 
	if (ulTPR > 256) ulTPR = 256;       						//防止过低的速率设置请求 
 	ulTPR = ulTPR - 1; 
  	HWREG(ulBase + I2C_O_MTPR) = ulTPR; 
}

unsigned char I2CMasterTransmit_Burst_2Bytes
							 (unsigned long ulBase,				//发送完成后才会退出
					 		  unsigned char ucSla,				//从机地址
							  unsigned char ucAddr,				//从机子地址
							  unsigned char ucData)				//传送的1个数据位
{

/****************************Put your code here!!************************************/
	I2CMasterSlaveAddrSet(ulBase, ucSla, false);   //设置I2C主机模块的从机地址，并设置传输方式为主机写数据至从机
	I2CMasterDataPut(ulBase, ucAddr);        //设置目标从机子地址
	I2CMasterControl(ulBase, I2C_MASTER_CMD_BURST_SEND_START);        //控制主机作出一次‘突发发送起始’动作
/************************************************************************************/

	while(I2CMasterBusy(ulBase));
	if (I2CMasterErr(ulBase)!=I2C_MASTER_ERR_NONE)	
	{
		UARTStringPut(UART0_BASE,"I2C0 Transmission Fault!!\r\n");
		return 0;
	}

/****************************Put your code here!!************************************/
	I2CMasterDataPut(ulBase, ucData);		//从主机发送一个数据到从机
	I2CMasterControl(ulBase, I2C_MASTER_CMD_BURST_SEND_FINISH);		//控制主机作出一次‘突发发送完成’动作
/************************************************************************************/

	while(I2CMasterBusy(ulBase));
	if (I2CMasterErr(ulBase)!=I2C_MASTER_ERR_NONE)	
	{
		UARTStringPut(UART0_BASE,"I2C0 Transmission Fault!!\r\n");
		return 0;
	}
	return 1;
}						 

