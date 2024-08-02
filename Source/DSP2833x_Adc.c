// TI File $Revision: /main/4 $
// Checkin $Date: July 30, 2007   14:15:53 $
//###########################################################################
//
// FILE:	DSP2833x_Adc.c
//
// TITLE:	DSP2833x ADC Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define ADC_usDELAY  5000L

//---------------------------------------------------------------------------
// InitAdc:
//---------------------------------------------------------------------------
// This function initializes ADC to a known state.
//
void InitAdc(void)
{
	AdcRegs.ADCREFSEL.bit.REF_SEL=0x40;	//Ñ¡Ôñ2.048V

    extern void DSP28x_usDelay(Uint32 Count);
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
	ADC_cal();
	EDIS;

    AdcRegs.ADCTRL3.all = 0x00E0;  // Power up bandgap/reference/ADC circuits
    DELAY_US(ADC_usDELAY);         // Delay before converting ADC channels

// Specific ADC setup for this example:
   AdcRegs.ADCTRL1.bit.ACQ_PS = 0x4 ;
   AdcRegs.ADCTRL3.bit.ADCCLKPS = 0x1;
   AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;        // 0 Non-Cascaded Mode; 1 Cascaded Mode
   AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0x1;
   AdcRegs.ADCTRL2.bit.RST_SEQ1 = 0x1;
//   AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;
   AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;
//   AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2;
   AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3;
//   AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x4;
   AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x5;
//   AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x6;
//   AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x7;
//   AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0x8;
//   AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x9;
//   AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 0xA;
//   AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 0xB;
//   AdcRegs.ADCCHSELSEQ4.bit.CONV12 = 0xC;
//   AdcRegs.ADCCHSELSEQ4.bit.CONV13 = 0xD;
//   AdcRegs.ADCCHSELSEQ4.bit.CONV14 = 0xE;
//   AdcRegs.ADCCHSELSEQ4.bit.CONV15 = 0xF;

   AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 4;   // Set up ADC to perform 4 conversions for every SOC
}



//===========================================================================
// End of file.
//===========================================================================
