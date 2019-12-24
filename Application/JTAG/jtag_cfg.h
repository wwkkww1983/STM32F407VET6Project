#ifndef JTAG_CFG_H_
#define JTAG_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	#include "spi_task.h"
	//////////////////////////////////////////////////////////////////////////////////////

	//===定义是否使用电平转换芯片，带OE控制端的
	#define JTAG_USE_lEVEL_SHIFT 	

	//===JTAG的GPIO的操作定义
	#define	JTAG_GPIO_STATE(tp)					GPIO_GET_STATE(tp.msgGPIOPort,tp.msgGPIOBit)
	#define	JTAG_GPIO_1(tp)						GPIO_OUT_1(tp.msgGPIOPort,tp.msgGPIOBit)
	#define	JTAG_GPIO_0(tp)						GPIO_OUT_0(tp.msgGPIOPort,tp.msgGPIOBit)
	//===TCK的脉冲宽度
	#define JTAG_TCK_PULSE(tck)					(	JTAG_GPIO_1(tck->msgTCK),\
													tck->msgDelayus(tck->msgPluseWidth),\
													JTAG_GPIO_0(tck->msgTCK),\
													tck->msgDelayus(tck->msgPluseWidth) \
												)

	//===TAP的运行状态
	typedef enum
	{
		TEST_LOGIC_RESET	= 0,
		RUN_TEST_IDLE		= 1,

		SELECT_DR_SCAN		= 2,
		CAPTURE_DR			= 3,
		SHIFT_DR			= 4,
		EXIT1_DR			= 5,
		PAUSE_DR			= 6,
		EXIT2_DR			= 7,
		UPDATE_DR			= 8,

		SELECT_IR_SCAN		= 12,
		CAPTURE_IR			= 13,
		SHIFT_IR			= 14,
		EXIT1_IR			= 15,
		PAUSE_IR			= 16,
		EXIT2_IR			= 17,
		UPDATE_IR			= 18,
	}TAP_STATE;

	//===JTAG开源指令
	typedef enum
	{
		EXTEST				= 0x00,
		IDCODE				= 0x01,
		SAMPLE				= 0x02,
		AVR_RESET			= 0x0C,
		BYPASS				= 0x0F,
		PROG_ENABLE			= 0x04,
		PROG_COMMANDS		= 0x05,
		PROG_PAGELOAD		= 0x06,
		PROG_PAGEREAD		= 0x07,

		PRIVATEE0			= 0x08,																	//---强制断点
		PRIVATEE1			= 0x09,																	//---运行
		PRIVATEE2			= 0x0A,																	//---指令执行
		PRIVATEE3			= 0x0B,																	//---访问OCD寄存器
	}TAP_CMD;

	//===定义结构体
	typedef struct _JTAG_HandlerType			JTAG_HandlerType;
	//===定义指针结构体
	typedef struct _JTAG_HandlerType			* pJTAG_HandlerType;
	//===结构体变量
	struct _JTAG_HandlerType
	{
		TAP_STATE			msgTapState;															//---当前jtag的状态
		UINT8_T				msgWaitms;																//---编程之后的延时函数，单位是ms
		GPIO_HandlerType	msgTDI;																	//---TDI使用的端口
		GPIO_HandlerType	msgTDO;																	//---TDO使用的端口
		GPIO_HandlerType	msgTCK;																	//---TCK使用的端口
		GPIO_HandlerType	msgTMS;																	//---TMS使用的端口
		GPIO_HandlerType	msgRST;																	//---RST使用的端口,硬件复位端口
	#ifdef JTAG_USE_lEVEL_SHIFT
		GPIO_HandlerType	msgOE;																	//---OE使用的端口，用于控制电平装换的开关
	#endif
		UINT16_T			msgPluseWidth;															//---非编程状态下TCK的脉冲宽度
		void(*msgDelayus)(UINT32_T delay);															//---us延时参数
		void(*msgDelayms)(UINT32_T delay);															//---ms延时参数
		//SPI_HandlerType msgSPI;																	//---使用的SPI模式
	};

	//===任务函数
	#define JTAG_TASK_ONE						pJtagDevice0
	#define JTAG_TASK_TWO						0
	#define JTAG_TASK_THREE						0

	//===外部调用接口
	extern JTAG_HandlerType						g_JtagDevice0;
	extern pJTAG_HandlerType					pJtagDevice0;

	//===函数定义
	UINT8_T JTAG_Init(JTAG_HandlerType* JTAGx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void));

	UINT32_T JTAG_ReadIDChip(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T isRunAvrReset);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*JTAG_CFG_H_ */