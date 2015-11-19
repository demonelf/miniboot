

#define  ADCCON        (*((volatile unsigned long*)0x58000000)) 
#define  ADCTSC        (*((volatile unsigned long*)0x58000004))
#define  ADCDAT0       (*((volatile unsigned long*)0x5800000c))
#define  ADCDAT1       (*((volatile unsigned long*)0x58000010))

#define  SRCPND        (*((volatile unsigned long*)0x4a000000)) 
#define  INTMSK        (*((volatile unsigned long*)0x4a000008)) 
#define  INTPND        (*((volatile unsigned long*)0x4a000010))
#define  INTSUBMSK     (*((volatile unsigned long*)0x4a00001c))
#define  SUBSRCPND     (*((volatile unsigned long*)0x4a000018)) 

int xdata, ydata;

void ts_init()
{
    ADCCON = (1<<14)|(49<<6);
    
    INTMSK &=~(1<<31);  
    INTSUBMSK &=~(1<<9);
    
    ADCTSC = 0xd3;   
	
}


void tc_handler()
{
    /**����xy�����Զ�ת��**/
    ADCTSC = (1<<2); 
    ADCCON |=(1<<0);
    
    /**�ȴ�ת�����**/
    while(!(ADCCON&(1<<15)));
    
    /**��ȡ����**/
    xdata = ADCDAT0 & 0x3ff;
    ydata = ADCDAT1 & 0x3ff;
    /**��������ж�**/
    SUBSRCPND |= (1<<9);
    SRCPND |=(1<<31);
    INTPND |=(1<<31);
       
    /**����ȴ������ж�**/
    ADCTSC = 0xd3;
    ADCTSC |= (1<<8);
    
    while(1)
    {
        if(SUBSRCPND&(1<<9))
             break;
    }
    /**��������ж�**/
    SUBSRCPND |= (1<<9);
    SRCPND |=(1<<31);
    INTPND |=(1<<31);
    printf("x= %d,y= %d\n",xdata,ydata);
    /**�ٴν���ȴ������жϵ�״̬**/
    ADCTSC = 0xd3;
    	
}