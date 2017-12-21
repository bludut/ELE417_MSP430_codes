################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
PROJE.cpp: ../PROJE.ino
	@echo 'Building file: $<'
	@echo 'Invoking: Resource Custom Build Step'
	
	@echo 'Finished building: $<'
	@echo ' '

%.o: ./%.cpp $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/energia-1.6.10E18/hardware/tools/msp430/bin/msp430-gcc.exe" -c -mmcu=msp430g2553 -fno-exceptions -DF_CPU=16000000L -DENERGIA_MSP_EXP430G2553LP -DENERGIA_ARCH_MSP430 -DENERGIA=18 -DARDUINO=10610 -I"C:/Users/FatihKaya/AppData/Local/Energia15/packages/energia/hardware/msp430/1.0.3/cores/msp430" -I"C:/Users/FatihKaya/AppData/Local/Energia15/packages/energia/hardware/msp430/1.0.3/variants/MSP-EXP430G2553LP" -I"C:/Users/FatihKaya/Documents/CCS_MSP430_WS/PROJE" -I"C:/Users/FatihKaya/AppData/Local/Energia15/packages/energia/hardware/msp430/1.0.3/libraries/Wire" -I"C:/ti/energia-1.6.10E18/hardware/tools/msp430/msp430/include" -Os -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -w -Wall -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o"$@" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


