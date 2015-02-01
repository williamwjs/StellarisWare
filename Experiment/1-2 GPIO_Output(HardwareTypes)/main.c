#include "inc/hw_types.h"				//�������ͺ궨�壬�Ĵ������ʺ���
#include "inc/hw_memmap.h"				//��ַ�궨��
#include "inc/hw_sysctl.h"				//ϵͳ���ƺ궨��
#include "inc/hw_gpio.h"				//ͨ��IO�ں궨��
/*
LED0(Yellow)-->PF3,	LED1(Green)-->PF2	�͵�ƽ��Ч
*/

int main(void)							
{   
/*
GPIO	����������ã�
AFSEL	DIR		ODR		DEN		PUR		PDR		DR2R	DR4R	DR8R	SLR
0		1		0		1		?		?		?		?		?		?	
X������ԣ������ݾ�������趨
*/                           		
	HWREG(SYSCTL_RCGC2)=0x00000020;		//ʹ��PORTF����ȴ�����ʱ������
	__nop();							//asm�����
	__nop();

	HWREG(GPIO_PORTF_BASE+GPIO_O_DEN)=0x0000000c;		//ʹ��PORTF������ģ��
	HWREG(GPIO_PORTF_BASE+GPIO_O_DIR)=0x000c;			//��Ϊ���ģʽ
	HWREGH(GPIO_PORTF_BASE+GPIO_O_AFSEL)=0x0000;		//�رձ��ù���
	HWREGH(GPIO_PORTF_BASE+GPIO_O_DR8R)=0x000c;			//�����������Ϊ8-mA��2-mA��4-mA�ļĴ����Զ����㣩
	HWREGB(GPIO_PORTF_BASE+GPIO_O_ODR)=0x00;			//��Ϊ�������(���Բ����ã�Ĭ�ϣ�
	HWREGB(GPIO_PORTF_BASE+GPIO_O_SLR)=0x0c;			//��б�ʿ��ƣ������ٶȿ��ƣ�
	HWREGB(GPIO_PORTF_BASE+GPIO_O_DATA+0x3fc)=0x04;		//��LED0���ر�LED1
	while(1);
}
