################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Bowling\ definitivo.c 

C_DEPS += \
./src/Bowling\ definitivo.d 

OBJS += \
./src/Bowling\ definitivo.o 


# Each subdirectory must supply rules for building sources it contributes
src/Bowling\ definitivo.o: ../src/Bowling\ definitivo.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -Im -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Bowling definitivo.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Bowling\ definitivo.d ./src/Bowling\ definitivo.o

.PHONY: clean-src

