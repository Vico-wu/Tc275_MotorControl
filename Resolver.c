/**********************************************************************************************************************
 * \file Resolver.c
 * \copyright Copyright (C) Infineon Technologies AG 2019
 * 
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of 
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and 
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all 
 * derivative works of the Software, unless such copies or derivative works are solely in the form of 
 * machine-executable object code generated by a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE 
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN 
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 *********************************************************************************************************************/

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "Resolver.h"
#include "IfxPort.h"
#include "Bsp.h"
/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define GPIO_RDVEL_OUTPUT   &MODULE_P15, 4
#define GPIO_SAMPLE_OUTPUT  &MODULE_P15, 5
#define GPIO_CS_RD_OUTPUT   &MODULE_P15, 6
#define GPIO_XB_NRST_OUTPUT &MODULE_P15, 8

#define RDVEL_ON            IfxPort_setPinHigh(GPIO_RDVEL_OUTPUT)    // AD2S1205时序控制引脚初始化
#define RDVEL_OFF           IfxPort_setPinLow(GPIO_RDVEL_OUTPUT)
#define SAMPLE_ON           IfxPort_setPinHigh(GPIO_SAMPLE_OUTPUT)
#define SAMPLE_OFF          IfxPort_setPinLow(GPIO_SAMPLE_OUTPUT)
#define CS_RD_ON            IfxPort_setPinHigh(GPIO_CS_RD_OUTPUT)
#define CS_RD_OFF           IfxPort_setPinLow(GPIO_CS_RD_OUTPUT)
#define XB_NRST_ON          IfxPort_setPinHigh(GPIO_XB_NRST_OUTPUT)
#define XB_NRST_OFF         IfxPort_setPinLow(GPIO_XB_NRST_OUTPUT)

// DOS 表示输入信号质量的退化。当旋转变压器的输入信号超出了正常范围，或者信号失真较严重时，AD2S1205 会将 DOS 信号 置为高电平。
#define GPIO_LOT            &MODULE_P14, 0
//LOT 表示解码器无法正确跟踪旋转变压器的角度信号。如果解码器的内部跟踪速率无法跟上实际的旋转速度，或者跟踪出现错误，AD2S1205 会将 LOT 信号 置为高电平。
#define GPIO_DOS            &MODULE_P14, 2

#define GPIO_DBI0           &MODULE_P20, 7
#define GPIO_DBI1           &MODULE_P20, 8
#define GPIO_DBI2           &MODULE_P20, 9
#define GPIO_DBI3           &MODULE_P20, 10
#define GPIO_DBI4           &MODULE_P20, 11
#define GPIO_DBI5           &MODULE_P20, 12
#define GPIO_DBI6           &MODULE_P20, 13
#define GPIO_DBI7           &MODULE_P20, 14
#define GPIO_DBI8           &MODULE_P15, 0
#define GPIO_DBI9           &MODULE_P15, 1
#define GPIO_DBI10          &MODULE_P15, 2
#define GPIO_DBI11          &MODULE_P15, 3

#define WAIT_TIME_10MS      10
#define WAIT_TIME_50MS      50
#define WAIT_TIME_100US     100
#define WAIT_TIME_100NS     100

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
Resolver_tu Resolver_u;
/*********************************************************************************************************************/
/*--------------------------------------------Private Variables/Constants--------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
void initResolver (void)
{
    // Output
    IfxPort_setPinMode(GPIO_RDVEL_OUTPUT, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinMode(GPIO_SAMPLE_OUTPUT, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinMode(GPIO_CS_RD_OUTPUT, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinMode(GPIO_XB_NRST_OUTPUT, IfxPort_Mode_outputPushPullGeneral);
    //Input
    IfxPort_setPinMode(GPIO_LOT, IfxPort_Mode_inputPullUp);
    IfxPort_setPinMode(GPIO_DOS, IfxPort_Mode_inputPullUp);

    IfxPort_setPinMode(GPIO_DBI0, IfxPort_Mode_inputPullUp);
    IfxPort_setPinMode(GPIO_DBI1, IfxPort_Mode_inputPullUp);
    IfxPort_setPinMode(GPIO_DBI2, IfxPort_Mode_inputPullUp);
    IfxPort_setPinMode(GPIO_DBI3, IfxPort_Mode_inputPullUp);
    IfxPort_setPinMode(GPIO_DBI4, IfxPort_Mode_inputPullUp);
    IfxPort_setPinMode(GPIO_DBI5, IfxPort_Mode_inputPullUp);
    IfxPort_setPinMode(GPIO_DBI6, IfxPort_Mode_inputPullUp);
    IfxPort_setPinMode(GPIO_DBI7, IfxPort_Mode_inputPullUp);
    IfxPort_setPinMode(GPIO_DBI8, IfxPort_Mode_inputPullUp);
    IfxPort_setPinMode(GPIO_DBI9, IfxPort_Mode_inputPullUp);
    IfxPort_setPinMode(GPIO_DBI10, IfxPort_Mode_inputPullUp);
    IfxPort_setPinMode(GPIO_DBI11, IfxPort_Mode_inputPullUp);
}
void initAD2S1205 (void)
{
    Ifx_TickTime ticksFor10ms = IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_TIME_10MS);
    Ifx_TickTime ticksFor50ms = IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_TIME_50MS);
    Ifx_TickTime ticksFor100us = IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER, WAIT_TIME_100US);


    waitTime(ticksFor10ms);
    XB_NRST_OFF;
    SAMPLE_ON;
    waitTime(ticksFor100us);
    XB_NRST_ON;
    waitTime(ticksFor50ms);
    SAMPLE_OFF;
    waitTime(ticksFor10ms);
    SAMPLE_ON;
}
uint16 readIoInp (void)
{
    SAMPLE_OFF;
    waitTime();
    Resolver_u.bit.dbi0 = IfxPort_getPinState(GPIO_DBI0);
    Resolver_u.bit.dbi1 = IfxPort_getPinState(GPIO_DBI1);
    Resolver_u.bit.dbi2 = IfxPort_getPinState(GPIO_DBI2);
    Resolver_u.bit.dbi3 = IfxPort_getPinState(GPIO_DBI3);
    Resolver_u.bit.dbi4 = IfxPort_getPinState(GPIO_DBI4);
    Resolver_u.bit.dbi5 = IfxPort_getPinState(GPIO_DBI5);
    Resolver_u.bit.dbi6 = IfxPort_getPinState(GPIO_DBI6);
    Resolver_u.bit.dbi7 = IfxPort_getPinState(GPIO_DBI7);
    Resolver_u.bit.dbi8 = IfxPort_getPinState(GPIO_DBI8);
    Resolver_u.bit.dbi9 = IfxPort_getPinState(GPIO_DBI9);
    Resolver_u.bit.dbi10 = IfxPort_getPinState(GPIO_DBI10);
    Resolver_u.bit.dbi11 = IfxPort_getPinState(GPIO_DBI11);
    return Resolver_u.data;
}

