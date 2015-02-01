#ifndef	__I2CCONFIGURE_H_
#define __I2CCONFIGURE_H_

#define LED_I2CADDR				0x1c

#define PCA9557_REG_INPUT		0x00
#define	PCA9557_REG_OUTPUT		0x01
#define PCA9557_REG_PolInver	0x02
#define PCA9557_REG_CONFIG		0x03		

//I2C����ģʽ�£�����I2C0���߳�ʼ��
extern void I2C0MasterInitial(void);
extern void I2CMasterSpeedSet(unsigned long ulBase, 
							  unsigned long ulSpeed);

extern unsigned char I2CMasterTransmit_Burst_2Bytes		//ͻ������2Bytes��1λ�ӵ�ַ��1λ���ݣ�
							 (unsigned long ulBase,		//������ɺ�Ż��˳�
					 		  unsigned char ucSla,		//�ӻ���ַ
							  unsigned char ucAddr,		//�ӻ��ӵ�ַ
							  unsigned char ucData);	//���͵�1������λ

#endif
