#include "uart_cfg.h"

//===全局变量定义
UART_HandlerType  g_Uart1 = { 0 };
pUART_HandlerType pUart1 = &g_Uart1;

//=== 全局变量定义
UART_HandlerType  g_Uart3 = { 0 };
pUART_HandlerType pUart3 = &g_Uart3;

//===printf函数使用的缓存区
#ifdef USE_UART_PRINTF
	char g_PrintfBuffer[UART_PRINTF_SIZE] = { 0 };
	//---初始化printf环形缓存区
	UART_PrintfType g_Printf = 
	{ 
		.msgIndex =0,
		.pMsgVal= g_PrintfBuffer
	};
	pUART_PrintfType pPrintf =&g_Printf;
#endif

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_StructInit(UART_HandlerType*  UARTx)
{
	//---串口的数据处理流程
	UARTx->msgIndex = 0;
	UARTx->msgRxdID = 0;
	UARTx->msgTxdID = 0;
	UARTx->msgID = 0;
	UARTx->msgIDIndex = 0;
	UARTx->msgCmdIndex = 0;
	UARTx->msgDataOneIndex = 0;
	UARTx->msgDataTwoIndex = 0;
	UARTx->msgIndexOffset=0;
	UARTx->msgTxPort.msgPort = NULL;
	UARTx->msg485Port.msgPort = NULL;
	UARTx->msgUART = NULL;

	//---接收缓存区
	UARTx->msgRxdHandler.msgDMAMode = 1;
	UARTx->msgRxdHandler.msgCheckSum = 0;
	UARTx->msgRxdHandler.msgCRCFlag = 0;
	UARTx->msgRxdHandler.msgStep = 0;
	UARTx->msgRxdHandler.msgAddNewLine = 0;
	UARTx->msgRxdHandler.msgWIndex = 0;
	UARTx->msgRxdHandler.msgRIndex = 0;
	UARTx->msgRxdHandler.msgFlagIndex =0;
	UARTx->msgRxdHandler.msgCount = 0;
	UARTx->msgRxdHandler.msgMaxSize = 0;
	UARTx->msgRxdHandler.msgState = UART_BUSY;
	UARTx->msgRxdHandler.msgOverFlow = 0;
	UARTx->msgRxdHandler.msgRecordTick = 0;
	UARTx->msgRxdHandler.msgRecordTime=0;
	UARTx->msgRxdHandler.msgMaxTime = 0;
	UARTx->msgRxdHandler.pMsgVal = NULL;
	//---计数器
	UARTx->msgRxdHandler.msgTimeTick = NULL;

	//---发送缓存区
	UARTx->msgTxdHandler.msgDMAMode = 1;
	UARTx->msgTxdHandler.msgCheckSum = 0;
	UARTx->msgTxdHandler.msgCRCFlag = 0;
	UARTx->msgTxdHandler.msgStep = 0;
	UARTx->msgTxdHandler.msgAddNewLine = 0;
	UARTx->msgTxdHandler.msgWIndex = 0;
	UARTx->msgTxdHandler.msgRIndex = 0;
	UARTx->msgTxdHandler.msgFlagIndex = 0;
	UARTx->msgTxdHandler.msgCount = 0;
	UARTx->msgTxdHandler.msgMaxSize = 0;
	UARTx->msgTxdHandler.msgState = UART_OK;
	UARTx->msgTxdHandler.msgOverFlow = 0;
	UARTx->msgTxdHandler.msgRecordTick = 0;
	UARTx->msgTxdHandler.msgRecordTime = 0;
	UARTx->msgTxdHandler.msgMaxTime = 0;
	UARTx->msgTxdHandler.pMsgVal = NULL;
	//---计数器
	UARTx->msgTxdHandler.msgTimeTick = NULL;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：用指定的配置，初始化指定的串口
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_ConfigInit(UART_HandlerType* UARTx, UART_HandlerType* UARTInitx)
{
	//---串口的数据处理流程
	UARTx->msgIndex				= UARTInitx->msgIndex								;
	UARTx->msgRxdID				= UARTInitx->msgRxdID								;
	UARTx->msgTxdID				= UARTInitx->msgTxdID								;
	UARTx->msgID				= UARTInitx->msgID									;
	UARTx->msgIDIndex			= UARTInitx->msgIDIndex								;
	UARTx->msgCmdIndex			= UARTInitx->msgCmdIndex							;
	UARTx->msgDataOneIndex		= UARTInitx->msgDataOneIndex						;
	UARTx->msgDataTwoIndex		= UARTInitx->msgDataTwoIndex						;
	UARTx->msgIndexOffset		= UARTInitx->msgIndexOffset							;
	UARTx->msgTxPort.msgPort	= UARTInitx->msgTxPort.msgPort						;
	UARTx->msg485Port.msgPort	= UARTInitx->msg485Port.msgPort						;
	UARTx->msgUART				= UARTInitx->msgUART								;

	//---接收缓存区
	UARTx->msgRxdHandler.msgDMAMode		= UARTInitx->msgRxdHandler.msgDMAMode		;
	UARTx->msgRxdHandler.msgCheckSum	= UARTInitx->msgRxdHandler.msgCheckSum		;
	UARTx->msgRxdHandler.msgCRCFlag		= UARTInitx->msgRxdHandler.msgCRCFlag		;
	UARTx->msgRxdHandler.msgStep		= UARTInitx->msgRxdHandler.msgStep			;
	UARTx->msgRxdHandler.msgAddNewLine	= UARTInitx->msgRxdHandler.msgAddNewLine	;
	UARTx->msgRxdHandler.msgWIndex		= UARTInitx->msgRxdHandler.msgWIndex		;
	UARTx->msgRxdHandler.msgRIndex		= UARTInitx->msgRxdHandler.msgRIndex		;
	UARTx->msgRxdHandler.msgFlagIndex	= UARTInitx->msgRxdHandler.msgFlagIndex		;
	UARTx->msgRxdHandler.msgCount		= UARTInitx->msgRxdHandler.msgCount			;
	UARTx->msgRxdHandler.msgMaxSize		= UARTInitx->msgRxdHandler.msgMaxSize		;
	UARTx->msgRxdHandler.msgState		= UARTInitx->msgRxdHandler.msgState			;
	UARTx->msgRxdHandler.msgOverFlow	= UARTInitx->msgRxdHandler.msgOverFlow		;
	UARTx->msgRxdHandler.msgRecordTick	= UARTInitx->msgRxdHandler.msgRecordTick	;
	UARTx->msgRxdHandler.msgRecordTime	= UARTInitx->msgRxdHandler.msgRecordTime	;
	UARTx->msgRxdHandler.msgMaxTime		= UARTInitx->msgRxdHandler.msgMaxTime		;
	UARTx->msgRxdHandler.pMsgVal		= UARTInitx->msgRxdHandler.pMsgVal			;
	//---计数器
	UARTx->msgRxdHandler.msgTimeTick	= UARTInitx->msgRxdHandler.msgTimeTick		;

	//---发送缓存区
	UARTx->msgTxdHandler.msgDMAMode		= UARTInitx->msgTxdHandler.msgDMAMode		;
	UARTx->msgTxdHandler.msgCheckSum	= UARTInitx->msgTxdHandler.msgCheckSum		;
	UARTx->msgTxdHandler.msgCRCFlag		= UARTInitx->msgTxdHandler.msgCRCFlag		;
	UARTx->msgTxdHandler.msgStep		= UARTInitx->msgTxdHandler.msgStep			;
	UARTx->msgTxdHandler.msgAddNewLine	= UARTInitx->msgTxdHandler.msgAddNewLine 	;
	UARTx->msgTxdHandler.msgWIndex		= UARTInitx->msgTxdHandler.msgWIndex		;
	UARTx->msgTxdHandler.msgRIndex		= UARTInitx->msgTxdHandler.msgRIndex		;
	UARTx->msgTxdHandler.msgFlagIndex	= UARTInitx->msgTxdHandler.msgFlagIndex		;
	UARTx->msgTxdHandler.msgCount		= UARTInitx->msgTxdHandler.msgCount			;
	UARTx->msgTxdHandler.msgMaxSize		= UARTInitx->msgTxdHandler.msgMaxSize		;
	UARTx->msgTxdHandler.msgState		= UARTInitx->msgTxdHandler.msgState			;
	UARTx->msgTxdHandler.msgOverFlow	= UARTInitx->msgTxdHandler.msgOverFlow		;
	UARTx->msgTxdHandler.msgRecordTick	= UARTInitx->msgTxdHandler.msgRecordTick 	;
	UARTx->msgTxdHandler.msgRecordTime	= UARTInitx->msgTxdHandler.msgRecordTime 	;
	UARTx->msgTxdHandler.msgMaxTime		= UARTInitx->msgTxdHandler.msgMaxTime		;
	UARTx->msgTxdHandler.pMsgVal		= UARTInitx->msgTxdHandler.pMsgVal			;
	//---计数器
	UARTx->msgTxdHandler.msgTimeTick	= UARTInitx->msgTxdHandler.msgTimeTick		;
	
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：UART1的参数配置
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART1_ConfigInit(UART_HandlerType* UARTx)
{
	//---UART1 GPIO Configuration
	//---PA9  ------> UART1_TX---端口复用为7
	//---PA10 ------> UART1_RX---端口复用为7
	//---使能端口时钟
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(GPIOA, PERIPHERAL_CLOCK_ENABLE);
	#endif
	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---模式配置
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	//---工作速度
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	//---复用功能的推完输出
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	//---输入上拉使能
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	#ifdef USE_MCU_STM32F1
	//---TX
	GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	//---RX
	GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	#else
	//---端口号
	GPIO_InitStruct.Pin = LL_GPIO_PIN_9 | LL_GPIO_PIN_10;
	//---复用功能为UART1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	#endif
	//---配置消息结构体中的信息
	UARTx->msgTxPort.msgPort = GPIOA;
	UARTx->msgTxPort.msgBit = LL_GPIO_PIN_9;
	UARTx->msgUART = USART1;
	//---串口序号
	UARTx->msgIndex = 1 + 1;
	//---注销串口的初始化
	LL_USART_DeInit(UARTx->msgUART);
	//---使能UART1的时钟信号
	UART_Clock(UARTx->msgUART, PERIPHERAL_CLOCK_ENABLE);
	//---UART的接口结构体
	LL_USART_InitTypeDef USART_InitStruct = { 0 };
	//---波特率
	USART_InitStruct.BaudRate = 115200;
	//---数据位
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	//---停止位
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	//---校验位
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	//---配置为收发模式
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	//---硬件流控制---默认为无
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	//---过采样配置
	#ifdef UART_CR1_OVER8
	//---过采样次数---默认配置为16
	UART_InitStruct.OverSampling = LL_UART_OVERSAMPLING_16;
	#endif
	//---初始化串口
	LL_USART_Init(UARTx->msgUART, &USART_InitStruct);
	//---串口异步模式配置
	LL_USART_ConfigAsyncMode(UARTx->msgUART);
	//---校验是否接收需要超时函数
	(UARTx->msgRxdHandler.msgTimeTick != NULL)?(UARTx->msgRxdHandler.msgMaxTime = 100):(UARTx->msgRxdHandler.msgMaxTime = 0);
	//---校验是否发送需要超时函数
	(UARTx->msgTxdHandler.msgTimeTick != NULL)?(UARTx->msgTxdHandler.msgMaxTime = 100):(UARTx->msgTxdHandler.msgMaxTime = 0);
	//---配置CRC的等级
	UARTx->msgTxdHandler.msgCRCFlag = UART_CRC_NONE;
	//---配置报头和报尾
	UARTx->msgRxdID = 0x55;
	UARTx->msgTxdID = 0x5A;
	//---命令和地址配置
	UART_ParamInit(UARTx, UART1_DEVICE_ID, UART1_ID_INDEX, UART1_CMD_INDEX, UART1_DATA1_INDEX, UART1_DATA2_INDEX);
	//---定义485为接收模式--推完输出模式，配置为接收模式
	UART_485GPIOInit(UARTx, UART_485_RX_ENABLE);
	//---设置TX端口为输入模式
	UART_TXGPIOInit(UARTx, UART_TXGPIO_SET_INPUT);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：接收DMA初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART1_Read_DMA_Init(UART_HandlerType* UARTx)
{
	//>>>---RX的DMA配置
	//---将DMA全部寄存器重新设置为缺省值
	#ifdef USE_MCU_STM32F1
	//---F1对应是的DMA1的通道1对应ADC1
	LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_1);
	//---DMA时钟总线配置
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	#else
	LL_DMA_DeInit(DMA2, LL_DMA_STREAM_2);
	//---DMA时钟总线配置
	//LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
	DMATask_Clock(DMA2, PERIPHERAL_CLOCK_ENABLE);
	UARTx->msgRxdHandler.msgDMA = DMA2;
	UARTx->msgRxdHandler.msgDMAChannelOrStream = LL_DMA_STREAM_2;
	#endif
	//---DMA初始化结构体
	LL_DMA_InitTypeDef DMA_InitTypeDef = { 0 };
	#ifndef USE_MCU_STM32F1
	//---DMA通道
	DMA_InitTypeDef.Channel = LL_DMA_CHANNEL_4;
	#endif
	//---数据大小
	DMA_InitTypeDef.NbData = UARTx->msgRxdHandler.msgMaxSize;
	//---方向从外设到存储器
	DMA_InitTypeDef.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
	#ifndef USE_MCU_STM32F1
	//---不用FIFO用直连模式
	DMA_InitTypeDef.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
	//---半字两字节
	DMA_InitTypeDef.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
	#endif
	//---存储器地址
	DMA_InitTypeDef.MemoryOrM2MDstAddress = (UINT32_T)(UARTx->msgRxdHandler.pMsgVal);
	//---半字两字节
	DMA_InitTypeDef.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
	//---存储器地址增加
	DMA_InitTypeDef.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
	//---DMA正常模式
	DMA_InitTypeDef.Mode = LL_DMA_MODE_NORMAL; //LL_DMA_MODE_CIRCULAR;
	//---DMA外设地址
	DMA_InitTypeDef.PeriphOrM2MSrcAddress = (UINT32_T) & (UARTx->msgUART->DR);
	#ifndef USE_MCU_STM32F1
	//---无FIFO
	DMA_InitTypeDef.PeriphBurst = LL_DMA_PBURST_SINGLE;
	#endif
	//---半字两字节
	DMA_InitTypeDef.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
	//---外设基地址不变
	DMA_InitTypeDef.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
	//---传输通道优先级为高
	DMA_InitTypeDef.Priority = LL_DMA_PRIORITY_HIGH;
	//---DMA初始化
	#ifdef USE_MCU_STM32F1
	//---初始化DMA
	LL_DMA_Init(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---使能DMA
	LL_DMA_EnableChannel(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream);
	#else
	//---初始化DMA
	LL_DMA_Init(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---使能DMA
	LL_DMA_EnableStream(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
	//---是能串口接收DMA
	LL_USART_EnableDMAReq_RX(UARTx->msgUART);
	#endif
	//---中断配置
	#ifdef USE_MCU_STM32F1
	//---DMA中断配置
	NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---使能中断
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
	#else
	//---DMA中断配置
	NVIC_SetPriority(DMA2_Stream2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---使能中断
	NVIC_EnableIRQ(DMA2_Stream2_IRQn);
	#endif
	//---使能DMA传输结束中断
	LL_DMA_EnableIT_TC(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
	//<<<---RX的DMA配置结束
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送DMA的初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART1_Write_DMA_Init(UART_HandlerType* UARTx)
{
	//>>>---TX的DMA配置
	//---将DMA全部寄存器重新设置为缺省值
	#ifdef USE_MCU_STM32F1
	//---F1对应是的DMA1的通道1对应ADC1
	LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_1);
	//---DMA时钟总线配置
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	#else
	LL_DMA_DeInit(DMA2, LL_DMA_STREAM_7);
	//---DMA时钟总线配置
	//LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
	DMATask_Clock(DMA2, PERIPHERAL_CLOCK_ENABLE);
	UARTx->msgTxdHandler.msgDMA = DMA2;
	UARTx->msgTxdHandler.msgDMAChannelOrStream = LL_DMA_STREAM_7;
	#endif
	//---DMA初始化结构体
	LL_DMA_InitTypeDef DMA_InitTypeDef = { 0 };
	#ifndef USE_MCU_STM32F1
	//---DMA通道
	DMA_InitTypeDef.Channel = LL_DMA_CHANNEL_4;
	#endif
	//---数据大小,如果是首次发送，这里的参数只能写0，否则容易发生数据不完整，可能只发送了接个字节就停止发送
	DMA_InitTypeDef.NbData = 0;//UARTx->msgTxdHandler.msgSize;
	//---方向从存储器到外设
	DMA_InitTypeDef.Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
	#ifndef USE_MCU_STM32F1
	//---不用FIFO用直连模式
	DMA_InitTypeDef.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
	//---半字两字节
	DMA_InitTypeDef.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
	#endif
	//---存储器地址
	DMA_InitTypeDef.MemoryOrM2MDstAddress = (UINT32_T)(UARTx->msgTxdHandler.pMsgVal);
	//---半字两字节
	DMA_InitTypeDef.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
	//---存储器地址增加
	DMA_InitTypeDef.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
	//---DMA正常模式
	DMA_InitTypeDef.Mode = LL_DMA_MODE_NORMAL; //LL_DMA_MODE_CIRCULAR;
	//---DMA外设地址
	DMA_InitTypeDef.PeriphOrM2MSrcAddress = (UINT32_T) & (UARTx->msgUART->DR);
	#ifndef USE_MCU_STM32F1
	//---无FIFO
	DMA_InitTypeDef.PeriphBurst = LL_DMA_PBURST_SINGLE;
	#endif
	//---半字两字节
	DMA_InitTypeDef.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
	//---外设基地址不变
	DMA_InitTypeDef.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
	//---传输通道优先级为高
	DMA_InitTypeDef.Priority = LL_DMA_PRIORITY_HIGH;
	//---DMA初始化
	#ifdef USE_MCU_STM32F1
	//---初始化DMA
	LL_DMA_Init(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---使能DMA
	LL_DMA_EnableChannel(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream);
	#else
	//---初始化DMA
	LL_DMA_Init(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---使能DMA,注意发送状态下不能使能DMA，只有需要的时候才能打开
	//LL_DMA_EnableStream(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream);
	//---使能串口发送DMA
	LL_USART_EnableDMAReq_TX(UARTx->msgUART);
	#endif
	//---中断配置
	#ifdef USE_MCU_STM32F1
	//---DMA中断配置
	NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---使能中断
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
	#else
	//---DMA中断配置
	NVIC_SetPriority(DMA2_Stream7_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---使能中断
	NVIC_EnableIRQ(DMA2_Stream7_IRQn);
	#endif
	//---使能DMA传输结束中断
	LL_DMA_EnableIT_TC(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream);
	//<<<---TX的DMA配置结束
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART1_Init(UART_HandlerType* UARTx)
{
	UART1_ConfigInit(UARTx);
	//---校验接收是不是DMA传输
	if (UARTx->msgRxdHandler.msgDMAMode == 0)
	{
		//---使能接收中断
		LL_USART_EnableIT_RXNE(USART1);
	}
	else
	{
		//---使能接收空闲中断
		LL_USART_EnableIT_IDLE(USART1);
		//---初始化DMA设置
		UART1_Read_DMA_Init(UARTx);
	}
	//---校验发送是不是DMA传输方式
	if (UARTx->msgTxdHandler.msgDMAMode != 0)
	{
		UART1_Write_DMA_Init(UARTx);
	}
	//---UART1_IRQ中断配置---中断等级配置
	NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---使能中断
	NVIC_EnableIRQ(USART1_IRQn);
	//---使能串口
	LL_USART_Enable(USART1);
	//---打印初始化信息
	//UART_Printf(UARTx, "=>>串口1的初始化<<=\r\n");
	UART_Printf(UARTx, "=>>Init SP1<<=\r\n");
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART2_ConfigInit(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART2_Read_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART2_Write_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART2_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART3_ConfigInit(UART_HandlerType* UARTx)
{
	//---UART3 GPIO Configuration
	//---PB10  ------> UART1_TX---端口复用为7
	//---PB11  ------> UART1_RX---端口复用为7
	//---使能端口时钟
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(GPIOB, PERIPHERAL_CLOCK_ENABLE);
	#endif
	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---模式配置
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	//---工作速度
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	//---复用功能的推完输出
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	//---输入上拉使能
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
#ifdef USE_MCU_STM32F1
	//---TX
	GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	//---RX
	GPIO_InitStruct.Pin = LL_GPIO_PIN_11;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#else
	//---端口号
	GPIO_InitStruct.Pin = LL_GPIO_PIN_10 | LL_GPIO_PIN_11;
	//---复用功能为UART3
	GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#endif
	//---配置消息结构体中的信息
	UARTx->msgTxPort.msgPort = GPIOB;
	UARTx->msgTxPort.msgBit = LL_GPIO_PIN_10;
	UARTx->msgUART = USART3;
	//---串口序号
	UARTx->msgIndex = 3 + 1;
	//---注销串口的初始化
	LL_USART_DeInit(UARTx->msgUART);
	//---使能UART1的时钟信号
	UART_Clock(UARTx->msgUART, PERIPHERAL_CLOCK_ENABLE);
	//---UART的接口结构体
	LL_USART_InitTypeDef USART_InitStruct = { 0 };
	//---波特率
	USART_InitStruct.BaudRate = 115200;
	//---数据位
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	//---停止位
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	//---校验位
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	//---配置为收发模式
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	//---硬件流控制---默认为无
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	//---过采样配置
	#ifdef UART_CR1_OVER8
		//---过采样次数---默认配置为16
	UART_InitStruct.OverSampling = LL_UART_OVERSAMPLING_16;
	#endif
	//---初始化串口
	LL_USART_Init(UARTx->msgUART, &USART_InitStruct);
	//---串口异步模式配置
	LL_USART_ConfigAsyncMode(UARTx->msgUART);
	//---校验是否接收需要超时函数
	(UARTx->msgRxdHandler.msgTimeTick != NULL) ? (UARTx->msgRxdHandler.msgMaxTime = 10) : (UARTx->msgRxdHandler.msgMaxTime = 0);
	//---校验是否发送需要超时函数
	(UARTx->msgTxdHandler.msgTimeTick != NULL) ? (UARTx->msgTxdHandler.msgMaxTime = 100) : (UARTx->msgTxdHandler.msgMaxTime = 0);
	//---配置CRC的等级
	UARTx->msgTxdHandler.msgCRCFlag = UART_CRC_NONE;
	//---配置报头和报尾
	UARTx->msgRxdID = 0x55;
	UARTx->msgTxdID = 0x5A;
	//---命令和地址配置
	//UART_ParamInit(UARTx, UART1_DEVICE_ID, UART1_ID_INDEX, UART1_CMD_INDEX, UART1_DATA1_INDEX, UART1_DATA2_INDEX);
	//---定义485为接收模式--推完输出模式，配置为接收模式
	UART_485GPIOInit(UARTx, UART_485_RX_ENABLE);
	//---设置TX端口为输入模式
	UART_TXGPIOInit(UARTx, UART_TXGPIO_SET_INPUT);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART3_Read_DMA_Init(UART_HandlerType* UARTx)
{
	//>>>---RX的DMA配置
	//---将DMA全部寄存器重新设置为缺省值
	#ifdef USE_MCU_STM32F1
	//---F1对应是的DMA1的通道1对应ADC1
	LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_1);
	//---DMA时钟总线配置
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	#else
	LL_DMA_DeInit(DMA1, LL_DMA_STREAM_1);
	//---DMA时钟总线配置
	//LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	DMATask_Clock(DMA1, PERIPHERAL_CLOCK_ENABLE);
	UARTx->msgRxdHandler.msgDMA = DMA1;
	UARTx->msgRxdHandler.msgDMAChannelOrStream = LL_DMA_STREAM_1;
	#endif
	//---DMA初始化结构体
	LL_DMA_InitTypeDef DMA_InitTypeDef = { 0 };
	#ifndef USE_MCU_STM32F1
	//---DMA通道
	DMA_InitTypeDef.Channel = LL_DMA_CHANNEL_4;
	#endif
	//---数据大小
	DMA_InitTypeDef.NbData = UARTx->msgRxdHandler.msgMaxSize;
	//---方向从外设到存储器
	DMA_InitTypeDef.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
	#ifndef USE_MCU_STM32F1
	//---不用FIFO用直连模式
	DMA_InitTypeDef.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
	//---半字两字节
	DMA_InitTypeDef.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
	#endif
	//---存储器地址
	DMA_InitTypeDef.MemoryOrM2MDstAddress = (UINT32_T)(UARTx->msgRxdHandler.pMsgVal);
	//---半字两字节
	DMA_InitTypeDef.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
	//---存储器地址增加
	DMA_InitTypeDef.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
	//---DMA正常模式
	DMA_InitTypeDef.Mode = LL_DMA_MODE_NORMAL; //LL_DMA_MODE_CIRCULAR;
	//---DMA外设地址
	DMA_InitTypeDef.PeriphOrM2MSrcAddress = (UINT32_T) & (UARTx->msgUART->DR);
	#ifndef USE_MCU_STM32F1
	//---无FIFO
	DMA_InitTypeDef.PeriphBurst = LL_DMA_PBURST_SINGLE;
	#endif
	//---半字两字节
	DMA_InitTypeDef.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
	//---外设基地址不变
	DMA_InitTypeDef.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
	//---传输通道优先级为高
	DMA_InitTypeDef.Priority = LL_DMA_PRIORITY_HIGH;
	//---DMA初始化
	#ifdef USE_MCU_STM32F1
	//---初始化DMA
	LL_DMA_Init(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---使能DMA
	LL_DMA_EnableChannel(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream);
	#else
	//---初始化DMA
	LL_DMA_Init(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---使能DMA
	LL_DMA_EnableStream(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
	//---是能串口接收DMA
	LL_USART_EnableDMAReq_RX(UARTx->msgUART);
	#endif
	//---中断配置
	#ifdef USE_MCU_STM32F1
	//---DMA中断配置
	NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---使能中断
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
	#else
	//---DMA中断配置
	NVIC_SetPriority(DMA1_Stream1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---使能中断
	NVIC_EnableIRQ(DMA1_Stream1_IRQn);
	#endif
	//---使能DMA传输结束中断
	LL_DMA_EnableIT_TC(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
	//<<<---RX的DMA配置结束
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART3_Write_DMA_Init(UART_HandlerType* UARTx)
{
	//>>>---TX的DMA配置
	//---将DMA全部寄存器重新设置为缺省值
	#ifdef USE_MCU_STM32F1
	//---F1对应是的DMA1的通道1对应ADC1
	LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_1);
	//---DMA时钟总线配置
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	#else
	LL_DMA_DeInit(DMA1, LL_DMA_STREAM_3);
	//---DMA时钟总线配置
	//LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	DMATask_Clock(DMA1, PERIPHERAL_CLOCK_ENABLE);
	UARTx->msgTxdHandler.msgDMA = DMA1;
	UARTx->msgTxdHandler.msgDMAChannelOrStream = LL_DMA_STREAM_3;
	#endif
	//---DMA初始化结构体
	LL_DMA_InitTypeDef DMA_InitTypeDef = { 0 };
	#ifndef USE_MCU_STM32F1
	//---DMA通道
	DMA_InitTypeDef.Channel = LL_DMA_CHANNEL_4;
	#endif
	//---数据大小,如果是首次发送，这里的参数只能写0，否则容易发生数据不完整，可能只发送了接个字节就停止发送
	DMA_InitTypeDef.NbData = 0;//UARTx->msgTxdHandler.msgSize;
	//---方向从存储器到外设
	DMA_InitTypeDef.Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
	#ifndef USE_MCU_STM32F1
	//---不用FIFO用直连模式
	DMA_InitTypeDef.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
	//---半字两字节
	DMA_InitTypeDef.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
	#endif
	//---存储器地址
	DMA_InitTypeDef.MemoryOrM2MDstAddress = (UINT32_T)(UARTx->msgTxdHandler.pMsgVal);
	//---半字两字节
	DMA_InitTypeDef.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
	//---存储器地址增加
	DMA_InitTypeDef.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
	//---DMA正常模式
	DMA_InitTypeDef.Mode = LL_DMA_MODE_NORMAL; //LL_DMA_MODE_CIRCULAR;
	//---DMA外设地址
	DMA_InitTypeDef.PeriphOrM2MSrcAddress = (UINT32_T) & (UARTx->msgUART->DR);
	#ifndef USE_MCU_STM32F1
	//---无FIFO
	DMA_InitTypeDef.PeriphBurst = LL_DMA_PBURST_SINGLE;
	#endif
	//---半字两字节
	DMA_InitTypeDef.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
	//---外设基地址不变
	DMA_InitTypeDef.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
	//---传输通道优先级为高
	DMA_InitTypeDef.Priority = LL_DMA_PRIORITY_HIGH;
	//---DMA初始化
	#ifdef USE_MCU_STM32F1
	//---初始化DMA
	LL_DMA_Init(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---使能DMA
	LL_DMA_EnableChannel(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream);
	#else
	//---初始化DMA
	LL_DMA_Init(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---使能DMA,注意发送状态下不能使能DMA，只有需要的时候才能打开
	//LL_DMA_EnableStream(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream);
	//---使能串口发送DMA
	LL_USART_EnableDMAReq_TX(UARTx->msgUART);
	#endif
	//---中断配置
	#ifdef USE_MCU_STM32F1
	//---DMA中断配置
	NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---使能中断
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
	#else
	//---DMA中断配置
	NVIC_SetPriority(DMA1_Stream3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---使能中断
	NVIC_EnableIRQ(DMA1_Stream3_IRQn);
	#endif
	//---使能DMA传输结束中断
	LL_DMA_EnableIT_TC(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream);
	//<<<---TX的DMA配置结束
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART3_Init(UART_HandlerType* UARTx)
{
	UART3_ConfigInit(UARTx);
	//---校验接收是不是DMA传输
	if (UARTx->msgRxdHandler.msgDMAMode == 0)
	{
		//---使能接收中断
		LL_USART_EnableIT_RXNE(UARTx->msgUART);
	}
	else
	{
		//---使能接收空闲中断
		LL_USART_EnableIT_IDLE(UARTx->msgUART);
		//---初始化DMA设置
		UART3_Read_DMA_Init(UARTx);
	}
	//---校验发送是不是DMA传输方式
	if (UARTx->msgTxdHandler.msgDMAMode != 0)
	{
		UART3_Write_DMA_Init(UARTx);
	}
	//---UART1_IRQ中断配置---中断等级配置
	NVIC_SetPriority(USART3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---使能中断
	NVIC_EnableIRQ(USART3_IRQn);
	//---使能串口
	LL_USART_Enable(UARTx->msgUART);
	//---打印初始化信息
	//UART_Printf(UARTx, "=>>串口1的初始化<<=\r\n");
	UART_Printf(UARTx, "=>>Init SP3<<=\r\n");
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART4_ConfigInit(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART4_Read_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART4_Write_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART4_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART5_ConfigInit(UART_HandlerType* UARTx)
{
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART5_Read_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART5_Write_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART5_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART6_ConfigInit(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART6_Read_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART6_Write_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART6_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART7_ConfigInit(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART7_Read_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART7_Write_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART7_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART8_ConfigInit(UART_HandlerType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART8_Read_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART8_Write_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART8_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART9_ConfigInit(UART_HandlerType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART9_Read_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART9_Write_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}



///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART9_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART10_ConfigInit(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART10_Read_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART10_Write_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART10_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_Init(UART_HandlerType*  UARTx, UINT16_T rxSize, UINT8_T* pRxVal, UINT8_T rxCRCFlag, UINT16_T txSize, UINT8_T* pTxVal, UINT8_T txCRCFlag, UINT32_T(*pTimerTick)(void))
{
	UART_StructInit(UARTx);
	UARTx->msgRxdHandler.msgCRCFlag = rxCRCFlag;
	UARTx->msgRxdHandler.msgMaxSize = rxSize;
	UARTx->msgRxdHandler.pMsgVal = pRxVal;
	UARTx->msgTxdHandler.msgCRCFlag = txCRCFlag;
	UARTx->msgTxdHandler.msgMaxSize = txSize;
	UARTx->msgTxdHandler.pMsgVal = pTxVal;
	//---注册计数函数
	UARTx->msgTxdHandler.msgTimeTick = pTimerTick;
	UARTx->msgRxdHandler.msgTimeTick = pTimerTick;
	//---端口初始化
	if ((UARTx != NULL) && (UARTx == UART_TASK_ONE))
	{
		UART1_Init(UARTx);
	}
	else if ((UARTx != NULL) && (UARTx == UART_TASK_TWO))
	{
		UART2_Init(UARTx);
	}
	else if ((UARTx != NULL) && (UARTx == UART_TASK_THREE))
	{
		UART3_Init(UARTx);
	}
	else if ((UARTx != NULL) && (UARTx == UART_TASK_FOUR))
	{
		UART4_Init(UARTx);
	}
	else if ((UARTx != NULL) && (UARTx == UART_TASK_FIVE))
	{
		UART5_Init(UARTx);
	}
	else if ((UARTx != NULL) && (UARTx == UART_TASK_SIX))
	{
		UART6_Init(UARTx);
	}
	if ((UARTx != NULL) && (UARTx == UART_TASK_SEVEN))
	{
		UART7_Init(UARTx);
	}
	else if ((UARTx != NULL) && (UARTx == UART_TASK_EIGHT))
	{
		UART8_Init(UARTx);
	}
	else if ((UARTx != NULL) && (UARTx == UART_TASK_NINE))
	{
		UART9_Init(UARTx);
	}
	else if ((UARTx != NULL) && (UARTx == UART_TASK_TEN))
	{
		UART10_Init(UARTx);
	}
	else
	{
		return ERROR_2;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：串口的发送端口的初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_TXGPIOInit(UART_HandlerType*  UARTx, UINT8_T isInput)
{
#ifdef UART_INIT_GPIO
	if (UARTx->msgTxPort.msgPort != NULL)
	{
		(isInput == UART_TXGPIO_SET_OUTPUT) ? (LL_GPIO_SetPinMode(UARTx->msgTxPort.msgPort, UARTx->msgTxPort.msgBit, LL_GPIO_MODE_ALTERNATE)) : (LL_GPIO_SetPinMode(UARTx->msgTxPort.msgPort, UARTx->msgTxPort.msgBit, LL_GPIO_MODE_INPUT));
	}
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：485方向控制端口的初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_485GPIOInit(UART_HandlerType*  UARTx, UINT8_T isEnable)
{
	if (UARTx->msg485Port.msgPort != NULL)
	{
		(isEnable == UART_485_TX_ENABLE) ? (GPIO_OUT_0(UARTx->msg485Port.msgPort, UARTx->msg485Port.msgBit)) : (GPIO_OUT_1(UARTx->msg485Port.msgPort, UARTx->msg485Port.msgBit));
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置CRC校验模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_SetCRC(UART_HandlerDef* UARTDefx, UINT8_T crcFlag)
{
	UARTDefx->msgCRCFlag = crcFlag;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：获取CRC校验模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_GetCRC(UART_HandlerDef* UARTDefx)
{
	return UARTDefx->msgCRCFlag;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_TimeTick_Init(UART_HandlerDef* UARTDefx)
{
	//---时间节点
	UARTDefx->msgRecordTick = ((UARTDefx->msgTimeTick != NULL)?(UARTDefx->msgTimeTick()):0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：注销超时计数器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_TimeTick_DeInit(UART_HandlerDef* UARTDefx)
{
	//---清零溢出标志位
	UARTDefx->msgOverFlow = 0;
	//---清零当前时钟
	UARTDefx->msgRecordTick = 0;
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 时间计数是否发生超时
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_TimeTick_OverFlow(UART_HandlerDef* UARTDefx)
{
	UINT32_T temp = 0;
	//---获取当前时间
	temp = ((UARTDefx->msgTimeTick != NULL) ? (UARTDefx->msgTimeTick()+2) : 0);
	//---判断是否发生超时错误
	if (temp > UARTDefx->msgRecordTick)
	{
		//---计时器未发生溢出操作
		if ((temp - UARTDefx->msgRecordTick) > UARTDefx->msgMaxTime)
		{
			UARTDefx->msgOverFlow = 1;
			return ERROR_1;
		}
	}
	else 
	{
		//---计时器发生溢出操作
		if ((0xFFFFFFFF - UARTDefx->msgRecordTick + temp) > UARTDefx->msgMaxTime)
		{
			UARTDefx->msgOverFlow = 1;
			return ERROR_1;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_TimeTask_OverFlow(UART_HandlerType*UARTx, UINT8_T isRx)
{
	UINT8_T _return = OK_0;
	//---判断是接收还是发送并校验是不是DMA接收模式
	if ((isRx != 0) && (UARTx->msgRxdHandler.msgDMAMode == 0))
	{
		if ((UARTx->msgRxdHandler.msgRecordTick != 0) && (UARTx->msgRxdHandler.msgMaxTime != 0))
		{
			if (UARTx->msgRxdHandler.msgRecordTick == 0)
			{
				return OK_0;
			}
			//---获取超时值
			_return = UART_TimeTick_OverFlow(&(UARTx->msgRxdHandler));
			//---超时条件判断，发现某些状态下当前记录的时间值在改写为零的时候，时间记录点没有发生同步更新
			//if ((_return != OK_0))
			if ((_return != OK_0) && (UARTx->msgRxdHandler.msgRecordTick != 0))
			{
				//---打印超时的串口信息
				UART_Printf(UARTx, "=>>SP%d:Receive Mode Timeout Error!<<=\r\n", (UARTx->msgIndex - 1));
				//---复位接收数据缓存区
				UART_Read_Init(UARTx);
			}
		}
	}
	else if(UARTx->msgTxdHandler.msgDMAMode == 0)
	{
		if ((UARTx->msgTxdHandler.msgRecordTick != 0) && (UARTx->msgTxdHandler.msgMaxTime != 0))
		{
			if (UARTx->msgTxdHandler.msgRecordTick == 0)
			{
				return OK_0;
			}
			//---获取超时值
			_return = UART_TimeTick_OverFlow(&(UARTx->msgTxdHandler));
			//---超时条件判断，发现某些状态下当前记录的时间值在改写为零的时候，时间记录点没有发生同步更新
			if ((_return != OK_0) && (UARTx->msgTxdHandler.msgRecordTick != 0))
			{
				//---打印超时的串口信息
				UART_Printf(UARTx, "=>>SP%d:Send Mode Timeout Error!<<=\r\n", (UARTx->msgIndex - 1));
				//---复位发送数据缓存区
				UART_Write_Init(UARTx);
			}
			else
			{
				UARTx->msgTxdHandler.msgOverFlow = 0;
			}
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 接受到数据最大长度使用1字节表示
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITRead_8BitsTask(UART_HandlerType*UARTx, UINT8_T val)
{
	//---保存数到的数据
	static UINT8_T tempVal;
	tempVal = val;
	//---数据接收步序
	switch (UARTx->msgRxdHandler.msgStep)
	{
		//---接收数据的报头
		case 0:
			if (UARTx->msgRxdHandler.msgRIndex == 0)
			{
				if (UARTx->msgRxdID == tempVal)
				{
					UARTx->msgRxdHandler.pMsgVal[0] = tempVal;
					UARTx->msgRxdHandler.msgStep = 1;
					//---记录数据的个数
					UARTx->msgRxdHandler.msgCount = 1;
					//---收到第一个符合格式的数据，启动超时计数器
					UART_TimeTick_Init(&(UARTx->msgRxdHandler));
					//---清零超时标志
					UART_ClearOverFlow(&(UARTx->msgRxdHandler));
				}
			}
			break;

			//---接收数据的长度
		case 1:
			if ((tempVal > 0) && (tempVal < (UINT8_T)(UARTx->msgRxdHandler.msgMaxSize & 0xFF)))
			{
				UARTx->msgRxdHandler.pMsgVal[1] = tempVal;
				//---获取数据的接收长度
				UARTx->msgRxdHandler.msgWIndex = tempVal;
				//---记录数据的个数
				UARTx->msgRxdHandler.msgCount += 1;
				//---下一步骤
				UARTx->msgRxdHandler.msgStep = 2;
			}
			else
			{
				UARTx->msgRxdHandler.msgStep = 0;
			}
			//---复位超时计数器
			UART_TimeTick_Init(&(UARTx->msgRxdHandler));
			break;
			//---接收数据信息
		case 2:
			UARTx->msgRxdHandler.pMsgVal[UARTx->msgRxdHandler.msgRIndex + 2] = tempVal;
			UARTx->msgRxdHandler.msgRIndex++;
			//---记录数据的个数
			UARTx->msgRxdHandler.msgCount += 1;
			//---判断是否溢出
			if (UARTx->msgRxdHandler.msgRIndex >= UARTx->msgRxdHandler.msgMaxSize)
			{
				UARTx->msgRxdHandler.msgRIndex = 0;
			}
			//---复位超时计数器
			UART_TimeTick_Init(&(UARTx->msgRxdHandler));
			//---判断是否接收完成
			if (UARTx->msgRxdHandler.msgRIndex >= UARTx->msgRxdHandler.msgWIndex)
			{
				UARTx->msgRxdHandler.msgStep = 3;
				UARTx->msgRxdHandler.msgState = UART_OK;
				//---清零超时计数器
				//UART_TimeTick_DeInit(UARTx, 1);
				//---记录接收完成的时间
				UARTx->msgRxdHandler.msgRecordTime = ((UARTx->msgRxdHandler.msgTimeTick != NULL) ? (UARTx->msgRxdHandler.msgTimeTick()) : 0);
			}
			break;
		case 3:
			//---清零超时计数器
			//UART_TimeTick_DeInit(UARTx,1);
			break;
		default:
			//UARTx->msgRxHandler.msgNowTime = 0;
			break;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 接受到数据最大长度使用2字节表示
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITRead_16BitsTask(UART_HandlerType*UARTx, UINT8_T val)
{
	//---保存数到的数据
	static UINT8_T tempVal;
	tempVal = val;
	//---数据接收步序
	switch (UARTx->msgRxdHandler.msgStep)
	{
		//---接收数据的报头
		case 0:
			if (UARTx->msgRxdHandler.msgRIndex == 0)
			{
				if (UARTx->msgRxdID == tempVal)
				{
					UARTx->msgRxdHandler.pMsgVal[0] = tempVal;
					UARTx->msgRxdHandler.msgStep = 1;
					//---记录数据的个数
					UARTx->msgRxdHandler.msgCount = 1;
					//---收到第一个符合格式的数据，启动超时计数器
					UART_TimeTick_Init(&(UARTx->msgRxdHandler));
					//---清零超时标志
					UART_ClearOverFlow(&(UARTx->msgRxdHandler));
				}
			}
			break;

			//---接收数据的长度高位
		case 1:
			UARTx->msgRxdHandler.pMsgVal[1] = tempVal;
			UARTx->msgRxdHandler.msgWIndex = tempVal;
			UARTx->msgRxdHandler.msgWIndex <<= 8;
			UARTx->msgRxdHandler.msgStep = 2;
			//---记录数据的个数
			UARTx->msgRxdHandler.msgCount += 1;
			//---复位超时计数器
			UART_TimeTick_Init(&(UARTx->msgRxdHandler));
			break;
			//---接收数据的长度低位
		case 2:
			UARTx->msgRxdHandler.pMsgVal[2] = tempVal;
			UARTx->msgRxdHandler.msgWIndex += tempVal;
			//---记录数据的个数
			UARTx->msgRxdHandler.msgCount += 1;
			//---判断数据是否合法
			if ((UARTx->msgRxdHandler.msgWIndex > 0) && (UARTx->msgRxdHandler.msgWIndex < UARTx->msgRxdHandler.msgMaxSize))
			{
				//---记录数据的个数
				UARTx->msgRxdHandler.msgCount = UARTx->msgRxdHandler.msgWIndex;
				//---下一步骤
				UARTx->msgRxdHandler.msgStep = 3;
			}
			else
			{
				UARTx->msgRxdHandler.msgStep = 0;
			}
			//---复位超时计数器
			UART_TimeTick_Init(&(UARTx->msgRxdHandler));
			break;
			//---接收数据信息
		case 3:
			UARTx->msgRxdHandler.pMsgVal[UARTx->msgRxdHandler.msgRIndex + 3] = tempVal;
			UARTx->msgRxdHandler.msgRIndex++;
			//---记录数据的个数
			UARTx->msgRxdHandler.msgCount += 1;
			//---判断是否溢出
			if (UARTx->msgRxdHandler.msgRIndex >= UARTx->msgRxdHandler.msgMaxSize)
			{
				UARTx->msgRxdHandler.msgRIndex = 0;
			}
			//---复位超时计数器
			UART_TimeTick_Init(&(UARTx->msgRxdHandler));
			//---判断是否接收完成
			if (UARTx->msgRxdHandler.msgRIndex >= UARTx->msgRxdHandler.msgWIndex)
			{
				UARTx->msgRxdHandler.msgStep = 4;
				UARTx->msgRxdHandler.msgState = UART_OK;
				//---清零超时计数器
				//UART_TimeTick_DeInit(UARTx, 1);
				//---记录接收完成的时间
				UARTx->msgRxdHandler.msgRecordTime = ((UARTx->msgRxdHandler.msgTimeTick != NULL) ? (UARTx->msgRxdHandler.msgTimeTick()) : 0);
			}
			break;
		case 4:
			//---清零超时计数器
			//UART_TimeTick_DeInit(UARTx,1);
			break;
		default:
			//UARTx->msgRxHandler.msgNowTime = 0;
			break;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITRead_Task(UART_HandlerType*UARTx, UINT8_T val)
{
	if (UARTx->msgRxdHandler.msgMaxSize < 0xFF)
	{
		return UART_ITRead_8BitsTask(UARTx, val);
	}
	else
	{
		return UART_ITRead_16BitsTask(UARTx, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_PollMode_WriteByte(UART_HandlerType*UARTx, UINT8_T  val)
{
	//---发送数据
	LL_USART_TransmitData8(UARTx->msgUART, val);
	//---等待发送完成
	while (LL_USART_IsActiveFlag_TC(UARTx->msgUART) == RESET)
	{
		WDT_RESET();
	}
	//---清除发送完成标志位
	LL_USART_ClearFlag_TC(UARTx->msgUART);
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 发送字符串
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_PollMode_WriteData(UART_HandlerType*UARTx, char *pVal)
{
	//---设置485为发送模式
	UART_485GPIOInit(UARTx, UART_485_TX_ENABLE);
	//---切换发送端口为输出模式
	UART_TXGPIOInit(UARTx, UART_TXGPIO_SET_OUTPUT);
	//---关闭中断
	//CLI();
	while (*pVal != '\0')
	{
		UART_PollMode_WriteByte(UARTx, (UINT8_T)*pVal);
		pVal++;
	}
	//---使能中断
	//SEI();
	//---设置485为接收模式
	UART_485GPIOInit(UARTx, UART_485_RX_ENABLE);
	//---切换发送端口为输入模式
	UART_TXGPIOInit(UARTx, UART_TXGPIO_SET_INPUT);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_PollMode_ReadByte(UART_HandlerType*UARTx)
{
	//---等待接收完成
	while (LL_USART_IsActiveFlag_RXNE(UARTx->msgUART) != RESET)
	{
		WDT_RESET();
	}
	return LL_USART_ReceiveData8(UARTx->msgUART);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_PollMode_ReadData(UART_HandlerType*UARTx, char *pVal)
{
	while (*pVal != '\0')
	{
		*pVal = UART_PollMode_ReadByte(UARTx);
		pVal++;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITWrite_TXETask(UART_HandlerType*UARTx)
{
	VLTUINT8_T tempFlag=OK_0;
	if (UARTx->msgTxdHandler.msgWIndex != 0)
	{
		if (UARTx->msgTxdHandler.msgRIndex != UARTx->msgTxdHandler.msgWIndex)
		{
			//---发送8Bit的数据
			LL_USART_TransmitData8(UARTx->msgUART, UARTx->msgTxdHandler.pMsgVal[UARTx->msgTxdHandler.msgRIndex]);
			//---数据缓存区序号增加
			UARTx->msgTxdHandler.msgRIndex++;
			//---校验缓存区是否溢出
			if (UARTx->msgTxdHandler.msgRIndex >= UARTx->msgTxdHandler.msgMaxSize)
			{
				UARTx->msgTxdHandler.msgRIndex = 0;
			}
			//---校验数据是否都填入缓存区
			if ((UARTx->msgTxdHandler.msgRIndex >= UARTx->msgTxdHandler.msgWIndex) && (UARTx->msgTxdHandler.msgCount > 0) && (UARTx->msgTxdHandler.msgRIndex >= UARTx->msgTxdHandler.msgCount))
			{
				//---发送完成,发送数据寄存器空中断不使能
				LL_USART_DisableIT_TXE(UARTx->msgUART);
				//---使能发送完成中断，用于切换TXD端口为输入状态
				LL_USART_EnableIT_TC(UARTx->msgUART);
			}
		}
		else
		{
			tempFlag = ERROR_1;
		}
	}
	else
	{
		tempFlag = ERROR_2;
	}
	//---校验结果
	if (tempFlag)
	{
		//---发送完成,发送数据寄存器空中断不使能---检查是否存在异常；关闭发送数据寄存器空中断
		LL_USART_DisableIT_TXE(UARTx->msgUART);
		//---清空数据发送缓存区
		UART_Write_Init(UARTx);
	}
	//---复位超时计数器
	UART_TimeTick_Init(&(UARTx->msgTxdHandler));
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITWrite_TCTask(UART_HandlerType*UARTx)
{
	//---定义了485，由于485响应的延迟问题,增加发送换行符，用于缓冲485的响应
	if ((UARTx->msg485Port.msgPort != NULL) && (UARTx->msgTxdHandler.msgStep == 0))
	{
		//---发送8Bit的数据
		LL_USART_TransmitData8(UARTx->msgUART, 0x0D);
		UARTx->msgTxdHandler.msgStep = 1;
	}
	else if ((UARTx->msg485Port.msgPort != NULL) && (UARTx->msgTxdHandler.msgStep == 1))
	{
		//---发送8Bit的数据
		LL_USART_TransmitData8(UARTx->msgUART, 0x0A);
		UARTx->msgTxdHandler.msgStep = 2;
	}
	else
	{
		//---清零发送步序
		UARTx->msgTxdHandler.msgStep = 0;
		//---发送完成,发送数据发送完成中断不使能
		LL_USART_DisableIT_TC(UARTx->msgUART);
		//---清空数据发送缓存区
		UART_Write_Init(UARTx);
		//---清零超时计数器
		//UART_TimeTick_DeInit(UARTx, 0);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_RealTime_AddByte(UART_HandlerType*UARTx, UINT8_T val)
{
	if (UARTx->msgTxdHandler.pMsgVal != NULL)
	{
		if (UARTx->msgTxdHandler.msgWIndex >= UARTx->msgTxdHandler.msgMaxSize)
		{
			UARTx->msgTxdHandler.msgWIndex = 0;
		}
		UARTx->msgTxdHandler.pMsgVal[UARTx->msgTxdHandler.msgWIndex] = val;
		UARTx->msgTxdHandler.msgWIndex++;
		//---判断发送寄存器空中断是否使能
		if (LL_USART_IsEnabledIT_TXE(UARTx->msgUART) == 0)
		{
			//---设置485为发送模式
			UART_485GPIOInit(UARTx, UART_485_TX_ENABLE);
			//---切换发送端口为输出模式
			UART_TXGPIOInit(UARTx, UART_TXGPIO_SET_OUTPUT);
			//---使能发送空中断
			LL_USART_EnableIT_TXE(UARTx->msgUART);
		}
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送数据的大小
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_RealTime_AddSize(UART_HandlerType*UARTx, UINT16_T val)
{
	UINT8_T _return = ERROR_1;
	if (UARTx->msgTxdHandler.pMsgVal != NULL)
	{
		if ((UARTx->msgTxdHandler.msgCRCFlag == UART_CRC_CHECKSUM) || (UARTx->msgTxdHandler.msgCRCFlag == UART_CRC_CRC8))
		{
			val += 1;
		}
		else if (UARTx->msgTxdHandler.msgCRCFlag == UART_CRC_CRC16)
		{
			val += 2;
		}
		else if (UARTx->msgTxdHandler.msgCRCFlag == UART_CRC_CRC32)
		{
			val += 4;
		}
		//---判断是否有设备的ID信息
		if ((UARTx->msgCmdIndex - UARTx->msgIDIndex) != 0)
		{
			val += 1;
		}
		//---判断是否增加换行符
		if ((UARTx->msgTxdHandler.msgAddNewLine==1))
		{
			val += 2;
		}
		//---判断数据的格式
		if (UARTx->msgTxdHandler.msgMaxSize > 250)
		{
			UART_RealTime_AddByte(UARTx, (UINT8_T)(val >> 8));
			_return = UART_RealTime_AddByte(UARTx, (UINT8_T)(val & 0xFF));
			val += 3;
		}
		else
		{
			_return = UART_RealTime_AddByte(UARTx, (UINT8_T)(val & 0xFF));
			val += 2;
		}
		//---判断是否有设备的ID信息并填充ID信息
		if ((UARTx->msgCmdIndex - UARTx->msgIDIndex) != 0)
		{
			_return = UART_RealTime_AddByte(UARTx, UARTx->msgID);
		}		
		//---计算发送数据的个数
		UARTx->msgTxdHandler.msgCount = val;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：填充数据的CRC校验信息
//////输入参数:
//////输出参数:
//////说		明：使用CRC，数据的必须从0开始使用
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_RealTime_AddCRC(UART_HandlerType*UARTx)
{
	//---校验CRC是否初始化
	if ((UARTx->msgTxdHandler.msgCRCFlag != UART_CRC_NONE) && (CRCTask_Enable() == OK_0))
	{
		UINT32_T crcVal = 0;
		//---判断数据校验模式
		if (UARTx->msgTxdHandler.msgCRCFlag == UART_CRC_CHECKSUM)
		{
			crcVal = CRCTask_CheckSum(UARTx->msgTxdHandler.pMsgVal, UARTx->msgTxdHandler.msgWIndex);
			UART_RealTime_AddByte(UARTx, (UINT8_T)crcVal);
		}
		else if (UARTx->msgTxdHandler.msgCRCFlag == UART_CRC_CRC8)
		{
			crcVal = CRCTask_CRC8(USE_CRC8_07H, UARTx->msgTxdHandler.pMsgVal, UARTx->msgTxdHandler.msgWIndex);
			UART_RealTime_AddByte(UARTx, (UINT8_T)crcVal);
		}
		else if (UARTx->msgTxdHandler.msgCRCFlag == UART_CRC_CRC16)
		{
			crcVal = CRCTask_CRC16(UARTx->msgTxdHandler.pMsgVal, UARTx->msgTxdHandler.msgWIndex);
			UART_RealTime_AddByte(UARTx, (UINT8_T)(crcVal >> 8));
			UART_RealTime_AddByte(UARTx, (UINT8_T)crcVal);
		}
		else if (UARTx->msgTxdHandler.msgCRCFlag == UART_CRC_CRC32)
		{
			crcVal = CRCTask_CRC32(UARTx->msgTxdHandler.pMsgVal, UARTx->msgTxdHandler.msgWIndex);
			UART_RealTime_AddByte(UARTx, (UINT8_T)(crcVal >> 24));
			UART_RealTime_AddByte(UARTx, (UINT8_T)(crcVal >> 16));
			UART_RealTime_AddByte(UARTx, (UINT8_T)(crcVal >> 8));
			UART_RealTime_AddByte(UARTx, (UINT8_T)crcVal);
		}
		return OK_0;
	}
	//---判断是否增加换行符
	if ((UARTx->msgTxdHandler.msgAddNewLine==1))
	{
		UART_RealTime_AddByte(UARTx, 0x0D);
		UART_RealTime_AddByte(UARTx, 0x0A);
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 处理数据填充前的操作，约定好报头，和有效数据开始的位置
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_FillMode_Init(UART_HandlerType*UARTx,UINT8_T isChildCmd)
{
	//---检查发送状态，等待之前的数据发送完成;必须是空闲状态，总线上没有其他数据放
	while ((UARTx->msgTxdHandler.msgState == UART_BUSY) || (UARTx->msgTxdHandler.msgState == UART_PRINTF) || (UARTx->msgTxdHandler.msgState == UART_DMA))
	{
		WDT_RESET();
	}
	UARTx->msgTxdHandler.msgWIndex = 0;
	UARTx->msgTxdHandler.msgFlagIndex=0;
	//---填充数据报头
	UART_FillMode_AddByte( UARTx, UARTx->msgTxdID );
	//---填充数据长度
	UART_FillMode_AddByte( UARTx, 0x00 );
	if (UARTx->msgTxdHandler.msgMaxSize > 0xFF)
	{
		UART_FillMode_AddByte( UARTx, 0x00 );
		UARTx->msgTxdHandler.msgFlagIndex+=1;
	}
	//---填充多设备通信的设备ID
	if ((UARTx->msgCmdIndex - UARTx->msgIDIndex) != 0)
	{
		UART_FillMode_AddByte(UARTx, UARTx->msgID);
	}
	//---主命令/命令
	UART_FillMode_AddByte(UARTx, UARTx->msgRxdHandler.pMsgVal[UARTx->msgCmdIndex]);
	//---校验是否有子命令
	if (isChildCmd!=0)
	{
		//---子命令
		UART_FillMode_AddByte(UARTx, UARTx->msgRxdHandler.pMsgVal[UARTx->msgCmdIndex + (isChildCmd == 0 ? 0 : 1)]);
	}
	//---标识返回执行结果在缓存区中断的序号
	UARTx->msgTxdHandler.msgFlagIndex = UARTx->msgTxdHandler.msgWIndex;
	//---返回执行结果
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：数据填充后在发送
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_FillMode_AddByte(UART_HandlerType*UARTx, UINT8_T val)
{
	UARTx->msgTxdHandler.pMsgVal[UARTx->msgTxdHandler.msgWIndex] = val;
	UARTx->msgTxdHandler.msgWIndex++;
	if (UARTx->msgTxdHandler.msgWIndex >= UARTx->msgTxdHandler.msgMaxSize)
	{
		UARTx->msgTxdHandler.msgWIndex = 0;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_FillMode_AddData(UART_HandlerType*UARTx, UINT8_T *pVal, UINT16_T length)
{
	UINT16_T i = 0;
	UINT8_T _return = OK_0;
	for (i = 0; i < length; i++)
	{
		_return = UART_FillMode_AddByte(UARTx, pVal[i]);
		//---判断数据是否填充正确
		if (_return != OK_0)
		{
			break;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置执行结果标识
//////输入参数:
//////输出参数:
//////说		明：数据填充后在发送
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_FillMode_SetResultFlag(UART_HandlerType* UARTx, UINT8_T val)
{
	UARTx->msgTxdHandler.pMsgVal[UARTx->msgTxdHandler.msgFlagIndex] = val;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：写的序号的增加值
//////输入参数:
//////输出参数:
//////说		明：数据填充后在发送
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_FillMode_AddIndexW(UART_HandlerType* UARTx, UINT16_T val)
{
	UARTx->msgTxdHandler.msgWIndex += val;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_CRCTask_Read(UART_HandlerType*UARTx)
{
	UINT32_T crcVal = 0;
	UINT32_T crcTemp = 0;
	//---接收数据的个数
	UINT16_T length = UARTx->msgRxdHandler.msgWIndex;
	//---校验CRC是否初始化
	if ((UARTx->msgRxdHandler.msgCRCFlag != UART_CRC_NONE) && (CRCTask_Enable() == OK_0))
	{
		//---判断数据校验模式
		if (UARTx->msgRxdHandler.msgCRCFlag == UART_CRC_CHECKSUM)
		{
			length -= 1;
			if (UARTx->msgRxdHandler.msgMaxSize < 250)
			{
				UARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length);
				//---获取校验和
				crcTemp = UARTx->msgRxdHandler.pMsgVal[length + 2];
				//---参与校验和计算的数据总长度
				length += 2;
			}
			else
			{
				UARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				UARTx->msgRxdHandler.pMsgVal[2] = (UINT8_T)(length);
				//---获取校验和
				crcTemp = UARTx->msgRxdHandler.pMsgVal[length + 3];
				//---参与校验和计算的数据总长度
				length += 3;
			}
			//---计算校验和
			crcVal = CRCTask_CheckSum(UARTx->msgRxdHandler.pMsgVal, length);
		}
		else if (UARTx->msgRxdHandler.msgCRCFlag == UART_CRC_CRC8)
		{
			length -= 1;
			if (UARTx->msgRxdHandler.msgMaxSize < 250)
			{
				UARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length);
				//---获取校验和
				crcTemp = UARTx->msgRxdHandler.pMsgVal[length + 2];
				//---参与校验和计算的数据总长度
				length += 2;
			}
			else
			{
				UARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				UARTx->msgRxdHandler.pMsgVal[2] = (UINT8_T)(length);
				//---获取校验和
				crcTemp = UARTx->msgRxdHandler.pMsgVal[length + 3];
				//---参与校验和计算的数据总长度
				length += 3;
			}
			//---计算CRC8校验值
			crcVal = CRCTask_CRC8(USE_CRC8_07H, UARTx->msgRxdHandler.pMsgVal, length);
		}
		else if (UARTx->msgRxdHandler.msgCRCFlag == UART_CRC_CRC16)
		{
			length -= 2;
			if (UARTx->msgRxdHandler.msgMaxSize < 250)
			{
				UARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length);
				//---获取CRC16的高位值
				crcTemp = UARTx->msgRxdHandler.pMsgVal[length + 1];
				//---获取CRC16的低位值
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandler.pMsgVal[length + 2];
				//---参与校验和计算的数据总长度
				length += 2;
			}
			else
			{
				UARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				UARTx->msgRxdHandler.pMsgVal[2] = (UINT8_T)(length);
				//---获取CRC16的高位值
				crcTemp = UARTx->msgRxdHandler.pMsgVal[length + 2];
				//---获取CRC16的低位值
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandler.pMsgVal[length + 3];
				//---参与校验和计算的数据总长度
				length += 3;
			}
			//---计算CRC16校验值
			crcVal = CRCTask_CRC16(UARTx->msgRxdHandler.pMsgVal, length);
		}
		else if (UARTx->msgRxdHandler.msgCRCFlag == UART_CRC_CRC32)
		{
			length -= 4;
			if (UARTx->msgRxdHandler.msgMaxSize < 250)
			{
				UARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length);
				//---获取CRC32的最高位值
				crcTemp = UARTx->msgRxdHandler.pMsgVal[length - 1];
				//---获取CRC32的次高位值
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandler.pMsgVal[length];
				//---获取CRC32的次低位值
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandler.pMsgVal[length + 1];
				//---获取CRC32的低位值
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandler.pMsgVal[length + 2];
				//---参与校验和计算的数据总长度
				length += 2;
			}
			else
			{
				UARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				UARTx->msgRxdHandler.pMsgVal[2] = (UINT8_T)(length);
				//---获取CRC32的最高位值
				crcTemp = UARTx->msgRxdHandler.pMsgVal[length];
				//---获取CRC32的次高位值
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandler.pMsgVal[length + 1];
				//---获取CRC32的次低位值
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandler.pMsgVal[length + 2];
				//---获取CRC32的低位值
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandler.pMsgVal[length + 3];
				length += 3;
			}
			crcVal = CRCTask_CRC32(UARTx->msgRxdHandler.pMsgVal, length);
		}
		//---比对CRC的值
		if (crcVal != crcTemp)
		{
			return  ERROR_1;
		}
	}
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_CRCTask_Write(UART_HandlerType*UARTx)
{
	//---校验CRC是否初始化
	if ((UARTx->msgTxdHandler.msgCRCFlag != UART_CRC_NONE) && (CRCTask_Enable() == OK_0))
	{
		UINT32_T crcVal = 0;
		//--要发送数据的总长度
		UINT16_T length = UARTx->msgTxdHandler.msgWIndex;
		//---判断是否增加换行符
		if ((UARTx->msgTxdHandler.msgAddNewLine==1))
		{
			length += 2;
		}
		//---数据大小的整理
		if (UARTx->msgTxdHandler.msgMaxSize < 0xFF)
		{
			UARTx->msgTxdHandler.pMsgVal[1] = (UINT8_T)(length- 2);
		}
		else
		{
			UARTx->msgTxdHandler.pMsgVal[1] = (UINT8_T)((length - 3) >> 8);
			UARTx->msgTxdHandler.pMsgVal[2] = (UINT8_T)((length - 3));
		}		
		//---判断数据校验模式
		if (UARTx->msgTxdHandler.msgCRCFlag == UART_CRC_CHECKSUM)
		{
			//---校验和
			crcVal = CRCTask_CheckSum(UARTx->msgTxdHandler.pMsgVal, UARTx->msgTxdHandler.msgWIndex);
			UART_FillMode_AddByte(UARTx, (UINT8_T)crcVal);
		}
		else if (UARTx->msgTxdHandler.msgCRCFlag == UART_CRC_CRC8)
		{
			//---CRC8校验
			crcVal = CRCTask_CRC8(USE_CRC8_07H, UARTx->msgTxdHandler.pMsgVal, UARTx->msgTxdHandler.msgWIndex);
			UART_FillMode_AddByte(UARTx, (UINT8_T)crcVal);
		}
		else if (UARTx->msgTxdHandler.msgCRCFlag == UART_CRC_CRC16)
		{
			//---CRC16校验
			crcVal = CRCTask_CRC16(UARTx->msgTxdHandler.pMsgVal, UARTx->msgTxdHandler.msgWIndex);
			UART_FillMode_AddByte(UARTx, (UINT8_T)(crcVal >> 8));
			UART_FillMode_AddByte(UARTx, (UINT8_T)crcVal);
		}
		else if (UARTx->msgTxdHandler.msgCRCFlag == UART_CRC_CRC32)
		{
			//---CRC32校验
			crcVal = CRCTask_CRC32(UARTx->msgTxdHandler.pMsgVal, UARTx->msgTxdHandler.msgWIndex);
			UART_FillMode_AddByte(UARTx, (UINT8_T)(crcVal >> 24));
			UART_FillMode_AddByte(UARTx, (UINT8_T)(crcVal >> 16));
			UART_FillMode_AddByte(UARTx, (UINT8_T)(crcVal >> 8));
			UART_FillMode_AddByte(UARTx, (UINT8_T)crcVal);
		}
		//---发送数据的大小
		UARTx->msgTxdHandler.msgCount = UARTx->msgTxdHandler.msgWIndex;
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：填充模式启动发送，这里适合填充之后中断发送和DMA模式（DMA模式是数据填充完成之后，才能启动发送的）
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_FillMode_WriteByteSTART(UART_HandlerType*UARTx, UINT8_T isNeedID)
{
	//---检查发送状态，等待之前的数据发送完成;必须是空闲状态，总线上没有其他数据放
	while ((UARTx->msgTxdHandler.msgState == UART_BUSY) || (UARTx->msgTxdHandler.msgState == UART_PRINTF) || (UARTx->msgTxdHandler.msgState == UART_DMA))
	{
		WDT_RESET();
	}
	//---设置发送状态为空闲中
	UARTx->msgTxdHandler.msgState = UART_BUSY;
	//---判断是否需要填充报头
	if (isNeedID == 1)
	{
		//---填充报头和数据长度
		UARTx->msgTxdHandler.pMsgVal[0] = UARTx->msgTxdID;
	}
	//---填充设备ID
	if ((UARTx->msgCmdIndex - UARTx->msgIDIndex) != 0)
	{
		UARTx->msgTxdHandler.pMsgVal[UARTx->msgIDIndex] = UARTx->msgID;
	}	
	//---发送CRC处理
	UART_CRCTask_Write(UARTx);
	//---判断是否增加换行符
	if (( UARTx->msgTxdHandler.msgAddNewLine == 1 ))
	{
		UART_FillMode_AddByte( UARTx, 0x0D );
		UART_FillMode_AddByte( UARTx, 0x0A );
	}	
	//---数据大小的整理
	if (UARTx->msgTxdHandler.msgMaxSize < 0xFF)
	{
		UARTx->msgTxdHandler.pMsgVal[1] = (UINT8_T)(UARTx->msgTxdHandler.msgWIndex - 2);
	}
	else
	{
		UARTx->msgTxdHandler.pMsgVal[1] = (UINT8_T)((UARTx->msgTxdHandler.msgWIndex - 3) >> 8);
		UARTx->msgTxdHandler.pMsgVal[2] = (UINT8_T)((UARTx->msgTxdHandler.msgWIndex - 3));
	}
	UARTx->msgTxdHandler.msgCount=UARTx->msgTxdHandler.msgWIndex;
	//---设置485为发送模式
	UART_485GPIOInit(UARTx, UART_485_TX_ENABLE);
	//---切换发送端口为输出模式
	UART_TXGPIOInit(UARTx, UART_TXGPIO_SET_OUTPUT);
	//---校验是不是DMA模式
	if (UARTx->msgTxdHandler.msgDMAMode==0)
	{
		//---发送数据寄存器空中断使能
		LL_USART_EnableIT_TXE(UARTx->msgUART);
	}
	else
	{
		//---设置数据地址
		UART_Write_DMA_SetMemoryAddress(UARTx, (UARTx->msgTxdHandler.pMsgVal));
		//---启动DMA发送
		UART_Write_DMA_RESTART(UARTx);
	}
	//---复位超时计数器
	UART_TimeTick_Init(&(UARTx->msgTxdHandler));
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：填充模式启动发送，这里适合填充之后中断发送和DMA模式（DMA模式是数据填充完成之后，才能启动发送的）
//////输入参数: 发送指定长度的数组信息，默认给定的数据是需要的数据，内部没有对数据进行处理
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_FillMode_WriteArraySTART(UART_HandlerType* UARTx, UINT8_T *pArrayVal,UINT16_T length)
{
	//---检查发送状态，等待之前的数据发送完成;必须是空闲状态，总线上没有其他数据放
	while ((UARTx->msgTxdHandler.msgState == UART_BUSY) || (UARTx->msgTxdHandler.msgState == UART_PRINTF) || (UARTx->msgTxdHandler.msgState == UART_DMA))
	{
		WDT_RESET();
	}
	//---设置发送状态为忙碌状态
	UARTx->msgTxdHandler.msgState = UART_BUSY;
	//---拷贝数据长度
	memcpy(UARTx->msgTxdHandler.pMsgVal, pArrayVal, length);
	//---要写入数据的个数
	UARTx->msgTxdHandler.msgWIndex = length;
	//---发送CRC处理
	UART_CRCTask_Write(UARTx);
	//---判断是否增加换行符
	if ((UARTx->msgTxdHandler.msgAddNewLine == 1))
	{
		UART_FillMode_AddByte(UARTx, 0x0D);
		UART_FillMode_AddByte(UARTx, 0x0A);
	}
	UARTx->msgTxdHandler.msgCount = UARTx->msgTxdHandler.msgWIndex;
	//---设置485为发送模式
	UART_485GPIOInit(UARTx, UART_485_TX_ENABLE);
	//---切换发送端口为输出模式
	UART_TXGPIOInit(UARTx, UART_TXGPIO_SET_OUTPUT);
	//---校验是不是DMA模式
	if (UARTx->msgTxdHandler.msgDMAMode == 0)
	{
		//---发送数据寄存器空中断使能
		LL_USART_EnableIT_TXE(UARTx->msgUART);
	}
	else
	{
		//---设置数据地址
		UART_Write_DMA_SetMemoryAddress(UARTx, (UARTx->msgTxdHandler.pMsgVal));
		//---启动DMA发送
		UART_Write_DMA_RESTART(UARTx);
	}
	//---复位超时计数器
	UART_TimeTick_Init(&(UARTx->msgTxdHandler));
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 获取溢出标志
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_GetOverFlow(UART_HandlerDef* UARTDefx)
{
	return UARTDefx->msgOverFlow ;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 清除溢出标志
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_ClearOverFlow(UART_HandlerDef* UARTDefx)
{
	UARTDefx->msgOverFlow = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：获取状态标识
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_GetState(UART_HandlerDef* UARTDefx)
{
	return UARTDefx->msgState;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：清楚状态标识
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_ClearState(UART_HandlerDef* UARTDefx)
{
	UARTDefx->msgState = UART_OK;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：复位接收参数
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_Read_Init(UART_HandlerType*  UARTx)
{
	//---设置485位接收模式
	UART_485GPIOInit(UARTx, UART_485_RX_ENABLE);
	//---清零步序
	UARTx->msgRxdHandler.msgStep = 0;
	//---清除写数组索引
	UARTx->msgRxdHandler.msgWIndex = 0;
	//---清除读数组索引
	UARTx->msgRxdHandler.msgRIndex = 0;
	//---清零接收数据个数
	UARTx->msgRxdHandler.msgCount = 0;
	//---清零接收完成标志
	UARTx->msgRxdHandler.msgState = UART_BUSY;
	//---清零超时计数
	UARTx->msgRxdHandler.msgRecordTick = 0;
	//---清零超时标志
	UARTx->msgRxdHandler.msgOverFlow = 0;
	//---校验是不是DMA模式
	if(UARTx->msgRxdHandler.msgDMAMode!=0)
	{
		UART_Read_DMA_RESTART(UARTx);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：复位发送参数
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_Write_Init(UART_HandlerType*  UARTx)
{
	//---设置发送状态为发送完成
	UARTx->msgTxdHandler.msgState = UART_OK;
	//---清除写数组索引
	UARTx->msgTxdHandler.msgWIndex = 0;
	//---清除读数组索引
	UARTx->msgTxdHandler.msgRIndex = 0;
	//---清零发送数据个数
	UARTx->msgTxdHandler.msgCount = 0;
	//---清零超时计数
	UARTx->msgTxdHandler.msgRecordTick = 0;
	//---清零超时标志
	UARTx->msgTxdHandler.msgOverFlow = 0;
	//---操作步序归零
	UARTx->msgTxdHandler.msgStep = 0;
	//---设置485为接收模式
	UART_485GPIOInit(UARTx, UART_485_RX_ENABLE);
	//---数据发送完成，切换端口为输入模式
	UART_TXGPIOInit(UARTx, UART_TXGPIO_SET_INPUT);
	//---记录发送完成的时间
	UARTx->msgTxdHandler.msgRecordTime = ((UARTx->msgTxdHandler.msgTimeTick != NULL) ? (UARTx->msgTxdHandler.msgTimeTick()) : 0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：校验设备的ID信息
//////输入参数:
//////输出参数:
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_DeviceID(UART_HandlerType*UARTx)
{
	if ((UARTx->msgCmdIndex - UARTx->msgIDIndex) != 0)
	{
		if (UARTx->msgRxdHandler.pMsgVal[UARTx->msgIDIndex] != UARTx->msgID)
		{
			return ERROR_1;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：挂起发送
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void UART_PrintfSuspend(UART_HandlerType* UARTx)
{
#ifdef USE_UART_PRINTF
	//---检查发送状态，等待之前的数据发送完成;必须是空闲状态，总线上没有其他数据放
	while ((UARTx->msgTxdHandler.msgState == UART_BUSY) || (UARTx->msgTxdHandler.msgState == UART_PRINTF)||(UARTx->msgTxdHandler.msgState == UART_DMA))
	{
		//--->>>是不是对这里进行超时异常处理，超过规定时间，还没有发送完成，那么进行强制发送完成标识，清零状态
		WDT_RESET();
	}
	////---检查发送寄存器空中断是否使能
	//if (LL_UART_IsEnabledIT_TXE(UARTx->msgUART))
	//{
	//	//---等待发送完成
	//	while (LL_UART_IsActiveFlag_TXE(UARTx->msgUART) != RESET)
	//	{
	//		WDT_RESET();
	//	}
	//}
	////---检查发送完成中断
	//if (LL_UART_IsEnabledIT_TC(UARTx->msgUART))
	//{
	//	//---等待发送完成
	//	while ((LL_UART_IsActiveFlag_TC(UARTx->msgUART) != RESET) && (UARTx->msgTxdHandler.msgStep == 0))
	//	{
	//		WDT_RESET();
	//	}
	//	LL_UART_ClearFlag_TC(UARTx->msgUART);
	//}
	//---定义485为发送模式
	UART_485GPIOInit(UARTx, UART_485_TX_ENABLE);
	//---切换发送端口为输出模式
	UART_TXGPIOInit(UARTx, UART_TXGPIO_SET_OUTPUT);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：恢复发送
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void UART_PrintfResume(UART_HandlerType* UARTx)
{
#ifdef USE_UART_PRINTF
	//---定义485为接收模式
	UART_485GPIOInit(UARTx, UART_485_RX_ENABLE);
	//---数据发送完成，切换端口为输入模式
	UART_TXGPIOInit(UARTx, UART_TXGPIO_SET_INPUT);
	//---记录发送完成的时间
	UARTx->msgTxdHandler.msgRecordTime = ((UARTx->msgTxdHandler.msgTimeTick != NULL) ? (UARTx->msgTxdHandler.msgTimeTick()) : 0);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：自定义的Printf函数
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void UART_Printf(UART_HandlerType*UARTx, char*fmt, ...)
{
#ifdef USE_UART_PRINTF
	//---校验串口是否已经初始化过
	if (UARTx->msgUART!=NULL)
	{
		//---挂起操作，等待上一次的发送完成
		UART_PrintfSuspend(UARTx);
		//---计算数据
		UINT16_T length = 0;
		//---这里是保护缓存区的索引，后面会改变这个索引，如果不保存索引，数据的偏移会发生异常
		UINT16_T index = pPrintf->msgIndex;
		//---定义一个va_list型的变量,这个变量是指向参数的指针
		va_list arg;
		//---用va_start宏初始化变量,这个宏的第二个参数是第一个可变参数的前一个参数,是一个固定的参数
		va_start(arg, fmt);
		//---用于向字符串中打印数据、数据格式用户自定义;返回参数是最终生成字符串的长度
		//length = (UINT16_T)vsnprintf(g_PrintfBuffer, UART_PRINTF_SIZE, fmt, arg_ptr);
		length = (UINT16_T)vsnprintf(&(pPrintf->pMsgVal[pPrintf->msgIndex]),(UART_PRINTF_SIZE- pPrintf->msgIndex), fmt, arg);
		//---用va_end宏结束可变参数的获取
		va_end(arg);
		//---判断数据
		if (length > (UART_PRINTF_SIZE - pPrintf->msgIndex))
		{
			length = UART_PRINTF_SIZE - pPrintf->msgIndex; //UART_PRINTF_SIZE;
			//---缓存区满，字符归零处理
			pPrintf->msgIndex=0;
			return;
		}
		else
		{
		  	//---数据索引偏移
			pPrintf->msgIndex += length;
			//---至少空闲64字节的缓存区
			if ((UART_PRINTF_SIZE- UART_PRINTF_IDLE_SIZE)<(pPrintf->msgIndex))
			{
				//---缓存区满，字符归零处理
				pPrintf->msgIndex = 0;
			}
		}
		//---校验是不是DMA模式
		if (UARTx->msgTxdHandler.msgDMAMode!=0)
		{
			//--->>>DMA发送模式
			UARTx->msgTxdHandler.msgCount = length;
			//---设置数据地址
			UART_Write_DMA_SetMemoryAddress(UARTx, (UINT8_T*)(pPrintf->pMsgVal+index));
			//---启动DMA发送
			UART_Write_DMA_RESTART(UARTx);
		}
		else
		{
			//--->>>中断发送模式
			//---要发送数据的个数
			UARTx->msgPCount = length;
			//---使用的发送完成中断，这里需要首先发送一次数据
			UARTx->msgPIndex = 1;
			//---工作在使用PRINTF模式
			UARTx->msgTxdHandler.msgState = UART_PRINTF;
			//---发送完成,发送数据发送完成中断不使能
			LL_USART_EnableIT_TC(UARTx->msgUART);
			//---发送8Bit的数据
			LL_USART_TransmitData8(UARTx->msgUART, pPrintf->pMsgVal[index]);
		}
		//---复位超时计数器
		UART_TimeTick_Init(&(UARTx->msgTxdHandler));
	}
#endif	
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：打印LOG信息
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void UART_PrintfLog(UART_HandlerType* UARTx, char* fmt, va_list args)
{
	#ifdef USE_UART_PRINTF
	//---校验串口是否已经初始化过
	if (UARTx->msgUART != NULL)
	{
		//---挂起操作，等待上一次的发送完成
		UART_PrintfSuspend(UARTx);
		//---计算数据
		UINT16_T length = 0;
		//---这里是保护缓存区的索引，后面会改变这个索引，如果不保存索引，数据的偏移会发生异常
		UINT16_T index = pPrintf->msgIndex;
		//---用于向字符串中打印数据、数据格式用户自定义;返回参数是最终生成字符串的长度
		//length = (UINT16_T)vsnprintf(g_PrintfBuffer, UART_PRINTF_SIZE, fmt, args);
		length = (UINT16_T)vsnprintf(&(pPrintf->pMsgVal[pPrintf->msgIndex]), (UART_PRINTF_SIZE - pPrintf->msgIndex), fmt, args);
		////---判断数据
		//if (length > UART_PRINTF_SIZE)
		//{
		//	length = UART_PRINTF_SIZE;
		//}
		//---判断数据
		if (length > (UART_PRINTF_SIZE - pPrintf->msgIndex))
		{
			length = UART_PRINTF_SIZE - pPrintf->msgIndex; //UART_PRINTF_SIZE;
			//---缓存区满，字符归零处理
			pPrintf->msgIndex = 0;
			return;
		}
		else
		{
		  	//---数据索引偏移
			pPrintf->msgIndex += length;
			//---至少空闲64字节的缓存区
			if ((UART_PRINTF_SIZE - UART_PRINTF_IDLE_SIZE) < (pPrintf->msgIndex))
			{
				//---缓存区满，字符归零处理
				pPrintf->msgIndex = 0;
			}
		}
		//---校验是不是DMA模式
		if (UARTx->msgTxdHandler.msgDMAMode != 0)
		{
			//--->>>DMA发送模式
			UARTx->msgTxdHandler.msgCount = length;
			//---设置数据地址
			//UART_Write_DMA_SetMemoryAddress(UARTx, (UINT8_T*)g_PrintfBuffer);
			//---设置数据地址
			UART_Write_DMA_SetMemoryAddress(UARTx, (UINT8_T*)(pPrintf->pMsgVal + index));
			//---启动DMA发送
			UART_Write_DMA_RESTART(UARTx);
		}
		else
		{
			//--->>>中断发送模式
			//---要发送数据的个数
			UARTx->msgPCount = length;
			//---使用的发送完成中断，这里需要首先发送一次数据
			UARTx->msgPIndex = 1;
			//---工作在使用PRINTF模式
			UARTx->msgTxdHandler.msgState = UART_PRINTF;
			//---发送完成,发送数据发送完成中断不使能
			LL_USART_EnableIT_TC(UARTx->msgUART);
			//---发送8Bit的数据
			//LL_UART_TransmitData8(UARTx->msgUART, g_PrintfBuffer[0]);
			LL_USART_TransmitData8(UARTx->msgUART, pPrintf->pMsgVal[index]);
		}
		//---复位超时计数器
		UART_TimeTick_Init(&(UARTx->msgTxdHandler));
	}
	#endif
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITPrintf_TCTask(UART_HandlerType* UARTx)
{
#ifdef USE_UART_PRINTF
	if (UARTx->msgPIndex>=UARTx->msgPCount)
	{
		//---发送完成,发送数据发送完成中断不使能
		LL_USART_DisableIT_TC(UARTx->msgUART);
		//---恢复操作
		UART_PrintfResume(UARTx);
		//---标识发送完成
		UARTx->msgTxdHandler.msgState = UART_OK;
	}
	else
	{
		//---发送8Bit的数据
		LL_USART_TransmitData8(UARTx->msgUART, g_PrintfBuffer[UARTx->msgPIndex]);
		UARTx->msgPIndex++;
	}
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：中断发送完成函数
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_IT_TCTask(UART_HandlerType* UARTx)
{
	if (UARTx->msgTxdHandler.msgState == UART_BUSY)
	{
		UART_ITWrite_TCTask(UARTx);
	}
	else if (UARTx->msgTxdHandler.msgState == UART_PRINTF)
	{
		UART_ITPrintf_TCTask(UARTx);
	}
	else
	{
		UARTx->msgTxdHandler.msgState = UART_OK;
		LL_USART_DisableIT_TC(UARTx->msgUART);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：打印系统时钟
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void UART_PrintfClockFreq(UART_HandlerType*UARTx)
{
	LL_RCC_ClocksTypeDef rccClock = { 0 };
	//---获取系统时钟
	LL_RCC_GetSystemClocksFreq(&rccClock);
	//---打印系统时钟
	UART_Printf(UARTx, "SYSCLK=%UHz\r\n", rccClock.SYSCLK_Frequency);
	//---打印系统时钟
	UART_Printf(UARTx, "HCLK=%UHz\r\n", rccClock.HCLK_Frequency);
	//---打印系统时钟
	UART_Printf(UARTx, "PCLK1=%UHz\r\n", rccClock.PCLK1_Frequency);
	//---打印系统时钟
	UART_Printf(UARTx, "PCLK2=%UHz\r\n", rccClock.PCLK2_Frequency);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：UART的总线时钟
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_Clock(USART_TypeDef* UARTx, UINT8_T isEnable)
{
	#ifdef UART1
	if (UARTx == UART1)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---不使能SPI的时钟线
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_UART1);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_UART1);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_UART1);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_UART1);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
	#endif
	#ifdef UART2
	if (UARTx == UART2)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---不使能SPI的时钟线
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART2);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---使能SPI的时钟线
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART2);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_UART2);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_UART2);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
	#endif
#ifdef UART3
	if (UARTx == UART3)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---不使能SPI的时钟线
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART3);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---使能SPI的时钟线
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART3);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_UART3);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_UART3);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif /* UART3 */
#ifdef UART6
	if (UARTx == UART6)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---不使能SPI的时钟线
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_UART6);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_UART6);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_UART6);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_UART6);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif /* UART6 */
#ifdef UART4
	if (UARTx == UART4)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---不使能SPI的时钟线
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART4);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---使能SPI的时钟线
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART4);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_UART4);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_UART4);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif /* UART4 */
#ifdef UART5
	if (UARTx == UART5)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---不使能SPI的时钟线
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART5);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---使能SPI的时钟线
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART5);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_UART5);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_UART5);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif /* UART5 */
#ifdef UART7
	if (UARTx == UART7)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---不使能SPI的时钟线
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART7);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---使能SPI的时钟线
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART7);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_UART7);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_UART7);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif /* UART7 */
#ifdef UART8
	if (UARTx == UART8)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---不使能SPI的时钟线
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART8);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---使能SPI的时钟线
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART8);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_UART8);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_UART8);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif /* UART8 */
#ifdef UART9
	if (UARTx == UART9)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---不使能SPI的时钟线
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_UART9);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_UART9);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_UART9);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_UART9);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif /* UART9 */
#ifdef UART10
	if (UARTx == UART10)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---不使能SPI的时钟线
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_UART10);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_UART10);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_UART10);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_UART10);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif /* UART10 */
	else
	{
		return ERROR_2;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：销毁配置
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_DeInit(UART_HandlerType*UARTx)
{
	LL_USART_DeInit(UARTx->msgUART);
	UART_Clock(UARTx->msgUART, 0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：参数配置
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_ParamInit(UART_HandlerType *UARTx, UINT8_T id, UINT8_T idIndex, UINT8_T cmdIndex, UINT8_T d1Index, UINT8_T d2Index)
{
	UARTx->msgID = id;
	UARTx->msgIDIndex = idIndex;
	UARTx->msgCmdIndex = cmdIndex;
	UARTx->msgDataOneIndex = d1Index;
	UARTx->msgDataTwoIndex = d2Index;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：中断处理函数
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////、
void UART_IRQTask(UART_HandlerType* UARTx)
{
	//---数据接收中断处理函数---接收寄存器不为空
	if (LL_USART_IsActiveFlag_RXNE(UARTx->msgUART) && LL_USART_IsEnabledIT_RXNE(UARTx->msgUART))
	{
		//---中断处理函数
		UART_ITRead_Task(UARTx, LL_USART_ReceiveData8(UARTx->msgUART));
		//---清楚中断标志位
		LL_USART_ClearFlag_RXNE(UARTx->msgUART);
	}

	//---数据发送寄存器空发送中断处理函数
	if (LL_USART_IsActiveFlag_TXE(UARTx->msgUART) && LL_USART_IsEnabledIT_TXE(UARTx->msgUART))
	{
		//---中断处理函数
		UART_ITWrite_TXETask(UARTx);
	}
	//---数据发送完成中断处理函数
	if (LL_USART_IsActiveFlag_TC(UARTx->msgUART) && LL_USART_IsEnabledIT_TC(UARTx->msgUART))
	{
		//---中断处理函数
		UART_IT_TCTask(UARTx);
		//---清楚中断标志位
		LL_USART_ClearFlag_TC(UARTx->msgUART);
	}
	//---UART5和UART5，不适用CTS检测
	if ((UARTx->msgUART!=UART4)&& (UARTx->msgUART != UART5))
	{
		//---CTS状态线变化中断
		if (LL_USART_IsActiveFlag_nCTS(UARTx->msgUART) && LL_USART_IsEnabledIT_CTS(UARTx->msgUART))
		{
			//---中断处理函数

			//---清楚中断标志位
			LL_USART_ClearFlag_nCTS(UARTx->msgUART);
		}
	}
	//---LIN断路检测中断
	if (LL_USART_IsActiveFlag_LBD(UARTx->msgUART) && LL_USART_IsEnabledIT_LBD(UARTx->msgUART))
	{
		//---中断处理函数

		//---清楚中断标志位
		LL_USART_ClearFlag_LBD(UARTx->msgUART);
	}
	//---空闲状态中断，主要是用于DMA接收不定长数据
	if (LL_USART_IsActiveFlag_IDLE(UARTx->msgUART) && LL_USART_IsEnabledIT_IDLE(UARTx->msgUART))
	{
		//---中断处理函数,DMA数据接收
		UART_DMA_IDLETask(UARTx);
		//---清楚空闲中断标志位
		LL_USART_ClearFlag_IDLE(UARTx->msgUART);
		//---清楚DMA中断标识
		LL_DMA_ClearFlag(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
	}
	//---上溢错误中断
	if (LL_USART_IsActiveFlag_ORE(UARTx->msgUART) && LL_USART_IsEnabledIT_ERROR(UARTx->msgUART))
	{
		//---中断处理函数

		//---清楚中断标志位
		LL_USART_ClearFlag_ORE(UARTx->msgUART);
	}
	//---噪声中断
	if (LL_USART_IsActiveFlag_NE(UARTx->msgUART) && LL_USART_IsEnabledIT_ERROR(UARTx->msgUART))
	{
		//---中断处理函数

		//---清楚中断标志位
		LL_USART_ClearFlag_NE(UARTx->msgUART);
	}
	//---帧错误中断
	if (LL_USART_IsActiveFlag_FE(UARTx->msgUART) && LL_USART_IsEnabledIT_ERROR(UARTx->msgUART))
	{
		//---中断处理函数

		//---清楚中断标志位
		LL_USART_ClearFlag_FE(UARTx->msgUART);
	}
	//---奇偶校验中断
	if (LL_USART_IsActiveFlag_PE(UARTx->msgUART) && LL_USART_IsEnabledIT_PE(UARTx->msgUART))
	{
		//---中断处理函数

		//---清楚中断标志位
		LL_USART_ClearFlag_PE(UARTx->msgUART);
	}
}

////////////////////////////////////////////////////////////////////////////////
////DMA模式配置
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：关闭DMA的接受模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT16_T UART_Read_DMA_STOP(UART_HandlerType* UARTx)
{
#ifdef USE_MCU_STM32F1
	//---使能DMA
	LL_DMA_DisableChannel(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream);
	LL_DMA_ClearFlag_GI1(UARTx->msgRxHandler.msgDMA);
#else
	//---不使能DMA
	LL_DMA_DisableStream(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
#endif
	LL_DMA_ClearFlag(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
	//---计算接收数据的长度
	UINT16_T length = UARTx->msgRxdHandler.msgMaxSize - LL_DMA_GetDataLength(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
	return length;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：重启DMA的接受模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_Read_DMA_RESTART(UART_HandlerType* UARTx)
{
	//---设置DMA读取数据的大小
	LL_DMA_SetDataLength(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream, UARTx->msgRxdHandler.msgMaxSize);
	//---使能DMA
#ifdef USE_MCU_STM32F1
	//---使能DMA
	LL_DMA_EnableChannel(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
#else
	//---使能DMA
	LL_DMA_EnableStream(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置DMA发送模式下，数据存储的地址
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_Write_DMA_SetMemoryAddress(UART_HandlerType* UARTx,UINT8_T *pVal)
{
	#ifdef USE_MCU_STM32F1
		
	#else
		LL_DMA_SetMemoryAddress(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream,(UINT32_T)pVal);
	#endif
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：停止DMA的发送模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT16_T UART_Write_DMA_STOP(UART_HandlerType* UARTx)
{
#ifdef USE_MCU_STM32F1
	//---使能DMA
	LL_DMA_DisableChannel(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream);
	LL_DMA_ClearFlag_GI1(UARTx->msgRxHandler.msgDMA);
#else
	//---不使能DMA
	LL_DMA_DisableStream(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream);
#endif
	LL_DMA_ClearFlag(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream);
	//---计算接收数据的长度
	UINT16_T length = UARTx->msgTxdHandler.msgMaxSize - LL_DMA_GetDataLength(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream);
	return length;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：重启DMA的发送模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_Write_DMA_RESTART(UART_HandlerType* UARTx)
{
	//---设置DMA发送数据的大小
	LL_DMA_SetDataLength(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream, UARTx->msgTxdHandler.msgCount);
#ifdef USE_MCU_STM32F1
	//---使能DMA
	LL_DMA_EnableChannel(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream);
#else
	//---使能DMA
	LL_DMA_EnableStream(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream);
#endif
	//---设置为DMA状态
	UARTx->msgTxdHandler.msgState= UART_DMA;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_DMA_IDLETask(UART_HandlerType* UARTx)
{
	UINT8_T _return = OK_0;
	//---停止接收DMA模式,并获取接收数据的长度
	UINT16_T dataLength= UART_Read_DMA_STOP(UARTx);
	//---校验报头是否正确
	if (UARTx->msgRxdHandler.pMsgVal[0] == UARTx->msgRxdID)
	{
		//---数据长度信息
		UINT16_T length = UARTx->msgRxdHandler.pMsgVal[1];
		//---校验数据长度信息
		if (UARTx->msgRxdHandler.msgMaxSize < 0xFF)
		{
			length += 2;
		}
		else
		{
			length = (length << 8) + UARTx->msgRxdHandler.pMsgVal[1];
			length += 3;
		}
		//---校验数据是否合法
		if (length == dataLength)
		{
			UARTx->msgRxdHandler.msgState = UART_OK;
			UARTx->msgRxdHandler.msgCount=dataLength;
		}
		else
		{
			//---数据不符合规则，使能重新接收
			UART_Read_Init(UARTx);
			//---返回错误信息
			_return = ERROR_2;
		}
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：接收中断DMA处理程序
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void UART_Read_DMA_IRQTask(UART_HandlerType* UARTx)
{
	//---DMA处理模式
	UART_DMA_IDLETask(UARTx);
	//---清楚空闲中断标志位
	LL_USART_ClearFlag_IDLE(UARTx->msgUART);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：接收中断DMA处理程序
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void UART_Write_DMA_IRQTask(UART_HandlerType* UARTx)
{
#ifdef USE_MCU_STM32F1
	//---不使能DMA
	LL_DMA_DisableChannel(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream;
	LL_DMA_ClearFlag_GI1(UARTx->msgTxHandler.msgDMA);
#else
	//---不使能DMA
	LL_DMA_DisableStream(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream);
#endif
	//---清除标识
	LL_DMA_ClearFlag(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream);
	//---清零发送
	//UART_Write_Init(UARTx);
	//---使能发送完成中断，用于切换TXD端口为输入状态
	LL_USART_EnableIT_TC(UARTx->msgUART);
}

