/*
LED0(Yellow)-->PF3,	LED1(Green)-->PF2	�͵�ƽ��Ч
*/

//�Ĵ�����ַ����
#define RCGC2		(*((volatile unsigned long *)(0x400FE108)))	//��ģ��ʱ���ſؿ��ƼĴ��� *ע�ⲻ��DATASHEET�ϵ�0x000
#define GPIOFDATA	(*((volatile unsigned long *)(0x400253fc)))	//PortF ���ݼĴ���
#define GPIOFDIR	(*((volatile unsigned long *)(0x40025400)))	//PortF ����Ĵ���
#define GPIOFAFSEL	(*((volatile unsigned long *)(0x40025420)))	//PortF ���ù���ѡ��Ĵ���
#define GPIOFDR2R	(*((volatile unsigned long *)(0x40025500)))	//PortF 2-mA�����Ĵ���
#define GPIOFDR4R	(*((volatile unsigned long *)(0x40025504)))	//PortF 4-mA�����Ĵ���
#define GPIOFDR8R	(*((volatile unsigned long *)(0x40025508)))	//PortF 8-mA�����Ĵ���
#define GPIOFODR	(*((volatile unsigned long *)(0x4002550c)))	//PortF ��©ѡ��Ĵ���
#define GPIOFDEN	(*((volatile unsigned long *)(0x4002551c)))	//PortF ����ʹ�ܼĴ���
#define GPIOFSLR	(*((volatile unsigned long *)(0x40025518)))	//PortF б�ʼĴ���

int main(void)						//������
{   
/*
GPIO	����������ã�
AFSEL	DIR		ODR		DEN		PUR		PDR		DR2R	DR4R	DR8R	SLR
0		1		0		1		?		?		?		?		?		?	
X������ԣ������ݾ�������趨
*/                           		
    RCGC2=0x00000020;		//ʹ��PORTF����ȴ�����ʱ������
	__nop();				//asm�����
	__nop();

	GPIOFDEN=0x0000000c;	//ʹ��PORTF������ģ��
	GPIOFDIR=0x0000000c;	//��Ϊ���ģʽ
	GPIOFAFSEL=0x00000000;	//�رձ��ù���
	GPIOFDR8R=0x0000000c;	//�����������Ϊ8-mA��2-mA��4-mA�ļĴ����Զ����㣩
	GPIOFODR=0x00000000;	//��Ϊ�������(���Բ����ã�Ĭ�ϣ�
	GPIOFSLR=0x0000000c;	//��б�ʿ��ƣ������ٶȿ��ƣ�
	GPIOFDATA=0x00000004;	//��LED0���ر�LED1
	while(1);
}
