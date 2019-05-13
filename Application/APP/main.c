#include "main.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ϵͳʱ�ӵ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void SystemClock_Config(void)
{
	//---����FLASH����ʱ��ȡ������
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);
	//---�ȴ�FLASH��ʱ�������---�ж������Ƿ�ɹ�
	if (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_5)
	{
		Error_Handler();
	}
	//---�����ڲ��������������ѹ
	LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
	//---ʹ���ⲿ����
	LL_RCC_HSE_Enable();
	//---�ȴ��ⲿ�����ȶ�
	while (LL_RCC_HSE_IsReady() != 1)
	{
	}
	//---ʹ���ڲ���Ƶ����
	LL_RCC_LSI_Enable();
	//---�ȴ��ڲ���Ƶ�����ȶ�
	while (LL_RCC_LSI_IsReady() != 1)
	{
	}
	//---ʹ�ܱ�����ķ���
	LL_PWR_EnableBkUpAccess();
	//---ǿ�Ʊ�����ĸ�λ
	LL_RCC_ForceBackupDomainReset();
	//---�ͷŶԱ�����ķ���
	LL_RCC_ReleaseBackupDomainReset();
	//---����RTCʱ��
	LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_HSE);
	//---����RTCʱ�ӷ�Ƶ��
	LL_RCC_SetRTC_HSEPrescaler(LL_RCC_RTC_HSE_DIV_8);
	//---ʹ��RTC
	LL_RCC_EnableRTC();
	//---����ϵͳ��PLL
	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_4, 168, LL_RCC_PLLP_DIV_2);
	//---����USBʱ��
	LL_RCC_PLL_ConfigDomain_48M(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_4, 168, LL_RCC_PLLQ_DIV_7);
	//---ʹ��PLL
	LL_RCC_PLL_Enable();

	//---�ȴ�PLL�ȶ�
	while (LL_RCC_PLL_IsReady() != 1)
	{
	}
	//---����AHB����ʱ�ӷ�Ƶ
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	//---����APB1����ʱ�ӷ�Ƶ
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
	//---����APB2����ʱ�ӷ�Ƶ
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
	//---����ϵͳʱ��
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

	//--- �ȴ�ϵͳʱ���ȶ�
	while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
	{
	}
	//LL_Init1msTick( 168000000 );
	//---����ϵͳ�δ�ʱ����ʱ��Ϊϵͳ����ʱ��--ʹ�ܵδ�ʱ����ʱ��
	LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
	//---����ϵͳʱ��
	LL_SetSystemCoreClock(168000000);
	//---ʹ��Flash��Ԥ��ȡ����
	LL_FLASH_EnablePrefetch();

	//---ʹ�����ݻ��湦��
	LL_FLASH_EnableDataCache();

	//---ʹ��ָ����ٻ���
	LL_FLASH_EnableInstCache();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void NVIC_Init(void)
{
	//---����NVIC�ķ���ģʽ
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	/* System interrupt init*/
	/* HardFault_IRQn interrupt configuration */
#ifdef USE_MCU_STM32F1
	NVIC_SetPriority(HardFault_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
#endif
	/* MemoryManagement_IRQn interrupt configuration */
	NVIC_SetPriority(MemoryManagement_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	/* BusFault_IRQn interrupt configuration */
	NVIC_SetPriority(BusFault_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	/* UsageFault_IRQn interrupt configuration */
	NVIC_SetPriority(UsageFault_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	/* SVCall_IRQn interrupt configuration */
	NVIC_SetPriority(SVCall_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	/* DebugMonitor_IRQn interrupt configuration */
	NVIC_SetPriority(DebugMonitor_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	/* PendSV_IRQn interrupt configuration */
	NVIC_SetPriority(PendSV_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Sys_Init(void)
{
    UINT8_T id=0;
    
	//---ϵͳʱ�ӵĳ�ʼ��
	SystemClock_Config();

	//---NVIC��ʼ��
	NVIC_Init();

	//---�Զ����ڴ�����ʼ��
	MyMemInit();

	//---GPIO��ʼ��
	GPIOTask_Init();
    
	//---�δ�ʱ����ʼ��
	SysTickTask_Init();

	//---�������ʼ��
	//RandomTask_Init();

	//---CRCУ���ʼ��
	CRCTask_Init();

    ADS1256Task_SPI_Init(pADS1256Device0,DelayTask_us,DelayTask_ms,SysTickTask_GetTick,0);
	
   // ADS1256_SPI_SoftReset(pADS1256Device0);
   // 
   // ADS1256_SPI_ReadDRate(pADS1256Device0,&id);
   // 
   // ADS1256_SPI_SetDRate(pADS1256Device0,ADS1256_DRATE_500SPS);
   // 
   //// ADS1256_SPI_SetDRate(pADS1256Device0,ADS1256_DRATE_5SPS);
   // 
   // ADS1256_SPI_ReadChipID(pADS1256Device0,&id);
   // 
   // ADS1256_SPI_ReadDRate(pADS1256Device0,&id);
   // 
   // DelayTask_ms(10);
   // 
   // ADS1256_SPI_SetDRate(pADS1256Device0,ADS1256_DRATE_1000SPS);
   // 
   // ADS1256_SPI_ReadDRate(pADS1256Device0,&id);
    
    
    //---��ʼ����ʱ��
	//TimerTask_Init();
	//---ADC��ʼ��
	//ADCTask_ADC_Init();
	//---��Դ���Ƴ�ʼ��
	//PowerTask_Init();
	//---���ڵĳ�ʼ��
	USARTTask_Init( pUSART1 , USART1_RX_MAX_SIZE , USART1_RX_BUFFER , USART_CRC_NONE , USART1_TX_MAX_SIZE , USART1_TX_BUFFER , USART_CRC_NONE , SysTickTask_GetTick );
	//---�������Ź�
	//IWDGTask_Init(pIWDG);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
int main(void)
{
	UINT8_T ch = 0;
	//---ϵͳ��ʼ������
	Sys_Init();
	//---��ѭ��
	while (1)
	{
		//USART_Printf(pUSART1, "\r\n��ʼʱ��:%d ms\r\n",SysTickTask_GetTick());
		//---�������
		USARTTask_FillMode_Init(pUSART1);
		USARTTask_FillMode_AddByte(pUSART1, 0xAA);
		USARTTask_FillMode_AddByte(pUSART1, 0x00);
		for (ch=0;ch<8;ch++)
		{
			ADS1256_SPI_AutoReadChannelResult(pADS1256Device0, ch);
			//---ADCͨ��
			USARTTask_FillMode_AddByte(pUSART1, (ch + 1));
			if (pADS1256Device0->msgDeviceReady == 0)
			{
				//if (pADS1256Device0->msgIsPositive[ch] != 0)
				//{
				//	//USART_Printf(pUSART1, "ADC1SampleResult:%d\r\n", pADS1256Device0->msgChannelADCResult[0]);
				//	USART_Printf(pUSART1, "ͨ��%d��ѹ:%7duV\r\n", (ch+1), pADS1256Device0->msgChannelNowPowerResult[ch]);
				//}
				//---�����Ƿ���Ч
				USARTTask_FillMode_AddByte(pUSART1, pADS1256Device0->msgIsPositive[ch]);
			}
			else
			{
				USARTTask_FillMode_AddByte(pUSART1, 0);
			}
			//---���������
			USARTTask_FillMode_AddByte(pUSART1, (UINT8_T)(pADS1256Device0->msgChannelNowPowerResult[ch]>>16));
			USARTTask_FillMode_AddByte(pUSART1, (UINT8_T)(pADS1256Device0->msgChannelNowPowerResult[ch] >> 8));
			USARTTask_FillMode_AddByte(pUSART1, (UINT8_T)(pADS1256Device0->msgChannelNowPowerResult[ch] ));
			pADS1256Device0->msgSPI.msgFuncDelayus(100);
		}
		//USART_Printf(pUSART1, "����ʱ��:%d ms\r\n", SysTickTask_GetTick());
		//---��������
		USARTTask_FillMode_WriteSTART(pUSART1, 1);
		DelayTask_ms(300);
		
		////---���ߵ�������
		//USARTTask_FuncTask(pUSART1,NULL);
		//---ģ��RTC����
		SysRTCTask_SoftBuildTask(pSysSoftRTC, SysTickTask_GetTick());
		WDT_RESET();
	}
}