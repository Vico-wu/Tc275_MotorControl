/**********************************************************************************************************************
 * \file park.c
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
#include "transform_Park.h"
#include "math.h"
/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*-------------------------------------------------Data Structures---------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*--------------------------------------------Private Variables/Constants--------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
void transform_Park (float Ialpha, float Ibeta, float theta, float *Id, float *Iq)
{
    float cos_theta = cos(theta);
    float sin_theta = sin(theta);

    *Id = Ialpha * cos_theta + Ibeta * sin_theta;
    *Iq = -Ialpha * sin_theta + Ibeta * cos_theta;
}
void transform_iPark (float Id, float Iq, float theta, float *Ialpha, float *Ibeta)
{
    float cos_theta = cos(theta);
    float sin_theta = sin(theta);

    *Ialpha = Id * cos_theta - Iq * sin_theta;
    *Ibeta = Id * sin_theta + Iq * cos_theta;
}
