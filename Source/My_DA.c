#include "DSP2833x_Device.h"    // Device Headerfile and Examples Include File
#include "My_structure.h"
#include "My_variable_extern.h"   // DSP2802x Examples Include File
extern void DA_deal() ;
void InitXintf(void);
#define DA_CHA		*(Uint16 *)0x4100	
#define DA_CHB		*(Uint16 *)0x4101
#define DA_CHC		*(Uint16 *)0x4102
#define DA_CHD		*(Uint16 *)0x4103
#define DA_CHE		*(Uint16 *)0x4104
#define DA_CHF		*(Uint16 *)0x4105  //4104
#define DA_CHG		*(Uint16 *)0x4106
#define DA_CHH		*(Uint16 *)0x4107
void DA_deal()
{/*	Uint16 CHA_DATA;
    Uint16 CHB_DATA;
    Uint16 CHC_DATA;
    Uint16 CHD_DATA;
 	Uint16 CHE_DATA;
    Uint16 CHF_DATA;
    Uint16 CHG_DATA;
    Uint16 CHH_DATA;*/

/*	CHC_DATA=AC_U2.fInvalue*32.77+4096;//输出电压125v对应2.5v  100倍 DA芯片输出值1V对应实际值50V，故K=4096/125=32.77（下同）.
	CHD_DATA=AC_Iu.fInvalue*1638.4+4096;	//输出电流1A对应1v	1倍	DA芯片输出值1V对应实际值1A，故K=4096/2.5=1638.400（下同）.	
	CHA_DATA=DC_U1.fAve*32.768+4096; 	//输入电压125v对应2.5v  100倍 DA芯片输出值1V对应实际值50V，故K=4096/250=32.77,然后微调        
	CHB_DATA=DC_I1.fInvalue*1638.4+4096;						
	CHE_DATA=4096;
	CHF_DATA=4096;
	CHG_DATA=4096;
	CHH_DATA=4096;

	DA_CHA = CHA_DATA;
	DA_CHB = CHB_DATA;
	DA_CHC = CHC_DATA;
	DA_CHD = CHD_DATA;
	DA_CHE = CHE_DATA;
	DA_CHF = CHF_DATA;
	DA_CHG = CHG_DATA;
	DA_CHH = CHH_DATA;*/

					}








