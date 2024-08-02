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
	int iSamp;			//采样值
	int iSamp1;			//去偏置采样值
	int iBuf[32];//保存数据值
	long int lSum;		//累加值
	int   iOffset;		//偏置值	
	float fKins;		//瞬时值系数
	float fInvalue;		//实际瞬时值
	float fKave;		//平均值系数
	float fAve;			//实际平均值
};

struct AC_DATASET{      
	int iSamp;			//采样值
	int iSamp1;
	int iBuf[128];		//去偏置采样值
	unsigned int sample_buf[128];
	int   Sum;			//去偏置采样值累加
	double   Sum2;		//去偏置采样值平方和
	int   iOffset;		// 偏置值
	float fKrms;		//有效值系数
	float fRms;			//实际有效值
	float fRms_aver;    //实际瞬时值
	float fKins;		//瞬时值系数	
};

struct Power_Deal{
    float fYpower;      //有功功率
    float fYpbuff[128];
    float fWpbuff[128];
    float fSpower;      //视在功率
    float fWpower;      //无功功率
    float fGlys;        //功率因素
    float fXiebo[HARMONIICS];             // 谐波
    float fTHD_Base;
    float fTHD_Rms;
};
struct FFT_data{
    float RFFToutBuff[FFT_SIZE];            // RFFT 复数结果
    float RFFTmagBuff[FFT_SIZE/2 + 1];        // RFFT 幅值向量
    float RFFTF32Coef[FFT_SIZE];    // RFFT 旋转因子
};

struct PIBUF{
    float fGive;        //给定值
    float fFeed;        //反馈值
    float fErr;         //给定值与反馈值的误差
    float fPout;        //比例量
    float fIout;        //积分量
    float fOut;         //输出量
    float fKp;          //比例系数
    float fKi;          //积分系数
    float fIoutmax;     //积分量上限
    float fIoutmin;     //积分量下限
    float fOutmax;      //输出量上限
    float fOutmin;      //输出量下限
    float fOut1;        //输出量限幅1
};

struct SYSTEM_STATUS{   
    unsigned int    uiStatus;       //系统状态
    unsigned int    uiWork_status;      //工作模式
    unsigned int    pwm360_cnt;             //0-359 一个正弦周期计数
    unsigned int    uiFlag_05ms;        //05ms标记
    unsigned int    uiSystem_error;     //高8位不可恢复错误，低8位可恢复故障
    unsigned long   ulError_delay;
    unsigned int    LCD_flag;
    unsigned int    lcd_auto;
    unsigned int    adc_flag;

    int iPwmDuty;                       //占空比
    int iPower2;                        //占空比
    int iuduty;
    int ivduty;
    int iwduty;
    unsigned int    uiRelay_en_delay;   //启动前继电器合闸延时计数
};

struct MENU_CMD{
	int 	itheta;		
	float 	fDutyGive;   		//占空比开环的速度给定
	float 	fIoGive;		//电流给定
	float   fUgive;  		//电压给定
	int	iFrqGive;		//频率给定
	float   fSpeedGive;           //转速给定
};

struct MENU_DISPLAY{		
	unsigned int uisystemstatus;//系统状态显示
	unsigned int uiworkstatus;	//工作状态显示
	unsigned int uifaultstatus;	//错误状态显示
	int iU2;			//输出电压显示
	int iI2;
	int iIv;
	int iIw;			//输出电流显示
	int itheta;					
	unsigned int uiP2;
	unsigned int uiQo;		//输出功率显示
	int 	iDuty;			//占空比显示
	int	iFrqGive;		//频率给定显示
	int 	iDutygive;		//占空比给定显示
	unsigned int uiUgive;		//给定电压显示
	int iIgive;			//电流给定显示
	unsigned int uiU1;		//输入电压显示
	unsigned int uiI1;          	//输入电流
	unsigned int uiTem;  		//温度显示
	int    uiN;           //转速显示
	int    uiNgive;     //转速给定显示 
	int    moshi;  
};
struct MENU_KEY{		
	unsigned int uiKEY_IO;     	//描述8个按键的高低电平状态   1按下
	unsigned int uiKEYsacn_status;  //描述按键是否有效状态 0无效/1按键有效
};

struct SINGLE{
	unsigned int 	uiFrq;		//输出频率
	float 			fUgive;		//加补偿以后的电压给定
	unsigned int 	uiPwmprd;	//每个三角波的周期值
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












