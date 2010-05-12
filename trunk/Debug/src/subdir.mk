################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Calculator.cpp \
../src/CalculatorAtlas.cpp \
../src/ColumnChecksumMatrix.cpp \
../src/FullChecksumMatrix.cpp \
../src/Matrix.cpp \
../src/PSTL.cpp \
../src/Processor.cpp \
../src/RowChecksumMatrix.cpp \
../src/Vector.cpp 

OBJS += \
./src/Calculator.o \
./src/CalculatorAtlas.o \
./src/ColumnChecksumMatrix.o \
./src/FullChecksumMatrix.o \
./src/Matrix.o \
./src/PSTL.o \
./src/Processor.o \
./src/RowChecksumMatrix.o \
./src/Vector.o 

CPP_DEPS += \
./src/Calculator.d \
./src/CalculatorAtlas.d \
./src/ColumnChecksumMatrix.d \
./src/FullChecksumMatrix.d \
./src/Matrix.d \
./src/PSTL.d \
./src/Processor.d \
./src/RowChecksumMatrix.d \
./src/Vector.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


