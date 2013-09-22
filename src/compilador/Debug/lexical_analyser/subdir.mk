################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lexical_analyser/lexical_analyser.c 

OBJS += \
./lexical_analyser/lexical_analyser.o 

C_DEPS += \
./lexical_analyser/lexical_analyser.d 


# Each subdirectory must supply rules for building sources it contributes
lexical_analyser/%.o: ../lexical_analyser/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


