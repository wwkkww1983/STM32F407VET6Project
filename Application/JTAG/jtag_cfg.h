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

	//===�����Ƿ�ʹ�õ�ƽת��оƬ����OE���ƶ˵�
	#define JTAG_USE_lEVEL_SHIFT 	

	//===JTAG��GPIO�Ĳ�������
	#define	JTAG_GPIO_STATE(tp)					GPIO_GET_STATE(tp.msgGPIOPort,tp.msgGPIOBit)
	#define	JTAG_GPIO_1(tp)						GPIO_OUT_1(tp.msgGPIOPort,tp.msgGPIOBit)
	#define	JTAG_GPIO_0(tp)						GPIO_OUT_0(tp.msgGPIOPort,tp.msgGPIOBit)
	//===TCK��������
	#define JTAG_TCK_PULSE(tck)					(	JTAG_GPIO_1(tck->msgTCK),\
													tck->msgDelayus(tck->msgPluseWidth),\
													JTAG_GPIO_0(tck->msgTCK),\
													tck->msgDelayus(tck->msgPluseWidth) \
												)

	//===TAP������״̬
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

	//===JTAG��Դָ��
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
	}TAP_CMD;

	//===����ṹ��
	typedef struct _JTAG_HandlerType			JTAG_HandlerType;
	//===����ָ��ṹ��
	typedef struct _JTAG_HandlerType			* pJTAG_HandlerType;
	//===�ṹ�����
	struct _JTAG_HandlerType
	{
		TAP_STATE			msgTapState;															//---��ǰjtag��״̬
		UINT8_T				msgWaitms;																//---���֮�����ʱ��������λ��ms
		GPIO_HandlerType	msgTDI;																	//---TDIʹ�õĶ˿�
		GPIO_HandlerType	msgTDO;																	//---TDOʹ�õĶ˿�
		GPIO_HandlerType	msgTCK;																	//---TCKʹ�õĶ˿�
		GPIO_HandlerType	msgTMS;																	//---TMSʹ�õĶ˿�
		GPIO_HandlerType	msgRST;																	//---RSTʹ�õĶ˿�,Ӳ����λ�˿�
	#ifdef JTAG_USE_lEVEL_SHIFT
		GPIO_HandlerType	msgOE;																	//---OEʹ�õĶ˿ڣ����ڿ��Ƶ�ƽװ���Ŀ���
	#endif
		UINT16_T			msgPluseWidth;															//---�Ǳ��״̬��TCK��������
		void(*msgDelayus)(UINT32_T delay);															//---us��ʱ����
		void(*msgDelayms)(UINT32_T delay);															//---ms��ʱ����
		//SPI_HandlerType msgSPI;																	//---ʹ�õ�SPIģʽ
	};

	//===������
	#define JTAG_TASK_ONE						pJtagDevice0
	#define JTAG_TASK_TWO						0
	#define JTAG_TASK_THREE						0

	//===�ⲿ���ýӿ�
	extern JTAG_HandlerType						g_JtagDevice0;
	extern pJTAG_HandlerType					pJtagDevice0;

	//===��������
	UINT8_T JTAG_Init(JTAG_HandlerType* JTAGx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void));

	UINT32_T JTAG_ReadIDChip(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T isRunAvrReset);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*JTAG_CFG_H_ */