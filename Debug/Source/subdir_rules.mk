################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Source/%.obj: ../Source/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="E:/controlSUITE/libs/dsp/FPU/v131/include" --include_path="E:/controlSUITE/libs/math/FPUfastRTS/V100/include" --include_path="D:/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="E:/dspworkspace/DLDZ_V3.1_1/Documents" --include_path="E:/dspworkspace/DLDZ_V3.1_1/Include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Source/$(basename $(<F)).d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/%.obj: ../Source/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="E:/controlSUITE/libs/dsp/FPU/v131/include" --include_path="E:/controlSUITE/libs/math/FPUfastRTS/V100/include" --include_path="D:/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="E:/dspworkspace/DLDZ_V3.1_1/Documents" --include_path="E:/dspworkspace/DLDZ_V3.1_1/Include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Source/$(basename $(<F)).d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/%.obj: ../Source/%.ASM $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="E:/controlSUITE/libs/dsp/FPU/v131/include" --include_path="E:/controlSUITE/libs/math/FPUfastRTS/V100/include" --include_path="D:/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="E:/dspworkspace/DLDZ_V3.1_1/Documents" --include_path="E:/dspworkspace/DLDZ_V3.1_1/Include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Source/$(basename $(<F)).d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


