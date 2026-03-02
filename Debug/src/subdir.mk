################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Artista.cpp \
../src/Cancion.cpp \
../src/Fecha.cpp \
../src/Pruebas.cpp \
../src/PruebasArtista.cpp \
../src/PruebasCancion.cpp \
../src/Usuario.cpp \
../src/main.cpp 

CPP_DEPS += \
./src/Artista.d \
./src/Cancion.d \
./src/Fecha.d \
./src/Pruebas.d \
./src/PruebasArtista.d \
./src/PruebasCancion.d \
./src/Usuario.d \
./src/main.d 

OBJS += \
./src/Artista.o \
./src/Cancion.o \
./src/Fecha.o \
./src/Pruebas.o \
./src/PruebasArtista.o \
./src/PruebasCancion.o \
./src/Usuario.o \
./src/main.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Artista.d ./src/Artista.o ./src/Cancion.d ./src/Cancion.o ./src/Fecha.d ./src/Fecha.o ./src/Pruebas.d ./src/Pruebas.o ./src/PruebasArtista.d ./src/PruebasArtista.o ./src/PruebasCancion.d ./src/PruebasCancion.o ./src/Usuario.d ./src/Usuario.o ./src/main.d ./src/main.o

.PHONY: clean-src

