#include <stdint.h>
#include "reg.h"
#include "blink.h"

int main(void)
{
	//RCC Enable GPIOA
	SET_BIT(RCC_BASE + RCC_AHB1ENR_OFFSET, GPIO_EN_BIT(GPIO_PORTA));
	//GPIO Configurations
		//MODER BUTTON pin = 00 => General purpose input mode
	CLEAR_BIT(GPIO_BASE(GPIO_PORTA)+GPIOx_MODER_OFFSET,MODERy_1_BIT(0));
	CLEAR_BIT(GPIO_BASE(GPIO_PORTA)+GPIOx_MODER_OFFSET,MODERy_0_BIT(0));
		//PUPDR led pin = 00 => No pull-up, pull-down
	CLEAR_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_PUPDR_OFFSET, PUPDRy_1_BIT(0));
	CLEAR_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_PUPDR_OFFSET, PUPDRy_0_BIT(0));

	//RCC Enable SYSCFG
	SET_BIT(RCC_BASE + RCC_AHB1ENR_OFFSET, GPIO_EN_BIT(GPIO_PORTA));


	//SYSCFG Configurations
	WRITE_BITS(SYSCFG_BASE + SYSCFG_EXTICR1_OFFSET, EXTI0_3_BIT,EXTI0_0_BIT,0b0000);


	//EXTI Configurations
		//not mask interrupt request //1= not mask=啟用
	SET_BIT(EXTI_BASE+EXTI_IMR_OFFSET,0);
		//rising triger 1=enable
	SET_BIT(EXTI_BASE+EXTI_RTSR_OFFSET,0);
		//falling trigrt 0=disable
	CLEAR_BIT(EXTI_BASE+EXTI_FTSR_OFFSET,0);
		//SET PEDDING
	SET_BIT(EXTI_BASE+EXTI_PR_OFFSET,0);



	//NVIC Configurations
	SET_BIT(NVIC_ISER_BASE + NVIC_ISERn_OFFSET(0), 6); //IRQ6

	blink(LED_BLUE);
}

void exti0_handler(void)
{
	blink_count(LED_ORANGE, 10);
	SET_BIT(EXTI_BASE + EXTI_PR_OFFSET, 0);
}

