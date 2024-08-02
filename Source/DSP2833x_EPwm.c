// TI File $Revision: /main/1 $
// Checkin $Date: August 18, 2006   13:46:19 $
//###########################################################################
//
// FILE:   DSP2833x_EPwm.c
//
// TITLE:  DSP2833x ePWM Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

void  	InitEpwmT()   //正弦逆变用
{	EPwm1Regs.TBPRD = 11718;       // Set timer period \
	EPwm1Regs.CMPA.half.CMPA = 0;    // Set compare A value  下管为两边模式  小于比较直为高电平
	EPwm1Regs.CMPB = 0;              // Set Compare B value  上管为中央模式  小于比较直为低电平
	EPwm1Regs.TBPHS.half.TBPHS = 0; //设置相位寄存器置零
	EPwm1Regs.TBCTR = 0;   //清楚TB计数器
	EPwm1Regs.TBSTS.all=0;
	EPwm1Regs.TZSEL.all=0;

	EPwm1Regs.TZCTL.all=0;
	EPwm1Regs.TZEINT.all=0;
	EPwm1Regs.TZFLG.all=0;
	EPwm1Regs.TZCLR.all=0;
	EPwm1Regs.TZFRC.all=0;

	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 
	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;    // Disable phase loading
	EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;  // dao 0
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm1Regs.AQSFRC.bit.RLDCSF=0x3;            //？？
	EPwm1Regs.AQCTLA.bit.CAD =AQ_CLEAR;         // Set PWM1A on Zero
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;          // Clear PWM1A on event A, up count
    EPwm1Regs.AQCTLB.bit.CAD = AQ_CLEAR;            // Set PWM1B on Zero
    EPwm1Regs.AQCTLB.bit.CAU =AQ_SET ;          // Clear PWM1B on event B, up count
//	EPwm1Regs.AQSFRC.all=0;
	EPwm1Regs.AQCSFRC.all=0;
//	EPwm1Regs.DBCTL.all=0xb;          // EPWMxB is inverted
	EPwm1Regs.DBRED=0x4B;    //死区时间  0.5us
	EPwm1Regs.DBFED=0x4B;
	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;      // Enable INT on Zero event
	EPwm1Regs.ETSEL.bit.INTEN =1;   // Enable INT
	EPwm1Regs.ETPS.bit.INTPRD = 1;
	EPwm1Regs.ETCLR.bit.INT=1;

	EPwm2Regs.TBPRD =3750;       // Set timer period \
	EPwm2Regs.CMPA.half.CMPA = 0;    // Set compare A value  下管为两边模式  小于比较直为高电平
	EPwm2Regs.CMPB = 0;              // Set Compare B value  上管为中央模式  小于比较直为低电平
	EPwm2Regs.TBPHS.half.TBPHS = 0; //设置相位寄存器置零
	EPwm2Regs.TBCTR = 0;   //清楚TB计数器
	EPwm2Regs.TBSTS.all=0;
	EPwm2Regs.TZSEL.all=0;

	EPwm2Regs.TZCTL.all=0;
	EPwm2Regs.TZEINT.all=0;
	EPwm2Regs.TZFLG.all=0;
	EPwm2Regs.TZCLR.all=0;
	EPwm2Regs.TZFRC.all=0;

	EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 
	EPwm2Regs.TBCTL.bit.PHSEN = 1;    // Disable phase loading
	EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;  //
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm2Regs.AQCTLA.bit.CAD =AQ_CLEAR;         // Set PWM1A on Zero
    EPwm2Regs.AQCTLA.bit.CAU =AQ_SET ;          // Clear PWM1A on event A, up count
    EPwm2Regs.AQCTLB.bit.CBD =AQ_CLEAR ;            // Set PWM1B on Zero
    EPwm2Regs.AQCTLB.bit.CBU =AQ_SET;          // Clear PWM1B on event B, up count
	EPwm2Regs.AQSFRC.all=0;
	EPwm2Regs.AQCSFRC.all=0;
	EPwm2Regs.DBRED=0x4B;    //死区时间  0.5us
	EPwm2Regs.DBFED=0x4B;
	EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;      // Enable INT on Zero event
	EPwm2Regs.ETSEL.bit.INTEN =1;   // Enable INT
	EPwm2Regs.ETPS.bit.INTPRD = 1;

	EPwm3Regs.TBPRD =3750;       // Set timer period \
	EPwm3Regs.CMPA.half.CMPA = 0;    // Set compare A value  下管为两边模式  小于比较直为高电平
	EPwm3Regs.CMPB = 0;              // Set Compare B value  上管为中央模式  小于比较直为低电平
	EPwm3Regs.TBPHS.half.TBPHS = 0; //设置相位寄存器置零
	EPwm3Regs.TBCTR = 0;   //清楚TB计数器
	EPwm3Regs.TBSTS.all=0;
	EPwm3Regs.TZSEL.all=0;

	EPwm3Regs.TZCTL.all=0;
	EPwm3Regs.TZEINT.all=0;
	EPwm3Regs.TZFLG.all=0;
	EPwm3Regs.TZCLR.all=0;
	EPwm3Regs.TZFRC.all=0;

	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 
	EPwm3Regs.TBCTL.bit.PHSEN = 1;    // Disable phase loading
	EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;  //3
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm3Regs.AQCTLA.bit.CAD =AQ_CLEAR;         // Set PWM1A on Zero
    EPwm3Regs.AQCTLA.bit.CAU =AQ_SET;          // Clear PWM1A on event A, up count
    EPwm3Regs.AQCTLB.bit.CAD = AQ_CLEAR;            // Set PWM1B on Zero
    EPwm3Regs.AQCTLB.bit.CAU =AQ_SET ;          // Clear PWM1B on event B, up count
	EPwm3Regs.AQSFRC.all=0;
	EPwm3Regs.AQCSFRC.all=0;
	EPwm3Regs.DBRED=0x4B;    //死区时间  0.5us
	EPwm3Regs.DBFED=0x4B;
	EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;      // Enable INT on Zero event
	EPwm3Regs.ETSEL.bit.INTEN =1;   // Enable INT
	EPwm3Regs.ETPS.bit.INTPRD = 1;

   EALLOW;
   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;         // Start all the timers synced
   EDIS;




}


void InitEPwmSyncGpio(void)
{

   EALLOW;

/* Configure EPWMSYNCI  */
   
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;   // Enable pull-up on GPIO32 (EPWMSYNCI)    

/* Set qualification for selected pins to asynch only */
// This will select synch to SYSCLKOUT for the selected pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO6 = 0;   // Synch to SYSCLKOUT GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 0;  // Synch to SYSCLKOUT GPIO32 (EPWMSYNCI)    

/* Configure EPwmSync pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPwmSync functional pins.
// Comment out other unwanted lines.   

   GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 2;    // Enable pull-up on GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 2;   // Enable pull-up on GPIO32 (EPWMSYNCI)    



/* Configure EPWMSYNC0  */

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWMSYNC0)
   GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;   // Enable pull-up on GPIO33 (EPWMSYNC0)    

// GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 3;    // Enable pull-up on GPIO6 (EPWMSYNC0)
   GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 2;   // Enable pull-up on GPIO33 (EPWMSYNC0)    

}



//---------------------------------------------------------------------------
// Example: InitTzGpio: 
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as Trip Zone (TZ) pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.  
// 

void InitTzGpio(void)
{
   EALLOW; 
   EDIS;
}


//===========================================================================
// End of file.
//===========================================================================
