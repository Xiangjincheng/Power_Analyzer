#ifndef STRUCTURE_H
#define STRUCTURE_H

#ifdef __cplusplus
extern "C" {
#endif
#define FFT_STAGES 7
#define FFT_SIZE (1 << FFT_STAGES)
#define HARMONIICS 11
#define SAPMLE_NUM FFT_SIZE
struct DC_DATASET{ 
	int iSamp;			//����ֵ
	int iSamp1;			//ȥƫ�ò���ֵ
	int iBuf[32];//��������ֵ
	long int lSum;		//�ۼ�ֵ
	int   iOffset;		//ƫ��ֵ	
	float fKins;		//˲ʱֵϵ��
	float fInvalue;		//ʵ��˲ʱֵ
	float fKave;		//ƽ��ֵϵ��
	float fAve;			//ʵ��ƽ��ֵ
};

struct AC_DATASET{      
	int iSamp;			//����ֵ
	int iSamp1;
	int iBuf[128];		//ȥƫ�ò���ֵ
	unsigned int sample_buf[128];
	int   Sum;			//ȥƫ�ò���ֵ�ۼ�
	double   Sum2;		//ȥƫ�ò���ֵƽ����
	int   iOffset;		// ƫ��ֵ
	float fKrms;		//��Чֵϵ��
	float fRms;			//ʵ����Чֵ
	float fRms_aver;    //ʵ��˲ʱֵ
	float fKins;		//˲ʱֵϵ��	
};

struct Power_Deal{
    float fYpower;      //�й�����
    float fYpbuff[128];
    float fWpbuff[128];
    float fSpower;      //���ڹ���
    float fWpower;      //�޹�����
    float fGlys;        //��������
    float fXiebo[HARMONIICS];             // г��
    float fTHD_Base;
    float fTHD_Rms;
};
struct FFT_data{
    float RFFToutBuff[FFT_SIZE];            // RFFT �������
    float RFFTmagBuff[FFT_SIZE/2 + 1];        // RFFT ��ֵ����
    float RFFTF32Coef[FFT_SIZE];    // RFFT ��ת����
};

struct PIBUF{
    float fGive;        //����ֵ
    float fFeed;        //����ֵ
    float fErr;         //����ֵ�뷴��ֵ�����
    float fPout;        //������
    float fIout;        //������
    float fOut;         //�����
    float fKp;          //����ϵ��
    float fKi;          //����ϵ��
    float fIoutmax;     //����������
    float fIoutmin;     //����������
    float fOutmax;      //���������
    float fOutmin;      //���������
    float fOut1;        //������޷�1
};

struct SYSTEM_STATUS{   
    unsigned int    uiStatus;       //ϵͳ״̬
    unsigned int    uiWork_status;      //����ģʽ
    unsigned int    pwm360_cnt;             //0-359 һ���������ڼ���
    unsigned int    uiFlag_05ms;        //05ms���
    unsigned int    uiSystem_error;     //��8λ���ɻָ����󣬵�8λ�ɻָ�����
    unsigned long   ulError_delay;
    unsigned int    LCD_flag;
    unsigned int    lcd_auto;
    unsigned int    adc_flag;

    int iPwmDuty;                       //ռ�ձ�
    int iPower2;                        //ռ�ձ�
    int iuduty;
    int ivduty;
    int iwduty;
    unsigned int    uiRelay_en_delay;   //����ǰ�̵�����բ��ʱ����
};

struct MENU_CMD{
	int 	itheta;		
	float 	fDutyGive;   		//ռ�ձȿ������ٶȸ���
	float 	fIoGive;		//��������
	float   fUgive;  		//��ѹ����
	int	iFrqGive;		//Ƶ�ʸ���
	float   fSpeedGive;           //ת�ٸ���
};

struct MENU_DISPLAY{		
	unsigned int uisystemstatus;//ϵͳ״̬��ʾ
	unsigned int uiworkstatus;	//����״̬��ʾ
	unsigned int uifaultstatus;	//����״̬��ʾ
	int iU2;			//�����ѹ��ʾ
	int iI2;
	int iIv;
	int iIw;			//���������ʾ
	int itheta;					
	unsigned int uiP2;
	unsigned int uiQo;		//���������ʾ
	int 	iDuty;			//ռ�ձ���ʾ
	int	iFrqGive;		//Ƶ�ʸ�����ʾ
	int 	iDutygive;		//ռ�ձȸ�����ʾ
	unsigned int uiUgive;		//������ѹ��ʾ
	int iIgive;			//����������ʾ
	unsigned int uiU1;		//�����ѹ��ʾ
	unsigned int uiI1;          	//�������
	unsigned int uiTem;  		//�¶���ʾ
	int    uiN;           //ת����ʾ
	int    uiNgive;     //ת�ٸ�����ʾ 
	int    moshi;  
};
struct MENU_KEY{		
	unsigned int uiKEY_IO;     	//����8�������ĸߵ͵�ƽ״̬   1����
	unsigned int uiKEYsacn_status;  //���������Ƿ���Ч״̬ 0��Ч/1������Ч
};

struct SINGLE{
	unsigned int 	uiFrq;		//���Ƶ��
	float 			fUgive;		//�Ӳ����Ժ�ĵ�ѹ����
	unsigned int 	uiPwmprd;	//ÿ�����ǲ�������ֵ
   	unsigned int 	period;
	unsigned int 	itheta;
};

struct DA_BL{
	unsigned int TAG;
	unsigned int DA_Data;
	unsigned int DA_Data1;
	unsigned int tag;
};

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif	  //end












