#ifndef UART_CFG_H_
#define UART_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	#include "crc_task.h"
	#include "dma_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置参数---开始////////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===传输过程中判断判断是否需要初始化GPIO
	#define  UART_INIT_GPIO
	//===是否重映射printf函数
	#define  USE_UART_PRINTF	
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////配置参数---结束////////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////结构体定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===数据结构体
	typedef struct _UART_HandlerType			UART_HandlerType;
	typedef struct _UART_HandlerType			* pUART_HandlerType;
	//===数据结构体
	typedef struct _UART_HandlerDef				UART_HandlerDef;
	typedef struct _UART_HandlerDef				*pUART_HandlerDef;
	//===接收数据结构体
	typedef struct _UART_HandlerDef				UART_RXDHandlerType;
	typedef struct _UART_HandlerDef				*pUART_RXDHandlerType;
	//===发送数据结构体
	typedef struct _UART_HandlerDef				UART_TXDHandlerType;
	typedef struct _UART_HandlerDef				*pUART_TXDHandlerType;
	//===串口数据结构体定义
	struct _UART_HandlerDef
	{
		UINT8_T									msgDMAMode;																//---是否是DMA模式，0---非DMA模式，1---DMA模式
		VLTUINT8_T								msgCheckSum;															//---校验和
		VLTUINT8_T								msgCRCFlag;																//---校验标志位  0 ---无校验，1 ---校验和，2---CRC8校验，3---CRC16校验，4---CRC32校验
		VLTUINT8_T								msgState;																//---判断任务是否结束 0---未结束，1---结束
		VLTUINT8_T								msgStep;																//---步序
		VLTUINT8_T								msgAddNewLine;															//---是否需要换行符(\r\n)
		VLTUINT16_T								msgWIndex;																//---写序号
		VLTUINT16_T								msgRIndex;																//---读序号
		VLTUINT16_T								msgCount;																//---读写数据的长度
		VLTUINT16_T								msgFlagIndex;															//---执行结果的标识号，在数据缓存区的位置信息
		VLTUINT16_T								msgMaxSize;																//---数据缓存区的大小
		VLTUINT8_T								msgOverFlow;															//---超时标志位
		VLTUINT32_T								msgRecordTick;															//---超时时间节拍
		VLTUINT32_T								msgRecordTime;															//---超时时间记录时间
		VLTUINT32_T								msgMaxTime;																//---超时时间
		UINT8_T									*pMsgVal;																//---缓存区(需要提前定义好数据的缓存区)
		DMA_TypeDef								*msgDMA;																//---DMA号
		UINT32_T								msgDMAChannelOrStream;													//---DMA通道号或者流信息
		UINT32_T(*msgTimeTick)(void);																					//---用于超时计数
	};	
	//===串口数据定义
	struct _UART_HandlerType
	{
		#ifdef USE_UART_PRINTF
			UINT16_T							msgPCount;															//---打印发送总数
			UINT16_T							msgPIndex;															//---打印发送序号
		#endif
		UINT8_T									msgIndex;																//---UART端口的索引号
		UINT8_T									msgRxdID;																//---接收报头
		UINT8_T									msgTxdID;																//---发送报头
		UINT8_T									msgID;																	//---设备ID
		UINT8_T									msgIDIndex;																//---设备ID在数组中的位置
		UINT8_T									msgCmdIndex;															//---命令在数组中的位置
		UINT8_T									msgDataOneIndex;														//---数据1在数组中的位置
		UINT8_T									msgDataTwoIndex;														//---数据2在数组中的位置
		UINT8_T									msgIndexOffset;															//---索引的偏移量
		GPIO_HandlerType						msgTxPort;																//---UART的GPIO端口号
		GPIO_HandlerType						msg485Port;																//---485的使能GPIO端口
		USART_TypeDef							*msgUART;																//---UART端口
		UART_TXDHandlerType						msgTxdHandler;															//---发送函数
		UART_RXDHandlerType						msgRxdHandler;															//---接收函数
	};
	//===printf数据结构体
	typedef struct _UART_PrintfType				UART_PrintfType;
	typedef struct _UART_PrintfType				*pUART_PrintfType;
	//===Printf打印数据定义
	struct _UART_PrintfType
	{
		UINT16_T								msgIndex;																//---发送索引
		char									* pMsgVal;																//---缓存区(需要提前定义好数据的缓存区)
	};
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////结构体定义---结束//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置宏定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===重映射printf之后的数据缓存区
	#ifdef USE_UART_PRINTF
		#define UART_PRINTF_SIZE					512																	//---使用printf的时候的缓存区的大小
		#define UART_PRINTF_IDLE_SIZE				64																	//---printf的最小保留缓存区的大小
	#endif	
	//===使用的校验方式
	#define UART_CRC_NONE							0
	#define UART_CRC_CHECKSUM						1
	
	//===自适应CRC校验等级
	#ifdef USE_CRC8
		#define UART_CRC_CRC8						2
	#elif defined(UART_CRC_CHECKSUM)
		#define UART_CRC_CRC8						UART_CRC_CHECKSUM
	#else
		#define UART_CRC_CRC8						UART_CRC_NONE
	#endif
	
	#ifdef USE_CRC16
		#define UART_CRC_CRC16						3
	#elif defined(UART_CRC_CHECKSUM)
		#define UART_CRC_CRC16						UART_CRC_CHECKSUM
	#else
		#define UART_CRC_CRC16						UART_CRC_NONE
	#endif
	
	#ifdef USE_CRC32
		#define UART_CRC_CRC32						4
	#elif defined(UART_CRC_CHECKSUM)
		#define UART_CRC_CRC32						UART_CRC_CHECKSUM
	#else
		#define UART_CRC_CRC32						UART_CRC_NONE
	#endif	
	//===发送端口的配置
	#define UART_TXGPIO_SET_INPUT					0																	//---轮训地址时候，发送端口需要切换为输入
	#define UART_TXGPIO_SET_OUTPUT					1																	//---轮训地址时候，发送端口需要切换为输出
	//===485数据端口的控制使能
	#define UART_485_RX_ENABLE						0																	//---485模式下处于数据接收
	#define UART_485_TX_ENABLE						1																	//---485模式下处于数据发送
	//===串口的状态
	#define UART_BUSY								0																	//---串口忙碌状态
	#define UART_OK									1																	//---串口空闲状态	
	#define UART_ERROR								2																	//---串口错误状态
	#define UART_PRINTF								3																	//---使用Printf传输数据中
	#define UART_DMA								4																	//---串口DMA状态
	#define UART_IT_IDLE							5																	//---串口中断空闲状态

	//===定义的任务函数
	#define UART_TASK_ONE							pUart1																//---UART1的任务
	#define UART_TASK_TWO							0																	//---UART2的任务
	#define UART_TASK_THREE							pUart3																	//---UART3的任务
	#define UART_TASK_FOUR							0																	//---UART4的任务
	#define UART_TASK_FIVE							0																	//---UART5的任务
	#define UART_TASK_SIX							0																	//---UART6的任务
	#define UART_TASK_SEVEN							0																	//---UART7的任务
	#define UART_TASK_EIGHT							0																	//---UART8的任务
	#define UART_TASK_NINE							0																	//---UART9的任务
	#define UART_TASK_TEN							0																	//---UART10的任务	
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////配置宏定义---结束////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////

	//===外部调用接口
	extern UART_HandlerType							g_Uart1;
	extern pUART_HandlerType						pUart1;

	extern UART_HandlerType							g_Uart3;
	extern pUART_HandlerType						pUart3;

	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////串口1的配置参数开始//////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	//===定义缓存区的大小
	#define UART1_RX_BASE_SIZE						64//1800
	#define UART1_TX_BASE_SIZE						UART1_RX_BASE_SIZE	
	//===定义设备的地址，多设备的时候使用，0的时候是一对一
	#define UART1_DEVICE_ID						0x00
	
	//===配置设备ID的索引
	#if (UART1_DEVICE_ID!=0)
		#define	UART1_DEVICE_ID_INDEX				1
	#else
		#define	UART1_DEVICE_ID_INDEX				0
	#endif
	
	//===定义了CRC使用的最大缓存区,这样便于更换CRC校验的格式
	#if defined(USE_CRC32)
		#define UART1_RX_MAX_SIZE					( UART1_RX_BASE_SIZE+4 )
	#elif defined(USE_CRC16
		#define UART1_RX_MAX_SIZE					( UART1_RX_BASE_SIZE+2 )
	#elif defined(USE_CRC8)||defined(USE_CHECKSUM)
		#define UART1_RX_MAX_SIZE					( UART1_RX_BASE_SIZE+1 )
	#else
		#define UART1_RX_MAX_SIZE					( UART1_RX_BASE_SIZE )
	#endif
	
	//===定义了CRC使用的最大缓存区,这样便于更换CRC校验的格式
	#if defined(USE_CRC32)
		#define UART1_TX_MAX_SIZE					( UART1_TX_BASE_SIZE+4 )
	#elif defined(USE_CRC16)
		#define UART1_TX_MAX_SIZE					( UART1_TX_BASE_SIZE+2 )
	#elif defined(USE_CRC8)||defined(USE_CHECKSUM)
		#define UART1_TX_MAX_SIZE					( UART1_TX_BASE_SIZE+1 )
	#else
		#define UART1_TX_MAX_SIZE					( UART1_TX_BASE_SIZE )
	#endif
	
	//===解析命令中的含义
	#if (UART1_RX_MAX_SIZE>0xFB)	
		//===设备地址在命令中的位置
		#define UART1_ID_INDEX						3		
		//===协议中的命令1---主命令
		#define UART1_CMD_INDEX					( UART1_ID_INDEX+UART1_DEVICE_ID_INDEX)		
		//===协议中的命令2---子命令
		#define UART1_DATA1_INDEX					( UART1_CMD_INDEX+1 )		
		//===数据返回的值---对接收无效，对发送有效
		#define UART1_DATA2_INDEX					( UART1_CMD_INDEX+2 )
	#else	
		//===设备地址在命令中的位置
		#define UART1_ID_INDEX						2		
		//===协议中的命令1---主命令
		#define UART1_CMD_INDEX					( UART1_ID_INDEX+UART1_DEVICE_ID_INDEX)		
		//===协议中的命令2---子命令或则第一个数据
		#define UART1_DATA1_INDEX					( UART1_CMD_INDEX+1 )		
		//===协议中的第一个数据或则第二数据
		#define UART1_DATA2_INDEX					( UART1_CMD_INDEX+2 )
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////串口1的配置参数结束//////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////

	//===函数定义
	UINT8_T  UART_StructInit(UART_HandlerType*  UARTx);
	UINT8_T  UART_ConfigInit(UART_HandlerType* UARTx, UART_HandlerType* UARTInitx);
	UINT8_T  UART_Init(UART_HandlerType*  UARTx, UINT16_T rxSize, UINT8_T* pRxVal, UINT8_T rxCRCFlag, UINT16_T txSize, UINT8_T* pTxVal, UINT8_T txCRCFlag, UINT32_T(*pTimerTick)(void));
	UINT8_T  UART_TXGPIOInit(UART_HandlerType*  UARTx, UINT8_T isInput);
	UINT8_T  UART_485GPIOInit(UART_HandlerType*  UARTx, UINT8_T isEnable);
	UINT8_T  UART_SetCRC(UART_HandlerDef* UARTDefx, UINT8_T crcFlag);
	UINT8_T  UART_GetCRC(UART_HandlerDef* UARTDefx);
	UINT8_T  UART_TimeTick_Init(UART_HandlerDef* UARTDefx);
	UINT8_T  UART_TimeTick_DeInit(UART_HandlerDef* UARTDefx);
	UINT8_T  UART_TimeTick_OverFlow(UART_HandlerDef* UARTDefx);
	UINT8_T  UART_TimeTask_OverFlow(UART_HandlerType*UARTx, UINT8_T isRx);
	UINT8_T  UART_ITRead_8BitsTask(UART_HandlerType*UARTx, UINT8_T val);
	UINT8_T  UART_ITRead_16BitsTask(UART_HandlerType*UARTx, UINT8_T val);
	UINT8_T  UART_ITRead_Task(UART_HandlerType*UARTx, UINT8_T val);
	UINT8_T  UART_GetOverFlow(UART_HandlerDef* UARTDefx);
	UINT8_T  UART_ClearOverFlow(UART_HandlerDef* UARTDefx);
	UINT8_T  UART_PollMode_WriteByte(UART_HandlerType*UARTx, UINT8_T  val);
	UINT8_T  UART_PollMode_WriteData(UART_HandlerType*UARTx, char *pVal);
	UINT8_T  UART_PollMode_ReadByte(UART_HandlerType*UARTx);
	UINT8_T  UART_PollMode_ReadData(UART_HandlerType*UARTx, char *pVal);
	UINT8_T  UART_ITWrite_TXETask(UART_HandlerType*UARTx);
	UINT8_T  UART_ITWrite_TCTask(UART_HandlerType*UARTx);
	UINT8_T  UART_RealTime_AddByte(UART_HandlerType*UARTx, UINT8_T val);
	UINT8_T  UART_RealTime_AddSize(UART_HandlerType*UARTx, UINT16_T val);
	UINT8_T  UART_RealTime_AddCRC(UART_HandlerType*UARTx);
	UINT8_T  UART_FillMode_Init( UART_HandlerType*UARTx, UINT8_T isChildCmd);
	UINT8_T  UART_FillMode_AddByte(UART_HandlerType*UARTx, UINT8_T val);
	UINT8_T  UART_FillMode_AddData(UART_HandlerType*UARTx, UINT8_T *pVal, UINT16_T length);
	UINT8_T	 UART_FillMode_SetResultFlag(UART_HandlerType* UARTx, UINT8_T val);
	UINT8_T  UART_FillMode_AddIndexW(UART_HandlerType* UARTx, UINT16_T val);
	UINT8_T  UART_CRCTask_Read(UART_HandlerType*UARTx);
	UINT8_T  UART_CRCTask_Write(UART_HandlerType*UARTx);
	UINT8_T  UART_FillMode_WriteByteSTART(UART_HandlerType*UARTx, UINT8_T isNeedID);
	UINT8_T  UART_FillMode_WriteArraySTART(UART_HandlerType* UARTx, UINT8_T* pArrayVal, UINT16_T length);
	UINT8_T  UART_GetState(UART_HandlerDef* UARTDefx);
	UINT8_T  UART_ClearState(UART_HandlerDef* UARTDefx);
	UINT8_T  UART_Read_Init(UART_HandlerType*  UARTx);
	UINT8_T  UART_Write_Init(UART_HandlerType*  UARTx);
	UINT8_T  UART_DeviceID(UART_HandlerType*UARTx);
	void     UART_Printf(UART_HandlerType*UARTx, char*fmt, ...);
	void	 UART_PrintfLog(UART_HandlerType* UARTx, char* fmt, va_list args);
	UINT8_T  UART_IT_TCTask(UART_HandlerType* UARTx);
	void	 UART_PrintfClockFreq(UART_HandlerType*UARTx);
	UINT8_T  UART_Clock(USART_TypeDef* UARTx, UINT8_T isEnable);
	UINT8_T  UART_DeInit(UART_HandlerType*UARTx);
	UINT8_T  UART_ParamInit(UART_HandlerType *UARTx, UINT8_T id, UINT8_T idIndex, UINT8_T cmdIndex, UINT8_T d1Index, UINT8_T d2Index);
	UINT8_T  UART1_Init(UART_HandlerType*UARTx);
	UINT8_T  UART2_Init(UART_HandlerType*UARTx);
	UINT8_T  UART3_Init(UART_HandlerType*UARTx);
	void	 UART_IRQTask(UART_HandlerType* UARTx);

	//===函数定义
	UINT8_T	 UART1_Read_DMA_Init(UART_HandlerType* UARTx);
	UINT8_T  UART1_Write_DMA_Init(UART_HandlerType* UARTx);
	UINT16_T UART_Read_DMA_STOP(UART_HandlerType* UARTx);
	UINT8_T  UART_Write_DMA_SetMemoryAddress(UART_HandlerType* UARTx, UINT8_T* pVal);
	UINT8_T  UART_Read_DMA_RESTART(UART_HandlerType* UARTx);
	UINT16_T UART_Write_DMA_STOP(UART_HandlerType* UARTx);
	UINT8_T  UART_Write_DMA_RESTART(UART_HandlerType* UARTx);
	UINT8_T  UART_DMA_IDLETask(UART_HandlerType* UARTx);
	void	 UART_Read_DMA_IRQTask(UART_HandlerType* UARTx);
	void	 UART_Write_DMA_IRQTask(UART_HandlerType* UARTx);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*UART_CFG_H_ */
