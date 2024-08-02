#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "My_variable_extern.h"
#include "My_structure.h"
#include <math.h>
extern unsigned int ADCdata_Deal(void);

interrupt void epwm1tz_isr(void)    //错误联防中断 功率模块故障信号处理
{   EPwm1Regs.TZFLG.bit.INT = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
}
interrupt void epwm1_isr(void)    //PWM1 中断   频率20K
 {  //AdcRegs.ADCTRL2.bit.SOC_SEQ1= 0x1; // Start SEQ1;
    EPwm1Regs.ETCLR.bit.INT = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
 }
interrupt void  adc_isr(void)
{
    if(ADCdata_Deal() == 1)
    {
        System.adc_flag = 0;    //stop sample
        //AdcRegs.ADCTRL3.bit.ADCPWDN = 0;
        //AdcRegs.ADCTRL3.bit.ADCBGRFDN = 0;
    }
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         // Reset SEQ1
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       // Clear INT SEQ1 bit
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE
    return;
}

interrupt void cpu_timer0_isr(void)   
{   AdcRegs.ADCTRL2.bit.SOC_SEQ1= System.adc_flag;
    System.uiFlag_05ms=1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE
}
