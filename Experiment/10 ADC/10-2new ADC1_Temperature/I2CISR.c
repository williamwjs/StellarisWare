#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "I2CConfigure.h"
#include "NixieTubeConfigure.h"
#include "I2CISR.h"

unsigned char I2C0TransmitionState=0;

void I2C0_ISR(void)
{
	unsigned long ulStatus;		 	
	ulStatus=I2CMasterIntStatus(I2C0_MASTER_BASE,true);	//¶ÁÈ¡ÖÐ¶Ï×´Ì¬
	I2CMasterIntClear(I2C0_MASTER_BASE);				//Çå³ý¸ÃÖÐ¶Ï×´Ì¬

	if (I2CMasterErr(I2C0_MASTER_BASE)!=I2C_MASTER_ERR_NONE)
	{
		I2C0TransmitionState=0;
		return;
	}
	if (ulStatus)
	{
		I2C0TransmitionState++;
		switch (I2C0TransmitionState)
		{
			case 1:	
			{
				I2CMasterDataPut(I2C0_MASTER_BASE,0xff);
				I2CMasterControl(I2C0_MASTER_BASE,I2C_MASTER_CMD_BURST_SEND_FINISH);
				break;
			}
			case 2:	
			{
				I2CMasterSlaveAddrSet(I2C0_MASTER_BASE,TUBE_SEL1_I2CADDR,false);			
				I2CMasterDataPut(I2C0_MASTER_BASE,PCA9557_REG_OUTPUT);				
				I2CMasterControl(I2C0_MASTER_BASE,I2C_MASTER_CMD_BURST_SEND_START);
				break;
			}
			case 3: 
			{
				I2CMasterDataPut(I2C0_MASTER_BASE,NixieTubeSelected1);
				I2CMasterControl(I2C0_MASTER_BASE,I2C_MASTER_CMD_BURST_SEND_FINISH);
				break;
			}
			case 4:
			{
				I2CMasterSlaveAddrSet(I2C0_MASTER_BASE,TUBE_SEL2_I2CADDR,false);			
				I2CMasterDataPut(I2C0_MASTER_BASE,PCA9557_REG_OUTPUT);				
				I2CMasterControl(I2C0_MASTER_BASE,I2C_MASTER_CMD_BURST_SEND_START);
				break;
			}
			case 5:
			{
				I2CMasterDataPut(I2C0_MASTER_BASE,NixieTubeSelected2);
				I2CMasterControl(I2C0_MASTER_BASE,I2C_MASTER_CMD_BURST_SEND_FINISH);
				break;
			}
			case 6:
			{
				I2CMasterSlaveAddrSet(I2C0_MASTER_BASE,TUBE_SEG_I2CADDR,false);			
				I2CMasterDataPut(I2C0_MASTER_BASE,PCA9557_REG_OUTPUT);				
				I2CMasterControl(I2C0_MASTER_BASE,I2C_MASTER_CMD_BURST_SEND_START);
				break;
			}
			case 7:
			{
				I2CMasterDataPut(I2C0_MASTER_BASE,NixieTubeSegment);
				I2CMasterControl(I2C0_MASTER_BASE,I2C_MASTER_CMD_BURST_SEND_FINISH);
				break;
			}
			case 8:
			{
				I2CMasterSlaveAddrSet(I2C0_MASTER_BASE,LED_I2CADDR,false);			
				I2CMasterDataPut(I2C0_MASTER_BASE,PCA9557_REG_OUTPUT);				
				I2CMasterControl(I2C0_MASTER_BASE,I2C_MASTER_CMD_BURST_SEND_START);
				break;
			}
			case 9:
			{
				I2CMasterDataPut(I2C0_MASTER_BASE,LEDSerial);
				I2CMasterControl(I2C0_MASTER_BASE,I2C_MASTER_CMD_BURST_SEND_FINISH);
				break;
			}							
			default: break;
		}
		if (I2C0TransmitionState==10)	I2C0TransmitionState=0; 
	}	
}
