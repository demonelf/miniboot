
#define GPCCON      (*((volatile unsigned long*)0x56000020))
#define GPDCON      (*((volatile unsigned long*)0x56000030))
#define GPGCON      (*((volatile unsigned long*)0x56000060))
#define LCDCON1     (*((volatile unsigned long*)0x4D000000))
#define LCDCON2     (*((volatile unsigned long*)0x4D000004))
#define LCDCON3     (*((volatile unsigned long*)0x4D000008))
#define LCDCON4     (*((volatile unsigned long*)0x4D00000C))
#define LCDCON5     (*((volatile unsigned long*)0x4D000010))

#define LCDSADDR1   (*((volatile unsigned long*)0x4D000014))
#define LCDSADDR2   (*((volatile unsigned long*)0x4D000018))
#define LCDSADDR3   (*((volatile unsigned long*)0x4D00001C))
#define TPAL        (*((volatile unsigned long*)0x4D000050))


#define VSPW      9
#define VBPD      1
#define LINEVAL   319  //320*240
#define VFPD      1
#define CLKVAL    4  
#define HSPW      40
#define HBPD      1
#define HOZVAL    239
#define HFPD      1

unsigned short frame[240][320];

void lcd_port_init()
{
    GPCCON = 0xaaaaaaaa;
    GPDCON = 0xaaaaaaaa;
}


void lcd_timing_init()
{
    LCDCON1 = (CLKVAL<<8)|(0x3<<5)|(0xc<<1)|(0<<0);
    LCDCON2 = (VSPW<<0)|(VFPD<<6)|(LINEVAL<<14)|(VBPD<<24);
    LCDCON3 = (HFPD<<0)|(HOZVAL<<8)|(HBPD<<19);
    LCDCON4 = (HSPW<<0);
    LCDCON5 = (1<<11)|(1<<9)|(1<<8);
    TPAL = 0;	
}
void lcd_fram_init()
{
    /**allocate frame buffer**/	

    /****/
    LCDSADDR1 = (((unsigned int)frame>>22)<<21) | (((unsigned int)frame>>1)&0x1fffff)
    LCDSADDR2 = (((unsigned int)frame+240*320*2)>>1)&0x1fffff;
    LCDSADDR3 = (0<<11)|320;
}

void lcd_on()
{
    GPGCON |=(0x3<<8);
    LCDCON5 |=(1<<3);
    LCDCON1 |= (1<<0); 	
}

void lcd_init()
{
    lcd_port_init();
    
    lcd_timing_init();
    
    lcd_fram_init();
    
    lcd_on();  
}