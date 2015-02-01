#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "UARTConfigure.h"
#include "I2CConfigure.h"
#include "NixieTubeConfigure.h"

void I2C0MasterInitial(void)
{
	unsigned char tempCounter;

	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);					//ʹ��I2C0ģ��
	I2CMasterInit(I2C0_MASTER_BASE,true);						//400kbps����ͨģʽ
	I2CMasterSpeedSet(I2C0_MASTER_BASE,400000);					//�������ô����ٶ�
					  											//�˴�ΪĬ��100kbps����ʡ��
	I2CMasterEnable(I2C0_MASTER_BASE);
	I2CMasterIntEnable(I2C0_MASTER_BASE);
	
	//��������PCA9557Ϊ���ģʽ�����ر�����LED
	I2CMasterTransmit_Burst_2Bytes(I2C0_MASTER_BASE,LED_I2CADDR,PCA9557_REG_CONFIG,0x00);
	I2CMasterTransmit_Burst_2Bytes(I2C0_MASTER_BASE,TUBE_SEG_I2CADDR,PCA9557_REG_CONFIG,0x00);
	I2CMasterTransmit_Burst_2Bytes(I2C0_MASTER_BASE,TUBE_SEL1_I2CADDR,PCA9557_REG_CONFIG,0x00);
	I2CMasterTransmit_Burst_2Bytes(I2C0_MASTER_BASE,TUBE_SEL2_I2CADDR,PCA9557_REG_CONFIG,0x00);

	I2CMasterTransmit_Burst_2Bytes(I2C0_MASTER_BASE,LED_I2CADDR,PCA9557_REG_OUTPUT,0x00);
	I2CMasterTransmit_Burst_2Bytes(I2C0_MASTER_BASE,TUBE_SEG_I2CADDR,PCA9557_REG_OUTPUT,0xff);
	I2CMasterTransmit_Burst_2Bytes(I2C0_MASTER_BASE,TUBE_SEL1_I2CADDR,PCA9557_REG_OUTPUT,0xff);
	I2CMasterTransmit_Burst_2Bytes(I2C0_MASTER_BASE,TUBE_SEL2_I2CADDR,PCA9557_REG_OUTPUT,0xff);
	
	//LED_OnChip��������
	for (tempCounter=0;tempCounter<8;tempCounter++)
	{
		LEDSerial<<=1;
		SysCtlDelay(SysCtlClockGet()/60);
		I2CMasterTransmit_Burst_2Bytes(I2C0_MASTER_BASE,LED_I2CADDR,PCA9557_REG_OUTPUT,LEDSerial);
	}
	IntEnable(INT_I2C0);
}

void I2CMasterSpeedSet(unsigned long ulBase, unsigned long ulSpeed) 
{ 
	unsigned long ulClk, ulTPR; 
	ulClk = SysCtlClockGet( );         							//��ȡ��ǰ��ϵͳʱ������ 
	ulTPR = (ulClk / (2 * 10)) / ulSpeed; 
	if (ulTPR < 2) ulTPR = 2;        							//��ֹ���ߵ������������� 
	if (ulTPR > 256) ulTPR = 256;       						//��ֹ���͵������������� 
 	ulTPR = ulTPR - 1; 
  	HWREG(ulBase + I2C_O_MTPR) = ulTPR; 
}

unsigned char I2CMasterTransmit_Burst_2Bytes
							 (unsigned long ulBase,				//������ɺ�Ż��˳�
					 		  unsigned char ucSla,				//�ӻ���ַ
							  unsigned char ucAddr,				//�ӻ��ӵ�ַ
							  unsigned char ucData)				//���͵�1������λ
{
	I2CMasterSlaveAddrSet(ulBase,ucSla,false);					//false��ʾ�����������ӻ�
	I2CMasterDataPut(ulBase,ucAddr);							//����Ҫ���͵��ӵ�ַ
	I2CMasterControl(ulBase,I2C_MASTER_CMD_BURST_SEND_START);	//ͻ��������ʼ
	while(I2CMasterBusy(ulBase));
	if (I2CMasterErr(ulBase)!=I2C_MASTER_ERR_NONE)	
	{
		UARTStringPut(UART0_BASE,"I2C0 Transmission Fault!!\r\n");
		return 0;
	}

	I2CMasterDataPut(ulBase,ucData);
	I2CMasterControl(ulBase,I2C_MASTER_CMD_BURST_SEND_FINISH);
	while(I2CMasterBusy(ulBase));
	if (I2CMasterErr(ulBase)!=I2C_MASTER_ERR_NONE)	
	{
		UARTStringPut(UART0_BASE,"I2C0 Transmission Fault!!\r\n");
		return 0;
	}
	return 1;
}

void I2C0DeviceRefresh(void)
{
	NixieTubeCoding();
	I2CMasterSlaveAddrSet(I2C0_MASTER_BASE,TUBE_SEG_I2CADDR,false);			
	I2CMasterDataPut(I2C0_MASTER_BASE,PCA9557_REG_OUTPUT);				
	I2CMasterControl(I2C0_MASTER_BASE,I2C_MASTER_CMD_BURST_SEND_START);
}
