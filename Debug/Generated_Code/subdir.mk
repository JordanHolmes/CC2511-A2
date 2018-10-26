################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/ASerialLdd1.c \
../Generated_Code/BitIoLdd1.c \
../Generated_Code/BitIoLdd2.c \
../Generated_Code/BitIoLdd3.c \
../Generated_Code/Cpu.c \
../Generated_Code/Inhr1.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/PwmLdd1.c \
../Generated_Code/PwmLdd2.c \
../Generated_Code/PwmLdd3.c \
../Generated_Code/PwmLdd4.c \
../Generated_Code/SpindleSpeed.c \
../Generated_Code/TU1.c \
../Generated_Code/Term1.c \
../Generated_Code/Vectors.c \
../Generated_Code/XDirection.c \
../Generated_Code/XStepper.c \
../Generated_Code/YDirection.c \
../Generated_Code/YStepper.c \
../Generated_Code/ZDirection.c \
../Generated_Code/ZStepper.c 

OBJS += \
./Generated_Code/ASerialLdd1.o \
./Generated_Code/BitIoLdd1.o \
./Generated_Code/BitIoLdd2.o \
./Generated_Code/BitIoLdd3.o \
./Generated_Code/Cpu.o \
./Generated_Code/Inhr1.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/PwmLdd1.o \
./Generated_Code/PwmLdd2.o \
./Generated_Code/PwmLdd3.o \
./Generated_Code/PwmLdd4.o \
./Generated_Code/SpindleSpeed.o \
./Generated_Code/TU1.o \
./Generated_Code/Term1.o \
./Generated_Code/Vectors.o \
./Generated_Code/XDirection.o \
./Generated_Code/XStepper.o \
./Generated_Code/YDirection.o \
./Generated_Code/YStepper.o \
./Generated_Code/ZDirection.o \
./Generated_Code/ZStepper.o 

C_DEPS += \
./Generated_Code/ASerialLdd1.d \
./Generated_Code/BitIoLdd1.d \
./Generated_Code/BitIoLdd2.d \
./Generated_Code/BitIoLdd3.d \
./Generated_Code/Cpu.d \
./Generated_Code/Inhr1.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/PwmLdd1.d \
./Generated_Code/PwmLdd2.d \
./Generated_Code/PwmLdd3.d \
./Generated_Code/PwmLdd4.d \
./Generated_Code/SpindleSpeed.d \
./Generated_Code/TU1.d \
./Generated_Code/Term1.d \
./Generated_Code/Vectors.d \
./Generated_Code/XDirection.d \
./Generated_Code/XStepper.d \
./Generated_Code/YDirection.d \
./Generated_Code/YStepper.d \
./Generated_Code/ZDirection.d \
./Generated_Code/ZStepper.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/marni/Desktop/CC2511 2018 - Assignment 2/Assignment 2/Static_Code/PDD" -I"C:/Users/marni/Desktop/CC2511 2018 - Assignment 2/Assignment 2/Static_Code/IO_Map" -I"C:/Users/marni/Desktop/CC2511 2018 - Assignment 2/Assignment 2/Sources" -I"C:/Users/marni/Desktop/CC2511 2018 - Assignment 2/Assignment 2/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


