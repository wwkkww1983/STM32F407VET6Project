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
	//---PWRʱ��
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
	//---�����ڲ��������������ѹ
	LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
	#if 1
		//---ʹ��ϵͳ�ⲿ��Դ����
		LL_RCC_HSE_Enable();
	#else
		//---ʹ��ϵͳ�ⲿ��Դ����
		LL_RCC_HSE_EnableBypass();
	#endif
	//---�ȴ��ⲿϵͳ�����ȶ�
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
	//---����ϵͳ��PLL,��������ϵͳ����ʱ��
	#if (HSE_VALUE==4000000UL)
		LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_2, 168, LL_RCC_PLLP_DIV_2);
	#elif (HSE_VALUE==6000000UL)
		LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_3, 168, LL_RCC_PLLP_DIV_2);
	#elif (HSE_VALUE==8000000UL)
		LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_4, 168, LL_RCC_PLLP_DIV_2);
	#elif (HSE_VALUE==12000000UL)
		LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_6, 168, LL_RCC_PLLP_DIV_2);
	#elif (HSE_VALUE==16000000UL)
		LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_8, 168, LL_RCC_PLLP_DIV_2);
	#elif (HSE_VALUE==20000000UL)
		LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_10, 168, LL_RCC_PLLP_DIV_2);
	#elif (HSE_VALUE==24000000UL)
		LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_12, 168, LL_RCC_PLLP_DIV_2);
	#else
		#error "�ⲿ�������óɴ���ֻ֧��8M��16M������!"
	#endif
	//---����USBʱ��
	//LL_RCC_PLL_ConfigDomain_48M(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_4, 168, LL_RCC_PLLQ_DIV_7);
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
	//--- �ȴ�ϵͳʱ���ȶ�����PLL������Ƶ֮���Ƶ��
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
	//---ϵͳʱ�ӵĳ�ʼ��
	SystemClock_Config();	
	//---NVIC��ʼ��
	NVIC_Init();
	//---�Զ����ڴ�����ʼ��
	MyMemInit();
	//---Ӳ��RTC�ĳ�ʼ��
	//SysRTCTask_HardRTCInit(pSysHWRTC,0,0);
	//---���RTC�ĳ�ʼ��
	//SysRTCTask_SoftRTCInit(pSysSoftRTC,0,0);
	SysRTCTask_RTCInit(pSysSoftRTC, 0,0,0);
	//---GPIO��ʼ��
	GPIOTask_Init();    
	//---�δ�ʱ����ʼ��
	SysTickTask_Init();
	//---�������ʼ��,�����жϷ�ʽ
	//RandomTask_Init(0);
	//---CRCУ���ʼ��
	CRCTask_Init();
	//---��ʱ����ʼ��
	TimerTask_Init();
	//---���ڵĳ�ʼ��
	USARTTask_Init(pUsart1, USART1_RX_MAX_SIZE, USART1_RX_BUFFER, USART_CRC_NONE, USART1_TX_MAX_SIZE, USART1_TX_BUFFER, USART_CRC_NONE, SysTickTask_GetTick);
	//---HMC5883�ĳ�ʼ��
	HMC5883Task_I2C_Init(pHmc5883Device0, DelayTask_us,DelayTask_ms, SysTickTask_GetTick, 0);
	//---AHT10�ĳ�ʼ��
	AHT10Task_I2C_Init(pAht10Device0, DelayTask_us, DelayTask_ms, SysTickTask_GetTick, 0);
	//---ISP�ĳ�ʼ��
	//ISPTask_Init(pIspDevice0,DelayTask_us,DelayTask_ms, SysTickTask_GetTick);
	//---JTAG�ĳ�ʼ��
	//JTAG_Init(pJtagDevice0, DelayTask_us, DelayTask_ms, SysTickTask_GetTick);
	//---WM8510
	//WM8510Task_I2C_Init(pWm8510Device0, DelayTask_us, SysTickTask_GetTick, 0);
	//---SI5351A
	//SI5351ATask_I2C_Init(pSI5351ADevice0, DelayTask_us, SysTickTask_GetTick, 0);
	//---ָʾ�Ƶĳ�ʼ��
	//LEDTask_Init();	
	//---DAC�ĳ�ʼ��
	//DACTask_Init(DAC_CHANNEL_SELECT_ALL, DAC_CHANNEL_ENABLE_BUFFER);
	//---�������ߵĳ�ʼ��
	//DataBus_Init();
	//---��ʼ��LM317���Ŀɵ���Դ
	//LM317Task_Init(0,3000);
	//LM317_POWER_ON;
	//HMC5883Task_CalibrateMag(pHmc5883Device0);
	//---ADC��ʼ��
	//ADCTask_ADC_Init();
	//ADCTask_ADCTask_START(ADC1);
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
	UINT8_T _return=0;
	UINT16_T i=0;
	
	//---ϵͳ��ʼ������
	Sys_Init();
	//---��ѭ��
	while (1)
	{		
	//	for ( i = 0; i < 256; i++)
	//	{
	//		//---���������ź�
	//		GPIO_OUT_0(TRIG_PULSE_PORT, TRIG_PULSE_BIT);
	//		DelayTask_ms(1);
	//		GPIO_OUT_1(TRIG_PULSE_PORT, TRIG_PULSE_BIT);
	//		DelayTask_ms(1);
	//		//---��ʱ100ms����ȡƵ��ֵ
	//		DelayTask_ms(100);
	//		//---��ȡУ׼��
	//		_return = DataBus_Read();
	//		//---��ȡʱ��Ƶ��
	//		TimerTask_CalcFreq_Task(0);
	//		USART_Printf(pUsart1,"OSCCAL;%d;FREQ;%f;\r\n",_return, pCalcFreq->msgFreqKHz[0]);
	//	}
	//	if (i>0xFF)
	//	{
	//		while (1);
	//	}
		HMC5883Task_ReadRawData(pHmc5883Device0);
		USART_Printf(pUsart1, "X=%d,Y=%d,Y=%d,angle=%f\r\n",pHmc5883Device0->msgX,pHmc5883Device0->msgY,pHmc5883Device0->msgZ,pHmc5883Device0->msgAngle);
		//i++;
		AHT10Task_I2C_ReadTempHumi(pAht10Device0);
		USART_Printf(pUsart1, "Temp=%f,Humi=%f\r\n", AHT10Task_I2C_GetTemp(pAht10Device0),AHT10Task_I2C_GetHumi(pAht10Device0));
		DelayTask_ms(300);		
		//---ģ��RTC����
		SysRTCTask_SoftRTCTask(pSysSoftRTC, SysTickTask_GetTick());
		//---���������
		//Task_Manage();
		//---Ƶ�ʲ��Ժ���
		//USARTTask_DebugFreqTask(pUsart1,NULL);
		//---�߼�����
		//USARTTask_FuncTask(pUsart1,NULL);
		//---ι��
		WDT_RESET();
	}
}