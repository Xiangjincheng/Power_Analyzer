#include "DSP2833x_Device.h"    // Device Headerfile and Examples Include File
#include "My_structure.h"
#include "My_variable_extern.h"   // DSP2802x Examples Include File 
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
unsigned int Keysjudge_cnt=0;//閹稿鏁崚銈嗘焽婢跺嫮鎮婇敍宀�鏁ゆ禍搴℃閺冩儼顓搁弫锟�
unsigned int Keyjudge_delay=0;//閹稿鏁崚銈嗘焽瀵よ埖妞�
#define MENU_KEY1_EN    GpioDataRegs.GPBDAT.bit.GPIO55==0       //閼挎粌宕熼幐澶愭暛1 濡拷濞村鍩屾担搴ｆ暩楠烇拷
#define MENU_KEY2_EN    GpioDataRegs.GPBDAT.bit.GPIO54==0       //閼挎粌宕熼幐澶愭暛2 濡拷濞村鍩屾担搴ｆ暩楠烇拷
#define MENU_KEY3_EN    GpioDataRegs.GPBDAT.bit.GPIO53==0       //閼挎粌宕熼幐澶愭暛3 濡拷濞村鍩屾担搴ｆ暩楠烇拷
#define MENU_KEY4_EN    GpioDataRegs.GPBDAT.bit.GPIO52==0       //閼挎粌宕熼幐澶愭暛4 濡拷濞村鍩屾担搴ｆ暩楠烇拷
#define MENU_KEY5_EN    GpioDataRegs.GPBDAT.bit.GPIO51==0       //閼挎粌宕熼幐澶愭暛5 濡拷濞村鍩屾担搴ｆ暩楠烇拷
#define MENU_KEY6_EN    GpioDataRegs.GPBDAT.bit.GPIO50==0       //閼挎粌宕熼幐澶愭暛6 濡拷濞村鍩屾担搴ｆ暩楠烇拷

extern void LCD12864_init(void); 
extern void CLEAR_Screen(void); 
extern void   ServiceDog(void);
extern unsigned char LCD_char[8][18];
extern unsigned const char display_statusdata[5][7];
extern unsigned const char display_workstatusdata[6][7];
extern void lcd12864_display_picture(unsigned int LINE_start,unsigned char LINE_end,unsigned char ROW_start,unsigned char ROW_end);
extern void lcd12864_display_char(unsigned int LINE_start,unsigned char LINE_end,unsigned char ROW_start,unsigned char ROW_end,unsigned int f);
extern void lcd_display_shuju_deal(unsigned int shuju,unsigned int flag,unsigned char line,unsigned char row1,unsigned char row2,unsigned char row3,unsigned char row4);
extern void lcd_display_shuju_deal2(unsigned int shuju,unsigned int flag,unsigned char line,unsigned char row1,unsigned char row2);
extern void lcd_display_shuju_deal3(unsigned int shuju,unsigned int flag,unsigned char line,unsigned char row1,unsigned char row2,unsigned char row3);

unsigned int key_delay_cnt[8]={0,0,0,0,0,0,0,0};
unsigned int key_delay_max[8]={4000,1000,500,500,500,500,500,500};

void keyIO_scan(void)   //鐠囪褰囧В蹇庨嚋閹稿鏁璉O閸欙絿濮搁幀锟� 妤傛鏁搁獮鍏呰礋1 娴ｅ海鏁搁獮鍏呰礋0 娴ｅ海鏁搁獮铏鐠囧瓨妲戦張澶嬪瘻闁款喗瀵滄稉锟�
{   if(MENU_KEY1_EN)    Menu_key.uiKEY_IO&=~0x01;    //閸氼垰濮╅崑婊勵剾濡拷濞达拷 閺佺増宓佺�涙ê婀狵EYsacn_status閻ㄥ嫪缍�8娴ｏ拷
    else    Menu_key.uiKEY_IO|=0x01;
    if(MENU_KEY2_EN)    Menu_key.uiKEY_IO&=~0x02;   //濡�崇础閸掑洦宕插Λ锟藉ù锟�
    else    Menu_key.uiKEY_IO|=0x02;
    if(MENU_KEY3_EN)    Menu_key.uiKEY_IO&=~0x04;   //閸戝繐鐨紒娆忕暰濡拷濞达拷
    else    Menu_key.uiKEY_IO|=0x04;
    if(MENU_KEY4_EN)    Menu_key.uiKEY_IO&=~0x08;   //婢х偛濮炵紒娆忕暰濡拷濞达拷
    else    Menu_key.uiKEY_IO|=0x08;
    if(MENU_KEY5_EN)    Menu_key.uiKEY_IO&=~0x10;   //閸戝繐鐨０鎴犲芳濡拷濞达拷
    else    Menu_key.uiKEY_IO|=0x10;
    if(MENU_KEY6_EN)    Menu_key.uiKEY_IO&=~0x20;   //婢х偛濮炴０鎴犲芳濡拷濞达拷
    else    Menu_key.uiKEY_IO|=0x20;
}
void key_judge1(unsigned int BIT_station) //閹稿鏁張澶嬫櫏閻╂垶绁� 瑜版挻瀵滈柨顔芥緱瀵拷閺冭埖瀵滈柨顔芥箒閺侊拷
{   static unsigned int flag_ok = 0;
    if( !(Menu_key.uiKEY_IO & (1<<BIT_station)) ) //瑜版挻顥呭ù瀣煂娴ｅ海鏁搁獮锟� 閸掋倖鏌囬張澶嬪瘻闁款喗瀵滄稉锟�
    {   if( key_delay_cnt[BIT_station] < key_delay_max[BIT_station])    key_delay_cnt[BIT_station]++;
    }
    else //閹稿鏁弶鎯х磻閸氾拷 鏉╂稖顢戦張澶嬫櫏閸掋倖鏌囬崣濠傛倵缂侇厼顦╅悶锟�
    {   if(key_delay_cnt[BIT_station] > 49 )
        {   if( !flag_ok )  //婵″倹鐏夐幐澶愭暛鏉╂ɑ婀張澶嬫櫏 閸掓瑦鐖ｇ拋鐗堟箒閺侊拷
            {   Menu_key.uiKEYsacn_status|= 1<<(BIT_station);flag_ok = 1;}
            if( key_delay_cnt[BIT_station] < key_delay_max[BIT_station])    key_delay_cnt[BIT_station]++;
            else{   key_delay_cnt[BIT_station] = 0; flag_ok = 0;    }
        }
        else key_delay_cnt[BIT_station] = 0;
}   }
void key_judge2(unsigned int BIT_station) //閹稿鏁張澶嬫櫏閻╂垶绁� 闂冨弶濮堢紒鎾存将閺冭泛宓嗛幐澶愭暛閺堝鏅�
{   if((Menu_key.uiKEY_IO & (1<<BIT_station))==0) //瑜版挻顥呭ù瀣煂娴ｅ海鏁搁獮锟� 閸掋倖鏌囬張澶嬪瘻闁款喗瀵滄稉锟�
    {   if(key_delay_cnt[BIT_station] < 50)     //0-49  闂冨弶濮堥崚銈嗘焽50濞嗭拷
        {   key_delay_cnt[BIT_station]++;   //鐠佲剝鏆熺槐顖氬閻╃鍤﹂梼鍙夊鐠佲剝鏆熼崚锟�50 閸楀疇顓绘稉鐑樺瘻闁款喗婀侀弫锟�
            if(key_delay_cnt[BIT_station]==50) Menu_key.uiKEYsacn_status|=  1<<(BIT_station);
    }   }
    else if(key_delay_cnt[BIT_station]<49) key_delay_cnt[BIT_station]=0; //濞屸剝婀侀幐澶愭暛閹稿绗呴弮璁圭礉閹稿鏁梼鍙夊濞撳懘娴� 閺堝鏅ョ拋鈩冩殶濞撳懘娴�
    if(key_delay_cnt[BIT_station]>49)   //閹稿鏁張澶嬫櫏閸氾拷 缁涘绶熺拋鈩冩殶閸掔増娓舵径褍锟斤拷 閹靛秷鍏橀柌宥嗘煀瀵拷婵瀵滈柨顔炬磧濞达拷
    {   if(key_delay_cnt[BIT_station]< key_delay_max[BIT_station]) key_delay_cnt[BIT_station]++;
        else    key_delay_cnt[BIT_station]=0;
}   }
void key_judge(unsigned int BIT_station) //閹稿鏁張澶嬫櫏閻╂垶绁� 闂冨弶濮堢紒鎾存将閺冭泛宓嗛幐澶愭暛閺堝鏅�
{   if((Menu_key.uiKEY_IO & (1<<BIT_station))==0) //瑜版挻顥呭ù瀣煂娴ｅ海鏁搁獮锟� 閸掋倖鏌囬張澶嬪瘻闁款喗瀵滄稉锟�
    {   if(key_delay_cnt[BIT_station] < 50)     //0-49  闂冨弶濮堥崚銈嗘焽50濞嗭拷
        {   key_delay_cnt[BIT_station]++;   //鐠佲剝鏆熺槐顖氬閻╃鍤﹂梼鍙夊鐠佲剝鏆熼崚锟�50 閸楀疇顓绘稉鐑樺瘻闁款喗婀侀弫锟�
            if(key_delay_cnt[BIT_station]==50) Menu_key.uiKEYsacn_status|=  1<<(BIT_station);
    }   }
    else key_delay_cnt[BIT_station]=0; //濞屸剝婀侀幐澶愭暛閹稿绗呴弮璁圭礉閹稿鏁梼鍙夊濞撳懘娴� 閺堝鏅ョ拋鈩冩殶濞撳懘娴�
    if(key_delay_cnt[BIT_station]>49)   //閹稿鏁張澶嬫櫏閸氾拷 缁涘绶熺拋鈩冩殶閸掔増娓舵径褍锟斤拷 閹靛秷鍏橀柌宥嗘煀瀵拷婵瀵滈柨顔炬磧濞达拷
    {   if(key_delay_cnt[BIT_station]< key_delay_max[BIT_station]) key_delay_cnt[BIT_station]++;
        else    key_delay_cnt[BIT_station]=0;
}   }

void menu_key_deal(void)
{   unsigned int menu_key_cnt;
    keyIO_scan();       //閹稿鏁幙宥勭稊閹殿偅寮�
    for(menu_key_cnt=0;menu_key_cnt<6;menu_key_cnt++)   key_judge(menu_key_cnt);
    if((Menu_key.uiKEYsacn_status&0x0001)!=0)
    {   Menu_key.uiKEYsacn_status&=~0x0001;                     //閹稿鏁張澶嬫櫏瀹歌尙绮℃径鍕倞 濞撳懘娅庨張澶嬫櫏娴ｏ拷
        if((System.uiStatus&0x01)==0) System.uiStatus|=0x01;    //婵″倹鐏夐弰顖氱窡閺堝搫姘ㄦ潻鎰攽椤拷
            else System.uiStatus&=~0x01;                        //閺勵垵绻嶇悰灞藉灟瀵板懏婧�
        if((System.uiStatus&0x02)==2) System.uiStatus=0x00;     //???
    }
//  if((Menu_key.uiKEYsacn_status&0x0002)!=0)       //閸︺劎閮寸紒鐔奉槱娴滃骸绶熼張鐑樻閻绱濋崣顖欎簰0-5閸忥拷6缁夊秴浼愭担婊勀佸蹇撳瀼閹癸拷
//  {   Menu_key.uiKEYsacn_status&=~0x0002;         //閹稿鏁張澶嬫櫏瀹歌尙绮℃径鍕倞 濞撳懘娅庨張澶嬫櫏娴ｏ拷
//      if(System.LCD_flag < 3){System.LCD_flag++;}
//      else {System.LCD_flag = 0;}
//     //6娑擃亝膩瀵繐鍨忛幑锟�
//
//  }
    if((Menu_key.uiKEYsacn_status&0x0004)!=0)
    {   Menu_key.uiKEYsacn_status&=~0x0004;     //閹稿鏁張澶嬫櫏瀹歌尙绮℃径鍕倞 濞撳懘娅庨張澶嬫櫏娴ｏ拷
        Menu_cmd.fDutyGive-=0.01;   //鐠嬪啫鍩楁惔锕�鍣�
        if(Menu_cmd.fDutyGive<0.1) Menu_cmd.fDutyGive=0.1;
    }
    if((Menu_key.uiKEYsacn_status&0x0008)!=0)
    {   Menu_key.uiKEYsacn_status&=~0x0008;     //閹稿鏁張澶嬫櫏瀹歌尙绮℃径鍕倞 濞撳懘娅庨張澶嬫櫏娴ｏ拷
        Menu_cmd.fDutyGive+=0.01;   //鐠嬪啫鍩楁惔锕�濮�
        if(Menu_cmd.fDutyGive>1) Menu_cmd.fDutyGive=1;
    }
    if((Menu_key.uiKEYsacn_status&0x0010)!=0)
    {   Menu_key.uiKEYsacn_status&=~0x0010;
        if( Single.uiFrq>5) Single.uiFrq-=1;
        Single.uiPwmprd=(75000000/360)/Single.uiFrq;    //150M/(F*360*2)
    }
    if((Menu_key.uiKEYsacn_status&0x0020)!=0)
    {   Menu_key.uiKEYsacn_status&=~0x0020;
        if( Single.uiFrq<55)    Single.uiFrq+=1;
        Single.uiPwmprd=(75000000/360)/Single.uiFrq;    //150M/(F*360*2)
    }
}
void DATA_displaydata_init(void)    //閸氬嫮顫掗弰鍓с仛閺佺増宓侀崚婵嗩潗閸栵拷
{   Menu_display.uisystemstatus=0;
    Menu_display.uifaultstatus=0x0000;
    Menu_display.iU2=0;         Menu_display.iI2=0;
    Menu_display.iIv=0;         Menu_display.iIw=0;
    Menu_display.uiP2=0;        Menu_display.iDuty=0;
    Menu_display.itheta=0;      Menu_display.iDutygive=0;
    Menu_display.iFrqGive=0;    Menu_display.uiU1=0;
    Menu_display.uiI1=0;        Menu_display.uiTem=0;
    System.uiSystem_error=0;
}

void menu_lcddisplay_datadeal1(void)                //閸戣姤鏆熼柌宀�娈戦崣姗�鍣烘稊妯逛簰10閹存牞锟斤拷100閿涘本妲告稉杞扮啊閸︺劍妯夌粈鐑樻殶閹诡喖顦╅悶鍡楀毐閺佷即鍣锋潻娑滎攽濮ｅ繋绔存担宥囨畱閸掑棛顬�
{   unsigned int i;
    Menu_display.uisystemstatus=System.uiStatus;    //鐠囪褰囩化鑽ょ埠瀹搞儰缍旈悩鑸碉拷锟�
    Menu_display.uifaultstatus=System.uiSystem_error;   //鐠囪褰囬弫鍛存
    Menu_display.iFrqGive=Single.uiFrq;     Menu_display.itheta=Menu_cmd.itheta;
    Menu_display.uiU1=DC_U1.fAve*100;
//    if(System.uiWork_status==0) //闂勫秴甯�
//    {   Menu_display.uiI1=DC_I1.fAve*100;       Menu_display.iU2=AC_U2.iSamp*100;
//        Menu_display.iI2=AC_Iu.iSamp*100;       Menu_display.uiP2=PD1.fSpower;
//    }
//    else if(System.uiWork_status==1)    //閸楀洤甯�
//    {   Menu_display.uiI1=-DC_I1.fAve*100;      Menu_display.iU2=AC_U2.iSamp*100;
//        Menu_display.iI2=-AC_Iu.iSamp*100;      Menu_display.uiP2=PD1.fSpower;
//    }
//    else
//    {   Menu_display.uiI1=(Menu_display.uiI1*7+DC_I1.fAve*100)/8; //娴ｅ酣锟芥碍鎶ゅ▔锟�
//        Menu_display.iU2=AC_U2.fRms*100;        Menu_display.iI2=AC_Iu.fRms*100;
//        Menu_display.iIv=AC_Iv.fRms*100;        Menu_display.iIw=AC_Iw.fRms*100;
//        Menu_display.uiP2=PD1.fYpower;            //鐠囪褰囬張澶婂閸旓拷
//    }
    Menu_display.iDuty=Menu_cmd.fDutyGive*100;      //鐠囪褰囬崡鐘碘敄濮ｏ拷
    if(DC_Untc.iSamp>3680)  {Menu_display.uiTem=0.62*(float)DC_Untc.iSamp-1681.6;}
    else Menu_display.uiTem=0.30*(float)DC_Untc.iSamp-504;//DC_Untc.fAve*100;//鐠囪褰囧〒鈺佸
//    Menu_display.uiN=MotorStatus.fRpm;
    Menu_display.uiNgive=Menu_cmd.fSpeedGive;
//    if(Menu_display.uifaultstatus!=0)           //閺佸懘娈� 閺勫墽銇欶T +閺佸懘娈伴弽鍥唶娴ｏ拷
//    {   for(i=0;i<7;i++)    LCD_char[0][i]=display_statusdata[2][i];
//        LCD_char[0][7]=(Menu_display.uifaultstatus>>4)&0x000F;
//        LCD_char[0][8]=Menu_display.uifaultstatus&0x000F;
//    }
//    else if(Menu_display.uisystemstatus==0)         //瀵板懏婧�閺冿拷 閺勫墽銇氬鍛簚
//    {   for(i=0;i<7;i++)
//        {  LCD_char[0][i]=display_statusdata[0][i];//瀵板懏婧�閺勫墽銇歋TANDBY
//           LCD_char[0][7]=LCD_char[0][8]=LCD_char[0][9]= LCD_char[0][10]=64;
//           LCD_char[1][i+1]=display_workstatusdata[4][i];//閺勫墽銇氬Ο鈥崇础
//    }   }
//    else if((Menu_display.uisystemstatus&0x01)!=0)          //鏉╂劘顢�
//    {   for(i=0;i<7;i++)
//        {   LCD_char[0][i]=display_statusdata[1][i];//閺勫墽銇歊UNING
//            LCD_char[0][7]=LCD_char[0][8]=LCD_char[0][9]=LCD_char[0][10]=64;
//    }   }
    //for(i=0;i<7;i++)LCD_char[5][i+1]=display_workstatusdata[4][i];//閺勫墽銇氬Ο鈥崇础閻樿埖锟斤拷

//    LCD_char[1][9]=13;  LCD_char[1][10]=30; LCD_char[1][11]=29;//閸楁洜娴塖PWM
//    LCD_char[1][12]=34; LCD_char[1][13]=64; LCD_char[1][17]=65;
//    LCD_char[0][11]=64; LCD_char[0][17]=35; LCD_char[0][16]=17;
//    if(System.LCD_flag==0)
//    lcd_display_shuju_deal(Menu_display.iFrqGive,System.LCD_flag,0,12,13,14,15);//缁楋拷1鐞涘本妯夌粈铏圭舶鐎规岸顣堕悳锟�
//    if(System.LCD_flag==0)
//    lcd_display_shuju_deal2(Menu_display.iDuty  ,System.LCD_flag,1,15,16);     //缁楋拷2鐞涘本妯夌粈楦跨殶閸掕泛瀹�

}
//void uiLCD_auto(void)
//{
//    if(System.uiFlag_05ms == 1 && System.lcd_auto != 4000)
//    {System.lcd_auto++;}
//    else if(System.lcd_auto == 4000 && System.LCD_flag != 3)
//    {System.LCD_flag++;}
//    else if(System.lcd_auto == 4000 && System.LCD_flag == 3)
//    {System.LCD_flag = 0;}
//}
void menu_lcddisplay_datadeal2(void)
{
    if(System.LCD_flag==0)
    {
        lcd_display_shuju_deal(PD1.fTHD_Base*100,System.LCD_flag,0,5,6,8,9);
        lcd_display_shuju_deal(PD1.fTHD_Rms*100,System.LCD_flag,1,5,6,8,9);
        lcd_display_shuju_deal(AC_Iin.fRms*100,System.LCD_flag,2,3,4,6,7);
           lcd_display_shuju_deal(AC_Uin.fRms*100,System.LCD_flag,3,3,4,6,7);     //缁楋拷3鐞涘本妯夌粈楦跨翻閸忋儳鏁搁崢锟�
           lcd_display_shuju_deal(PD1.fYpower*10 ,System.LCD_flag,4,2,3,4,6);//缁楋拷5鐞涘本妯夌粈绨庨惄鍝ユ暩濞翠焦婀侀弫鍫濓拷锟�
           lcd_display_shuju_deal(PD1.fSpower*10 ,System.LCD_flag,5,2,3,4,6);     //缁楋拷5鐞涘本妯夌粈楦跨翻閸戣櫣鏁搁崢瀣箒閸婏拷
           lcd_display_shuju_deal(PD1.fGlys*1000 ,System.LCD_flag,6,2,4,5,6);   //缁楋拷6鐞涘本妯夌粈绨愰惄鍝ユ暩濞翠焦婀侀弫鍫濓拷锟�
//           lcd_display_shuju_deal(PD1.fTHD_Base*100   ,System.LCD_flag,3,13,15,16,17);//缁楋拷6鐞涘本妯夌粈绨戦惄鍝ユ暩濞翠焦婀侀弫鍫濓拷锟�
//           lcd_display_shuju_deal(PD1.fTHD_Rms*100   ,System.LCD_flag,4,13,15,16,17);//缁楋拷6鐞涘本妯夌粈绨戦惄鍝ユ暩濞翠焦婀侀弫鍫濓拷锟�
       //  lcd_display_shuju_deal(PD1.fYpower,System.LCD_flag,2,3,4,6,7);    //缁楋拷7鐞涘本妯夌粈鐑樻箒閸旂喎濮涢悳锟�
       ////    lcd_display_shuju_deal(Menu_display.uiN ,System.LCD_flag,3,3,4,5,6);    //缁楋拷8鐞涘本妯夌粈楦挎祮闁拷
       //  lcd_display_shuju_deal(Menu_display.uiTem,System.LCD_flag,3,12,13,14,16);//缁楋拷8鐞涘本妯夌粈鐑樹刊鎼达拷
    }
    else if(System.LCD_flag==1)
    {lcd_display_shuju_deal(PD1.fXiebo[0]*1000,System.LCD_flag,1,3,5,6,7);
    lcd_display_shuju_deal(PD1.fXiebo[1]*1000,System.LCD_flag,2,3,5,6,7);
    lcd_display_shuju_deal(PD1.fXiebo[2]*1000,System.LCD_flag,3,3,5,6,7);     //缁楋拷3鐞涘本妯夌粈楦跨翻閸忋儳鏁搁崢锟�
    lcd_display_shuju_deal(PD1.fXiebo[3]*1000,System.LCD_flag,4,3,5,6,7);//缁楋拷5鐞涘本妯夌粈绨庨惄鍝ユ暩濞翠焦婀侀弫鍫濓拷锟�
    lcd_display_shuju_deal(PD1.fXiebo[4]*1000,System.LCD_flag,5,3,5,6,7);     //缁楋拷5鐞涘本妯夌粈楦跨翻閸戣櫣鏁搁崢瀣箒閸婏拷
    lcd_display_shuju_deal(PD1.fXiebo[5]*1000,System.LCD_flag,1,12,14,15,16);
    lcd_display_shuju_deal(PD1.fXiebo[6]*1000,System.LCD_flag,2,12,14,15,16);
    lcd_display_shuju_deal(PD1.fXiebo[7]*1000,System.LCD_flag,3,12,14,15,16);     //缁楋拷3鐞涘本妯夌粈楦跨翻閸忋儳鏁搁崢锟�
    lcd_display_shuju_deal(PD1.fXiebo[8]*1000,System.LCD_flag,4,12,14,15,16);//缁楋拷5鐞涘本妯夌粈绨庨惄鍝ユ暩濞翠焦婀侀弫鍫濓拷锟�
    lcd_display_shuju_deal(PD1.fXiebo[9]*1000,System.LCD_flag,5,12,14,15,16);     //缁楋拷5鐞涘本妯夌粈楦跨翻閸戣櫣鏁搁崢瀣箒閸婏拷
   //  lcd_display_shuju_deal(Menu_display.iIw ,System.LCD_flag,1,12,13,15,16);//缁楋拷6鐞涘本妯夌粈绨戦惄鍝ユ暩濞翠焦婀侀弫鍫濓拷锟�
//    //  lcd_display_shuju_deal(PD1.fYpower,System.LCD_flag,2,3,4,6,7);    //缁楋拷7鐞涘本妯夌粈鐑樻箒閸旂喎濮涢悳锟�
//    ////    lcd_display_shuju_deal(Menu_display.uiN ,System.LCD_flag,3,3,4,5,6);    //缁楋拷8鐞涘本妯夌粈楦挎祮闁拷
//    //  lcd_display_shuju_deal(Menu_display.uiTem,System.LCD_flag,3,12,13,14,16);//缁楋拷8鐞涘本妯夌粈鐑樹刊鎼达拷
     }
  //  else if(System.LCD_flag==2)
     //   {
//            lcd_display_shuju_deal(AC_Iu.iSamp,System.LCD_flag,7,3,4,6,7);
//            lcd_display_shuju_deal(AC_U2.iSamp ,System.LCD_flag,0,3,4,6,7);     //缁楋拷3鐞涘本妯夌粈楦跨翻閸忋儳鏁搁崢锟�
//            lcd_display_shuju_deal(PD1.fYpower*10  ,System.LCD_flag,1,2,3,4,6);//缁楋拷5鐞涘本妯夌粈绨庨惄鍝ユ暩濞翠焦婀侀弫鍫濓拷锟�
//            lcd_display_shuju_deal(PD1.fSpower*10  ,System.LCD_flag,2,2,3,4,6);     //缁楋拷5鐞涘本妯夌粈楦跨翻閸戣櫣鏁搁崢瀣箒閸婏拷
//            lcd_display_shuju_deal(PD1.fGlys*1000  ,System.LCD_flag,3,2,4,5,6);   //缁楋拷6鐞涘本妯夌粈绨愰惄鍝ユ暩濞翠焦婀侀弫鍫濓拷锟�
//        //  lcd_display_shuju_deal(Menu_display.iIw ,System.LCD_flag,1,12,13,15,16);//缁楋拷6鐞涘本妯夌粈绨戦惄鍝ユ暩濞翠焦婀侀弫鍫濓拷锟�
//        //  lcd_display_shuju_deal(PD1.fYpower,System.LCD_flag,2,3,4,6,7);    //缁楋拷7鐞涘本妯夌粈鐑樻箒閸旂喎濮涢悳锟�
//        ////    lcd_display_shuju_deal(Menu_display.uiN ,System.LCD_flag,3,3,4,5,6);    //缁楋拷8鐞涘本妯夌粈楦挎祮闁拷
//        //  lcd_display_shuju_deal(Menu_display.uiTem,System.LCD_flag,3,12,13,14,16);//缁楋拷8鐞涘本妯夌粈鐑樹刊鎼达拷
      //   }
   // else if(System.LCD_flag==3)
      //  {
//            lcd_display_shuju_deal(AC_Iu.iSamp,System.LCD_flag,7,3,4,6,7);
//            lcd_display_shuju_deal(AC_U2.iSamp ,System.LCD_flag,0,3,4,6,7);     //缁楋拷3鐞涘本妯夌粈楦跨翻閸忋儳鏁搁崢锟�
//            lcd_display_shuju_deal(PD1.fYpower*10  ,System.LCD_flag,1,2,3,4,6);//缁楋拷5鐞涘本妯夌粈绨庨惄鍝ユ暩濞翠焦婀侀弫鍫濓拷锟�
//            lcd_display_shuju_deal(PD1.fSpower*10  ,System.LCD_flag,2,2,3,4,6);     //缁楋拷5鐞涘本妯夌粈楦跨翻閸戣櫣鏁搁崢瀣箒閸婏拷
//            lcd_display_shuju_deal(PD1.fGlys*1000  ,System.LCD_flag,3,2,4,5,6);   //缁楋拷6鐞涘本妯夌粈绨愰惄鍝ユ暩濞翠焦婀侀弫鍫濓拷锟�
//        //  lcd_display_shuju_deal(Menu_display.iIw ,System.LCD_flag,1,12,13,15,16);//缁楋拷6鐞涘本妯夌粈绨戦惄鍝ユ暩濞翠焦婀侀弫鍫濓拷锟�
//        //  lcd_display_shuju_deal(PD1.fYpower,System.LCD_flag,2,3,4,6,7);    //缁楋拷7鐞涘本妯夌粈鐑樻箒閸旂喎濮涢悳锟�
//        ////    lcd_display_shuju_deal(Menu_display.uiN ,System.LCD_flag,3,3,4,5,6);    //缁楋拷8鐞涘本妯夌粈楦挎祮闁拷
//        //  lcd_display_shuju_deal(Menu_display.uiTem,System.LCD_flag,3,12,13,14,16);//缁楋拷8鐞涘本妯夌粈鐑樹刊鎼达拷
         //}

}
void menu_init(void)            //閹稿鏁稉搴㈡▔缁�鍝勫灥婵瀵查崙鑺ユ殶
{   unsigned int i;
    Menu_key.uiKEYsacn_status=0;//閹稿鏁弰顖氭儊閺堝鏅ラ崣姗�鍣哄〒鍛存祩
    Menu_key.uiKEY_IO=0;        //閹稿鏁悩鑸碉拷浣瑰閹诲繐褰夐柌蹇旂闂嗭拷
    LCD12864_init();            //濞戝弶娅犵仦蹇撳灥婵瀵查崙鑺ユ殶
    CLEAR_Screen();           //閸忋劌鐫嗗〒鍛潌閸戣姤鏆�
    for(i=0;i<800;i++)
    {    //lcd12864_display_picture(0,7,0,127); //閺勫墽銇氬锟介張铏规櫕闂堛垺鐪界�涳拷
         DELAY_US(1000);//瀵よ埖妞�
         ServiceDog();  //鐎规碍婀＄紒娆戞箙闂傘劎瀚嶉崘娆忓弳閸婂ジ妲诲銏狀槻娴ｏ拷
    }
    DATA_displaydata_init();    //閺勫墽銇氶弫鐗堝祦閻ㄥ嫬鍨垫慨瀣
}
void menu_deal(void) 
{   static unsigned int cnt800=0;
    menu_key_deal();                                //閹稿鏁幓蹇撳灲閺傤厼顦╅悶锟�
    if(cnt800<799)  cnt800++;                       //800閸婂秴鍨庢０锟�
    else cnt800=0;
    if(cnt800==100)menu_lcddisplay_datadeal1();     //閺勫墽銇氶弫鐗堝祦鐎涙顦╅悶锟�1
    if(cnt800==200)menu_lcddisplay_datadeal2();     //閺勫墽銇氶弫鐗堝祦鐎涙顑佹径鍕倞2
    if(cnt800==300)lcd12864_display_char(0,7,0,17,System.LCD_flag); //閺勫墽銇氶幍锟介張澶婄摟缁楋拷
}
