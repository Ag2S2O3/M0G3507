################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-582232897: ../MyProject.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"E:/ti/ccstheia141/ccs/utils/sysconfig_1.20.0/sysconfig_cli.bat" --script "C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/MyProject.syscfg" -o "." -s "E:/ti/mspm0_sdk_2_01_00_03/.metadata/product.json" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-582232897 ../MyProject.syscfg
device.opt: build-582232897
device.cmd.genlibs: build-582232897
ti_msp_dl_config.c: build-582232897
ti_msp_dl_config.h: build-582232897
Event.dot: build-582232897

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"E:/ti/ccstheia141/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/PWM" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/SSD1106_OLED" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/ST7789" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/ENCODER" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/UART" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/Debug" -I"E:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"E:/ti/mspm0_sdk_2_01_00_03/source" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/Delay" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: E:/ti/mspm0_sdk_2_01_00_03/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"E:/ti/ccstheia141/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/PWM" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/SSD1106_OLED" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/ST7789" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/ENCODER" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/UART" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/Debug" -I"E:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"E:/ti/mspm0_sdk_2_01_00_03/source" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/Delay" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"E:/ti/ccstheia141/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/PWM" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/SSD1106_OLED" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/ST7789" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/ENCODER" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/UART" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/Debug" -I"E:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"E:/ti/mspm0_sdk_2_01_00_03/source" -I"C:/Users/HMRda/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/Delay" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


