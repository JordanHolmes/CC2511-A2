################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Display.c \
../Sources/Events.c \
../Sources/main.c 

OBJS += \
./Sources/Display.o \
./Sources/Events.o \
./Sources/main.o 

C_DEPS += \
./Sources/Display.d \
./Sources/Events.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/marni/Desktop/CC2511 2018 - Assignment 2/Assignment 2/Static_Code/PDD" -I"C:/Users/marni/Desktop/CC2511 2018 - Assignment 2/Assignment 2/Static_Code/IO_Map" -I"C:/Users/marni/Desktop/CC2511 2018 - Assignment 2/Assignment 2/Sources" -I"C:/Users/marni/Desktop/CC2511 2018 - Assignment 2/Assignment 2/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


