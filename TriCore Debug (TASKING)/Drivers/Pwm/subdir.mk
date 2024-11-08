################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../Drivers/Pwm/ThreePhase_Pwm.c" 

COMPILED_SRCS += \
"Drivers/Pwm/ThreePhase_Pwm.src" 

C_DEPS += \
"./Drivers/Pwm/ThreePhase_Pwm.d" 

OBJS += \
"Drivers/Pwm/ThreePhase_Pwm.o" 


# Each subdirectory must supply rules for building sources it contributes
"Drivers/Pwm/ThreePhase_Pwm.src":"../Drivers/Pwm/ThreePhase_Pwm.c" "Drivers/Pwm/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/WQU3WX/AURIX-v1.10.6-workspace/TC275_MotorControl_001/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"Drivers/Pwm/ThreePhase_Pwm.o":"Drivers/Pwm/ThreePhase_Pwm.src" "Drivers/Pwm/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Drivers-2f-Pwm

clean-Drivers-2f-Pwm:
	-$(RM) ./Drivers/Pwm/ThreePhase_Pwm.d ./Drivers/Pwm/ThreePhase_Pwm.o ./Drivers/Pwm/ThreePhase_Pwm.src

.PHONY: clean-Drivers-2f-Pwm

