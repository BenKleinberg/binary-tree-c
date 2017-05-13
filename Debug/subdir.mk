################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../binarytree.cpp \
../binarytreenode.cpp \
../command.cpp \
../int.cpp \
../main.cpp \
../redblacknode.cpp \
../redblacktree.cpp 

OBJS += \
./binarytree.o \
./binarytreenode.o \
./command.o \
./int.o \
./main.o \
./redblacknode.o \
./redblacktree.o 

CPP_DEPS += \
./binarytree.d \
./binarytreenode.d \
./command.d \
./int.d \
./main.d \
./redblacknode.d \
./redblacktree.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


