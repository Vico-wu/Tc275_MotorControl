################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../UserLib/Transforms/park/transform_Park.c" 

COMPILED_SRCS += \
"UserLib/Transforms/park/transform_Park.src" 

C_DEPS += \
"./UserLib/Transforms/park/transform_Park.d" 

OBJS += \
"UserLib/Transforms/park/transform_Park.o" 


# Each subdirectory must supply rules for building sources it contributes
"UserLib/Transforms/park/transform_Park.src":"../UserLib/Transforms/park/transform_Park.c" "UserLib/Transforms/park/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/WQU3WX/AURIX-v1.10.6-workspace/TC275_MotorControl_001/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"UserLib/Transforms/park/transform_Park.o":"UserLib/Transforms/park/transform_Park.src" "UserLib/Transforms/park/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-UserLib-2f-Transforms-2f-park

clean-UserLib-2f-Transforms-2f-park:
	-$(RM) ./UserLib/Transforms/park/transform_Park.d ./UserLib/Transforms/park/transform_Park.o ./UserLib/Transforms/park/transform_Park.src

.PHONY: clean-UserLib-2f-Transforms-2f-park

