/*
*********************************************************************
* Copyright (C) 2008  ZOF LTD.
* All rights reserved.
* 
* File name: ModBusConm.h
* Description: Device SCI Register Definitions
* 
* Revision:	1.0
* 
* Author: gwwsoft
*
* Notes£º Record the note during the programming
*
* Time£º2008.3.20
*
* Update:
*********************************************************************
*/
//---------------------------------------------------------------------------
// MODBUS Individual Register Bit Definitions

//----------------------------------------------------------
// MODBUS communication control register bit definitions:
//----------------------------------------------------------


#ifndef MODBUSCONM_H
#define MODBUSCONM_H

typedef struct {								// bit   description
					Uint16 RX_ST:1;				// 0
					Uint16 RX_OK:1;				// 1
					Uint16 TX_OK:1;				// 2
					Uint16 resv1:5;				// 7:3
					Uint16 TX_LONG:8;			// 15:8
					Uint16 RX_COUNT:8;			// 7:0   Character length control        
					Uint16 RX_NUM:8;   			// 15:8  ADDR/IDLE Mode control
					Uint16 uchCRCHi:8;			// 7:0  Parity enable   
					Uint16 uchCRCLo:8;			// 15:8  Parity enable   
					Uint16 TRANADDR:8;			// 7:0
					Uint16 TRANCOM:8;			// 15:8
					Uint16 DATANUM:8;			// 7:0
					Uint16 DATA1L:8;			// 15:8   Character length control        
					Uint16 DATA1H:8;   			// 7:0  ADDR/IDLE Mode control
					Uint16 DATA2L:8;			// 15:8  Parity enable   
					Uint16 DATA2H:8;			// 7:0  Parity enable   
					Uint16 DATA3L:8;			// 15:8  Parity enable   
					Uint16 DATA3H:8;			// 7:0  Parity enable   
					Uint16 DATA4L:8;			// 15:8  Parity enable   
					Uint16 DATA4H:8;			// 7:0  Parity enable   
					Uint16 STATENUM:8;			// 15:8  Parity enable
			   } SCIINT_CONMMUN; 

typedef SCIINT_CONMMUN *SCIINT_CONMMUN_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the receive_conmmu object.
-----------------------------------------------------------------------------*/
#define SCIINT_CONMMUN_DEFAULTS {	0, \
									0, \
                          			0, \
                           			0, \
                           			0, \
									0, \
                           			0, \
									0, \
									0, \
                           			0, \
									0, \
									0, \
                           			0, \
                           			0, \
									0, \
									0, \
                           			0, \
									0, \
									0, \
                           			0, \
                           			0 }

/*-----------------------------------------------------------------------------*/

struct STATUS1_BITS {
    Uint16  STATUS10:2;
    Uint16  STATUS11:2;
    Uint16  STATUS12:2;
    Uint16  STATUS13:2;
};

struct STATUS2_BITS {
    Uint16  STATUS20:2;
    Uint16  STATUS21:2;
    Uint16  STATUS22:2;
    Uint16  STATUS23:2;
};

struct STATUS3_BITS {
    Uint16  STATUS30:2;
    Uint16  STATUS31:2;
    Uint16  STATUS32:2;
    Uint16  STATUS33:2;
};

struct STATUS4_BITS {
    Uint16  STATUS40:2;
    Uint16  STATUS41:2;
    Uint16  STATUS42:2;
    Uint16  STATUS43:2;
};

union STATUS1_REG {
   Uint16             all;
   struct STATUS1_BITS  bit;
};
union STATUS2_REG {
   Uint16             all;
   struct STATUS2_BITS  bit;
};
union STATUS3_REG {
   Uint16             all;
   struct STATUS3_BITS  bit;
};
union STATUS4_REG {
   Uint16             all;
   struct STATUS4_BITS  bit;
};

typedef struct {
	union STATUS1_REG STATUS1;
	union STATUS2_REG STATUS2;
	union STATUS3_REG STATUS3;
	union STATUS4_REG STATUS4;
} STATUS_REG;	

#endif 


//===========================================================================
// No more.
//===========================================================================







