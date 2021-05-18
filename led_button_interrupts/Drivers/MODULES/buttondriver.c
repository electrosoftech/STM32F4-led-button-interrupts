/*
 * buttondriver.c
 *
 *  Created on: Mar 18, 2021
 *      Author: Numan
 */
#include "stm32f4xx_hal.h"

void buttondriver_init()
{
	RCC->AHB1ENR |= (1<<0);

	GPIOA->MODER &= ~(1<<1);
	GPIOA->MODER &= ~(1<<0);
}

void buttonDriverInt_Init()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_SYSCFG_CLK_ENABLE();
	//GPIOC

	GPIOA->MODER &= ~(1<<1);
	GPIOA->MODER &= ~(1<<0);
//	GPIOA ->MODER &= ~((3UL << 0));
//	GPIOA ->PUPDR &= ~((3UL << 0));
	//SYSCFG
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
	//EXTI
	EXTI-> IMR |= EXTI_IMR_IM0;
	EXTI-> RTSR |= EXTI_RTSR_TR0;
	//NVIC
	NVIC_SetPriority(EXTI0_IRQn, 1);
	NVIC_EnableIRQ(EXTI0_IRQn);

}

void EXTI0_IRQHandler(void)
{

	GPIOD->ODR ^= GPIO_PIN_12;
	GPIOD->ODR ^= GPIO_PIN_13;
	GPIOD->ODR ^= GPIO_PIN_14;
	GPIOD->ODR ^= GPIO_PIN_15;
	EXTI->PR |= EXTI_PR_PR0;
}
