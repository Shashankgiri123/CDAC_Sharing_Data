/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include<stdio.h>
#include<stdint.h>

int flag=0;
uint32_t  volatile *const pClkCtrlReg =   (uint32_t*)0x40023830;
uint32_t  volatile *const pPortDModeReg = (uint32_t*)0x40020C00;
uint32_t  volatile *const pPortDOutReg =  (uint32_t*)0x40020C14;
/* This function executes in THREAD MODE of the processor */
void generate_interrupt()
{
	uint32_t *pSTIR  = (uint32_t*)0xE000EF00;
	uint32_t *pISER0 = (uint32_t*)0xE000E100;

	//enable IRQ3 interrupt
	*pISER0 |= ( 1 << 3);

	//generate an interrupt from software for IRQ3
	*pSTIR = (3 & 0x1FF);

}

/* This function executes in THREAD MODE of the processor */
int main(void)
{

	*pClkCtrlReg |= ( 1 << 3);
	//make 24th &26th bit position as 1 (SET)
	*pPortDModeReg |= ( 1 << 24)|(1<<26);

	generate_interrupt();
	while(flag==0);
	//Green LED ON
	*pPortDOutReg |= ( 1 << 12);

	for(;;);
}

/* This function(ISR) executes in HANDLER MODE of the processor */
void RTC_WKUP_IRQHandler(void)
{
	flag=1;
	//Orange LED ON
	*pPortDOutReg |= ( 1 << 13);
}
