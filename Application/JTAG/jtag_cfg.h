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
	}JTAG_STATE;

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
	}JTAG_CMD;

	//===定义结构体
	typedef struct _JTAG_HandlerType			JTAG_HandlerType;
	//===定义指针结构体
	typedef struct _JTAG_HandlerType			* pJTAG_HandlerType;
	//===结构体变量
	struct _JTAG_HandlerType
	{
		UINT8_T				msgJtagState;															//---当前jtag的状态
		GPIO_HandlerType	msgTDI;																	//---TDI使用的端口
		GPIO_HandlerType	msgTDO;																	//---TDO使用的端口
		GPIO_HandlerType	msgTCK;																	//---TCK使用的端口
		GPIO_HandlerType	msgTMS;																	//---TMS使用的端口
		GPIO_HandlerType	msgRST;																	//---RST使用的端口,硬件复位端口
		UINT16_T			msgPluseWidth;															//---非编程状态下TCK的脉冲宽度
		void(*msgFuncDelayus)(UINT32_T delay);														//---延时参数
		SPI_HandlerType msgSPI;																		//---使用的SPI模式
	};

	//===任务函数
	#define JTAG_TASK_ONE						pISPDevice0
	#define JTAG_TASK_TWO						0
	#define JTAG_TASK_THREE						0

	//===外部调用接口
	extern JTAG_HandlerType						g_JtagDevice0;
	extern pJTAG_HandlerType					pJtagDevice0;

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*JTAG_CFG_H_ */