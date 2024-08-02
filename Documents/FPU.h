// TI File $Revision: /main/2 $
// Checkin $Date: January 7, 2008   14:41:24 $
//###########################################################################
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// ------------------------------------------------------------------------
//          Copyright (C) 2007 Texas Instruments, Incorporated.
//                          All Rights Reserved.
// ==========================================================================
//
// FILE:   FPU.h
//
// TITLE:  Prototypes and Definitions for the C28x FPU Library
//
//###########################################################################
// $TI Release: C28x FPU Library 1.00 Beta1 $
// $Release Date: January 7, 2008 $
//###########################################################################

#ifndef C28X_FPU_LIB_H
#define C28X_FPU_LIB_H


#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Standard C28x Data Types
//-----------------------------------------------------------------------------


#ifndef DSP28_DATA_TYPES
#define DSP28_DATA_TYPES
typedef int                 int16;
typedef long                int32;
typedef long long           int64;
typedef unsigned int        Uint16;
typedef unsigned long       Uint32;
typedef unsigned long long  Uint64;
typedef float               float32;
typedef long double         float64;
#endif


//-----------------------------------------------------------------------------
// Float32 Real FFT Definitions and Prototypes
//-----------------------------------------------------------------------------

typedef struct {
  float32  *InBuf;
  float32  *OutBuf;
  float32  *CosSinBuf;
  float32  *MagBuf;
  float32  *PhaseBuf;
  Uint16   FFTSize;
  Uint16   FFTStages;
} RFFT_F32_STRUCT;

extern void RFFT_f32(RFFT_F32_STRUCT *);                // Real FFT, aligned input
extern void RFFT_f32u(RFFT_F32_STRUCT *);               // Real FFT, unaligned input
extern void RFFT_f32_mag(RFFT_F32_STRUCT *);            // Real FFT, magnitude
extern void RFFT_f32s_mag(RFFT_F32_STRUCT *);           // Real FFT, sclaed magnitude
extern void RFFT_f32_phase(RFFT_F32_STRUCT *);          // Real FFT, phase
extern void RFFT_f32_sincostable(RFFT_F32_STRUCT *);    // Real FFT, twiddle calculation

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of C28X_FPU_LIB_H

//===========================================================================
// End of file.
//===========================================================================
