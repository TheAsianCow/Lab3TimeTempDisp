################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.2.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./peripherals.obj" \
"./LcdDriver/HAL_MSP_EXP430FR5529_Sharp96x96.obj" \
"./LcdDriver/Sharp96x96.obj" \
"./fonts/fontfixed6x8.obj" \
"./images/LPRocket_96x37.obj" \
"./images/TI_Logo_69x64.obj" \
"../lnk_msp430f5529.cmd" \
"../lib/grlib.lib" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-llibmath.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include LcdDriver/subdir_vars.mk
-include fonts/subdir_vars.mk
-include images/subdir_vars.mk
-include lib/subdir_vars.mk
-include subdir_rules.mk
-include LcdDriver/subdir_rules.mk
-include fonts/subdir_rules.mk
-include images/subdir_rules.mk
-include lib/subdir_rules.mk
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
Lab3TimeTempDisp.out \

EXE_OUTPUTS__QUOTED += \
"Lab3TimeTempDisp.out" \

BIN_OUTPUTS += \
Lab3TimeTempDisp.hex \

BIN_OUTPUTS__QUOTED += \
"Lab3TimeTempDisp.hex" \


# All Target
all: Lab3TimeTempDisp.out

# Tool invocations
Lab3TimeTempDisp.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.2.LTS/bin/cl430" -vmspx --data_model=restricted -Ooff --use_hw_mpy=F5 --advice:power_severity=suppress --define=__MSP430F5529__ -g --gcc --printf_support=minimal --diag_warning=225 --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 -z -m"Lab3TimeTempDisp.map" --heap_size=160 --stack_size=160 --cinit_hold_wdt=on -i"C:/ti/ccsv8/ccs_base/msp430/include" -i"C:/ti/ccsv8/ccs_base/msp430/include" -i"C:/Users/Jeffrey Huang/Documents/WPI/2019-2020/A term/ECE2049/Labs/Lab3TimeTempDisp/lib" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.2.LTS/lib" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.2.LTS/include" -i"C:/ti/ccsv8/ccs_base/msp430/lib/5xx_6xx_FRxx" --reread_libs --warn_sections --xml_link_info="Lab3TimeTempDisp_linkInfo.xml" --use_hw_mpy=F5 --rom_model -o "Lab3TimeTempDisp.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

Lab3TimeTempDisp.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: MSP430 Hex Utility'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.2.LTS/bin/hex430" --memwidth=8 --romwidth=8 -o "Lab3TimeTempDisp.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "peripherals.obj" "LcdDriver\HAL_MSP_EXP430FR5529_Sharp96x96.obj" "LcdDriver\Sharp96x96.obj" "fonts\fontfixed6x8.obj" "images\LPRocket_96x37.obj" "images\TI_Logo_69x64.obj" 
	-$(RM) "main.d" "peripherals.d" "LcdDriver\HAL_MSP_EXP430FR5529_Sharp96x96.d" "LcdDriver\Sharp96x96.d" "fonts\fontfixed6x8.d" "images\LPRocket_96x37.d" "images\TI_Logo_69x64.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

