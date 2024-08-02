################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
ASM_UPPER_SRCS += \
../Source/FPUmathTables.ASM 

ASM_SRCS += \
../Source/DSP2833x_ADC_cal.asm \
../Source/DSP2833x_CodeStartBranch.asm \
../Source/DSP2833x_usDelay.asm \
../Source/sqrt_f32.asm 

C_SRCS += \
../Source/DSP2833x_Adc.c \
../Source/DSP2833x_CpuTimers.c \
../Source/DSP2833x_DefaultIsr.c \
../Source/DSP2833x_ECap.c \
../Source/DSP2833x_EPwm.c \
../Source/DSP2833x_EQep.c \
../Source/DSP2833x_GlobalVariableDefs.c \
../Source/DSP2833x_MemCopy.c \
../Source/DSP2833x_PieCtrl.c \
../Source/DSP2833x_PieVect.c \
../Source/DSP2833x_Sci.c \
../Source/DSP2833x_SysCtrl.c \
../Source/DSP2833x_Xintf.c \
../Source/MY_DLDZSY.c \
../Source/MY_menu.c \
../Source/My_DA.c \
../Source/My_Oled12864.c \
../Source/My_interrupt.c \
../Source/My_main.c \
../Source/My_monitor.c \
../Source/My_variable.c 

ASM_UPPER_DEPS += \
./Source/FPUmathTables.d 

C_DEPS += \
./Source/DSP2833x_Adc.d \
./Source/DSP2833x_CpuTimers.d \
./Source/DSP2833x_DefaultIsr.d \
./Source/DSP2833x_ECap.d \
./Source/DSP2833x_EPwm.d \
./Source/DSP2833x_EQep.d \
./Source/DSP2833x_GlobalVariableDefs.d \
./Source/DSP2833x_MemCopy.d \
./Source/DSP2833x_PieCtrl.d \
./Source/DSP2833x_PieVect.d \
./Source/DSP2833x_Sci.d \
./Source/DSP2833x_SysCtrl.d \
./Source/DSP2833x_Xintf.d \
./Source/MY_DLDZSY.d \
./Source/MY_menu.d \
./Source/My_DA.d \
./Source/My_Oled12864.d \
./Source/My_interrupt.d \
./Source/My_main.d \
./Source/My_monitor.d \
./Source/My_variable.d 

OBJS += \
./Source/DSP2833x_ADC_cal.obj \
./Source/DSP2833x_Adc.obj \
./Source/DSP2833x_CodeStartBranch.obj \
./Source/DSP2833x_CpuTimers.obj \
./Source/DSP2833x_DefaultIsr.obj \
./Source/DSP2833x_ECap.obj \
./Source/DSP2833x_EPwm.obj \
./Source/DSP2833x_EQep.obj \
./Source/DSP2833x_GlobalVariableDefs.obj \
./Source/DSP2833x_MemCopy.obj \
./Source/DSP2833x_PieCtrl.obj \
./Source/DSP2833x_PieVect.obj \
./Source/DSP2833x_Sci.obj \
./Source/DSP2833x_SysCtrl.obj \
./Source/DSP2833x_Xintf.obj \
./Source/DSP2833x_usDelay.obj \
./Source/FPUmathTables.obj \
./Source/MY_DLDZSY.obj \
./Source/MY_menu.obj \
./Source/My_DA.obj \
./Source/My_Oled12864.obj \
./Source/My_interrupt.obj \
./Source/My_main.obj \
./Source/My_monitor.obj \
./Source/My_variable.obj \
./Source/sqrt_f32.obj 

ASM_DEPS += \
./Source/DSP2833x_ADC_cal.d \
./Source/DSP2833x_CodeStartBranch.d \
./Source/DSP2833x_usDelay.d \
./Source/sqrt_f32.d 

ASM_UPPER_DEPS__QUOTED += \
"Source\FPUmathTables.d" 

OBJS__QUOTED += \
"Source\DSP2833x_ADC_cal.obj" \
"Source\DSP2833x_Adc.obj" \
"Source\DSP2833x_CodeStartBranch.obj" \
"Source\DSP2833x_CpuTimers.obj" \
"Source\DSP2833x_DefaultIsr.obj" \
"Source\DSP2833x_ECap.obj" \
"Source\DSP2833x_EPwm.obj" \
"Source\DSP2833x_EQep.obj" \
"Source\DSP2833x_GlobalVariableDefs.obj" \
"Source\DSP2833x_MemCopy.obj" \
"Source\DSP2833x_PieCtrl.obj" \
"Source\DSP2833x_PieVect.obj" \
"Source\DSP2833x_Sci.obj" \
"Source\DSP2833x_SysCtrl.obj" \
"Source\DSP2833x_Xintf.obj" \
"Source\DSP2833x_usDelay.obj" \
"Source\FPUmathTables.obj" \
"Source\MY_DLDZSY.obj" \
"Source\MY_menu.obj" \
"Source\My_DA.obj" \
"Source\My_Oled12864.obj" \
"Source\My_interrupt.obj" \
"Source\My_main.obj" \
"Source\My_monitor.obj" \
"Source\My_variable.obj" \
"Source\sqrt_f32.obj" 

C_DEPS__QUOTED += \
"Source\DSP2833x_Adc.d" \
"Source\DSP2833x_CpuTimers.d" \
"Source\DSP2833x_DefaultIsr.d" \
"Source\DSP2833x_ECap.d" \
"Source\DSP2833x_EPwm.d" \
"Source\DSP2833x_EQep.d" \
"Source\DSP2833x_GlobalVariableDefs.d" \
"Source\DSP2833x_MemCopy.d" \
"Source\DSP2833x_PieCtrl.d" \
"Source\DSP2833x_PieVect.d" \
"Source\DSP2833x_Sci.d" \
"Source\DSP2833x_SysCtrl.d" \
"Source\DSP2833x_Xintf.d" \
"Source\MY_DLDZSY.d" \
"Source\MY_menu.d" \
"Source\My_DA.d" \
"Source\My_Oled12864.d" \
"Source\My_interrupt.d" \
"Source\My_main.d" \
"Source\My_monitor.d" \
"Source\My_variable.d" 

ASM_DEPS__QUOTED += \
"Source\DSP2833x_ADC_cal.d" \
"Source\DSP2833x_CodeStartBranch.d" \
"Source\DSP2833x_usDelay.d" \
"Source\sqrt_f32.d" 

ASM_SRCS__QUOTED += \
"../Source/DSP2833x_ADC_cal.asm" \
"../Source/DSP2833x_CodeStartBranch.asm" \
"../Source/DSP2833x_usDelay.asm" \
"../Source/sqrt_f32.asm" 

C_SRCS__QUOTED += \
"../Source/DSP2833x_Adc.c" \
"../Source/DSP2833x_CpuTimers.c" \
"../Source/DSP2833x_DefaultIsr.c" \
"../Source/DSP2833x_ECap.c" \
"../Source/DSP2833x_EPwm.c" \
"../Source/DSP2833x_EQep.c" \
"../Source/DSP2833x_GlobalVariableDefs.c" \
"../Source/DSP2833x_MemCopy.c" \
"../Source/DSP2833x_PieCtrl.c" \
"../Source/DSP2833x_PieVect.c" \
"../Source/DSP2833x_Sci.c" \
"../Source/DSP2833x_SysCtrl.c" \
"../Source/DSP2833x_Xintf.c" \
"../Source/MY_DLDZSY.c" \
"../Source/MY_menu.c" \
"../Source/My_DA.c" \
"../Source/My_Oled12864.c" \
"../Source/My_interrupt.c" \
"../Source/My_main.c" \
"../Source/My_monitor.c" \
"../Source/My_variable.c" 

ASM_UPPER_SRCS__QUOTED += \
"../Source/FPUmathTables.ASM" 


