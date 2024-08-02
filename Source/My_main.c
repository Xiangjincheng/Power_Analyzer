//###########################################################################
// FILE:   Example_2833xAdcToDMA.c
// TITLE:  DSP2833x ADC To DMA
// ASSUMPTIONS:
//    This program requires the DSP2833x header files. Make sure the CPU clock speed is properly defined in DSP2833x_Examples.h before compiling this example.
//    Connect the signals to be converted to channel A0, A1, A2, and A3. As supplied, this project is configured for "boot to SARAM" operation.  The 2833x Boot Mode table is shown below.
// 		For information on configuring the boot mode of an eZdsp, please refer to the documentation included with the eZdsp,
// Original source by: M.P.
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "C28x_FPU_FastRTS.h"
#include <math.h>
#include "FPU.h"
#include "My_main.h"
#include "My_structure.h"
#include "My_variable_extern.h"
void delay(unsigned int data);
void InitGpio(void);
void data_Init(void);
extern void DA(void);
extern void InitCpuTimers(void);
extern void posspeed_Init(void);
extern void ConfigCpuTimer(struct CPUTIMER_VARS *Timer, float Freq, float Period);
extern void menu_init(void);
extern void InitGpioDA(void);
extern void menu_deal(void);
extern void InitEpwmT();
extern interrupt void cpu_timer0_isr(void);//T0中断
unsigned int delayt;



//*****************************
//主函数
//*****************************
void main(void)
{   InitSysCtrl();  //系统初始化
    EALLOW;
    SysCtrlRegs.HISPCP.all = ADC_MODCLK;    // HSPCLK = SYSCLKOUT/ADC_MODCLK   50M
    EDIS;
    DINT;
    InitPieCtrl();  //PIE初始化
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();     //PIE向量表初始化
    MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
    InitFlash();
    EALLOW; // Allow access to EALLOW protected registers
    PieVectTable.ADCINT     = &adc_isr;
    PieVectTable.TINT0  = &cpu_timer0_isr;
    EDIS;   // Disable access to EALLOW protected registers
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
    PieCtrlRegs.PIEIER1.bit.INTx6 = 1;          //adc中断
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;          //T0中断
    InitCpuTimers();   // 配置定时器TIMER0
    ConfigCpuTimer(&CpuTimer0, 60, 156.25);
    CpuTimer0Regs.TCR.all=0x4001;
    EALLOW;
    SysCtrlRegs.WDCR= 0x002F;   //enable WATCHDOG
    EDIS;
    InitGpio();     //初始化GPIO
    InitAdc();      //初始化ADC
    menu_init();    //按键初始化
    InitXintf();
    posspeed_Init();
    data_Init();    //数据初始化
    IER =M_INT1|M_INT3|M_INT4|M_INT14;
    EnableInterrupts(); //中断使能
    DELAY_US(10000);
    while(1)
    {
        if(System.adc_flag == 0){
            Calcaculate();
            System.adc_flag = 1;
            //AdcRegs.ADCTRL3.bit.ADCPWDN = 1;
        }
        if(System.uiFlag_05ms==1)
        {   System.uiFlag_05ms=0;
            System.lcd_auto++;
            if(System.lcd_auto == 4096)
            {
                System.lcd_auto = 0;
                System.LCD_flag ++;
                if(System.LCD_flag == 2){System.LCD_flag = 0;}
            }
            menu_deal();    //按键处理函数
            ServiceDog();   //定期给看门狗写入值防止复位
        }
    }   }

/*延时函数*/
void delay(unsigned int data)
{ 	while(data--)
    {	for(delayt=0;delayt<100;delayt++);
    }  
}
void InitGpio(void)
{	EALLOW;
/******************液晶显示管脚*********************/
    SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;//set pull-up resistor
    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 1;     //
    GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;     //
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;    //
    GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3;   //

    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 1;     //
    GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;     //
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;    //
    GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3;   //
/******************PWM输出脚和 联防脚TZ5*************/
	GpioCtrlRegs.GPAMUX1.bit.GPIO0=1;//epwm1a
	GpioCtrlRegs.GPADIR.bit.GPIO0 =1;//输出
	GpioDataRegs.GPACLEAR.bit.GPIO0 =1;// don
	GpioCtrlRegs.GPAPUD.bit.GPIO0 =1;// up
	GpioCtrlRegs.GPAMUX1.bit.GPIO1=1;//epwm1b
	GpioCtrlRegs.GPADIR.bit.GPIO1 =1;//输出
	GpioCtrlRegs.GPAMUX1.bit.GPIO2=1;//epwm2a
	GpioCtrlRegs.GPADIR.bit.GPIO2 =1;//输出
	GpioCtrlRegs.GPAMUX1.bit.GPIO3=1;//epwm2b
	GpioCtrlRegs.GPADIR.bit.GPIO3 =1;//输出
	GpioCtrlRegs.GPAMUX1.bit.GPIO4=1;//epwm3a
	GpioCtrlRegs.GPADIR.bit.GPIO4 =1;//输出
	GpioCtrlRegs.GPAMUX1.bit.GPIO5=1;//epwm3b
	GpioCtrlRegs.GPADIR.bit.GPIO5 =1;//输出
	GpioCtrlRegs.GPAMUX1.bit.GPIO6=0;//io  epwm4a
	GpioCtrlRegs.GPADIR.bit.GPIO6 =1;//输出
	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 3;  // Configure GPIO16 as TZ5
	GpioCtrlRegs.GPAQSEL2.bit.GPIO16= 3;  // Asynch input GPIO16 (TZ5)
	GpioCtrlRegs.GPAPUD.bit.GPIO16 	= 0;  // Enable pull-up on GPIO16 (TZ5)
/********************GPIO62**********/
	GpioCtrlRegs.GPBMUX2.bit.GPIO62 = 0;   
	GpioCtrlRegs.GPBDIR.bit.GPIO62 = 1;
    EDIS;
}

void data_Init()
{   unsigned int i;
    int *frame;
    float *frame_f;
    System.uiStatus=0;          //系统状态
    System.uiRelay_en_delay=0;
    System.uiWork_status=4;     //工作模式
    System.uiFlag_05ms=0;
    System.iPwmDuty=0;
    System.pwm360_cnt=0;
    System.LCD_flag=0;
    System.lcd_auto=0;
    System.adc_flag = 1;

	Menu_cmd.fDutyGive=0.3;	//占空比开环给定
	Menu_cmd.fIoGive=0; 	//电流闭环模式 给定	
	Menu_cmd.fUgive=20;
	Single.fUgive=1;
    Menu_cmd.itheta=179;
	Single.itheta=5;
	Single.uiFrq=50;
	Single.uiPwmprd=(75000000/360)/50;
	Da_bl.TAG=0;

	frame=&AC_Uin.iBuf[0];
	for(i=0;i<128;i++)*(frame++)=0;
    AC_Uin.Sum = 0; AC_Uin.Sum2 = 0;
    AC_Uin.fKins = 0.1669921875*1.304; 	    //samp=0.75/48*4096/3*U2,OK
    AC_Uin.iOffset =2048;			AC_Uin.fKrms =0.1669921875*1.304; //U2=0.046875*( Samp_I-2048),OK  //0.046875

	frame=&AC_Iin.iBuf[0];
    for(i=0;i<128;i++)*(frame++)=0;
    AC_Iin.Sum = 0; AC_Iin.Sum2 = 0;
    AC_Iin.fKins =0.000825845;	            //Samp_I=2048+4096/3*0.1875*I1,OK
    AC_Iin.iOffset =2063;		AC_Iin.fKrms =0.000825845;//I1=0.00390625×( Samp-2048),OK

	frame_f=&PD1.fYpower;
    for(i=0;i<542;i++)*(frame_f++)=0;
}
