#include "main.h"

UINT8_T ads8688Tem[2] = {0};

UINT8_T debugWTemp[80] = {
	0x30,0x73,0x67,0x66,0x6E,0x7C,0x10,0x3C,0x7E,0x4B,0x4F,0x6E,0x30,0x00,0x7E,0x7F,
	0x03,0x7F,0x20,0x6E,0x6F,0x7B,0x3B,0x13,0x3E,0x6F,0x4B,0x6F,0x6E,0x30,0x00,0x3E,
	0x7E,0x67,0x73,0x3F,0x7E,0x60,0x7F,0x03,0x3F,0x7F,0x60,0x3E,0x63,0x63,0x7F,0x7F,
	0x00,0x00,0x00,0x7F,0x60,0x60,0x61,0x73,0x3F,0x00,0x7F,0x7F,0x03,0x07,0x0F,0x00,
	0x7F,0x00,0x07,0x1F,0x78,0x78,0x1F,0x3E,0x7B,0x6B,0x6F,0x6F,0x76,0x00,0x03,0x03
};

UINT8_T debugRTemp[80] = {0};

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ϵͳʱ�ӵ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void SystemClock_Config(void)
{
	//---PWRʱ��
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
	//---�����ڲ��������������ѹ
	LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
	//---����FLASH����ʱ��ȡ������
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);
	//---�ȴ�FLASH��ʱ�������---�ж������Ƿ�ɹ�
	if (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_5)
	{
		Error_Handler();
	}
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
    //UINT8_T id=0;
    
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
	
	//---ָʾ�Ƶĳ�ʼ��
	//LEDTask_Init();
	
	//---DAC�ĳ�ʼ��
	//DACTask_Init();
	//DACTask_DAC_WriteVoltageMV(20);
	
	//---ADS8688�ĳ�ʼ��
	//ADS868X_SPI_Init(pADS868XDevice0, DelayTask_us, DelayTask_ms, SysTickTask_GetTick, 1);
	//---ADS8698�ĳ�ʼ��
	//ADS869X_SPI_Init(pADS869XDevice0, DelayTask_us, DelayTask_ms, SysTickTask_GetTick, 1);
	W25QXXTask_SPI_Init(pW25QXXDevice0, DelayTask_us, DelayTask_ms, SysTickTask_GetTick, 1);

	W25QXXTask_SPI_ReadID(pW25QXXDevice0);
	
	W25QXXTask_SPI_EraseSector(pW25QXXDevice0,0);
	
	W25QXXTask_SPI_WritePage(pW25QXXDevice0,0,debugWTemp,80);
	W25QXXTask_SPI_ReadData(pW25QXXDevice0,0,debugRTemp,80);
	
	CompareFun1(debugWTemp, debugRTemp, 80);
	//---��ʼ����ʱ��
	//TimerTask_Init();
	//---ADC��ʼ��
	//ADCTask_ADC_Init();
	//---��Դ���Ƴ�ʼ��
	//PowerTask_Init();
	//---���ڵĳ�ʼ��
	//USARTTask_Init( pUSART1 , USART1_RX_MAX_SIZE , USART1_RX_BUFFER , USART_CRC_NONE , USART1_TX_MAX_SIZE , USART1_TX_BUFFER , USART_CRC_NONE , SysTickTask_GetTick );
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
	UINT16_T cnt = 0;
	//---ϵͳ��ʼ������
	Sys_Init();
	//---��ѭ��
	while (1)
	{
		
		//ADS8688_SPI_WriteProgramReg(pADS8688Device0, ADS8688_PROG_REG_AUTO_SEQ_EN, 0xFF);
		//ADS8688_SPI_ReadProgramReg(pADS8688Device0, ADS8688_PROG_REG_AUTO_SEQ_EN, &ads8688Tem[0]);
		//DelayTask_ms(100);
		//USART_Printf(pUSART1, "д�뵽SEQ_EN���ݣ�%X \r\n", ads8688Tem[1]);
		//ADS8688_SPI_WriteProgramReg(pADS8688Device0, ADS8688_PROG_REG_FEATURE_SELECT, 0x28);
		//ADS8688_SPI_ReadProgramReg(pADS8688Device0, ADS8688_PROG_REG_FEATURE_SELECT, ads8688Tem);
		//USART_Printf(pUSART1, "д�뵽FEATURE_SELECT���ݣ�%X \r\n", ads8688Tem[1]);
		//ADS868X_SPI_GetAutoRSTResult(pADS8688Device0, 8);
		/*
		ADS868X_SPI_GetAutoRSTNSampleResult(pADS868XDevice0, 8);
		for (ch  = 0; ch < 8; ch++)
		{
			USART_Printf(pUSART1, "ADCSampleResult:%d\r\n", pADS868XDevice0->msgChannelNowADCResult[ch]);
			USART_Printf(pUSART1, "ͨ��%d��ѹ:%7duV\r\n", (ch + 1), pADS868XDevice0->msgChannelPowerResult[ch]);
		}
		*/
		//ADS8688_SPI_GetManualChannelResult(pADS8688Device0, ADS8688_CMD_REG_MAN_CH_0);
		//USART_Printf(pUSART1, "��������:%d\r\n", cnt+1);
		//ADS868X_SPI_GetManualChannelNSampleResult(pADS868XDevice0, ADS868X_CMD_REG_MAN_CH_0);
		//ch = 0;
		//USART_Printf(pUSART1, "���ݸ�ʽ:%d\r\n", pADS868XDevice0->msgIsPositive[ch]);
		//USART_Printf(pUSART1, "ADCNowSampleResult:%d\r\n", pADS868XDevice0->msgChannelNowADCResult[ch]);
		//USART_Printf(pUSART1, "ADCOldSampleResult:%d\r\n", pADS868XDevice0->msgChannelOldADCResult[ch]);
		//USART_Printf(pUSART1, "ͨ��%d��ѹ:%7duV\r\n", (ch + 1), pADS868XDevice0->msgChannelPowerResult[ch]);
		//USART_Printf(pUSART1, "ƽ����͵Ĳ������\r\n");
		//ADS869X_SPI_GetManualChannelNSampleResult(pADS869XDevice0, ADS869X_CMD_REG_MAN_CH_0,0);
		////ADS869X_SPI_KalmanFilterGetManualChannelNSampleResult(pADS869XDevice0, ADS869X_CMD_REG_MAN_CH_0);
		//ch = 0;
		//USART_Printf(pUSART1, "���ݸ�ʽ:%d\r\n", pADS869XDevice0->msgIsPositive[ch]);
		//USART_Printf(pUSART1, "ADCNowSampleResult:%d\r\n", pADS869XDevice0->msgChannelNowADCResult[ch]);
		//USART_Printf(pUSART1, "ADCOldSampleResult:%d\r\n", pADS869XDevice0->msgChannelOldADCResult[ch]);
		//USART_Printf(pUSART1, "ͨ��%d��ѹ:%7duV\r\n", (ch + 1), pADS869XDevice0->msgChannelPowerResult[ch]);

		//USART_Printf(pUSART1, "�������˲��Ĳ������\r\n");
		////ADS869X_SPI_GetManualChannelNSampleResult(pADS869XDevice0, ADS869X_CMD_REG_MAN_CH_0);
		//ADS869X_SPI_KalmanFilterGetManualChannelNSampleResult(pADS869XDevice0, ADS869X_CMD_REG_MAN_CH_0,0);
		//ch = 0;
		//USART_Printf(pUSART1, "���ݸ�ʽ:%d\r\n", pADS869XDevice0->msgIsPositive[ch]);
		//USART_Printf(pUSART1, "ADCNowSampleResult:%d\r\n", pADS869XDevice0->msgChannelNowADCResult[ch]);
		//USART_Printf(pUSART1, "ADCOldSampleResult:%d\r\n", pADS869XDevice0->msgChannelOldADCResult[ch]);
		//USART_Printf(pUSART1, "ͨ��%d��ѹ:%7duV\r\n", (ch + 1), pADS869XDevice0->msgChannelPowerResult[ch]);
		/*
		ADS868X_SPI_GetManualChannelNSampleResult(pADS868XDevice0, ADS868X_CMD_REG_MAN_CH_1);
		ch = 1;
		USART_Printf(pUSART1, "���ݸ�ʽ:%d\r\n", pADS868XDevice0->msgIsPositive[ch]);
		USART_Printf(pUSART1, "ADCNowSampleResult:%d\r\n", pADS868XDevice0->msgChannelNowADCResult[ch]);
		USART_Printf(pUSART1, "ADCOldSampleResult:%d\r\n", pADS868XDevice0->msgChannelOldADCResult[ch]);
		USART_Printf(pUSART1, "ͨ��%d��ѹ:%7duV\r\n", (ch + 1), pADS868XDevice0->msgChannelPowerResult[ch]);
		
		ADS868X_SPI_GetManualChannelNSampleResult(pADS868XDevice0, ADS868X_CMD_REG_MAN_CH_2);
		ch = 2;
		USART_Printf(pUSART1, "���ݸ�ʽ:%d\r\n", pADS868XDevice0->msgIsPositive[ch]);
		USART_Printf(pUSART1, "ADCNowSampleResult:%d\r\n", pADS868XDevice0->msgChannelNowADCResult[ch]);
		USART_Printf(pUSART1, "ADCOldSampleResult:%d\r\n", pADS868XDevice0->msgChannelOldADCResult[ch]);
		USART_Printf(pUSART1, "ͨ��%d��ѹ:%7duV\r\n", (ch + 1), pADS868XDevice0->msgChannelPowerResult[ch]);*/
		//DelayTask_ms(300);
		////---���ߵ�������
		//USARTTask_FuncTask(pUSART1,NULL);
		//---ģ��RTC����
		//SysRTCTask_SoftBuildTask(pSysSoftRTC, SysTickTask_GetTick());
		//cnt++;
		/*if (cnt>10000)
		{
			cnt = 0;
		}*/
		WDT_RESET();
	}
}