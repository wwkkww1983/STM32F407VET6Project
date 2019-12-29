#include "gpio_cfg.h"

#ifdef USE_MCU_STM32
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T GPIO_Clock(GPIO_TypeDef *GPIOx, UINT8_T isEnable)
{
	//---ʹ�ܶ˿ڵ�ʱ��
#ifdef GPIOA
	if (GPIOx == GPIOA)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			#ifndef USE_MCU_STM32F1
				LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
			#else
				LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_GPIOA);
			#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			#ifndef USE_MCU_STM32F1
				LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
			#else
				LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
			#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			#ifndef USE_MCU_STM32F1
				LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPIOA);
			#else
				LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_GPIOA);
			#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			#ifndef USE_MCU_STM32F1
				LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPIOA);
			#else
				LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_GPIOA);
			#endif
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif // GPIOA

#ifdef GPIOB
	if (GPIOx == GPIOB)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
		#else
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_GPIOB);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
		#else
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPIOB);
		#else
			LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_GPIOB);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPIOB);
		#else
			LL_APB2_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPIOB);
		#endif
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif // GPIOB

#ifdef GPIOC
	if (GPIOx == GPIOC)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
		#else
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_GPIOC);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
		#else
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPIOC);
		#else
			LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_GPIOC);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPIOC);
		#else
			LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_GPIOC);
		#endif
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif // GPIOC

#ifdef GPIOD
	if (GPIOx == GPIOD)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
		#else
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_GPIOD);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
		#else
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPIOD);
		#else
			LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_GPIOD);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPIOD);
		#else
			LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_GPIOD);
		#endif
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif // GPIOD

#ifdef GPIOE
	if (GPIOx == GPIOE)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
		#else
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_GPIOE);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
		#else
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOE);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPIOE);
		#else
			LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_GPIOE);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPIOE);
		#else
			LL_APB2_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPIOE);
		#endif
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif // GPIOE

#ifdef GPIOF
	if (GPIOx == GPIOF)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
		#else
			LL_APB2_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
		#else
			LL_APB2_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPIOF);
		#else
			LL_APB2_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPIOF);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPIOF);
		#else
			LL_APB2_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPIOF);
		#endif
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif // GPIOF

#ifdef GPIOG
	if (GPIOx == GPIOG)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOG);
		#else
			LL_APB2_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOG);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOG);
		#else
			LL_APB2_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOG);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPIOG);
		#else
			LL_APB2_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPIOG);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPIOG);
		#else
			LL_APB2_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPIOG);
		#endif
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif // GPIOG

#ifdef GPIOH
	if (GPIOx == GPIOH)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOH);
		#else
			LL_APB2_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOH);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOH);
		#else
			LL_APB2_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOH);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPIOH);
		#else
			LL_APB2_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPIOH);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPIOH);
		#else
			LL_APB2_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPIOH);
		#endif
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif // GPIOH

#ifdef GPIOI
	if (GPIOx == GPIOI)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOI);
		#else
			LL_APB2_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOI);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOI);
		#else
			LL_APB2_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOI);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPIOI);
		#else
			LL_APB2_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPIOI);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPIOI);
		#else
			LL_APB2_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPIOI);
		#endif
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif // GPIOI

#ifdef GPIOJ
	if (GPIOx == GPIOJ)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOJ);
		#else
			LL_APB2_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOJ);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOJ);
		#else
			LL_APB2_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOJ);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPIOJ);
		#else
			LL_APB2_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPIOJ);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPIOJ);
		#else
			LL_APB2_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPIOJ);
		#endif
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif // GPIOJ

#ifdef GPIOK
	if (GPIOx == GPIOK)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOK);
		#else
			LL_APB2_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOK);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOK);
		#else
			LL_APB2_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOK);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPIOK);
		#else
			LL_APB2_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPIOK);
		#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPIOK);
		#else
			LL_APB2_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPIOK);
		#endif
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif // GPIOK
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ���� void GPIO_Init(void)
//////��	   �ܣ� �������еĶ˿�Ϊģ������
//////�������: ��
//////�������: ��
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
void GPIO_Init(void)
{
	//---ʹ�����ж˿ڵ�ʱ��
	#ifdef GPIOA
		GPIO_Clock(GPIOA, PERIPHERAL_CLOCK_ENABLE);
	#endif
	
	#ifdef GPIOB
		GPIO_Clock(GPIOB, PERIPHERAL_CLOCK_ENABLE);
	#endif
	
	#ifdef GPIOC
		GPIO_Clock(GPIOC, PERIPHERAL_CLOCK_ENABLE);
	#endif
	
	#ifdef GPIOD
		GPIO_Clock(GPIOD, PERIPHERAL_CLOCK_ENABLE);
	#endif
	
	#ifdef GPIOE
		GPIO_Clock(GPIOE, PERIPHERAL_CLOCK_ENABLE);
	#endif
	
	#ifdef GPIOF
		GPIO_Clock(GPIOF, PERIPHERAL_CLOCK_ENABLE);
	#endif
	
	#ifdef GPIOG
		GPIO_Clock(GPIOG, PERIPHERAL_CLOCK_ENABLE);
	#endif
	
	#ifdef GPIOH
		GPIO_Clock(GPIOH, PERIPHERAL_CLOCK_ENABLE);
	#endif
	
	#ifdef GPIOI
		GPIO_Clock(GPIOI, PERIPHERAL_CLOCK_ENABLE);
	#endif
	
	//---����ʱ��
	#ifndef USE_MCU_STM32F1
		//---ʹ�ܸ���ʱ��
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	#else
		//---ʹ�ܶ˿ڸ���ʱ��
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);
	#endif
	
	//---�Ƿ�ʹ��SWD���Զ˿�
	#ifdef USE_DEBUG_SWD
		#ifdef  USE_MCU_STM32F1
			//---����JTAG�˿ڣ�ʹ��SWD�˿�
			LL_GPIO_AF_Remap_SWJ_NOJTAG();
			//---�ͷ�PB4�˿�
			LL_GPIO_AF_Remap_SWJ_NONJTRST();
		#endif
	#endif
}

#endif 