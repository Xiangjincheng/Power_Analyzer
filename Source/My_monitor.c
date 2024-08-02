//###########################################################################
// $TI Release: 2802x C/C++ Header Files V1.26 $
// $Release Date: February 2, 2010 $
//###########################################################################

#include "DSP2833x_Device.h"  // Device Headerfile and Examples Include File
#include "My_structure.h"
#include "My_variable_extern.h"   // DSP2802x Examples Include File
#include <math.h>
#include "FPU.h"

long int sin_buf[FFT_SIZE]={
0, 491, 980, 1467, 1951, 2430, 2903, 3369, 3827, 4276, 4714, 5141, 5556, 5957, 6344, 6716, 7071, 7410, 7730, 8032, 8315, 8577, 8819, 9040, 9239, 9415, 9569, 9700, 9808, 9892, 9952, 9988, 10000, 9988, 9952, 9892, 9808, 9700, 9569, 9415, 9239, 9040, 8819, 8577, 8315, 8032, 7730, 7410, 7071, 6716, 6344, 5957, 5556, 5141, 4714, 4276, 3827, 3369, 2903, 2430, 1951, 1467, 980, 491, 0, -491, -980, -1467, -1951, -2430, -2903, -3369, -3827, -4276, -4714, -5141, -5556, -5957, -6344, -6716, -7071, -7410, -7730, -8032, -8315,
-8577, -8819, -9040, -9239, -9415, -9569, -9700, -9808, -9892, -9952, -9988, -10000, -9988, -9952, -9892, -9808, -9700, -9569, -9415, -9239, -9040, -8819, -8577, -8315, -8032, -7730, -7410, -7071, -6716, -6344, -5957, -5556, -5141, -4714, -4276, -3827, -3369, -2903, -2430, -1951, -1467, -980, -491
};
long int cos_buf[FFT_SIZE]={
10000, 9988, 9952, 9892, 9808, 9700, 9569, 9415, 9239, 9040, 8819, 8577, 8315, 8032, 7730, 7410, 7071, 6716, 6344, 5957, 5556, 5141, 4714, 4276, 3827, 3369, 2903, 2430, 1951, 1467, 980, 491, 0, -491, -980, -1467, -1951, -2430, -2903, -3369, -3827, -4276, -4714, -5141, -5556, -5957, -6344, -6716, -7071, -7410, -7730, -8032, -8315, -8577, -8819,
-9040, -9239, -9415, -9569, -9700, -9808, -9892, -9952, -9988, -10000, -9988, -9952, -9892, -9808, -9700, -9569, -9415, -9239, -9040, -8819, -8577, -8315, -8032, -7730, -7410, -7071, -6716, -6344, -5957, -5556, -5141, -4714, -4276, -3827, -3369, -2903, -2430, -1951, -1467, -980, -491, 0, 491, 980, 1467, 1951, 2430, 2903, 3369, 3827, 4276, 4714, 5141, 5556, 5957, 6344, 6716, 7071, 7410, 7730, 8032, 8315, 8577, 8819, 9040, 9239, 9415, 9569, 9700, 9808, 9892, 9952, 9988
};

// 计算实部
float Dft48_Harm_Real(int a[], int Harm) {
    long int sum = 0;
    int i;
    for ( i = 0; i < FFT_SIZE; i++) {
        sum += (long int)a[i] * (long int)sin_buf[(i * Harm) % FFT_SIZE];
    }
    return sum * 0.0001;
}

// 计算虚部
float Dft48_Harm_Image(int a[], int Harm) {
    long int sum = 0;
    int i;
    for ( i= 0; i < FFT_SIZE; i++) {
        sum += (long int)a[i] * (long int)cos_buf[(i * Harm) % FFT_SIZE];
    }
    return sum * 0.0001;
}

void calculateTHD(int numHarmonics) {
    float rr, xx, amplitude;
    int i;
    for (i = 0; i < numHarmonics; i++) {
        rr = Dft48_Harm_Real(AC_Iin.iBuf, i + 1);
        xx = Dft48_Harm_Image(AC_Iin.iBuf, i + 1);
        amplitude = sqrt(rr * rr + xx * xx) * 0.01104845261 * AC_Iin.fKrms;
        PD1.fXiebo[i] = amplitude;
    }
    PD1.fTHD_Base = sqrt(AC_Iin.fRms*AC_Iin.fRms - PD1.fXiebo[0]*PD1.fXiebo[0]) / PD1.fXiebo[0];
    PD1.fTHD_Rms = sqrt(AC_Iin.fRms*AC_Iin.fRms - PD1.fXiebo[0]*PD1.fXiebo[0]) / AC_Iin.fRms;
 }
void CalAdc(struct AC_DATASET *pdtaset,unsigned int count)
{   pdtaset->iSamp1=pdtaset->iSamp-pdtaset->iOffset;
    pdtaset->iBuf[count]=pdtaset->iSamp1;
}

void CalAverValue(unsigned int cnt){
    static float ursm_sum = 0, irsm_sum = 0;
    ursm_sum += AC_Uin.fRms;    irsm_sum += AC_Iin.fRms;
    if(cnt % 5 == 0){
        AC_Uin.fRms_aver = ursm_sum / 5;    ursm_sum = 0;
        AC_Iin.fRms_aver = irsm_sum / 5;    irsm_sum = 0;
    }
}

void Calcaculate(void){
    unsigned int i;
    long int u_sum = 0, i_sum = 0, y_powersum = 0, q_powersum = 0;
    float k_power = AC_Iin.fKrms * 0.001684051742742305;

    for (i = 0; i < SAPMLE_NUM; i++) {
        u_sum += (long int)AC_Uin.iBuf[i] * (long int)AC_Uin.iBuf[i];
        i_sum += (long int)AC_Iin.iBuf[i] * (long int)AC_Iin.iBuf[i];
        y_powersum += (long int)AC_Uin.iBuf[i] * (long int)AC_Iin.iBuf[(i +1) % 127];
        q_powersum += (long int)AC_Uin.iBuf[i] * (long int)AC_Iin.iBuf[(i + 30) % 127];
    }
    AC_Uin.fRms = sqrt(u_sum/SAPMLE_NUM) * AC_Uin.fKrms;
    AC_Iin.fRms = sqrt(i_sum/SAPMLE_NUM) * AC_Iin.fKrms;

    PD1.fYpower = y_powersum * k_power;
    PD1.fWpower = q_powersum * k_power;
    PD1.fSpower = sqrt(PD1.fYpower * PD1.fYpower + PD1.fWpower * PD1.fWpower);
    PD1.fGlys = PD1.fYpower / PD1.fSpower;

    calculateTHD(HARMONIICS);
}

unsigned int ADCdata_Deal(void)
{   static unsigned int uiADC_Soc128=0;
    static unsigned int Iin_adc_flag = 0;

    AC_Uin.iSamp = AdcRegs.ADCRESULT1>>4;       CalAdc(&AC_Uin,uiADC_Soc128);

    if(Iin_adc_flag == 0)
        AC_Iin.iSamp = AdcRegs.ADCRESULT3>>4;
    else
        AC_Iin.iSamp = AdcRegs.ADCRESULT5>>4;

    CalAdc(&AC_Iin,uiADC_Soc128);


    if(uiADC_Soc128<127){
        uiADC_Soc128++;
        return 0;
    }
    else {
        uiADC_Soc128=0;
        //change i_sample_channel
        if(AC_Iin.fRms > 0.9){
            Iin_adc_flag = 1;  AC_Iin.fKrms = 0.00295767442;    AC_Iin.fKins = 0.00295767442;
        }
        if(AC_Iin.fRms < 0.8){
            Iin_adc_flag = 0;  AC_Iin.fKrms = 0.000730162171;      AC_Iin.fKins = 0.000730162171; //0.000825845;
        }
        return 1;

    }
}
