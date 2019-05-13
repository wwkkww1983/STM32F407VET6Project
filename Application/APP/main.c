#include "main.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：系统时钟的配置
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void SystemClock_Config(void)
{
	//---设置FLASH的延时读取周期数
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);
	//---等待FLASH延时设置完成---判断设置是否成功
	if (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_5)
	{
		Error_Handler();
	}
	//---设置内部调节器的输出电压
	LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
	//---使能外部晶振
	LL_RCC_HSE_Enable();
	//---等待外部晶振稳定
	while (LL_RCC_HSE_IsReady() != 1)
	{
	}
	//---使能内部低频晶振
	LL_RCC_LSI_Enable();
	//---等待内部低频晶振稳定
	while (LL_RCC_LSI_IsReady() != 1)
	{
	}
	//---使能备份域的访问
	LL_PWR_EnableBkUpAccess();
	//---强制备份域的复位
	LL_RCC_ForceBackupDomainReset();
	//---释放对备份域的服务
	LL_RCC_ReleaseBackupDomainReset();
	//---设置RTC时钟
	LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_HSE);
	//---设置RTC时钟分频数
	LL_RCC_SetRTC_HSEPrescaler(LL_RCC_RTC_HSE_DIV_8);
	//---使能RTC
	LL_RCC_EnableRTC();
	//---设置系统的PLL
	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_4, 168, LL_RCC_PLLP_DIV_2);
	//---设置USB时钟
	LL_RCC_PLL_ConfigDomain_48M(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_4, 168, LL_RCC_PLLQ_DIV_7);
	//---使能PLL
	LL_RCC_PLL_Enable();

	//---等待PLL稳定
	while (LL_RCC_PLL_IsReady() != 1)
	{
	}
	//---设置AHB总线时钟分频
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	//---设置APB1总线时钟分频
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
	//---设置APB2总线时钟分频
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
	//---设置系统时钟
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

	//--- 等待系统时钟稳定
	while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
	{
	}
	//LL_Init1msTick( 168000000 );
	//---设置系统滴答定时器的时钟为系统高速时钿--使能滴答定时器的时钟
	LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
	//---设置系统时钟
	LL_SetSystemCoreClock(168000000);
	//---使能Flash的预读取功能
	LL_FLASH_EnablePrefetch();

	//---使能数据缓存功能
	LL_FLASH_EnableDataCache();

	//---使能指令高速缓存
	LL_FLASH_EnableInstCache();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void NVIC_Init(void)
{
	//---设置NVIC的分组模式
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void Sys_Init(void)
{
    UINT8_T id=0;
    
	//---系统时钟的初始化
	SystemClock_Config();

	//---NVIC初始化
	NVIC_Init();

	//---自定义内存管理初始化
	MyMemInit();

	//---GPIO初始化
	GPIOTask_Init();
    
	//---滴答定时器初始化
	SysTickTask_Init();

	//---随机数初始化
	//RandomTask_Init();

	//---CRC校验初始化
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
    
    
    //---初始化定时器
	//TimerTask_Init();
	//---ADC初始化
	//ADCTask_ADC_Init();
	//---电源控制初始化
	//PowerTask_Init();
	//---串口的初始化
	USARTTask_Init( pUSART1 , USART1_RX_MAX_SIZE , USART1_RX_BUFFER , USART_CRC_NONE , USART1_TX_MAX_SIZE , USART1_TX_BUFFER , USART_CRC_NONE , SysTickTask_GetTick );
	//---开启看门狗
	//IWDGTask_Init(pIWDG);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
int main(void)
{
	UINT8_T ch = 0;
	//---系统初始化函数
	Sys_Init();
	//---主循环
	while (1)
	{
		//USART_Printf(pUSART1, "\r\n开始时间:%d ms\r\n",SysTickTask_GetTick());
		//---填充数据
		USARTTask_FillMode_Init(pUSART1);
		USARTTask_FillMode_AddByte(pUSART1, 0xAA);
		USARTTask_FillMode_AddByte(pUSART1, 0x00);
		for (ch=0;ch<8;ch++)
		{
			ADS1256_SPI_AutoReadChannelResult(pADS1256Device0, ch);
			//---ADC通道
			USARTTask_FillMode_AddByte(pUSART1, (ch + 1));
			if (pADS1256Device0->msgDeviceReady == 0)
			{
				//if (pADS1256Device0->msgIsPositive[ch] != 0)
				//{
				//	//USART_Printf(pUSART1, "ADC1SampleResult:%d\r\n", pADS1256Device0->msgChannelADCResult[0]);
				//	USART_Printf(pUSART1, "通道%d电压:%7duV\r\n", (ch+1), pADS1256Device0->msgChannelNowPowerResult[ch]);
				//}
				//---数据是否有效
				USARTTask_FillMode_AddByte(pUSART1, pADS1256Device0->msgIsPositive[ch]);
			}
			else
			{
				USARTTask_FillMode_AddByte(pUSART1, 0);
			}
			//---填充采样结果
			USARTTask_FillMode_AddByte(pUSART1, (UINT8_T)(pADS1256Device0->msgChannelNowPowerResult[ch]>>16));
			USARTTask_FillMode_AddByte(pUSART1, (UINT8_T)(pADS1256Device0->msgChannelNowPowerResult[ch] >> 8));
			USARTTask_FillMode_AddByte(pUSART1, (UINT8_T)(pADS1256Device0->msgChannelNowPowerResult[ch] ));
			pADS1256Device0->msgSPI.msgFuncDelayus(100);
		}
		//USART_Printf(pUSART1, "结束时间:%d ms\r\n", SysTickTask_GetTick());
		//---启动发送
		USARTTask_FillMode_WriteSTART(pUSART1, 1);
		DelayTask_ms(300);
		
		////---在线调试命令
		//USARTTask_FuncTask(pUSART1,NULL);
		//---模拟RTC处理
		SysRTCTask_SoftBuildTask(pSysSoftRTC, SysTickTask_GetTick());
		WDT_RESET();
	}
}