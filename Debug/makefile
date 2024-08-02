################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
-l"E:/controlSUITE/libs/dsp/FPU/v131/lib/C28x_FPU_Lib.lib" \
-l"E:/controlSUITE/libs/math/FPUfastRTS/V100/lib/rts2800_fpu32_fast_supplement.lib" \
"./Source/DSP2833x_ADC_cal.obj" \
"./Source/DSP2833x_Adc.obj" \
"./Source/DSP2833x_CodeStartBranch.obj" \
"./Source/DSP2833x_CpuTimers.obj" \
"./Source/DSP2833x_DefaultIsr.obj" \
"./Source/DSP2833x_ECap.obj" \
"./Source/DSP2833x_EPwm.obj" \
"./Source/DSP2833x_EQep.obj" \
"./Source/DSP2833x_GlobalVariableDefs.obj" \
"./Source/DSP2833x_MemCopy.obj" \
"./Source/DSP2833x_PieCtrl.obj" \
"./Source/DSP2833x_PieVect.obj" \
"./Source/DSP2833x_Sci.obj" \
"./Source/DSP2833x_SysCtrl.obj" \
"./Source/DSP2833x_Xintf.obj" \
"./Source/DSP2833x_usDelay.obj" \
"./Source/FPUmathTables.obj" \
"./Source/MY_DLDZSY.obj" \
"./Source/MY_menu.obj" \
"./Source/My_DA.obj" \
"./Source/My_Oled12864.obj" \
"./Source/My_interrupt.obj" \
"./Source/My_main.obj" \
"./Source/My_monitor.obj" \
"./Source/My_variable.obj" \
"./Source/sqrt_f32.obj" \
"../Cmd/DSP2833x_Headers_nonBIOS.cmd" \
"../Cmd/F28335.cmd" \
"../Libraries/rts2800_fpu32.lib" \
"../Libraries/rts2800_fpu32_fast_supplement.lib" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include Cmd/subdir_vars.mk
-include Libraries/subdir_vars.mk
-include Source/subdir_vars.mk
-include Cmd/subdir_rules.mk
-include Libraries/subdir_rules.mk
-include Source/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
DLDZ_V3.1_1.out \

EXE_OUTPUTS__QUOTED += \
"DLDZ_V3.1_1.out" \


# All Target
all: DLDZ_V3.1_1.out

# Tool invocations
DLDZ_V3.1_1.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"D:/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi -z -m"DLDZ_V3.1_1.map" --stack_size=0x300 --warn_sections -i"D:/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/lib" -i"E:/controlSUITE/libs/dsp/FPU/v131/lib" -i"E:/controlSUITE/libs/math/FPUfastRTS/V100/lib" -i"E:/dspworkspace/DLDZ_V3.1_1/Libraries" -i"D:/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="DLDZ_V3.1_1_linkInfo.xml" --rom_model -o "DLDZ_V3.1_1.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "Source\FPUmathTables.d" 
	-$(RM) "Source\DSP2833x_ADC_cal.obj" "Source\DSP2833x_Adc.obj" "Source\DSP2833x_CodeStartBranch.obj" "Source\DSP2833x_CpuTimers.obj" "Source\DSP2833x_DefaultIsr.obj" "Source\DSP2833x_ECap.obj" "Source\DSP2833x_EPwm.obj" "Source\DSP2833x_EQep.obj" "Source\DSP2833x_GlobalVariableDefs.obj" "Source\DSP2833x_MemCopy.obj" "Source\DSP2833x_PieCtrl.obj" "Source\DSP2833x_PieVect.obj" "Source\DSP2833x_Sci.obj" "Source\DSP2833x_SysCtrl.obj" "Source\DSP2833x_Xintf.obj" "Source\DSP2833x_usDelay.obj" "Source\FPUmathTables.obj" "Source\MY_DLDZSY.obj" "Source\MY_menu.obj" "Source\My_DA.obj" "Source\My_Oled12864.obj" "Source\My_interrupt.obj" "Source\My_main.obj" "Source\My_monitor.obj" "Source\My_variable.obj" "Source\sqrt_f32.obj" 
	-$(RM) "Source\DSP2833x_Adc.d" "Source\DSP2833x_CpuTimers.d" "Source\DSP2833x_DefaultIsr.d" "Source\DSP2833x_ECap.d" "Source\DSP2833x_EPwm.d" "Source\DSP2833x_EQep.d" "Source\DSP2833x_GlobalVariableDefs.d" "Source\DSP2833x_MemCopy.d" "Source\DSP2833x_PieCtrl.d" "Source\DSP2833x_PieVect.d" "Source\DSP2833x_Sci.d" "Source\DSP2833x_SysCtrl.d" "Source\DSP2833x_Xintf.d" "Source\MY_DLDZSY.d" "Source\MY_menu.d" "Source\My_DA.d" "Source\My_Oled12864.d" "Source\My_interrupt.d" "Source\My_main.d" "Source\My_monitor.d" "Source\My_variable.d" 
	-$(RM) "Source\DSP2833x_ADC_cal.d" "Source\DSP2833x_CodeStartBranch.d" "Source\DSP2833x_usDelay.d" "Source\sqrt_f32.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

