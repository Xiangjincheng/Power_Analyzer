#include "DSP2833x_Device.h"     // Device Headerfile and Examples Include File
#include "My_structure.h"
#include "My_variable_extern.h"   // DSP2802x Examples Include File 
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include <math.h> 


void PI_Init (void)//PI算法参数设置
{   float *frame,i;
    frame=&PI_IU.fGive;                 //u相电流
    for(i=0;i<6;i++)*(frame++)=0;
    PI_IU.fKp   =0.1;       PI_IU.fKi   =0.11;
    PI_IU.fIoutmax=0.48;    PI_IU.fIoutmin=-0.48;
    PI_IU.fOutmax=0.48;     PI_IU.fOutmin=-0.48;
    frame=&PI_IV.fGive;
    for(i=0;i<6;i++)*(frame++)=0;       //v相电流
    PI_IV.fKp   =0.1;       PI_IV.fKi   =0.11;
    PI_IV.fIoutmax=0.48;    PI_IV.fIoutmin=-0.48;
    PI_IV.fOutmax=0.48;     PI_IV.fOutmin=-0.48;
    frame=&PI_IW.fGive;
    for(i=0;i<6;i++)*(frame++)=0;       //w相电流
    PI_IW.fKp   =0.1;       PI_IW.fKi   =0.11;  //200
    PI_IW.fIoutmax=0.48;    PI_IW.fIoutmin=-0.48;
    PI_IW.fOutmax=0.48;     PI_IW.fOutmin=-0.48;
}

void PI_deal(struct PIBUF*DATA)
{   DATA->fErr = DATA->fGive - DATA->fFeed;                 //给定减去反馈得到偏差
    DATA->fPout= DATA->fKp   * DATA->fErr;                  //偏差乘以比例系数得到Pout
    DATA->fIout= DATA->fKi   *  DATA->fErr + DATA->fIout;   //偏差积分得到Iout
    DATA->fOut = DATA->fPout + DATA->fIout;                 //占空比等于Pout+Iout
    if(DATA->fIout > DATA->fIoutmax) DATA->fIout =  DATA->fIoutmax;
    else if(DATA->fIout < DATA->fIoutmin)   DATA->fIout = DATA->fIoutmin;
    if(DATA->fOut > DATA->fOutmax) DATA->fOut =  DATA->fOutmax;
    else if(DATA->fOut < DATA->fOutmin)   DATA->fOut = DATA->fOutmin;
}

/*--------------------PWM处理程序--------------------------------*/
void PWM_Deal(void)
{
    EPwm1Regs.DBCTL.all=0xb;EPwm2Regs.DBCTL.all=0xb; EPwm3Regs.DBCTL.all=0xb;//两组PWM波形强制互补
    EPwm1Regs.TBPRD=EPwm2Regs.TBPRD=EPwm3Regs.TBPRD=Single.uiPwmprd;
    EPwm2Regs.AQCTLB.bit.CBD =0x1; 	EPwm2Regs.AQCTLB.bit.CBU =0x2; //????占空比给定乘以sin函数得到随正弦变化的值
    System.iPwmDuty=Single.uiPwmprd*Menu_cmd.fDutyGive*sin(6.2831852*System.pwm360_cnt/360);
    if(System.iPwmDuty>0)
    {   EPwm1Regs.CMPA.half.CMPA=EPwm2Regs.CMPA.half.CMPA=Single.uiPwmprd-System.iPwmDuty;//占空比赋值给比较值
    //			    EPwm1Regs.CMPA.half.CMPA=EPwm2Regs.CMPA.half.CMPA=Single.uiPwmprd-System.iPwmDuty;
        EPwm1Regs.AQCSFRC.bit.CSFB=0;	EPwm1Regs.AQCSFRC.bit.CSFA=0;
        EPwm2Regs.AQCSFRC.bit.CSFA=1;	EPwm2Regs.AQCSFRC.bit.CSFB=2;
        EPwm3Regs.AQCSFRC.bit.CSFA=1;	EPwm3Regs.AQCSFRC.bit.CSFB=1;
    }
    else if(System.iPwmDuty<0)
    {	EPwm1Regs.CMPA.half.CMPA=EPwm2Regs.CMPA.half.CMPA=Single.uiPwmprd+System.iPwmDuty;  //占空比取反后给比较值
    //				EPwm2Regs.CMPA.half.CMPA=EPwm1Regs.CMPA.half.CMPA=Single.uiPwmprd+System.iPwmDuty;
        EPwm1Regs.AQCSFRC.bit.CSFA=1;	EPwm1Regs.AQCSFRC.bit.CSFB=2;
        EPwm2Regs.AQCSFRC.bit.CSFA=0;	EPwm2Regs.AQCSFRC.bit.CSFB=0;
        EPwm3Regs.AQCSFRC.bit.CSFA=1;	EPwm3Regs.AQCSFRC.bit.CSFB=1;
    }

    if(System.pwm360_cnt<359) System.pwm360_cnt++;
    else System.pwm360_cnt=0;
}

void Work_Deal(void)		//工作处理函数
{/*-----------------故障状态------------*/
	if(System.uiSystem_error!=0) System.uiStatus=0;		
/*-----------------暂停状态------------*/
	if(System.uiStatus==0) 
	{	RELAY_OFF;						//关继电器
		System.iPwmDuty=0;				//占空比清零
		Menu_display.iU2=0;				//显示数据清零
		Menu_display.iI2=Menu_display.iIv=Menu_display.iIw=0;	//显示数据清零
		Menu_display.uiP2=Menu_display.uiQo=0;				
		EPwm3Regs.AQCSFRC.bit.CSFA=EPwm3Regs.AQCSFRC.bit.CSFB=1;	//3号桥壁上下管强制低	
		EPwm2Regs.AQCSFRC.bit.CSFA=EPwm2Regs.AQCSFRC.bit.CSFB=1;	//2号桥壁上下管强制低	
		EPwm1Regs.AQCSFRC.bit.CSFA=EPwm1Regs.AQCSFRC.bit.CSFB=1;	//1号桥壁上下管强制低	
	}
/*-----------------运行状态------------*/
	else if(System.uiStatus== 1)	
	{	RELAY_ON;	//开继电器
		if(System.uiRelay_en_delay<100)  System.uiRelay_en_delay++;
		else	PWM_Deal();		//pwm处理函数	
	}
}



