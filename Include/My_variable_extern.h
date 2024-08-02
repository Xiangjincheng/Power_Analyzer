#define PWMPRD 7500


/*-------------采样		 参数------------------------*/
extern struct DC_DATASET  DC_U1,DC_I1,DC_U2,DC_I2,DC_Untc;
extern struct AC_DATASET  AC_Uin,AC_Iin;
extern struct Power_Deal  PD1;
extern struct FFT_data    FFT;

extern struct PIBUF        PI_IS,PI_IQ,PI_IU,PI_IV,PI_IW;
extern struct SYSTEM_STATUS System;

extern struct MENU_CMD     	Menu_cmd; 
extern struct MENU_DISPLAY  Menu_display;
extern struct MENU_KEY		Menu_key;
extern struct SINGLE		Single;	
extern struct DA_BL			Da_bl;
#define RELAY_ON   GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;  //继电器开
#define RELAY_OFF  GpioDataRegs.GPASET.bit.GPIO6 = 1;    //继电器关
//#define BRAKE_ON   GpioDataRegs.GPASET.bit.GPIO7 = 1;       //制动信号
//#define BRAKE_OFF  GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;
