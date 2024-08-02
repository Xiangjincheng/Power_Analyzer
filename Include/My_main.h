
//#include "spinv_variable.h"

// Global variables
// Two bytes will be used for the outgoing address,
extern  struct I2CMSG *CurrentMsgPtr;				      // Used in interrupts
extern void Calcaculate(void);

extern void calc_temp(void); 

extern interrupt void epwm1tz_isr(void);
extern interrupt void  epwm1_isr(void);
extern interrupt void  eqep2_int1a_isr(void);
extern interrupt void  adc_isr(void);
extern interrupt void cpu_timer0_isr(void);//T0中断
//extern interrupt void cpu_timer2_isr(void);//T2中断
extern interrupt void ecap1_isr(void);
extern interrupt void ecap2_isr(void);
extern interrupt void ecap3_isr(void);

//interrupt void ScibTxInt_isr (void);    //串口b发送中断
//interrupt void ScibRxInt_isr (void);    //串口b接收中断
//interrupt void ScicTxInt_isr (void);
//interrupt void ScicRxInt_isr (void);

extern interrupt void i2c_int1a_isr(void);    //i2c中断
void Cpld_Reset(Uint16 on_off);


extern void bufferinit_I2C(void);
extern void InitEpwm(void);
extern void InitECapture();


extern void SCIb_Init();//初始化串口
extern void I2CA_Init();
extern void InitScia(void);
extern void InitScic(void);
extern void TX_SENDDATA();
extern interrupt void SCIRXINTAmod_ISR(void);
extern interrupt void SCIRXINTCmod_ISR(void);
//extern void InitAdc(void);
#define ADC_MODCLK 0x3
/*
// ADC start parameters
#if (CPU_FRQ_150MHZ)     // Default - 150 MHz SYSCLKOUT
  #define ADC_MODCLK 0x3 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 150/(2*3)   = 25.0 MHz
#endif
#if (CPU_FRQ_100MHZ)
  #define ADC_MODCLK 0x2 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 100/(2*2)   = 25.0 MHz

#endif
*/
