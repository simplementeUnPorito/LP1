################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Numeros\ complejos.c 

C_DEPS += \
./src/Numeros\ complejos.d 

OBJS += \
./src/Numeros\ complejos.o 


# Each subdirectory must supply rules for building sources it contributes
src/Numeros\ complejos.o: ../src/Numeros\ complejos.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Numeros complejos.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Numeros\ complejos.d ./src/Numeros\ complejos.o

.PHONY: clean-src

