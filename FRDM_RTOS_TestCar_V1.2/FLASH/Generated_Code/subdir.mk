################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Generated_Code/AD1.c" \
"../Generated_Code/AS1.c" \
"../Generated_Code/ASerialLdd1.c" \
"../Generated_Code/AdcLdd1.c" \
"../Generated_Code/BitIoLdd3.c" \
"../Generated_Code/BitIoLdd4.c" \
"../Generated_Code/CI2C1.c" \
"../Generated_Code/CLS1.c" \
"../Generated_Code/CS1.c" \
"../Generated_Code/Cpu.c" \
"../Generated_Code/DIR_LEFT.c" \
"../Generated_Code/DIR_RIGHT.c" \
"../Generated_Code/FRTOS1.c" \
"../Generated_Code/GI2C1.c" \
"../Generated_Code/KSDK1.c" \
"../Generated_Code/LED_GREEN.c" \
"../Generated_Code/LEDpin3.c" \
"../Generated_Code/LEDpin4.c" \
"../Generated_Code/PE_LDD.c" \
"../Generated_Code/PWM_Gyro.c" \
"../Generated_Code/PWM_LEFT.c" \
"../Generated_Code/PWM_RIGHT.c" \
"../Generated_Code/PwmLdd1.c" \
"../Generated_Code/PwmLdd2.c" \
"../Generated_Code/PwmLdd3.c" \
"../Generated_Code/RED.c" \
"../Generated_Code/TSK1.c" \
"../Generated_Code/TU1.c" \
"../Generated_Code/TU2.c" \
"../Generated_Code/TofCE1.c" \
"../Generated_Code/TofCE2.c" \
"../Generated_Code/TofCE3.c" \
"../Generated_Code/UTIL1.c" \
"../Generated_Code/Vectors.c" \
"../Generated_Code/WAIT1.c" \
"../Generated_Code/croutine.c" \
"../Generated_Code/event_groups.c" \
"../Generated_Code/heap_1.c" \
"../Generated_Code/heap_2.c" \
"../Generated_Code/heap_3.c" \
"../Generated_Code/heap_4.c" \
"../Generated_Code/heap_5.c" \
"../Generated_Code/list.c" \
"../Generated_Code/port.c" \
"../Generated_Code/queue.c" \
"../Generated_Code/tasks.c" \
"../Generated_Code/timers.c" \

C_SRCS += \
../Generated_Code/AD1.c \
../Generated_Code/AS1.c \
../Generated_Code/ASerialLdd1.c \
../Generated_Code/AdcLdd1.c \
../Generated_Code/BitIoLdd3.c \
../Generated_Code/BitIoLdd4.c \
../Generated_Code/CI2C1.c \
../Generated_Code/CLS1.c \
../Generated_Code/CS1.c \
../Generated_Code/Cpu.c \
../Generated_Code/DIR_LEFT.c \
../Generated_Code/DIR_RIGHT.c \
../Generated_Code/FRTOS1.c \
../Generated_Code/GI2C1.c \
../Generated_Code/KSDK1.c \
../Generated_Code/LED_GREEN.c \
../Generated_Code/LEDpin3.c \
../Generated_Code/LEDpin4.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/PWM_Gyro.c \
../Generated_Code/PWM_LEFT.c \
../Generated_Code/PWM_RIGHT.c \
../Generated_Code/PwmLdd1.c \
../Generated_Code/PwmLdd2.c \
../Generated_Code/PwmLdd3.c \
../Generated_Code/RED.c \
../Generated_Code/TSK1.c \
../Generated_Code/TU1.c \
../Generated_Code/TU2.c \
../Generated_Code/TofCE1.c \
../Generated_Code/TofCE2.c \
../Generated_Code/TofCE3.c \
../Generated_Code/UTIL1.c \
../Generated_Code/Vectors.c \
../Generated_Code/WAIT1.c \
../Generated_Code/croutine.c \
../Generated_Code/event_groups.c \
../Generated_Code/heap_1.c \
../Generated_Code/heap_2.c \
../Generated_Code/heap_3.c \
../Generated_Code/heap_4.c \
../Generated_Code/heap_5.c \
../Generated_Code/list.c \
../Generated_Code/port.c \
../Generated_Code/queue.c \
../Generated_Code/tasks.c \
../Generated_Code/timers.c \

S_SRCS += \
../Generated_Code/portasm.s \

S_SRCS_QUOTED += \
"../Generated_Code/portasm.s" \

S_DEPS_QUOTED += \
"./Generated_Code/portasm.d" \

OBJS += \
./Generated_Code/AD1.o \
./Generated_Code/AS1.o \
./Generated_Code/ASerialLdd1.o \
./Generated_Code/AdcLdd1.o \
./Generated_Code/BitIoLdd3.o \
./Generated_Code/BitIoLdd4.o \
./Generated_Code/CI2C1.o \
./Generated_Code/CLS1.o \
./Generated_Code/CS1.o \
./Generated_Code/Cpu.o \
./Generated_Code/DIR_LEFT.o \
./Generated_Code/DIR_RIGHT.o \
./Generated_Code/FRTOS1.o \
./Generated_Code/GI2C1.o \
./Generated_Code/KSDK1.o \
./Generated_Code/LED_GREEN.o \
./Generated_Code/LEDpin3.o \
./Generated_Code/LEDpin4.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/PWM_Gyro.o \
./Generated_Code/PWM_LEFT.o \
./Generated_Code/PWM_RIGHT.o \
./Generated_Code/PwmLdd1.o \
./Generated_Code/PwmLdd2.o \
./Generated_Code/PwmLdd3.o \
./Generated_Code/RED.o \
./Generated_Code/TSK1.o \
./Generated_Code/TU1.o \
./Generated_Code/TU2.o \
./Generated_Code/TofCE1.o \
./Generated_Code/TofCE2.o \
./Generated_Code/TofCE3.o \
./Generated_Code/UTIL1.o \
./Generated_Code/Vectors.o \
./Generated_Code/WAIT1.o \
./Generated_Code/croutine.o \
./Generated_Code/event_groups.o \
./Generated_Code/heap_1.o \
./Generated_Code/heap_2.o \
./Generated_Code/heap_3.o \
./Generated_Code/heap_4.o \
./Generated_Code/heap_5.o \
./Generated_Code/list.o \
./Generated_Code/port.o \
./Generated_Code/portasm.o \
./Generated_Code/queue.o \
./Generated_Code/tasks.o \
./Generated_Code/timers.o \

C_DEPS += \
./Generated_Code/AD1.d \
./Generated_Code/AS1.d \
./Generated_Code/ASerialLdd1.d \
./Generated_Code/AdcLdd1.d \
./Generated_Code/BitIoLdd3.d \
./Generated_Code/BitIoLdd4.d \
./Generated_Code/CI2C1.d \
./Generated_Code/CLS1.d \
./Generated_Code/CS1.d \
./Generated_Code/Cpu.d \
./Generated_Code/DIR_LEFT.d \
./Generated_Code/DIR_RIGHT.d \
./Generated_Code/FRTOS1.d \
./Generated_Code/GI2C1.d \
./Generated_Code/KSDK1.d \
./Generated_Code/LED_GREEN.d \
./Generated_Code/LEDpin3.d \
./Generated_Code/LEDpin4.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/PWM_Gyro.d \
./Generated_Code/PWM_LEFT.d \
./Generated_Code/PWM_RIGHT.d \
./Generated_Code/PwmLdd1.d \
./Generated_Code/PwmLdd2.d \
./Generated_Code/PwmLdd3.d \
./Generated_Code/RED.d \
./Generated_Code/TSK1.d \
./Generated_Code/TU1.d \
./Generated_Code/TU2.d \
./Generated_Code/TofCE1.d \
./Generated_Code/TofCE2.d \
./Generated_Code/TofCE3.d \
./Generated_Code/UTIL1.d \
./Generated_Code/Vectors.d \
./Generated_Code/WAIT1.d \
./Generated_Code/croutine.d \
./Generated_Code/event_groups.d \
./Generated_Code/heap_1.d \
./Generated_Code/heap_2.d \
./Generated_Code/heap_3.d \
./Generated_Code/heap_4.d \
./Generated_Code/heap_5.d \
./Generated_Code/list.d \
./Generated_Code/port.d \
./Generated_Code/queue.d \
./Generated_Code/tasks.d \
./Generated_Code/timers.d \

S_DEPS += \
./Generated_Code/portasm.d \

OBJS_QUOTED += \
"./Generated_Code/AD1.o" \
"./Generated_Code/AS1.o" \
"./Generated_Code/ASerialLdd1.o" \
"./Generated_Code/AdcLdd1.o" \
"./Generated_Code/BitIoLdd3.o" \
"./Generated_Code/BitIoLdd4.o" \
"./Generated_Code/CI2C1.o" \
"./Generated_Code/CLS1.o" \
"./Generated_Code/CS1.o" \
"./Generated_Code/Cpu.o" \
"./Generated_Code/DIR_LEFT.o" \
"./Generated_Code/DIR_RIGHT.o" \
"./Generated_Code/FRTOS1.o" \
"./Generated_Code/GI2C1.o" \
"./Generated_Code/KSDK1.o" \
"./Generated_Code/LED_GREEN.o" \
"./Generated_Code/LEDpin3.o" \
"./Generated_Code/LEDpin4.o" \
"./Generated_Code/PE_LDD.o" \
"./Generated_Code/PWM_Gyro.o" \
"./Generated_Code/PWM_LEFT.o" \
"./Generated_Code/PWM_RIGHT.o" \
"./Generated_Code/PwmLdd1.o" \
"./Generated_Code/PwmLdd2.o" \
"./Generated_Code/PwmLdd3.o" \
"./Generated_Code/RED.o" \
"./Generated_Code/TSK1.o" \
"./Generated_Code/TU1.o" \
"./Generated_Code/TU2.o" \
"./Generated_Code/TofCE1.o" \
"./Generated_Code/TofCE2.o" \
"./Generated_Code/TofCE3.o" \
"./Generated_Code/UTIL1.o" \
"./Generated_Code/Vectors.o" \
"./Generated_Code/WAIT1.o" \
"./Generated_Code/croutine.o" \
"./Generated_Code/event_groups.o" \
"./Generated_Code/heap_1.o" \
"./Generated_Code/heap_2.o" \
"./Generated_Code/heap_3.o" \
"./Generated_Code/heap_4.o" \
"./Generated_Code/heap_5.o" \
"./Generated_Code/list.o" \
"./Generated_Code/port.o" \
"./Generated_Code/portasm.o" \
"./Generated_Code/queue.o" \
"./Generated_Code/tasks.o" \
"./Generated_Code/timers.o" \

C_DEPS_QUOTED += \
"./Generated_Code/AD1.d" \
"./Generated_Code/AS1.d" \
"./Generated_Code/ASerialLdd1.d" \
"./Generated_Code/AdcLdd1.d" \
"./Generated_Code/BitIoLdd3.d" \
"./Generated_Code/BitIoLdd4.d" \
"./Generated_Code/CI2C1.d" \
"./Generated_Code/CLS1.d" \
"./Generated_Code/CS1.d" \
"./Generated_Code/Cpu.d" \
"./Generated_Code/DIR_LEFT.d" \
"./Generated_Code/DIR_RIGHT.d" \
"./Generated_Code/FRTOS1.d" \
"./Generated_Code/GI2C1.d" \
"./Generated_Code/KSDK1.d" \
"./Generated_Code/LED_GREEN.d" \
"./Generated_Code/LEDpin3.d" \
"./Generated_Code/LEDpin4.d" \
"./Generated_Code/PE_LDD.d" \
"./Generated_Code/PWM_Gyro.d" \
"./Generated_Code/PWM_LEFT.d" \
"./Generated_Code/PWM_RIGHT.d" \
"./Generated_Code/PwmLdd1.d" \
"./Generated_Code/PwmLdd2.d" \
"./Generated_Code/PwmLdd3.d" \
"./Generated_Code/RED.d" \
"./Generated_Code/TSK1.d" \
"./Generated_Code/TU1.d" \
"./Generated_Code/TU2.d" \
"./Generated_Code/TofCE1.d" \
"./Generated_Code/TofCE2.d" \
"./Generated_Code/TofCE3.d" \
"./Generated_Code/UTIL1.d" \
"./Generated_Code/Vectors.d" \
"./Generated_Code/WAIT1.d" \
"./Generated_Code/croutine.d" \
"./Generated_Code/event_groups.d" \
"./Generated_Code/heap_1.d" \
"./Generated_Code/heap_2.d" \
"./Generated_Code/heap_3.d" \
"./Generated_Code/heap_4.d" \
"./Generated_Code/heap_5.d" \
"./Generated_Code/list.d" \
"./Generated_Code/port.d" \
"./Generated_Code/queue.d" \
"./Generated_Code/tasks.d" \
"./Generated_Code/timers.d" \

OBJS_OS_FORMAT += \
./Generated_Code/AD1.o \
./Generated_Code/AS1.o \
./Generated_Code/ASerialLdd1.o \
./Generated_Code/AdcLdd1.o \
./Generated_Code/BitIoLdd3.o \
./Generated_Code/BitIoLdd4.o \
./Generated_Code/CI2C1.o \
./Generated_Code/CLS1.o \
./Generated_Code/CS1.o \
./Generated_Code/Cpu.o \
./Generated_Code/DIR_LEFT.o \
./Generated_Code/DIR_RIGHT.o \
./Generated_Code/FRTOS1.o \
./Generated_Code/GI2C1.o \
./Generated_Code/KSDK1.o \
./Generated_Code/LED_GREEN.o \
./Generated_Code/LEDpin3.o \
./Generated_Code/LEDpin4.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/PWM_Gyro.o \
./Generated_Code/PWM_LEFT.o \
./Generated_Code/PWM_RIGHT.o \
./Generated_Code/PwmLdd1.o \
./Generated_Code/PwmLdd2.o \
./Generated_Code/PwmLdd3.o \
./Generated_Code/RED.o \
./Generated_Code/TSK1.o \
./Generated_Code/TU1.o \
./Generated_Code/TU2.o \
./Generated_Code/TofCE1.o \
./Generated_Code/TofCE2.o \
./Generated_Code/TofCE3.o \
./Generated_Code/UTIL1.o \
./Generated_Code/Vectors.o \
./Generated_Code/WAIT1.o \
./Generated_Code/croutine.o \
./Generated_Code/event_groups.o \
./Generated_Code/heap_1.o \
./Generated_Code/heap_2.o \
./Generated_Code/heap_3.o \
./Generated_Code/heap_4.o \
./Generated_Code/heap_5.o \
./Generated_Code/list.o \
./Generated_Code/port.o \
./Generated_Code/portasm.o \
./Generated_Code/queue.o \
./Generated_Code/tasks.o \
./Generated_Code/timers.o \


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/AD1.o: ../Generated_Code/AD1.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/AD1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/AD1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/AS1.o: ../Generated_Code/AS1.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/AS1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/AS1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/ASerialLdd1.o: ../Generated_Code/ASerialLdd1.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/ASerialLdd1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/ASerialLdd1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/AdcLdd1.o: ../Generated_Code/AdcLdd1.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/AdcLdd1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/AdcLdd1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/BitIoLdd3.o: ../Generated_Code/BitIoLdd3.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/BitIoLdd3.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/BitIoLdd3.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/BitIoLdd4.o: ../Generated_Code/BitIoLdd4.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/BitIoLdd4.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/BitIoLdd4.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/CI2C1.o: ../Generated_Code/CI2C1.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/CI2C1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/CI2C1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/CLS1.o: ../Generated_Code/CLS1.c
	@echo 'Building file: $<'
	@echo 'Executing target #20 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/CLS1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/CLS1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/CS1.o: ../Generated_Code/CS1.c
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/CS1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/CS1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Cpu.o: ../Generated_Code/Cpu.c
	@echo 'Building file: $<'
	@echo 'Executing target #22 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Cpu.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Cpu.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/DIR_LEFT.o: ../Generated_Code/DIR_LEFT.c
	@echo 'Building file: $<'
	@echo 'Executing target #23 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/DIR_LEFT.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/DIR_LEFT.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/DIR_RIGHT.o: ../Generated_Code/DIR_RIGHT.c
	@echo 'Building file: $<'
	@echo 'Executing target #24 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/DIR_RIGHT.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/DIR_RIGHT.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/FRTOS1.o: ../Generated_Code/FRTOS1.c
	@echo 'Building file: $<'
	@echo 'Executing target #25 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/FRTOS1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/FRTOS1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/GI2C1.o: ../Generated_Code/GI2C1.c
	@echo 'Building file: $<'
	@echo 'Executing target #26 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/GI2C1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/GI2C1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/KSDK1.o: ../Generated_Code/KSDK1.c
	@echo 'Building file: $<'
	@echo 'Executing target #27 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/KSDK1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/KSDK1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/LED_GREEN.o: ../Generated_Code/LED_GREEN.c
	@echo 'Building file: $<'
	@echo 'Executing target #28 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/LED_GREEN.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/LED_GREEN.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/LEDpin3.o: ../Generated_Code/LEDpin3.c
	@echo 'Building file: $<'
	@echo 'Executing target #29 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/LEDpin3.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/LEDpin3.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/LEDpin4.o: ../Generated_Code/LEDpin4.c
	@echo 'Building file: $<'
	@echo 'Executing target #30 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/LEDpin4.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/LEDpin4.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PE_LDD.o: ../Generated_Code/PE_LDD.c
	@echo 'Building file: $<'
	@echo 'Executing target #31 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PE_LDD.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PE_LDD.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PWM_Gyro.o: ../Generated_Code/PWM_Gyro.c
	@echo 'Building file: $<'
	@echo 'Executing target #32 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PWM_Gyro.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PWM_Gyro.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PWM_LEFT.o: ../Generated_Code/PWM_LEFT.c
	@echo 'Building file: $<'
	@echo 'Executing target #33 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PWM_LEFT.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PWM_LEFT.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PWM_RIGHT.o: ../Generated_Code/PWM_RIGHT.c
	@echo 'Building file: $<'
	@echo 'Executing target #34 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PWM_RIGHT.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PWM_RIGHT.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PwmLdd1.o: ../Generated_Code/PwmLdd1.c
	@echo 'Building file: $<'
	@echo 'Executing target #35 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PwmLdd1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PwmLdd1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PwmLdd2.o: ../Generated_Code/PwmLdd2.c
	@echo 'Building file: $<'
	@echo 'Executing target #36 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PwmLdd2.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PwmLdd2.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PwmLdd3.o: ../Generated_Code/PwmLdd3.c
	@echo 'Building file: $<'
	@echo 'Executing target #37 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PwmLdd3.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PwmLdd3.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/RED.o: ../Generated_Code/RED.c
	@echo 'Building file: $<'
	@echo 'Executing target #38 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/RED.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/RED.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TSK1.o: ../Generated_Code/TSK1.c
	@echo 'Building file: $<'
	@echo 'Executing target #39 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/TSK1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/TSK1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TU1.o: ../Generated_Code/TU1.c
	@echo 'Building file: $<'
	@echo 'Executing target #40 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/TU1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/TU1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TU2.o: ../Generated_Code/TU2.c
	@echo 'Building file: $<'
	@echo 'Executing target #41 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/TU2.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/TU2.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TofCE1.o: ../Generated_Code/TofCE1.c
	@echo 'Building file: $<'
	@echo 'Executing target #42 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/TofCE1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/TofCE1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TofCE2.o: ../Generated_Code/TofCE2.c
	@echo 'Building file: $<'
	@echo 'Executing target #43 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/TofCE2.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/TofCE2.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TofCE3.o: ../Generated_Code/TofCE3.c
	@echo 'Building file: $<'
	@echo 'Executing target #44 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/TofCE3.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/TofCE3.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/UTIL1.o: ../Generated_Code/UTIL1.c
	@echo 'Building file: $<'
	@echo 'Executing target #45 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/UTIL1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/UTIL1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Vectors.o: ../Generated_Code/Vectors.c
	@echo 'Building file: $<'
	@echo 'Executing target #46 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Vectors.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Vectors.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/WAIT1.o: ../Generated_Code/WAIT1.c
	@echo 'Building file: $<'
	@echo 'Executing target #47 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/WAIT1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/WAIT1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/croutine.o: ../Generated_Code/croutine.c
	@echo 'Building file: $<'
	@echo 'Executing target #48 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/croutine.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/croutine.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/event_groups.o: ../Generated_Code/event_groups.c
	@echo 'Building file: $<'
	@echo 'Executing target #49 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/event_groups.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/event_groups.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/heap_1.o: ../Generated_Code/heap_1.c
	@echo 'Building file: $<'
	@echo 'Executing target #50 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/heap_1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/heap_1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/heap_2.o: ../Generated_Code/heap_2.c
	@echo 'Building file: $<'
	@echo 'Executing target #51 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/heap_2.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/heap_2.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/heap_3.o: ../Generated_Code/heap_3.c
	@echo 'Building file: $<'
	@echo 'Executing target #52 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/heap_3.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/heap_3.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/heap_4.o: ../Generated_Code/heap_4.c
	@echo 'Building file: $<'
	@echo 'Executing target #53 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/heap_4.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/heap_4.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/heap_5.o: ../Generated_Code/heap_5.c
	@echo 'Building file: $<'
	@echo 'Executing target #54 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/heap_5.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/heap_5.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/list.o: ../Generated_Code/list.c
	@echo 'Building file: $<'
	@echo 'Executing target #55 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/list.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/list.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/port.o: ../Generated_Code/port.c
	@echo 'Building file: $<'
	@echo 'Executing target #56 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/port.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/port.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/portasm.o: ../Generated_Code/portasm.s
	@echo 'Building file: $<'
	@echo 'Executing target #57 $<'
	@echo 'Invoking: ARM Ltd Windows GCC Assembler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/portasm.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/portasm.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/queue.o: ../Generated_Code/queue.c
	@echo 'Building file: $<'
	@echo 'Executing target #58 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/queue.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/queue.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/tasks.o: ../Generated_Code/tasks.c
	@echo 'Building file: $<'
	@echo 'Executing target #59 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/tasks.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/tasks.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/timers.o: ../Generated_Code/timers.c
	@echo 'Building file: $<'
	@echo 'Executing target #60 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/timers.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/timers.o"
	@echo 'Finished building: $<'
	@echo ' '

