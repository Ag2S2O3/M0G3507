################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Delay/%.o: ../Delay/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"E:/ti/ccstheia141/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/PID" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/PWM" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/SSD1106_OLED" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/ST7789" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/ENCODER" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/UART" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/Debug" -I"E:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"E:/ti/mspm0_sdk_2_01_00_03/source" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/Delay" -gdwarf-3 -MMD -MP -MF"Delay/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


