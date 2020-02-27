#include "uart_cfg.h"

//===ȫ�ֱ�������
UART_HandlerType  g_Uart1 = { 0 };
pUART_HandlerType pUart1 = &g_Uart1;

//=== ȫ�ֱ�������
UART_HandlerType  g_Uart3 = { 0 };
pUART_HandlerType pUart3 = &g_Uart3;

//===printf����ʹ�õĻ�����
#ifdef USE_UART_PRINTF
	char g_PrintfBuffer[UART_PRINTF_SIZE] = { 0 };
	//---��ʼ��printf���λ�����
	UART_PrintfType g_Printf = 
	{ 
		.msgIndex =0,
		.pMsgVal= g_PrintfBuffer
	};
	pUART_PrintfType pPrintf =&g_Printf;
#endif

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_StructInit(UART_HandlerType*  UARTx)
{
	//---���ڵ����ݴ�������
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

	//---���ջ�����
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
	//---������
	UARTx->msgRxdHandler.msgTimeTick = NULL;

	//---���ͻ�����
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
	//---������
	UARTx->msgTxdHandler.msgTimeTick = NULL;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ָ�������ã���ʼ��ָ���Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_ConfigInit(UART_HandlerType* UARTx, UART_HandlerType* UARTInitx)
{
	//---���ڵ����ݴ�������
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

	//---���ջ�����
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
	//---������
	UARTx->msgRxdHandler.msgTimeTick	= UARTInitx->msgRxdHandler.msgTimeTick		;

	//---���ͻ�����
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
	//---������
	UARTx->msgTxdHandler.msgTimeTick	= UARTInitx->msgTxdHandler.msgTimeTick		;
	
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�UART1�Ĳ�������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART1_ConfigInit(UART_HandlerType* UARTx)
{
	//---UART1 GPIO Configuration
	//---PA9  ------> UART1_TX---�˿ڸ���Ϊ7
	//---PA10 ------> UART1_RX---�˿ڸ���Ϊ7
	//---ʹ�ܶ˿�ʱ��
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(GPIOA, PERIPHERAL_CLOCK_ENABLE);
	#endif
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---ģʽ����
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	//---�����ٶ�
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	//---���ù��ܵ��������
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	//---��������ʹ��
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
	//---�˿ں�
	GPIO_InitStruct.Pin = LL_GPIO_PIN_9 | LL_GPIO_PIN_10;
	//---���ù���ΪUART1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	#endif
	//---������Ϣ�ṹ���е���Ϣ
	UARTx->msgTxPort.msgPort = GPIOA;
	UARTx->msgTxPort.msgBit = LL_GPIO_PIN_9;
	UARTx->msgUART = USART1;
	//---�������
	UARTx->msgIndex = 1 + 1;
	//---ע�����ڵĳ�ʼ��
	LL_USART_DeInit(UARTx->msgUART);
	//---ʹ��UART1��ʱ���ź�
	UART_Clock(UARTx->msgUART, PERIPHERAL_CLOCK_ENABLE);
	//---UART�Ľӿڽṹ��
	LL_USART_InitTypeDef USART_InitStruct = { 0 };
	//---������
	USART_InitStruct.BaudRate = 115200;
	//---����λ
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	//---ֹͣλ
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	//---У��λ
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	//---����Ϊ�շ�ģʽ
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	//---Ӳ��������---Ĭ��Ϊ��
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	//---����������
	#ifdef UART_CR1_OVER8
	//---����������---Ĭ������Ϊ16
	UART_InitStruct.OverSampling = LL_UART_OVERSAMPLING_16;
	#endif
	//---��ʼ������
	LL_USART_Init(UARTx->msgUART, &USART_InitStruct);
	//---�����첽ģʽ����
	LL_USART_ConfigAsyncMode(UARTx->msgUART);
	//---У���Ƿ������Ҫ��ʱ����
	(UARTx->msgRxdHandler.msgTimeTick != NULL)?(UARTx->msgRxdHandler.msgMaxTime = 100):(UARTx->msgRxdHandler.msgMaxTime = 0);
	//---У���Ƿ�����Ҫ��ʱ����
	(UARTx->msgTxdHandler.msgTimeTick != NULL)?(UARTx->msgTxdHandler.msgMaxTime = 100):(UARTx->msgTxdHandler.msgMaxTime = 0);
	//---����CRC�ĵȼ�
	UARTx->msgTxdHandler.msgCRCFlag = UART_CRC_NONE;
	//---���ñ�ͷ�ͱ�β
	UARTx->msgRxdID = 0x55;
	UARTx->msgTxdID = 0x5A;
	//---����͵�ַ����
	UART_ParamInit(UARTx, UART1_DEVICE_ID, UART1_ID_INDEX, UART1_CMD_INDEX, UART1_DATA1_INDEX, UART1_DATA2_INDEX);
	//---����485Ϊ����ģʽ--�������ģʽ������Ϊ����ģʽ
	UART_485GPIOInit(UARTx, UART_485_RX_ENABLE);
	//---����TX�˿�Ϊ����ģʽ
	UART_TXGPIOInit(UARTx, UART_TXGPIO_SET_INPUT);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����DMA��ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART1_Read_DMA_Init(UART_HandlerType* UARTx)
{
	//>>>---RX��DMA����
	//---��DMAȫ���Ĵ�����������Ϊȱʡֵ
	#ifdef USE_MCU_STM32F1
	//---F1��Ӧ�ǵ�DMA1��ͨ��1��ӦADC1
	LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_1);
	//---DMAʱ����������
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	#else
	LL_DMA_DeInit(DMA2, LL_DMA_STREAM_2);
	//---DMAʱ����������
	//LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
	DMATask_Clock(DMA2, PERIPHERAL_CLOCK_ENABLE);
	UARTx->msgRxdHandler.msgDMA = DMA2;
	UARTx->msgRxdHandler.msgDMAChannelOrStream = LL_DMA_STREAM_2;
	#endif
	//---DMA��ʼ���ṹ��
	LL_DMA_InitTypeDef DMA_InitTypeDef = { 0 };
	#ifndef USE_MCU_STM32F1
	//---DMAͨ��
	DMA_InitTypeDef.Channel = LL_DMA_CHANNEL_4;
	#endif
	//---���ݴ�С
	DMA_InitTypeDef.NbData = UARTx->msgRxdHandler.msgMaxSize;
	//---��������赽�洢��
	DMA_InitTypeDef.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
	#ifndef USE_MCU_STM32F1
	//---����FIFO��ֱ��ģʽ
	DMA_InitTypeDef.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
	//---�������ֽ�
	DMA_InitTypeDef.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
	#endif
	//---�洢����ַ
	DMA_InitTypeDef.MemoryOrM2MDstAddress = (UINT32_T)(UARTx->msgRxdHandler.pMsgVal);
	//---�������ֽ�
	DMA_InitTypeDef.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
	//---�洢����ַ����
	DMA_InitTypeDef.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
	//---DMA����ģʽ
	DMA_InitTypeDef.Mode = LL_DMA_MODE_NORMAL; //LL_DMA_MODE_CIRCULAR;
	//---DMA�����ַ
	DMA_InitTypeDef.PeriphOrM2MSrcAddress = (UINT32_T) & (UARTx->msgUART->DR);
	#ifndef USE_MCU_STM32F1
	//---��FIFO
	DMA_InitTypeDef.PeriphBurst = LL_DMA_PBURST_SINGLE;
	#endif
	//---�������ֽ�
	DMA_InitTypeDef.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
	//---�������ַ����
	DMA_InitTypeDef.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
	//---����ͨ�����ȼ�Ϊ��
	DMA_InitTypeDef.Priority = LL_DMA_PRIORITY_HIGH;
	//---DMA��ʼ��
	#ifdef USE_MCU_STM32F1
	//---��ʼ��DMA
	LL_DMA_Init(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---ʹ��DMA
	LL_DMA_EnableChannel(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream);
	#else
	//---��ʼ��DMA
	LL_DMA_Init(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---ʹ��DMA
	LL_DMA_EnableStream(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
	//---���ܴ��ڽ���DMA
	LL_USART_EnableDMAReq_RX(UARTx->msgUART);
	#endif
	//---�ж�����
	#ifdef USE_MCU_STM32F1
	//---DMA�ж�����
	NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
	#else
	//---DMA�ж�����
	NVIC_SetPriority(DMA2_Stream2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA2_Stream2_IRQn);
	#endif
	//---ʹ��DMA��������ж�
	LL_DMA_EnableIT_TC(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
	//<<<---RX��DMA���ý���
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����DMA�ĳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART1_Write_DMA_Init(UART_HandlerType* UARTx)
{
	//>>>---TX��DMA����
	//---��DMAȫ���Ĵ�����������Ϊȱʡֵ
	#ifdef USE_MCU_STM32F1
	//---F1��Ӧ�ǵ�DMA1��ͨ��1��ӦADC1
	LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_1);
	//---DMAʱ����������
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	#else
	LL_DMA_DeInit(DMA2, LL_DMA_STREAM_7);
	//---DMAʱ����������
	//LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
	DMATask_Clock(DMA2, PERIPHERAL_CLOCK_ENABLE);
	UARTx->msgTxdHandler.msgDMA = DMA2;
	UARTx->msgTxdHandler.msgDMAChannelOrStream = LL_DMA_STREAM_7;
	#endif
	//---DMA��ʼ���ṹ��
	LL_DMA_InitTypeDef DMA_InitTypeDef = { 0 };
	#ifndef USE_MCU_STM32F1
	//---DMAͨ��
	DMA_InitTypeDef.Channel = LL_DMA_CHANNEL_4;
	#endif
	//---���ݴ�С,������״η��ͣ�����Ĳ���ֻ��д0���������׷������ݲ�����������ֻ�����˽Ӹ��ֽھ�ֹͣ����
	DMA_InitTypeDef.NbData = 0;//UARTx->msgTxdHandler.msgSize;
	//---����Ӵ洢��������
	DMA_InitTypeDef.Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
	#ifndef USE_MCU_STM32F1
	//---����FIFO��ֱ��ģʽ
	DMA_InitTypeDef.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
	//---�������ֽ�
	DMA_InitTypeDef.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
	#endif
	//---�洢����ַ
	DMA_InitTypeDef.MemoryOrM2MDstAddress = (UINT32_T)(UARTx->msgTxdHandler.pMsgVal);
	//---�������ֽ�
	DMA_InitTypeDef.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
	//---�洢����ַ����
	DMA_InitTypeDef.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
	//---DMA����ģʽ
	DMA_InitTypeDef.Mode = LL_DMA_MODE_NORMAL; //LL_DMA_MODE_CIRCULAR;
	//---DMA�����ַ
	DMA_InitTypeDef.PeriphOrM2MSrcAddress = (UINT32_T) & (UARTx->msgUART->DR);
	#ifndef USE_MCU_STM32F1
	//---��FIFO
	DMA_InitTypeDef.PeriphBurst = LL_DMA_PBURST_SINGLE;
	#endif
	//---�������ֽ�
	DMA_InitTypeDef.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
	//---�������ַ����
	DMA_InitTypeDef.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
	//---����ͨ�����ȼ�Ϊ��
	DMA_InitTypeDef.Priority = LL_DMA_PRIORITY_HIGH;
	//---DMA��ʼ��
	#ifdef USE_MCU_STM32F1
	//---��ʼ��DMA
	LL_DMA_Init(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---ʹ��DMA
	LL_DMA_EnableChannel(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream);
	#else
	//---��ʼ��DMA
	LL_DMA_Init(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---ʹ��DMA,ע�ⷢ��״̬�²���ʹ��DMA��ֻ����Ҫ��ʱ����ܴ�
	//LL_DMA_EnableStream(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream);
	//---ʹ�ܴ��ڷ���DMA
	LL_USART_EnableDMAReq_TX(UARTx->msgUART);
	#endif
	//---�ж�����
	#ifdef USE_MCU_STM32F1
	//---DMA�ж�����
	NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
	#else
	//---DMA�ж�����
	NVIC_SetPriority(DMA2_Stream7_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA2_Stream7_IRQn);
	#endif
	//---ʹ��DMA��������ж�
	LL_DMA_EnableIT_TC(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream);
	//<<<---TX��DMA���ý���
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART1_Init(UART_HandlerType* UARTx)
{
	UART1_ConfigInit(UARTx);
	//---У������ǲ���DMA����
	if (UARTx->msgRxdHandler.msgDMAMode == 0)
	{
		//---ʹ�ܽ����ж�
		LL_USART_EnableIT_RXNE(USART1);
	}
	else
	{
		//---ʹ�ܽ��տ����ж�
		LL_USART_EnableIT_IDLE(USART1);
		//---��ʼ��DMA����
		UART1_Read_DMA_Init(UARTx);
	}
	//---У�鷢���ǲ���DMA���䷽ʽ
	if (UARTx->msgTxdHandler.msgDMAMode != 0)
	{
		UART1_Write_DMA_Init(UARTx);
	}
	//---UART1_IRQ�ж�����---�жϵȼ�����
	NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(USART1_IRQn);
	//---ʹ�ܴ���
	LL_USART_Enable(USART1);
	//---��ӡ��ʼ����Ϣ
	//UART_Printf(UARTx, "=>>����1�ĳ�ʼ��<<=\r\n");
	UART_Printf(UARTx, "=>>Init SP1<<=\r\n");
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART2_ConfigInit(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART2_Read_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART2_Write_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART2_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART3_ConfigInit(UART_HandlerType* UARTx)
{
	//---UART3 GPIO Configuration
	//---PB10  ------> UART1_TX---�˿ڸ���Ϊ7
	//---PB11  ------> UART1_RX---�˿ڸ���Ϊ7
	//---ʹ�ܶ˿�ʱ��
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(GPIOB, PERIPHERAL_CLOCK_ENABLE);
	#endif
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---ģʽ����
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	//---�����ٶ�
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	//---���ù��ܵ��������
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	//---��������ʹ��
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
	//---�˿ں�
	GPIO_InitStruct.Pin = LL_GPIO_PIN_10 | LL_GPIO_PIN_11;
	//---���ù���ΪUART3
	GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#endif
	//---������Ϣ�ṹ���е���Ϣ
	UARTx->msgTxPort.msgPort = GPIOB;
	UARTx->msgTxPort.msgBit = LL_GPIO_PIN_10;
	UARTx->msgUART = USART3;
	//---�������
	UARTx->msgIndex = 3 + 1;
	//---ע�����ڵĳ�ʼ��
	LL_USART_DeInit(UARTx->msgUART);
	//---ʹ��UART1��ʱ���ź�
	UART_Clock(UARTx->msgUART, PERIPHERAL_CLOCK_ENABLE);
	//---UART�Ľӿڽṹ��
	LL_USART_InitTypeDef USART_InitStruct = { 0 };
	//---������
	USART_InitStruct.BaudRate = 115200;
	//---����λ
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	//---ֹͣλ
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	//---У��λ
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	//---����Ϊ�շ�ģʽ
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	//---Ӳ��������---Ĭ��Ϊ��
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	//---����������
	#ifdef UART_CR1_OVER8
		//---����������---Ĭ������Ϊ16
	UART_InitStruct.OverSampling = LL_UART_OVERSAMPLING_16;
	#endif
	//---��ʼ������
	LL_USART_Init(UARTx->msgUART, &USART_InitStruct);
	//---�����첽ģʽ����
	LL_USART_ConfigAsyncMode(UARTx->msgUART);
	//---У���Ƿ������Ҫ��ʱ����
	(UARTx->msgRxdHandler.msgTimeTick != NULL) ? (UARTx->msgRxdHandler.msgMaxTime = 10) : (UARTx->msgRxdHandler.msgMaxTime = 0);
	//---У���Ƿ�����Ҫ��ʱ����
	(UARTx->msgTxdHandler.msgTimeTick != NULL) ? (UARTx->msgTxdHandler.msgMaxTime = 100) : (UARTx->msgTxdHandler.msgMaxTime = 0);
	//---����CRC�ĵȼ�
	UARTx->msgTxdHandler.msgCRCFlag = UART_CRC_NONE;
	//---���ñ�ͷ�ͱ�β
	UARTx->msgRxdID = 0x55;
	UARTx->msgTxdID = 0x5A;
	//---����͵�ַ����
	//UART_ParamInit(UARTx, UART1_DEVICE_ID, UART1_ID_INDEX, UART1_CMD_INDEX, UART1_DATA1_INDEX, UART1_DATA2_INDEX);
	//---����485Ϊ����ģʽ--�������ģʽ������Ϊ����ģʽ
	UART_485GPIOInit(UARTx, UART_485_RX_ENABLE);
	//---����TX�˿�Ϊ����ģʽ
	UART_TXGPIOInit(UARTx, UART_TXGPIO_SET_INPUT);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART3_Read_DMA_Init(UART_HandlerType* UARTx)
{
	//>>>---RX��DMA����
	//---��DMAȫ���Ĵ�����������Ϊȱʡֵ
	#ifdef USE_MCU_STM32F1
	//---F1��Ӧ�ǵ�DMA1��ͨ��1��ӦADC1
	LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_1);
	//---DMAʱ����������
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	#else
	LL_DMA_DeInit(DMA1, LL_DMA_STREAM_1);
	//---DMAʱ����������
	//LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	DMATask_Clock(DMA1, PERIPHERAL_CLOCK_ENABLE);
	UARTx->msgRxdHandler.msgDMA = DMA1;
	UARTx->msgRxdHandler.msgDMAChannelOrStream = LL_DMA_STREAM_1;
	#endif
	//---DMA��ʼ���ṹ��
	LL_DMA_InitTypeDef DMA_InitTypeDef = { 0 };
	#ifndef USE_MCU_STM32F1
	//---DMAͨ��
	DMA_InitTypeDef.Channel = LL_DMA_CHANNEL_4;
	#endif
	//---���ݴ�С
	DMA_InitTypeDef.NbData = UARTx->msgRxdHandler.msgMaxSize;
	//---��������赽�洢��
	DMA_InitTypeDef.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
	#ifndef USE_MCU_STM32F1
	//---����FIFO��ֱ��ģʽ
	DMA_InitTypeDef.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
	//---�������ֽ�
	DMA_InitTypeDef.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
	#endif
	//---�洢����ַ
	DMA_InitTypeDef.MemoryOrM2MDstAddress = (UINT32_T)(UARTx->msgRxdHandler.pMsgVal);
	//---�������ֽ�
	DMA_InitTypeDef.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
	//---�洢����ַ����
	DMA_InitTypeDef.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
	//---DMA����ģʽ
	DMA_InitTypeDef.Mode = LL_DMA_MODE_NORMAL; //LL_DMA_MODE_CIRCULAR;
	//---DMA�����ַ
	DMA_InitTypeDef.PeriphOrM2MSrcAddress = (UINT32_T) & (UARTx->msgUART->DR);
	#ifndef USE_MCU_STM32F1
	//---��FIFO
	DMA_InitTypeDef.PeriphBurst = LL_DMA_PBURST_SINGLE;
	#endif
	//---�������ֽ�
	DMA_InitTypeDef.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
	//---�������ַ����
	DMA_InitTypeDef.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
	//---����ͨ�����ȼ�Ϊ��
	DMA_InitTypeDef.Priority = LL_DMA_PRIORITY_HIGH;
	//---DMA��ʼ��
	#ifdef USE_MCU_STM32F1
	//---��ʼ��DMA
	LL_DMA_Init(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---ʹ��DMA
	LL_DMA_EnableChannel(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream);
	#else
	//---��ʼ��DMA
	LL_DMA_Init(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---ʹ��DMA
	LL_DMA_EnableStream(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
	//---���ܴ��ڽ���DMA
	LL_USART_EnableDMAReq_RX(UARTx->msgUART);
	#endif
	//---�ж�����
	#ifdef USE_MCU_STM32F1
	//---DMA�ж�����
	NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
	#else
	//---DMA�ж�����
	NVIC_SetPriority(DMA1_Stream1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA1_Stream1_IRQn);
	#endif
	//---ʹ��DMA��������ж�
	LL_DMA_EnableIT_TC(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
	//<<<---RX��DMA���ý���
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART3_Write_DMA_Init(UART_HandlerType* UARTx)
{
	//>>>---TX��DMA����
	//---��DMAȫ���Ĵ�����������Ϊȱʡֵ
	#ifdef USE_MCU_STM32F1
	//---F1��Ӧ�ǵ�DMA1��ͨ��1��ӦADC1
	LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_1);
	//---DMAʱ����������
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	#else
	LL_DMA_DeInit(DMA1, LL_DMA_STREAM_3);
	//---DMAʱ����������
	//LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	DMATask_Clock(DMA1, PERIPHERAL_CLOCK_ENABLE);
	UARTx->msgTxdHandler.msgDMA = DMA1;
	UARTx->msgTxdHandler.msgDMAChannelOrStream = LL_DMA_STREAM_3;
	#endif
	//---DMA��ʼ���ṹ��
	LL_DMA_InitTypeDef DMA_InitTypeDef = { 0 };
	#ifndef USE_MCU_STM32F1
	//---DMAͨ��
	DMA_InitTypeDef.Channel = LL_DMA_CHANNEL_4;
	#endif
	//---���ݴ�С,������״η��ͣ�����Ĳ���ֻ��д0���������׷������ݲ�����������ֻ�����˽Ӹ��ֽھ�ֹͣ����
	DMA_InitTypeDef.NbData = 0;//UARTx->msgTxdHandler.msgSize;
	//---����Ӵ洢��������
	DMA_InitTypeDef.Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
	#ifndef USE_MCU_STM32F1
	//---����FIFO��ֱ��ģʽ
	DMA_InitTypeDef.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
	//---�������ֽ�
	DMA_InitTypeDef.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
	#endif
	//---�洢����ַ
	DMA_InitTypeDef.MemoryOrM2MDstAddress = (UINT32_T)(UARTx->msgTxdHandler.pMsgVal);
	//---�������ֽ�
	DMA_InitTypeDef.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
	//---�洢����ַ����
	DMA_InitTypeDef.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
	//---DMA����ģʽ
	DMA_InitTypeDef.Mode = LL_DMA_MODE_NORMAL; //LL_DMA_MODE_CIRCULAR;
	//---DMA�����ַ
	DMA_InitTypeDef.PeriphOrM2MSrcAddress = (UINT32_T) & (UARTx->msgUART->DR);
	#ifndef USE_MCU_STM32F1
	//---��FIFO
	DMA_InitTypeDef.PeriphBurst = LL_DMA_PBURST_SINGLE;
	#endif
	//---�������ֽ�
	DMA_InitTypeDef.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
	//---�������ַ����
	DMA_InitTypeDef.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
	//---����ͨ�����ȼ�Ϊ��
	DMA_InitTypeDef.Priority = LL_DMA_PRIORITY_HIGH;
	//---DMA��ʼ��
	#ifdef USE_MCU_STM32F1
	//---��ʼ��DMA
	LL_DMA_Init(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---ʹ��DMA
	LL_DMA_EnableChannel(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream);
	#else
	//---��ʼ��DMA
	LL_DMA_Init(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---ʹ��DMA,ע�ⷢ��״̬�²���ʹ��DMA��ֻ����Ҫ��ʱ����ܴ�
	//LL_DMA_EnableStream(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream);
	//---ʹ�ܴ��ڷ���DMA
	LL_USART_EnableDMAReq_TX(UARTx->msgUART);
	#endif
	//---�ж�����
	#ifdef USE_MCU_STM32F1
	//---DMA�ж�����
	NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
	#else
	//---DMA�ж�����
	NVIC_SetPriority(DMA1_Stream3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA1_Stream3_IRQn);
	#endif
	//---ʹ��DMA��������ж�
	LL_DMA_EnableIT_TC(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream);
	//<<<---TX��DMA���ý���
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART3_Init(UART_HandlerType* UARTx)
{
	UART3_ConfigInit(UARTx);
	//---У������ǲ���DMA����
	if (UARTx->msgRxdHandler.msgDMAMode == 0)
	{
		//---ʹ�ܽ����ж�
		LL_USART_EnableIT_RXNE(UARTx->msgUART);
	}
	else
	{
		//---ʹ�ܽ��տ����ж�
		LL_USART_EnableIT_IDLE(UARTx->msgUART);
		//---��ʼ��DMA����
		UART3_Read_DMA_Init(UARTx);
	}
	//---У�鷢���ǲ���DMA���䷽ʽ
	if (UARTx->msgTxdHandler.msgDMAMode != 0)
	{
		UART3_Write_DMA_Init(UARTx);
	}
	//---UART1_IRQ�ж�����---�жϵȼ�����
	NVIC_SetPriority(USART3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(USART3_IRQn);
	//---ʹ�ܴ���
	LL_USART_Enable(UARTx->msgUART);
	//---��ӡ��ʼ����Ϣ
	//UART_Printf(UARTx, "=>>����1�ĳ�ʼ��<<=\r\n");
	UART_Printf(UARTx, "=>>Init SP3<<=\r\n");
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART4_ConfigInit(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART4_Read_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART4_Write_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART4_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART5_ConfigInit(UART_HandlerType* UARTx)
{
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART5_Read_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART5_Write_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART5_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART6_ConfigInit(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART6_Read_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART6_Write_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART6_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART7_ConfigInit(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART7_Read_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART7_Write_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART7_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART8_ConfigInit(UART_HandlerType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART8_Read_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART8_Write_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART8_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART9_ConfigInit(UART_HandlerType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART9_Read_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART9_Write_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}



///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART9_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART10_ConfigInit(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART10_Read_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART10_Write_DMA_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART10_Init(UART_HandlerType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
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
	//---ע���������
	UARTx->msgTxdHandler.msgTimeTick = pTimerTick;
	UARTx->msgRxdHandler.msgTimeTick = pTimerTick;
	//---�˿ڳ�ʼ��
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
//////��		����
//////��		�ܣ����ڵķ��Ͷ˿ڵĳ�ʼ��
//////�������:
//////�������:
//////˵		����
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
//////��		����
//////��		�ܣ�485������ƶ˿ڵĳ�ʼ��
//////�������:
//////�������:
//////˵		����
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
//////��		����
//////��		�ܣ�����CRCУ��ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_SetCRC(UART_HandlerDef* UARTDefx, UINT8_T crcFlag)
{
	UARTDefx->msgCRCFlag = crcFlag;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡCRCУ��ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_GetCRC(UART_HandlerDef* UARTDefx)
{
	return UARTDefx->msgCRCFlag;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_TimeTick_Init(UART_HandlerDef* UARTDefx)
{
	//---ʱ��ڵ�
	UARTDefx->msgRecordTick = ((UARTDefx->msgTimeTick != NULL)?(UARTDefx->msgTimeTick()):0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ע����ʱ������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_TimeTick_DeInit(UART_HandlerDef* UARTDefx)
{
	//---���������־λ
	UARTDefx->msgOverFlow = 0;
	//---���㵱ǰʱ��
	UARTDefx->msgRecordTick = 0;
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ʱ������Ƿ�����ʱ
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_TimeTick_OverFlow(UART_HandlerDef* UARTDefx)
{
	UINT32_T temp = 0;
	//---��ȡ��ǰʱ��
	temp = ((UARTDefx->msgTimeTick != NULL) ? (UARTDefx->msgTimeTick()+2) : 0);
	//---�ж��Ƿ�����ʱ����
	if (temp > UARTDefx->msgRecordTick)
	{
		//---��ʱ��δ�����������
		if ((temp - UARTDefx->msgRecordTick) > UARTDefx->msgMaxTime)
		{
			UARTDefx->msgOverFlow = 1;
			return ERROR_1;
		}
	}
	else 
	{
		//---��ʱ�������������
		if ((0xFFFFFFFF - UARTDefx->msgRecordTick + temp) > UARTDefx->msgMaxTime)
		{
			UARTDefx->msgOverFlow = 1;
			return ERROR_1;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_TimeTask_OverFlow(UART_HandlerType*UARTx, UINT8_T isRx)
{
	UINT8_T _return = OK_0;
	//---�ж��ǽ��ջ��Ƿ��Ͳ�У���ǲ���DMA����ģʽ
	if ((isRx != 0) && (UARTx->msgRxdHandler.msgDMAMode == 0))
	{
		if ((UARTx->msgRxdHandler.msgRecordTick != 0) && (UARTx->msgRxdHandler.msgMaxTime != 0))
		{
			if (UARTx->msgRxdHandler.msgRecordTick == 0)
			{
				return OK_0;
			}
			//---��ȡ��ʱֵ
			_return = UART_TimeTick_OverFlow(&(UARTx->msgRxdHandler));
			//---��ʱ�����жϣ�����ĳЩ״̬�µ�ǰ��¼��ʱ��ֵ�ڸ�дΪ���ʱ��ʱ���¼��û�з���ͬ������
			//if ((_return != OK_0))
			if ((_return != OK_0) && (UARTx->msgRxdHandler.msgRecordTick != 0))
			{
				//---��ӡ��ʱ�Ĵ�����Ϣ
				UART_Printf(UARTx, "=>>SP%d:Receive Mode Timeout Error!<<=\r\n", (UARTx->msgIndex - 1));
				//---��λ�������ݻ�����
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
			//---��ȡ��ʱֵ
			_return = UART_TimeTick_OverFlow(&(UARTx->msgTxdHandler));
			//---��ʱ�����жϣ�����ĳЩ״̬�µ�ǰ��¼��ʱ��ֵ�ڸ�дΪ���ʱ��ʱ���¼��û�з���ͬ������
			if ((_return != OK_0) && (UARTx->msgTxdHandler.msgRecordTick != 0))
			{
				//---��ӡ��ʱ�Ĵ�����Ϣ
				UART_Printf(UARTx, "=>>SP%d:Send Mode Timeout Error!<<=\r\n", (UARTx->msgIndex - 1));
				//---��λ�������ݻ�����
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
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ���ܵ�������󳤶�ʹ��1�ֽڱ�ʾ
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITRead_8BitsTask(UART_HandlerType*UARTx, UINT8_T val)
{
	//---��������������
	static UINT8_T tempVal;
	tempVal = val;
	//---���ݽ��ղ���
	switch (UARTx->msgRxdHandler.msgStep)
	{
		//---�������ݵı�ͷ
		case 0:
			if (UARTx->msgRxdHandler.msgRIndex == 0)
			{
				if (UARTx->msgRxdID == tempVal)
				{
					UARTx->msgRxdHandler.pMsgVal[0] = tempVal;
					UARTx->msgRxdHandler.msgStep = 1;
					//---��¼���ݵĸ���
					UARTx->msgRxdHandler.msgCount = 1;
					//---�յ���һ�����ϸ�ʽ�����ݣ�������ʱ������
					UART_TimeTick_Init(&(UARTx->msgRxdHandler));
					//---���㳬ʱ��־
					UART_ClearOverFlow(&(UARTx->msgRxdHandler));
				}
			}
			break;

			//---�������ݵĳ���
		case 1:
			if ((tempVal > 0) && (tempVal < (UINT8_T)(UARTx->msgRxdHandler.msgMaxSize & 0xFF)))
			{
				UARTx->msgRxdHandler.pMsgVal[1] = tempVal;
				//---��ȡ���ݵĽ��ճ���
				UARTx->msgRxdHandler.msgWIndex = tempVal;
				//---��¼���ݵĸ���
				UARTx->msgRxdHandler.msgCount += 1;
				//---��һ����
				UARTx->msgRxdHandler.msgStep = 2;
			}
			else
			{
				UARTx->msgRxdHandler.msgStep = 0;
			}
			//---��λ��ʱ������
			UART_TimeTick_Init(&(UARTx->msgRxdHandler));
			break;
			//---����������Ϣ
		case 2:
			UARTx->msgRxdHandler.pMsgVal[UARTx->msgRxdHandler.msgRIndex + 2] = tempVal;
			UARTx->msgRxdHandler.msgRIndex++;
			//---��¼���ݵĸ���
			UARTx->msgRxdHandler.msgCount += 1;
			//---�ж��Ƿ����
			if (UARTx->msgRxdHandler.msgRIndex >= UARTx->msgRxdHandler.msgMaxSize)
			{
				UARTx->msgRxdHandler.msgRIndex = 0;
			}
			//---��λ��ʱ������
			UART_TimeTick_Init(&(UARTx->msgRxdHandler));
			//---�ж��Ƿ�������
			if (UARTx->msgRxdHandler.msgRIndex >= UARTx->msgRxdHandler.msgWIndex)
			{
				UARTx->msgRxdHandler.msgStep = 3;
				UARTx->msgRxdHandler.msgState = UART_OK;
				//---���㳬ʱ������
				//UART_TimeTick_DeInit(UARTx, 1);
				//---��¼������ɵ�ʱ��
				UARTx->msgRxdHandler.msgRecordTime = ((UARTx->msgRxdHandler.msgTimeTick != NULL) ? (UARTx->msgRxdHandler.msgTimeTick()) : 0);
			}
			break;
		case 3:
			//---���㳬ʱ������
			//UART_TimeTick_DeInit(UARTx,1);
			break;
		default:
			//UARTx->msgRxHandler.msgNowTime = 0;
			break;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ���ܵ�������󳤶�ʹ��2�ֽڱ�ʾ
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITRead_16BitsTask(UART_HandlerType*UARTx, UINT8_T val)
{
	//---��������������
	static UINT8_T tempVal;
	tempVal = val;
	//---���ݽ��ղ���
	switch (UARTx->msgRxdHandler.msgStep)
	{
		//---�������ݵı�ͷ
		case 0:
			if (UARTx->msgRxdHandler.msgRIndex == 0)
			{
				if (UARTx->msgRxdID == tempVal)
				{
					UARTx->msgRxdHandler.pMsgVal[0] = tempVal;
					UARTx->msgRxdHandler.msgStep = 1;
					//---��¼���ݵĸ���
					UARTx->msgRxdHandler.msgCount = 1;
					//---�յ���һ�����ϸ�ʽ�����ݣ�������ʱ������
					UART_TimeTick_Init(&(UARTx->msgRxdHandler));
					//---���㳬ʱ��־
					UART_ClearOverFlow(&(UARTx->msgRxdHandler));
				}
			}
			break;

			//---�������ݵĳ��ȸ�λ
		case 1:
			UARTx->msgRxdHandler.pMsgVal[1] = tempVal;
			UARTx->msgRxdHandler.msgWIndex = tempVal;
			UARTx->msgRxdHandler.msgWIndex <<= 8;
			UARTx->msgRxdHandler.msgStep = 2;
			//---��¼���ݵĸ���
			UARTx->msgRxdHandler.msgCount += 1;
			//---��λ��ʱ������
			UART_TimeTick_Init(&(UARTx->msgRxdHandler));
			break;
			//---�������ݵĳ��ȵ�λ
		case 2:
			UARTx->msgRxdHandler.pMsgVal[2] = tempVal;
			UARTx->msgRxdHandler.msgWIndex += tempVal;
			//---��¼���ݵĸ���
			UARTx->msgRxdHandler.msgCount += 1;
			//---�ж������Ƿ�Ϸ�
			if ((UARTx->msgRxdHandler.msgWIndex > 0) && (UARTx->msgRxdHandler.msgWIndex < UARTx->msgRxdHandler.msgMaxSize))
			{
				//---��¼���ݵĸ���
				UARTx->msgRxdHandler.msgCount = UARTx->msgRxdHandler.msgWIndex;
				//---��һ����
				UARTx->msgRxdHandler.msgStep = 3;
			}
			else
			{
				UARTx->msgRxdHandler.msgStep = 0;
			}
			//---��λ��ʱ������
			UART_TimeTick_Init(&(UARTx->msgRxdHandler));
			break;
			//---����������Ϣ
		case 3:
			UARTx->msgRxdHandler.pMsgVal[UARTx->msgRxdHandler.msgRIndex + 3] = tempVal;
			UARTx->msgRxdHandler.msgRIndex++;
			//---��¼���ݵĸ���
			UARTx->msgRxdHandler.msgCount += 1;
			//---�ж��Ƿ����
			if (UARTx->msgRxdHandler.msgRIndex >= UARTx->msgRxdHandler.msgMaxSize)
			{
				UARTx->msgRxdHandler.msgRIndex = 0;
			}
			//---��λ��ʱ������
			UART_TimeTick_Init(&(UARTx->msgRxdHandler));
			//---�ж��Ƿ�������
			if (UARTx->msgRxdHandler.msgRIndex >= UARTx->msgRxdHandler.msgWIndex)
			{
				UARTx->msgRxdHandler.msgStep = 4;
				UARTx->msgRxdHandler.msgState = UART_OK;
				//---���㳬ʱ������
				//UART_TimeTick_DeInit(UARTx, 1);
				//---��¼������ɵ�ʱ��
				UARTx->msgRxdHandler.msgRecordTime = ((UARTx->msgRxdHandler.msgTimeTick != NULL) ? (UARTx->msgRxdHandler.msgTimeTick()) : 0);
			}
			break;
		case 4:
			//---���㳬ʱ������
			//UART_TimeTick_DeInit(UARTx,1);
			break;
		default:
			//UARTx->msgRxHandler.msgNowTime = 0;
			break;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
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
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_PollMode_WriteByte(UART_HandlerType*UARTx, UINT8_T  val)
{
	//---��������
	LL_USART_TransmitData8(UARTx->msgUART, val);
	//---�ȴ��������
	while (LL_USART_IsActiveFlag_TC(UARTx->msgUART) == RESET)
	{
		WDT_RESET();
	}
	//---���������ɱ�־λ
	LL_USART_ClearFlag_TC(UARTx->msgUART);
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� �����ַ���
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_PollMode_WriteData(UART_HandlerType*UARTx, char *pVal)
{
	//---����485Ϊ����ģʽ
	UART_485GPIOInit(UARTx, UART_485_TX_ENABLE);
	//---�л����Ͷ˿�Ϊ���ģʽ
	UART_TXGPIOInit(UARTx, UART_TXGPIO_SET_OUTPUT);
	//---�ر��ж�
	//CLI();
	while (*pVal != '\0')
	{
		UART_PollMode_WriteByte(UARTx, (UINT8_T)*pVal);
		pVal++;
	}
	//---ʹ���ж�
	//SEI();
	//---����485Ϊ����ģʽ
	UART_485GPIOInit(UARTx, UART_485_RX_ENABLE);
	//---�л����Ͷ˿�Ϊ����ģʽ
	UART_TXGPIOInit(UARTx, UART_TXGPIO_SET_INPUT);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_PollMode_ReadByte(UART_HandlerType*UARTx)
{
	//---�ȴ��������
	while (LL_USART_IsActiveFlag_RXNE(UARTx->msgUART) != RESET)
	{
		WDT_RESET();
	}
	return LL_USART_ReceiveData8(UARTx->msgUART);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
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
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITWrite_TXETask(UART_HandlerType*UARTx)
{
	VLTUINT8_T tempFlag=OK_0;
	if (UARTx->msgTxdHandler.msgWIndex != 0)
	{
		if (UARTx->msgTxdHandler.msgRIndex != UARTx->msgTxdHandler.msgWIndex)
		{
			//---����8Bit������
			LL_USART_TransmitData8(UARTx->msgUART, UARTx->msgTxdHandler.pMsgVal[UARTx->msgTxdHandler.msgRIndex]);
			//---���ݻ������������
			UARTx->msgTxdHandler.msgRIndex++;
			//---У�黺�����Ƿ����
			if (UARTx->msgTxdHandler.msgRIndex >= UARTx->msgTxdHandler.msgMaxSize)
			{
				UARTx->msgTxdHandler.msgRIndex = 0;
			}
			//---У�������Ƿ����뻺����
			if ((UARTx->msgTxdHandler.msgRIndex >= UARTx->msgTxdHandler.msgWIndex) && (UARTx->msgTxdHandler.msgCount > 0) && (UARTx->msgTxdHandler.msgRIndex >= UARTx->msgTxdHandler.msgCount))
			{
				//---�������,�������ݼĴ������жϲ�ʹ��
				LL_USART_DisableIT_TXE(UARTx->msgUART);
				//---ʹ�ܷ�������жϣ������л�TXD�˿�Ϊ����״̬
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
	//---У����
	if (tempFlag)
	{
		//---�������,�������ݼĴ������жϲ�ʹ��---����Ƿ�����쳣���رշ������ݼĴ������ж�
		LL_USART_DisableIT_TXE(UARTx->msgUART);
		//---������ݷ��ͻ�����
		UART_Write_Init(UARTx);
	}
	//---��λ��ʱ������
	UART_TimeTick_Init(&(UARTx->msgTxdHandler));
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITWrite_TCTask(UART_HandlerType*UARTx)
{
	//---������485������485��Ӧ���ӳ�����,���ӷ��ͻ��з������ڻ���485����Ӧ
	if ((UARTx->msg485Port.msgPort != NULL) && (UARTx->msgTxdHandler.msgStep == 0))
	{
		//---����8Bit������
		LL_USART_TransmitData8(UARTx->msgUART, 0x0D);
		UARTx->msgTxdHandler.msgStep = 1;
	}
	else if ((UARTx->msg485Port.msgPort != NULL) && (UARTx->msgTxdHandler.msgStep == 1))
	{
		//---����8Bit������
		LL_USART_TransmitData8(UARTx->msgUART, 0x0A);
		UARTx->msgTxdHandler.msgStep = 2;
	}
	else
	{
		//---���㷢�Ͳ���
		UARTx->msgTxdHandler.msgStep = 0;
		//---�������,�������ݷ�������жϲ�ʹ��
		LL_USART_DisableIT_TC(UARTx->msgUART);
		//---������ݷ��ͻ�����
		UART_Write_Init(UARTx);
		//---���㳬ʱ������
		//UART_TimeTick_DeInit(UARTx, 0);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
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
		//---�жϷ��ͼĴ������ж��Ƿ�ʹ��
		if (LL_USART_IsEnabledIT_TXE(UARTx->msgUART) == 0)
		{
			//---����485Ϊ����ģʽ
			UART_485GPIOInit(UARTx, UART_485_TX_ENABLE);
			//---�л����Ͷ˿�Ϊ���ģʽ
			UART_TXGPIOInit(UARTx, UART_TXGPIO_SET_OUTPUT);
			//---ʹ�ܷ��Ϳ��ж�
			LL_USART_EnableIT_TXE(UARTx->msgUART);
		}
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������ݵĴ�С
//////�������:
//////�������:
//////˵		����
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
		//---�ж��Ƿ����豸��ID��Ϣ
		if ((UARTx->msgCmdIndex - UARTx->msgIDIndex) != 0)
		{
			val += 1;
		}
		//---�ж��Ƿ����ӻ��з�
		if ((UARTx->msgTxdHandler.msgAddNewLine==1))
		{
			val += 2;
		}
		//---�ж����ݵĸ�ʽ
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
		//---�ж��Ƿ����豸��ID��Ϣ�����ID��Ϣ
		if ((UARTx->msgCmdIndex - UARTx->msgIDIndex) != 0)
		{
			_return = UART_RealTime_AddByte(UARTx, UARTx->msgID);
		}		
		//---���㷢�����ݵĸ���
		UARTx->msgTxdHandler.msgCount = val;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������ݵ�CRCУ����Ϣ
//////�������:
//////�������:
//////˵		����ʹ��CRC�����ݵı����0��ʼʹ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_RealTime_AddCRC(UART_HandlerType*UARTx)
{
	//---У��CRC�Ƿ��ʼ��
	if ((UARTx->msgTxdHandler.msgCRCFlag != UART_CRC_NONE) && (CRCTask_Enable() == OK_0))
	{
		UINT32_T crcVal = 0;
		//---�ж�����У��ģʽ
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
	//---�ж��Ƿ����ӻ��з�
	if ((UARTx->msgTxdHandler.msgAddNewLine==1))
	{
		UART_RealTime_AddByte(UARTx, 0x0D);
		UART_RealTime_AddByte(UARTx, 0x0A);
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� �����������ǰ�Ĳ�����Լ���ñ�ͷ������Ч���ݿ�ʼ��λ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_FillMode_Init(UART_HandlerType*UARTx,UINT8_T isChildCmd)
{
	//---��鷢��״̬���ȴ�֮ǰ�����ݷ������;�����ǿ���״̬��������û���������ݷ�
	while ((UARTx->msgTxdHandler.msgState == UART_BUSY) || (UARTx->msgTxdHandler.msgState == UART_PRINTF) || (UARTx->msgTxdHandler.msgState == UART_DMA))
	{
		WDT_RESET();
	}
	UARTx->msgTxdHandler.msgWIndex = 0;
	UARTx->msgTxdHandler.msgFlagIndex=0;
	//---������ݱ�ͷ
	UART_FillMode_AddByte( UARTx, UARTx->msgTxdID );
	//---������ݳ���
	UART_FillMode_AddByte( UARTx, 0x00 );
	if (UARTx->msgTxdHandler.msgMaxSize > 0xFF)
	{
		UART_FillMode_AddByte( UARTx, 0x00 );
		UARTx->msgTxdHandler.msgFlagIndex+=1;
	}
	//---�����豸ͨ�ŵ��豸ID
	if ((UARTx->msgCmdIndex - UARTx->msgIDIndex) != 0)
	{
		UART_FillMode_AddByte(UARTx, UARTx->msgID);
	}
	//---������/����
	UART_FillMode_AddByte(UARTx, UARTx->msgRxdHandler.pMsgVal[UARTx->msgCmdIndex]);
	//---У���Ƿ���������
	if (isChildCmd!=0)
	{
		//---������
		UART_FillMode_AddByte(UARTx, UARTx->msgRxdHandler.pMsgVal[UARTx->msgCmdIndex + (isChildCmd == 0 ? 0 : 1)]);
	}
	//---��ʶ����ִ�н���ڻ������жϵ����
	UARTx->msgTxdHandler.msgFlagIndex = UARTx->msgTxdHandler.msgWIndex;
	//---����ִ�н��
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�������������ڷ���
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
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_FillMode_AddData(UART_HandlerType*UARTx, UINT8_T *pVal, UINT16_T length)
{
	UINT16_T i = 0;
	UINT8_T _return = OK_0;
	for (i = 0; i < length; i++)
	{
		_return = UART_FillMode_AddByte(UARTx, pVal[i]);
		//---�ж������Ƿ������ȷ
		if (_return != OK_0)
		{
			break;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ִ�н����ʶ
//////�������:
//////�������:
//////˵		�������������ڷ���
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_FillMode_SetResultFlag(UART_HandlerType* UARTx, UINT8_T val)
{
	UARTx->msgTxdHandler.pMsgVal[UARTx->msgTxdHandler.msgFlagIndex] = val;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�д����ŵ�����ֵ
//////�������:
//////�������:
//////˵		�������������ڷ���
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_FillMode_AddIndexW(UART_HandlerType* UARTx, UINT16_T val)
{
	UARTx->msgTxdHandler.msgWIndex += val;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_CRCTask_Read(UART_HandlerType*UARTx)
{
	UINT32_T crcVal = 0;
	UINT32_T crcTemp = 0;
	//---�������ݵĸ���
	UINT16_T length = UARTx->msgRxdHandler.msgWIndex;
	//---У��CRC�Ƿ��ʼ��
	if ((UARTx->msgRxdHandler.msgCRCFlag != UART_CRC_NONE) && (CRCTask_Enable() == OK_0))
	{
		//---�ж�����У��ģʽ
		if (UARTx->msgRxdHandler.msgCRCFlag == UART_CRC_CHECKSUM)
		{
			length -= 1;
			if (UARTx->msgRxdHandler.msgMaxSize < 250)
			{
				UARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length);
				//---��ȡУ���
				crcTemp = UARTx->msgRxdHandler.pMsgVal[length + 2];
				//---����У��ͼ���������ܳ���
				length += 2;
			}
			else
			{
				UARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				UARTx->msgRxdHandler.pMsgVal[2] = (UINT8_T)(length);
				//---��ȡУ���
				crcTemp = UARTx->msgRxdHandler.pMsgVal[length + 3];
				//---����У��ͼ���������ܳ���
				length += 3;
			}
			//---����У���
			crcVal = CRCTask_CheckSum(UARTx->msgRxdHandler.pMsgVal, length);
		}
		else if (UARTx->msgRxdHandler.msgCRCFlag == UART_CRC_CRC8)
		{
			length -= 1;
			if (UARTx->msgRxdHandler.msgMaxSize < 250)
			{
				UARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length);
				//---��ȡУ���
				crcTemp = UARTx->msgRxdHandler.pMsgVal[length + 2];
				//---����У��ͼ���������ܳ���
				length += 2;
			}
			else
			{
				UARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				UARTx->msgRxdHandler.pMsgVal[2] = (UINT8_T)(length);
				//---��ȡУ���
				crcTemp = UARTx->msgRxdHandler.pMsgVal[length + 3];
				//---����У��ͼ���������ܳ���
				length += 3;
			}
			//---����CRC8У��ֵ
			crcVal = CRCTask_CRC8(USE_CRC8_07H, UARTx->msgRxdHandler.pMsgVal, length);
		}
		else if (UARTx->msgRxdHandler.msgCRCFlag == UART_CRC_CRC16)
		{
			length -= 2;
			if (UARTx->msgRxdHandler.msgMaxSize < 250)
			{
				UARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length);
				//---��ȡCRC16�ĸ�λֵ
				crcTemp = UARTx->msgRxdHandler.pMsgVal[length + 1];
				//---��ȡCRC16�ĵ�λֵ
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandler.pMsgVal[length + 2];
				//---����У��ͼ���������ܳ���
				length += 2;
			}
			else
			{
				UARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				UARTx->msgRxdHandler.pMsgVal[2] = (UINT8_T)(length);
				//---��ȡCRC16�ĸ�λֵ
				crcTemp = UARTx->msgRxdHandler.pMsgVal[length + 2];
				//---��ȡCRC16�ĵ�λֵ
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandler.pMsgVal[length + 3];
				//---����У��ͼ���������ܳ���
				length += 3;
			}
			//---����CRC16У��ֵ
			crcVal = CRCTask_CRC16(UARTx->msgRxdHandler.pMsgVal, length);
		}
		else if (UARTx->msgRxdHandler.msgCRCFlag == UART_CRC_CRC32)
		{
			length -= 4;
			if (UARTx->msgRxdHandler.msgMaxSize < 250)
			{
				UARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length);
				//---��ȡCRC32�����λֵ
				crcTemp = UARTx->msgRxdHandler.pMsgVal[length - 1];
				//---��ȡCRC32�Ĵθ�λֵ
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandler.pMsgVal[length];
				//---��ȡCRC32�Ĵε�λֵ
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandler.pMsgVal[length + 1];
				//---��ȡCRC32�ĵ�λֵ
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandler.pMsgVal[length + 2];
				//---����У��ͼ���������ܳ���
				length += 2;
			}
			else
			{
				UARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				UARTx->msgRxdHandler.pMsgVal[2] = (UINT8_T)(length);
				//---��ȡCRC32�����λֵ
				crcTemp = UARTx->msgRxdHandler.pMsgVal[length];
				//---��ȡCRC32�Ĵθ�λֵ
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandler.pMsgVal[length + 1];
				//---��ȡCRC32�Ĵε�λֵ
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandler.pMsgVal[length + 2];
				//---��ȡCRC32�ĵ�λֵ
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandler.pMsgVal[length + 3];
				length += 3;
			}
			crcVal = CRCTask_CRC32(UARTx->msgRxdHandler.pMsgVal, length);
		}
		//---�ȶ�CRC��ֵ
		if (crcVal != crcTemp)
		{
			return  ERROR_1;
		}
	}
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_CRCTask_Write(UART_HandlerType*UARTx)
{
	//---У��CRC�Ƿ��ʼ��
	if ((UARTx->msgTxdHandler.msgCRCFlag != UART_CRC_NONE) && (CRCTask_Enable() == OK_0))
	{
		UINT32_T crcVal = 0;
		//--Ҫ�������ݵ��ܳ���
		UINT16_T length = UARTx->msgTxdHandler.msgWIndex;
		//---�ж��Ƿ����ӻ��з�
		if ((UARTx->msgTxdHandler.msgAddNewLine==1))
		{
			length += 2;
		}
		//---���ݴ�С������
		if (UARTx->msgTxdHandler.msgMaxSize < 0xFF)
		{
			UARTx->msgTxdHandler.pMsgVal[1] = (UINT8_T)(length- 2);
		}
		else
		{
			UARTx->msgTxdHandler.pMsgVal[1] = (UINT8_T)((length - 3) >> 8);
			UARTx->msgTxdHandler.pMsgVal[2] = (UINT8_T)((length - 3));
		}		
		//---�ж�����У��ģʽ
		if (UARTx->msgTxdHandler.msgCRCFlag == UART_CRC_CHECKSUM)
		{
			//---У���
			crcVal = CRCTask_CheckSum(UARTx->msgTxdHandler.pMsgVal, UARTx->msgTxdHandler.msgWIndex);
			UART_FillMode_AddByte(UARTx, (UINT8_T)crcVal);
		}
		else if (UARTx->msgTxdHandler.msgCRCFlag == UART_CRC_CRC8)
		{
			//---CRC8У��
			crcVal = CRCTask_CRC8(USE_CRC8_07H, UARTx->msgTxdHandler.pMsgVal, UARTx->msgTxdHandler.msgWIndex);
			UART_FillMode_AddByte(UARTx, (UINT8_T)crcVal);
		}
		else if (UARTx->msgTxdHandler.msgCRCFlag == UART_CRC_CRC16)
		{
			//---CRC16У��
			crcVal = CRCTask_CRC16(UARTx->msgTxdHandler.pMsgVal, UARTx->msgTxdHandler.msgWIndex);
			UART_FillMode_AddByte(UARTx, (UINT8_T)(crcVal >> 8));
			UART_FillMode_AddByte(UARTx, (UINT8_T)crcVal);
		}
		else if (UARTx->msgTxdHandler.msgCRCFlag == UART_CRC_CRC32)
		{
			//---CRC32У��
			crcVal = CRCTask_CRC32(UARTx->msgTxdHandler.pMsgVal, UARTx->msgTxdHandler.msgWIndex);
			UART_FillMode_AddByte(UARTx, (UINT8_T)(crcVal >> 24));
			UART_FillMode_AddByte(UARTx, (UINT8_T)(crcVal >> 16));
			UART_FillMode_AddByte(UARTx, (UINT8_T)(crcVal >> 8));
			UART_FillMode_AddByte(UARTx, (UINT8_T)crcVal);
		}
		//---�������ݵĴ�С
		UARTx->msgTxdHandler.msgCount = UARTx->msgTxdHandler.msgWIndex;
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ģʽ�������ͣ������ʺ����֮���жϷ��ͺ�DMAģʽ��DMAģʽ������������֮�󣬲����������͵ģ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_FillMode_WriteByteSTART(UART_HandlerType*UARTx, UINT8_T isNeedID)
{
	//---��鷢��״̬���ȴ�֮ǰ�����ݷ������;�����ǿ���״̬��������û���������ݷ�
	while ((UARTx->msgTxdHandler.msgState == UART_BUSY) || (UARTx->msgTxdHandler.msgState == UART_PRINTF) || (UARTx->msgTxdHandler.msgState == UART_DMA))
	{
		WDT_RESET();
	}
	//---���÷���״̬Ϊ������
	UARTx->msgTxdHandler.msgState = UART_BUSY;
	//---�ж��Ƿ���Ҫ��䱨ͷ
	if (isNeedID == 1)
	{
		//---��䱨ͷ�����ݳ���
		UARTx->msgTxdHandler.pMsgVal[0] = UARTx->msgTxdID;
	}
	//---����豸ID
	if ((UARTx->msgCmdIndex - UARTx->msgIDIndex) != 0)
	{
		UARTx->msgTxdHandler.pMsgVal[UARTx->msgIDIndex] = UARTx->msgID;
	}	
	//---����CRC����
	UART_CRCTask_Write(UARTx);
	//---�ж��Ƿ����ӻ��з�
	if (( UARTx->msgTxdHandler.msgAddNewLine == 1 ))
	{
		UART_FillMode_AddByte( UARTx, 0x0D );
		UART_FillMode_AddByte( UARTx, 0x0A );
	}	
	//---���ݴ�С������
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
	//---����485Ϊ����ģʽ
	UART_485GPIOInit(UARTx, UART_485_TX_ENABLE);
	//---�л����Ͷ˿�Ϊ���ģʽ
	UART_TXGPIOInit(UARTx, UART_TXGPIO_SET_OUTPUT);
	//---У���ǲ���DMAģʽ
	if (UARTx->msgTxdHandler.msgDMAMode==0)
	{
		//---�������ݼĴ������ж�ʹ��
		LL_USART_EnableIT_TXE(UARTx->msgUART);
	}
	else
	{
		//---�������ݵ�ַ
		UART_Write_DMA_SetMemoryAddress(UARTx, (UARTx->msgTxdHandler.pMsgVal));
		//---����DMA����
		UART_Write_DMA_RESTART(UARTx);
	}
	//---��λ��ʱ������
	UART_TimeTick_Init(&(UARTx->msgTxdHandler));
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ģʽ�������ͣ������ʺ����֮���жϷ��ͺ�DMAģʽ��DMAģʽ������������֮�󣬲����������͵ģ�
//////�������: ����ָ�����ȵ�������Ϣ��Ĭ�ϸ�������������Ҫ�����ݣ��ڲ�û�ж����ݽ��д���
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_FillMode_WriteArraySTART(UART_HandlerType* UARTx, UINT8_T *pArrayVal,UINT16_T length)
{
	//---��鷢��״̬���ȴ�֮ǰ�����ݷ������;�����ǿ���״̬��������û���������ݷ�
	while ((UARTx->msgTxdHandler.msgState == UART_BUSY) || (UARTx->msgTxdHandler.msgState == UART_PRINTF) || (UARTx->msgTxdHandler.msgState == UART_DMA))
	{
		WDT_RESET();
	}
	//---���÷���״̬Ϊæµ״̬
	UARTx->msgTxdHandler.msgState = UART_BUSY;
	//---�������ݳ���
	memcpy(UARTx->msgTxdHandler.pMsgVal, pArrayVal, length);
	//---Ҫд�����ݵĸ���
	UARTx->msgTxdHandler.msgWIndex = length;
	//---����CRC����
	UART_CRCTask_Write(UARTx);
	//---�ж��Ƿ����ӻ��з�
	if ((UARTx->msgTxdHandler.msgAddNewLine == 1))
	{
		UART_FillMode_AddByte(UARTx, 0x0D);
		UART_FillMode_AddByte(UARTx, 0x0A);
	}
	UARTx->msgTxdHandler.msgCount = UARTx->msgTxdHandler.msgWIndex;
	//---����485Ϊ����ģʽ
	UART_485GPIOInit(UARTx, UART_485_TX_ENABLE);
	//---�л����Ͷ˿�Ϊ���ģʽ
	UART_TXGPIOInit(UARTx, UART_TXGPIO_SET_OUTPUT);
	//---У���ǲ���DMAģʽ
	if (UARTx->msgTxdHandler.msgDMAMode == 0)
	{
		//---�������ݼĴ������ж�ʹ��
		LL_USART_EnableIT_TXE(UARTx->msgUART);
	}
	else
	{
		//---�������ݵ�ַ
		UART_Write_DMA_SetMemoryAddress(UARTx, (UARTx->msgTxdHandler.pMsgVal));
		//---����DMA����
		UART_Write_DMA_RESTART(UARTx);
	}
	//---��λ��ʱ������
	UART_TimeTick_Init(&(UARTx->msgTxdHandler));
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ��ȡ�����־
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_GetOverFlow(UART_HandlerDef* UARTDefx)
{
	return UARTDefx->msgOverFlow ;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ��������־
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_ClearOverFlow(UART_HandlerDef* UARTDefx)
{
	UARTDefx->msgOverFlow = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ״̬��ʶ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_GetState(UART_HandlerDef* UARTDefx)
{
	return UARTDefx->msgState;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����״̬��ʶ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_ClearState(UART_HandlerDef* UARTDefx)
{
	UARTDefx->msgState = UART_OK;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���λ���ղ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_Read_Init(UART_HandlerType*  UARTx)
{
	//---����485λ����ģʽ
	UART_485GPIOInit(UARTx, UART_485_RX_ENABLE);
	//---���㲽��
	UARTx->msgRxdHandler.msgStep = 0;
	//---���д��������
	UARTx->msgRxdHandler.msgWIndex = 0;
	//---�������������
	UARTx->msgRxdHandler.msgRIndex = 0;
	//---����������ݸ���
	UARTx->msgRxdHandler.msgCount = 0;
	//---���������ɱ�־
	UARTx->msgRxdHandler.msgState = UART_BUSY;
	//---���㳬ʱ����
	UARTx->msgRxdHandler.msgRecordTick = 0;
	//---���㳬ʱ��־
	UARTx->msgRxdHandler.msgOverFlow = 0;
	//---У���ǲ���DMAģʽ
	if(UARTx->msgRxdHandler.msgDMAMode!=0)
	{
		UART_Read_DMA_RESTART(UARTx);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���λ���Ͳ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_Write_Init(UART_HandlerType*  UARTx)
{
	//---���÷���״̬Ϊ�������
	UARTx->msgTxdHandler.msgState = UART_OK;
	//---���д��������
	UARTx->msgTxdHandler.msgWIndex = 0;
	//---�������������
	UARTx->msgTxdHandler.msgRIndex = 0;
	//---���㷢�����ݸ���
	UARTx->msgTxdHandler.msgCount = 0;
	//---���㳬ʱ����
	UARTx->msgTxdHandler.msgRecordTick = 0;
	//---���㳬ʱ��־
	UARTx->msgTxdHandler.msgOverFlow = 0;
	//---�����������
	UARTx->msgTxdHandler.msgStep = 0;
	//---����485Ϊ����ģʽ
	UART_485GPIOInit(UARTx, UART_485_RX_ENABLE);
	//---���ݷ�����ɣ��л��˿�Ϊ����ģʽ
	UART_TXGPIOInit(UARTx, UART_TXGPIO_SET_INPUT);
	//---��¼������ɵ�ʱ��
	UARTx->msgTxdHandler.msgRecordTime = ((UARTx->msgTxdHandler.msgTimeTick != NULL) ? (UARTx->msgTxdHandler.msgTimeTick()) : 0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�У���豸��ID��Ϣ
//////�������:
//////�������:
//////˵		���� 
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
//////��		����
//////��		�ܣ�������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void UART_PrintfSuspend(UART_HandlerType* UARTx)
{
#ifdef USE_UART_PRINTF
	//---��鷢��״̬���ȴ�֮ǰ�����ݷ������;�����ǿ���״̬��������û���������ݷ�
	while ((UARTx->msgTxdHandler.msgState == UART_BUSY) || (UARTx->msgTxdHandler.msgState == UART_PRINTF)||(UARTx->msgTxdHandler.msgState == UART_DMA))
	{
		//--->>>�ǲ��Ƕ�������г�ʱ�쳣���������涨ʱ�䣬��û�з�����ɣ���ô����ǿ�Ʒ�����ɱ�ʶ������״̬
		WDT_RESET();
	}
	////---��鷢�ͼĴ������ж��Ƿ�ʹ��
	//if (LL_UART_IsEnabledIT_TXE(UARTx->msgUART))
	//{
	//	//---�ȴ��������
	//	while (LL_UART_IsActiveFlag_TXE(UARTx->msgUART) != RESET)
	//	{
	//		WDT_RESET();
	//	}
	//}
	////---��鷢������ж�
	//if (LL_UART_IsEnabledIT_TC(UARTx->msgUART))
	//{
	//	//---�ȴ��������
	//	while ((LL_UART_IsActiveFlag_TC(UARTx->msgUART) != RESET) && (UARTx->msgTxdHandler.msgStep == 0))
	//	{
	//		WDT_RESET();
	//	}
	//	LL_UART_ClearFlag_TC(UARTx->msgUART);
	//}
	//---����485Ϊ����ģʽ
	UART_485GPIOInit(UARTx, UART_485_TX_ENABLE);
	//---�л����Ͷ˿�Ϊ���ģʽ
	UART_TXGPIOInit(UARTx, UART_TXGPIO_SET_OUTPUT);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��ָ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void UART_PrintfResume(UART_HandlerType* UARTx)
{
#ifdef USE_UART_PRINTF
	//---����485Ϊ����ģʽ
	UART_485GPIOInit(UARTx, UART_485_RX_ENABLE);
	//---���ݷ�����ɣ��л��˿�Ϊ����ģʽ
	UART_TXGPIOInit(UARTx, UART_TXGPIO_SET_INPUT);
	//---��¼������ɵ�ʱ��
	UARTx->msgTxdHandler.msgRecordTime = ((UARTx->msgTxdHandler.msgTimeTick != NULL) ? (UARTx->msgTxdHandler.msgTimeTick()) : 0);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��Զ����Printf����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void UART_Printf(UART_HandlerType*UARTx, char*fmt, ...)
{
#ifdef USE_UART_PRINTF
	//---У�鴮���Ƿ��Ѿ���ʼ����
	if (UARTx->msgUART!=NULL)
	{
		//---����������ȴ���һ�εķ������
		UART_PrintfSuspend(UARTx);
		//---��������
		UINT16_T length = 0;
		//---�����Ǳ����������������������ı����������������������������ݵ�ƫ�ƻᷢ���쳣
		UINT16_T index = pPrintf->msgIndex;
		//---����һ��va_list�͵ı���,���������ָ�������ָ��
		va_list arg;
		//---��va_start���ʼ������,�����ĵڶ��������ǵ�һ���ɱ������ǰһ������,��һ���̶��Ĳ���
		va_start(arg, fmt);
		//---�������ַ����д�ӡ���ݡ����ݸ�ʽ�û��Զ���;���ز��������������ַ����ĳ���
		//length = (UINT16_T)vsnprintf(g_PrintfBuffer, UART_PRINTF_SIZE, fmt, arg_ptr);
		length = (UINT16_T)vsnprintf(&(pPrintf->pMsgVal[pPrintf->msgIndex]),(UART_PRINTF_SIZE- pPrintf->msgIndex), fmt, arg);
		//---��va_end������ɱ�����Ļ�ȡ
		va_end(arg);
		//---�ж�����
		if (length > (UART_PRINTF_SIZE - pPrintf->msgIndex))
		{
			length = UART_PRINTF_SIZE - pPrintf->msgIndex; //UART_PRINTF_SIZE;
			//---�����������ַ����㴦��
			pPrintf->msgIndex=0;
			return;
		}
		else
		{
		  	//---��������ƫ��
			pPrintf->msgIndex += length;
			//---���ٿ���64�ֽڵĻ�����
			if ((UART_PRINTF_SIZE- UART_PRINTF_IDLE_SIZE)<(pPrintf->msgIndex))
			{
				//---�����������ַ����㴦��
				pPrintf->msgIndex = 0;
			}
		}
		//---У���ǲ���DMAģʽ
		if (UARTx->msgTxdHandler.msgDMAMode!=0)
		{
			//--->>>DMA����ģʽ
			UARTx->msgTxdHandler.msgCount = length;
			//---�������ݵ�ַ
			UART_Write_DMA_SetMemoryAddress(UARTx, (UINT8_T*)(pPrintf->pMsgVal+index));
			//---����DMA����
			UART_Write_DMA_RESTART(UARTx);
		}
		else
		{
			//--->>>�жϷ���ģʽ
			//---Ҫ�������ݵĸ���
			UARTx->msgPCount = length;
			//---ʹ�õķ�������жϣ�������Ҫ���ȷ���һ������
			UARTx->msgPIndex = 1;
			//---������ʹ��PRINTFģʽ
			UARTx->msgTxdHandler.msgState = UART_PRINTF;
			//---�������,�������ݷ�������жϲ�ʹ��
			LL_USART_EnableIT_TC(UARTx->msgUART);
			//---����8Bit������
			LL_USART_TransmitData8(UARTx->msgUART, pPrintf->pMsgVal[index]);
		}
		//---��λ��ʱ������
		UART_TimeTick_Init(&(UARTx->msgTxdHandler));
	}
#endif	
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ӡLOG��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void UART_PrintfLog(UART_HandlerType* UARTx, char* fmt, va_list args)
{
	#ifdef USE_UART_PRINTF
	//---У�鴮���Ƿ��Ѿ���ʼ����
	if (UARTx->msgUART != NULL)
	{
		//---����������ȴ���һ�εķ������
		UART_PrintfSuspend(UARTx);
		//---��������
		UINT16_T length = 0;
		//---�����Ǳ����������������������ı����������������������������ݵ�ƫ�ƻᷢ���쳣
		UINT16_T index = pPrintf->msgIndex;
		//---�������ַ����д�ӡ���ݡ����ݸ�ʽ�û��Զ���;���ز��������������ַ����ĳ���
		//length = (UINT16_T)vsnprintf(g_PrintfBuffer, UART_PRINTF_SIZE, fmt, args);
		length = (UINT16_T)vsnprintf(&(pPrintf->pMsgVal[pPrintf->msgIndex]), (UART_PRINTF_SIZE - pPrintf->msgIndex), fmt, args);
		////---�ж�����
		//if (length > UART_PRINTF_SIZE)
		//{
		//	length = UART_PRINTF_SIZE;
		//}
		//---�ж�����
		if (length > (UART_PRINTF_SIZE - pPrintf->msgIndex))
		{
			length = UART_PRINTF_SIZE - pPrintf->msgIndex; //UART_PRINTF_SIZE;
			//---�����������ַ����㴦��
			pPrintf->msgIndex = 0;
			return;
		}
		else
		{
		  	//---��������ƫ��
			pPrintf->msgIndex += length;
			//---���ٿ���64�ֽڵĻ�����
			if ((UART_PRINTF_SIZE - UART_PRINTF_IDLE_SIZE) < (pPrintf->msgIndex))
			{
				//---�����������ַ����㴦��
				pPrintf->msgIndex = 0;
			}
		}
		//---У���ǲ���DMAģʽ
		if (UARTx->msgTxdHandler.msgDMAMode != 0)
		{
			//--->>>DMA����ģʽ
			UARTx->msgTxdHandler.msgCount = length;
			//---�������ݵ�ַ
			//UART_Write_DMA_SetMemoryAddress(UARTx, (UINT8_T*)g_PrintfBuffer);
			//---�������ݵ�ַ
			UART_Write_DMA_SetMemoryAddress(UARTx, (UINT8_T*)(pPrintf->pMsgVal + index));
			//---����DMA����
			UART_Write_DMA_RESTART(UARTx);
		}
		else
		{
			//--->>>�жϷ���ģʽ
			//---Ҫ�������ݵĸ���
			UARTx->msgPCount = length;
			//---ʹ�õķ�������жϣ�������Ҫ���ȷ���һ������
			UARTx->msgPIndex = 1;
			//---������ʹ��PRINTFģʽ
			UARTx->msgTxdHandler.msgState = UART_PRINTF;
			//---�������,�������ݷ�������жϲ�ʹ��
			LL_USART_EnableIT_TC(UARTx->msgUART);
			//---����8Bit������
			//LL_UART_TransmitData8(UARTx->msgUART, g_PrintfBuffer[0]);
			LL_USART_TransmitData8(UARTx->msgUART, pPrintf->pMsgVal[index]);
		}
		//---��λ��ʱ������
		UART_TimeTick_Init(&(UARTx->msgTxdHandler));
	}
	#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITPrintf_TCTask(UART_HandlerType* UARTx)
{
#ifdef USE_UART_PRINTF
	if (UARTx->msgPIndex>=UARTx->msgPCount)
	{
		//---�������,�������ݷ�������жϲ�ʹ��
		LL_USART_DisableIT_TC(UARTx->msgUART);
		//---�ָ�����
		UART_PrintfResume(UARTx);
		//---��ʶ�������
		UARTx->msgTxdHandler.msgState = UART_OK;
	}
	else
	{
		//---����8Bit������
		LL_USART_TransmitData8(UARTx->msgUART, g_PrintfBuffer[UARTx->msgPIndex]);
		UARTx->msgPIndex++;
	}
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��жϷ�����ɺ���
//////�������:
//////�������:
//////˵		����
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
//////��		����
//////��		�ܣ���ӡϵͳʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void UART_PrintfClockFreq(UART_HandlerType*UARTx)
{
	LL_RCC_ClocksTypeDef rccClock = { 0 };
	//---��ȡϵͳʱ��
	LL_RCC_GetSystemClocksFreq(&rccClock);
	//---��ӡϵͳʱ��
	UART_Printf(UARTx, "SYSCLK=%UHz\r\n", rccClock.SYSCLK_Frequency);
	//---��ӡϵͳʱ��
	UART_Printf(UARTx, "HCLK=%UHz\r\n", rccClock.HCLK_Frequency);
	//---��ӡϵͳʱ��
	UART_Printf(UARTx, "PCLK1=%UHz\r\n", rccClock.PCLK1_Frequency);
	//---��ӡϵͳʱ��
	UART_Printf(UARTx, "PCLK2=%UHz\r\n", rccClock.PCLK2_Frequency);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�UART������ʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_Clock(USART_TypeDef* UARTx, UINT8_T isEnable)
{
	#ifdef UART1
	if (UARTx == UART1)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---��ʹ��SPI��ʱ����
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_UART1);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
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
			//---��ʹ��SPI��ʱ����
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART2);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
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
			//---��ʹ��SPI��ʱ����
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART3);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
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
			//---��ʹ��SPI��ʱ����
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_UART6);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
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
			//---��ʹ��SPI��ʱ����
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART4);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
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
			//---��ʹ��SPI��ʱ����
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART5);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
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
			//---��ʹ��SPI��ʱ����
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART7);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
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
			//---��ʹ��SPI��ʱ����
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART8);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
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
			//---��ʹ��SPI��ʱ����
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_UART9);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
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
			//---��ʹ��SPI��ʱ����
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_UART10);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
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
//////��		����
//////��		�ܣ���������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_DeInit(UART_HandlerType*UARTx)
{
	LL_USART_DeInit(UARTx->msgUART);
	UART_Clock(UARTx->msgUART, 0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���������
//////�������:
//////�������:
//////˵		����
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
//////��		����
//////��		�ܣ��жϴ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////��
void UART_IRQTask(UART_HandlerType* UARTx)
{
	//---���ݽ����жϴ�����---���ռĴ�����Ϊ��
	if (LL_USART_IsActiveFlag_RXNE(UARTx->msgUART) && LL_USART_IsEnabledIT_RXNE(UARTx->msgUART))
	{
		//---�жϴ�����
		UART_ITRead_Task(UARTx, LL_USART_ReceiveData8(UARTx->msgUART));
		//---����жϱ�־λ
		LL_USART_ClearFlag_RXNE(UARTx->msgUART);
	}

	//---���ݷ��ͼĴ����շ����жϴ�����
	if (LL_USART_IsActiveFlag_TXE(UARTx->msgUART) && LL_USART_IsEnabledIT_TXE(UARTx->msgUART))
	{
		//---�жϴ�����
		UART_ITWrite_TXETask(UARTx);
	}
	//---���ݷ�������жϴ�����
	if (LL_USART_IsActiveFlag_TC(UARTx->msgUART) && LL_USART_IsEnabledIT_TC(UARTx->msgUART))
	{
		//---�жϴ�����
		UART_IT_TCTask(UARTx);
		//---����жϱ�־λ
		LL_USART_ClearFlag_TC(UARTx->msgUART);
	}
	//---UART5��UART5��������CTS���
	if ((UARTx->msgUART!=UART4)&& (UARTx->msgUART != UART5))
	{
		//---CTS״̬�߱仯�ж�
		if (LL_USART_IsActiveFlag_nCTS(UARTx->msgUART) && LL_USART_IsEnabledIT_CTS(UARTx->msgUART))
		{
			//---�жϴ�����

			//---����жϱ�־λ
			LL_USART_ClearFlag_nCTS(UARTx->msgUART);
		}
	}
	//---LIN��·����ж�
	if (LL_USART_IsActiveFlag_LBD(UARTx->msgUART) && LL_USART_IsEnabledIT_LBD(UARTx->msgUART))
	{
		//---�жϴ�����

		//---����жϱ�־λ
		LL_USART_ClearFlag_LBD(UARTx->msgUART);
	}
	//---����״̬�жϣ���Ҫ������DMA���ղ���������
	if (LL_USART_IsActiveFlag_IDLE(UARTx->msgUART) && LL_USART_IsEnabledIT_IDLE(UARTx->msgUART))
	{
		//---�жϴ�����,DMA���ݽ���
		UART_DMA_IDLETask(UARTx);
		//---��������жϱ�־λ
		LL_USART_ClearFlag_IDLE(UARTx->msgUART);
		//---���DMA�жϱ�ʶ
		LL_DMA_ClearFlag(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
	}
	//---��������ж�
	if (LL_USART_IsActiveFlag_ORE(UARTx->msgUART) && LL_USART_IsEnabledIT_ERROR(UARTx->msgUART))
	{
		//---�жϴ�����

		//---����жϱ�־λ
		LL_USART_ClearFlag_ORE(UARTx->msgUART);
	}
	//---�����ж�
	if (LL_USART_IsActiveFlag_NE(UARTx->msgUART) && LL_USART_IsEnabledIT_ERROR(UARTx->msgUART))
	{
		//---�жϴ�����

		//---����жϱ�־λ
		LL_USART_ClearFlag_NE(UARTx->msgUART);
	}
	//---֡�����ж�
	if (LL_USART_IsActiveFlag_FE(UARTx->msgUART) && LL_USART_IsEnabledIT_ERROR(UARTx->msgUART))
	{
		//---�жϴ�����

		//---����жϱ�־λ
		LL_USART_ClearFlag_FE(UARTx->msgUART);
	}
	//---��żУ���ж�
	if (LL_USART_IsActiveFlag_PE(UARTx->msgUART) && LL_USART_IsEnabledIT_PE(UARTx->msgUART))
	{
		//---�жϴ�����

		//---����жϱ�־λ
		LL_USART_ClearFlag_PE(UARTx->msgUART);
	}
}

////////////////////////////////////////////////////////////////////////////////
////DMAģʽ����
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��ر�DMA�Ľ���ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT16_T UART_Read_DMA_STOP(UART_HandlerType* UARTx)
{
#ifdef USE_MCU_STM32F1
	//---ʹ��DMA
	LL_DMA_DisableChannel(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream);
	LL_DMA_ClearFlag_GI1(UARTx->msgRxHandler.msgDMA);
#else
	//---��ʹ��DMA
	LL_DMA_DisableStream(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
#endif
	LL_DMA_ClearFlag(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
	//---����������ݵĳ���
	UINT16_T length = UARTx->msgRxdHandler.msgMaxSize - LL_DMA_GetDataLength(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
	return length;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����DMA�Ľ���ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_Read_DMA_RESTART(UART_HandlerType* UARTx)
{
	//---����DMA��ȡ���ݵĴ�С
	LL_DMA_SetDataLength(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream, UARTx->msgRxdHandler.msgMaxSize);
	//---ʹ��DMA
#ifdef USE_MCU_STM32F1
	//---ʹ��DMA
	LL_DMA_EnableChannel(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
#else
	//---ʹ��DMA
	LL_DMA_EnableStream(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����DMA����ģʽ�£����ݴ洢�ĵ�ַ
//////�������:
//////�������:
//////˵		����
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
//////��		����
//////��		�ܣ�ֹͣDMA�ķ���ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT16_T UART_Write_DMA_STOP(UART_HandlerType* UARTx)
{
#ifdef USE_MCU_STM32F1
	//---ʹ��DMA
	LL_DMA_DisableChannel(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream);
	LL_DMA_ClearFlag_GI1(UARTx->msgRxHandler.msgDMA);
#else
	//---��ʹ��DMA
	LL_DMA_DisableStream(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream);
#endif
	LL_DMA_ClearFlag(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream);
	//---����������ݵĳ���
	UINT16_T length = UARTx->msgTxdHandler.msgMaxSize - LL_DMA_GetDataLength(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream);
	return length;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����DMA�ķ���ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_Write_DMA_RESTART(UART_HandlerType* UARTx)
{
	//---����DMA�������ݵĴ�С
	LL_DMA_SetDataLength(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream, UARTx->msgTxdHandler.msgCount);
#ifdef USE_MCU_STM32F1
	//---ʹ��DMA
	LL_DMA_EnableChannel(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream);
#else
	//---ʹ��DMA
	LL_DMA_EnableStream(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream);
#endif
	//---����ΪDMA״̬
	UARTx->msgTxdHandler.msgState= UART_DMA;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_DMA_IDLETask(UART_HandlerType* UARTx)
{
	UINT8_T _return = OK_0;
	//---ֹͣ����DMAģʽ,����ȡ�������ݵĳ���
	UINT16_T dataLength= UART_Read_DMA_STOP(UARTx);
	//---У�鱨ͷ�Ƿ���ȷ
	if (UARTx->msgRxdHandler.pMsgVal[0] == UARTx->msgRxdID)
	{
		//---���ݳ�����Ϣ
		UINT16_T length = UARTx->msgRxdHandler.pMsgVal[1];
		//---У�����ݳ�����Ϣ
		if (UARTx->msgRxdHandler.msgMaxSize < 0xFF)
		{
			length += 2;
		}
		else
		{
			length = (length << 8) + UARTx->msgRxdHandler.pMsgVal[1];
			length += 3;
		}
		//---У�������Ƿ�Ϸ�
		if (length == dataLength)
		{
			UARTx->msgRxdHandler.msgState = UART_OK;
			UARTx->msgRxdHandler.msgCount=dataLength;
		}
		else
		{
			//---���ݲ����Ϲ���ʹ�����½���
			UART_Read_Init(UARTx);
			//---���ش�����Ϣ
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
//////��		����
//////��		�ܣ������ж�DMA�������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void UART_Read_DMA_IRQTask(UART_HandlerType* UARTx)
{
	//---DMA����ģʽ
	UART_DMA_IDLETask(UARTx);
	//---��������жϱ�־λ
	LL_USART_ClearFlag_IDLE(UARTx->msgUART);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ж�DMA�������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void UART_Write_DMA_IRQTask(UART_HandlerType* UARTx)
{
#ifdef USE_MCU_STM32F1
	//---��ʹ��DMA
	LL_DMA_DisableChannel(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream;
	LL_DMA_ClearFlag_GI1(UARTx->msgTxHandler.msgDMA);
#else
	//---��ʹ��DMA
	LL_DMA_DisableStream(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream);
#endif
	//---�����ʶ
	LL_DMA_ClearFlag(UARTx->msgTxdHandler.msgDMA, UARTx->msgTxdHandler.msgDMAChannelOrStream);
	//---���㷢��
	//UART_Write_Init(UARTx);
	//---ʹ�ܷ�������жϣ������л�TXD�˿�Ϊ����״̬
	LL_USART_EnableIT_TC(UARTx->msgUART);
}

