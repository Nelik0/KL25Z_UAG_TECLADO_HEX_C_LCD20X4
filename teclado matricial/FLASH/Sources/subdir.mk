################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/lcd.c" \
"../Sources/main.c" \
"../Sources/sa_mtb.c" \
"../Sources/teclado_matricial.c" \

C_SRCS += \
../Sources/lcd.c \
../Sources/main.c \
../Sources/sa_mtb.c \
../Sources/teclado_matricial.c \

OBJS += \
./Sources/lcd.o \
./Sources/main.o \
./Sources/sa_mtb.o \
./Sources/teclado_matricial.o \

C_DEPS += \
./Sources/lcd.d \
./Sources/main.d \
./Sources/sa_mtb.d \
./Sources/teclado_matricial.d \

OBJS_QUOTED += \
"./Sources/lcd.o" \
"./Sources/main.o" \
"./Sources/sa_mtb.o" \
"./Sources/teclado_matricial.o" \

C_DEPS_QUOTED += \
"./Sources/lcd.d" \
"./Sources/main.d" \
"./Sources/sa_mtb.d" \
"./Sources/teclado_matricial.d" \

OBJS_OS_FORMAT += \
./Sources/lcd.o \
./Sources/main.o \
./Sources/sa_mtb.o \
./Sources/teclado_matricial.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/lcd.o: ../Sources/lcd.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/lcd.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/lcd.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/teclado_matricial.o: ../Sources/teclado_matricial.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/teclado_matricial.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/teclado_matricial.o"
	@echo 'Finished building: $<'
	@echo ' '


