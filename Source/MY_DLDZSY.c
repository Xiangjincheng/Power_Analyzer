#include "DSP2833x_Device.h"     // Device Headerfile and Examples Include File
#include "My_structure.h"
#include "My_variable_extern.h"   // DSP2802x Examples Include File 
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include <math.h> 


void PI_Init (void)//PI�㷨��������
{   float *frame,i;
    frame=&PI_IU.fGive;                 //u�����
    for(i=0;i<6;i++)*(frame++)=0;
    PI_IU.fKp   =0.1;       PI_IU.fKi   =0.11;
    PI_IU.fIoutmax=0.48;    PI_IU.fIoutmin=-0.48;
    PI_IU.fOutmax=0.48;     PI_IU.fOutmin=-0.48;
    frame=&PI_IV.fGive;
    for(i=0;i<6;i++)*(frame++)=0;       //v�����
    PI_IV.fKp   =0.1;       PI_IV.fKi   =0.11;
    PI_IV.fIoutmax=0.48;    PI_IV.fIoutmin=-0.48;
    PI_IV.fOutmax=0.48;     PI_IV.fOutmin=-0.48;
    frame=&PI_IW.fGive;
    for(i=0;i<6;i++)*(frame++)=0;       //w�����
    PI_IW.fKp   =0.1;       PI_IW.fKi   =0.11;  //200
    PI_IW.fIoutmax=0.48;    PI_IW.fIoutmin=-0.48;
    PI_IW.fOutmax=0.48;     PI_IW.fOutmin=-0.48;
}

void PI_deal(struct PIBUF*DATA)
{   DATA->fErr = DATA->fGive - DATA->fFeed;                 //������ȥ�����õ�ƫ��
    DATA->fPout= DATA->fKp   * DATA->fErr;                  //ƫ����Ա���ϵ���õ�Pout
    DATA->fIout= DATA->fKi   *  DATA->fErr + DATA->fIout;   //ƫ����ֵõ�Iout
    DATA->fOut = DATA->fPout + DATA->fIout;                 //ռ�ձȵ���Pout+Iout
    if(DATA->fIout > DATA->fIoutmax) DATA->fIout =  DATA->fIoutmax;
    else if(DATA->fIout < DATA->fIoutmin)   DATA->fIout = DATA->fIoutmin;
    if(DATA->fOut > DATA->fOutmax) DATA->fOut =  DATA->fOutmax;
    else if(DATA->fOut < DATA->fOutmin)   DATA->fOut = DATA->fOutmin;
}

/*--------------------PWM�������--------------------------------*/
void PWM_Deal(void)
{
    EPwm1Regs.DBCTL.all=0xb;EPwm2Regs.DBCTL.all=0xb; EPwm3Regs.DBCTL.all=0xb;//����PWM����ǿ�ƻ���
    EPwm1Regs.TBPRD=EPwm2Regs.TBPRD=EPwm3Regs.TBPRD=Single.uiPwmprd;
    EPwm2Regs.AQCTLB.bit.CBD =0x1; 	EPwm2Regs.AQCTLB.bit.CBU =0x2; //????ռ�ձȸ�������sin�����õ������ұ仯��ֵ
    System.iPwmDuty=Single.uiPwmprd*Menu_cmd.fDutyGive*sin(6.2831852*System.pwm360_cnt/360);
    if(System.iPwmDuty>0)
    {   EPwm1Regs.CMPA.half.CMPA=EPwm2Regs.CMPA.half.CMPA=Single.uiPwmprd-System.iPwmDuty;//ռ�ձȸ�ֵ���Ƚ�ֵ
    //			    EPwm1Regs.CMPA.half.CMPA=EPwm2Regs.CMPA.half.CMPA=Single.uiPwmprd-System.iPwmDuty;
        EPwm1Regs.AQCSFRC.bit.CSFB=0;	EPwm1Regs.AQCSFRC.bit.CSFA=0;
        EPwm2Regs.AQCSFRC.bit.CSFA=1;	EPwm2Regs.AQCSFRC.bit.CSFB=2;
        EPwm3Regs.AQCSFRC.bit.CSFA=1;	EPwm3Regs.AQCSFRC.bit.CSFB=1;
    }
    else if(System.iPwmDuty<0)
    {	EPwm1Regs.CMPA.half.CMPA=EPwm2Regs.CMPA.half.CMPA=Single.uiPwmprd+System.iPwmDuty;  //ռ�ձ�ȡ������Ƚ�ֵ
    //				EPwm2Regs.CMPA.half.CMPA=EPwm1Regs.CMPA.half.CMPA=Single.uiPwmprd+System.iPwmDuty;
        EPwm1Regs.AQCSFRC.bit.CSFA=1;	EPwm1Regs.AQCSFRC.bit.CSFB=2;
        EPwm2Regs.AQCSFRC.bit.CSFA=0;	EPwm2Regs.AQCSFRC.bit.CSFB=0;
        EPwm3Regs.AQCSFRC.bit.CSFA=1;	EPwm3Regs.AQCSFRC.bit.CSFB=1;
    }

    if(System.pwm360_cnt<359) System.pwm360_cnt++;
    else System.pwm360_cnt=0;
}

void Work_Deal(void)		//����������
{/*-----------------����״̬------------*/
	if(System.uiSystem_error!=0) System.uiStatus=0;		
/*-----------------��ͣ״̬------------*/
	if(System.uiStatus==0) 
	{	RELAY_OFF;						//�ؼ̵���
		System.iPwmDuty=0;				//ռ�ձ�����
		Menu_display.iU2=0;				//��ʾ��������
		Menu_display.iI2=Menu_display.iIv=Menu_display.iIw=0;	//��ʾ��������
		Menu_display.uiP2=Menu_display.uiQo=0;				
		EPwm3Regs.AQCSFRC.bit.CSFA=EPwm3Regs.AQCSFRC.bit.CSFB=1;	//3���ű����¹�ǿ�Ƶ�	
		EPwm2Regs.AQCSFRC.bit.CSFA=EPwm2Regs.AQCSFRC.bit.CSFB=1;	//2���ű����¹�ǿ�Ƶ�	
		EPwm1Regs.AQCSFRC.bit.CSFA=EPwm1Regs.AQCSFRC.bit.CSFB=1;	//1���ű����¹�ǿ�Ƶ�	
	}
/*-----------------����״̬------------*/
	else if(System.uiStatus== 1)	
	{	RELAY_ON;	//���̵���
		if(System.uiRelay_en_delay<100)  System.uiRelay_en_delay++;
		else	PWM_Deal();		//pwm������	
	}
}



