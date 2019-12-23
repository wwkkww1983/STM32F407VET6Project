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

		PRIVATEE0			= 0x08,																	//---ǿ�ƶϵ�
		PRIVATEE1			= 0x09,																	//---����
		PRIVATEE2			= 0x0A,																	//---ָ��ִ��
		PRIVATEE3			= 0x0B,																	//---����OCD�Ĵ���
	}JTAG_CMD;

	//===����ṹ��
	typedef struct _JTAG_HandlerType			JTAG_HandlerType;
	//===����ָ��ṹ��
	typedef struct _JTAG_HandlerType			* pJTAG_HandlerType;
	//===�ṹ�����
	struct _JTAG_HandlerType
	{
		UINT8_T				msgJtagState;															//---��ǰjtag��״̬
		GPIO_HandlerType	msgTDI;																	//---TDIʹ�õĶ˿�
		GPIO_HandlerType	msgTDO;																	//---TDOʹ�õĶ˿�
		GPIO_HandlerType	msgTCK;																	//---TCKʹ�õĶ˿�
		GPIO_HandlerType	msgTMS;																	//---TMSʹ�õĶ˿�
		GPIO_HandlerType	msgRST;																	//---RSTʹ�õĶ˿�,Ӳ����λ�˿�
		UINT16_T			msgPluseWidth;															//---�Ǳ��״̬��TCK��������
		void(*msgFuncDelayus)(UINT32_T delay);														//---��ʱ����
		SPI_HandlerType msgSPI;																		//---ʹ�õ�SPIģʽ
	};

	//===������
	#define JTAG_TASK_ONE						pISPDevice0
	#define JTAG_TASK_TWO						0
	#define JTAG_TASK_THREE						0

	//===�ⲿ���ýӿ�
	extern JTAG_HandlerType						g_JtagDevice0;
	extern pJTAG_HandlerType					pJtagDevice0;

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*JTAG_CFG_H_ */