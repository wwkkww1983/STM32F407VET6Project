#include"jtag_cfg.h"

//===ȫ�ֱ�������
JTAG_HandlerType	g_JtagDevice0={0};
//===ȫ��ָ�����
pJTAG_HandlerType	pJtagDevice0=&g_JtagDevice0;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_Device0_Init(JTAG_HandlerType* JTAGx)
{
	JTAGx->msgTapState = TEST_LOGIC_RESET;

	//---TCK->PB3---host->device
	JTAGx->msgTCK.msgGPIOPort = GPIOB;
	JTAGx->msgTCK.msgGPIOBit = LL_GPIO_PIN_3;

	//---TMS->PC5---host->device
	JTAGx->msgTMS.msgGPIOPort = GPIOC;
	JTAGx->msgTMS.msgGPIOBit = LL_GPIO_PIN_5;

	//---RST->PC4---host->device
	JTAGx->msgRST.msgGPIOPort = GPIOC;
	JTAGx->msgRST.msgGPIOBit = LL_GPIO_PIN_4;

	//---TDI->PA7---host->device
	JTAGx->msgTDI.msgGPIOPort = GPIOA;
	JTAGx->msgTDI.msgGPIOBit = LL_GPIO_PIN_7;

	//---TDO->PA6---device->host
	JTAGx->msgTDO.msgGPIOPort = GPIOA;
	JTAGx->msgTDO.msgGPIOBit = LL_GPIO_PIN_6;
	//---OEʹ�õĶ˿�
#ifdef JTAG_USE_lEVEL_SHIFT
	//---OE->PD13---���Ƶ�ƽװ����ʹ��
	JTAGx->msgOE.msgGPIOPort = GPIOD;
	JTAGx->msgOE.msgGPIOBit = LL_GPIO_PIN_13;
#endif

	JTAGx->msgPluseWidth = 20;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_Device1_Init(JTAG_HandlerType* JTAGx)
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
UINT8_T JTAG_Device2_Init(JTAG_HandlerType* JTAGx)
{
	JTAGx->msgTapState = TEST_LOGIC_RESET;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_GPIO_Init(JTAG_HandlerType* JTAGx)
{
	//---ʹ��GPIO��ʱ��
	GPIOTask_Clock(JTAGx->msgTDI.msgGPIOPort, 1);
	GPIOTask_Clock(JTAGx->msgTDO.msgGPIOPort, 1);
	GPIOTask_Clock(JTAGx->msgTMS.msgGPIOPort, 1);
	GPIOTask_Clock(JTAGx->msgTCK.msgGPIOPort, 1);
	GPIOTask_Clock(JTAGx->msgRST.msgGPIOPort, 1);
	//---JTAG��OEʹ�ܶ�
#ifdef JTAG_USE_lEVEL_SHIFT
	GPIOTask_Clock(JTAGx->msgOE.msgGPIOPort, 1);
#endif

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;														//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;												//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;											//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;															//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;														//---�˿ڸ���ģʽ
#endif
	//---TDI---���Ϊ��
	GPIO_InitStruct.Pin = JTAGx->msgTDI.msgGPIOBit;
	LL_GPIO_Init(JTAGx->msgTDI.msgGPIOPort, &GPIO_InitStruct);
	JTAG_GPIO_0(JTAGx->msgTDI);
	//---TCK---���Ϊ��
	GPIO_InitStruct.Pin = JTAGx->msgTCK.msgGPIOBit;
	LL_GPIO_Init(JTAGx->msgTCK.msgGPIOPort, &GPIO_InitStruct);
	JTAG_GPIO_0(JTAGx->msgTCK);
	//---TMS---���Ϊ��
	GPIO_InitStruct.Pin = JTAGx->msgTMS.msgGPIOBit;
	LL_GPIO_Init(JTAGx->msgTMS.msgGPIOPort, &GPIO_InitStruct);
	JTAG_GPIO_1(JTAGx->msgTMS);
	//---RST---���Ϊ��
	GPIO_InitStruct.Pin = JTAGx->msgRST.msgGPIOBit;
	LL_GPIO_Init(JTAGx->msgRST.msgGPIOPort, &GPIO_InitStruct);
	JTAG_GPIO_1(JTAGx->msgRST);
#ifdef JTAG_USE_lEVEL_SHIFT
	//---OE---���Ϊ�ͣ�����Ч
	GPIO_InitStruct.Pin = JTAGx->msgOE.msgGPIOBit;
	LL_GPIO_Init(JTAGx->msgOE.msgGPIOPort, &GPIO_InitStruct);
	JTAG_GPIO_0(JTAGx->msgOE);
#endif 
	//---TDO---���룬����ʹ��
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;														//---����״̬Ϊ����ģʽ
	GPIO_InitStruct.Pin = JTAGx->msgTDO.msgGPIOBit;
	LL_GPIO_Init(JTAGx->msgTDO.msgGPIOPort, &GPIO_InitStruct);
	JTAG_GPIO_1(JTAGx->msgTDO);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_Init(JTAG_HandlerType* JTAGx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	//---ʹ�õ���Դ
	if ((JTAGx != NULL) && (JTAGx == JTAG_TASK_ONE))
	{
		JTAG_Device0_Init(JTAGx);
	}
	else if ((JTAGx != NULL) && (JTAGx == JTAG_TASK_TWO))
	{
		JTAG_Device1_Init(JTAGx);
	}
	else if ((JTAGx != NULL) && (JTAGx == JTAG_TASK_THREE))
	{
		JTAG_Device2_Init(JTAGx);
	}
	else
	{
		return ERROR_1;
	}
	JTAG_GPIO_Init(JTAGx);
	//---ע��ms����ʱ����
	if (pFuncDelayms != NULL)
	{
		JTAGx->msgDelayms = pFuncDelayms;
	}
	else
	{
		JTAGx->msgDelayms = DelayTask_us;
	}
	//---ע��us��ʱ����
	if (pFuncDelayus != NULL)
	{
		JTAGx->msgDelayus = pFuncDelayus;
	}
	else
	{
		JTAGx->msgDelayus = DelayTask_us;
	}
	////---ע��δ���
	//JTAGx->msgSPI.msgFuncTimeTick = pFuncTimerTick;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�TMSΪ�ߣ�TCK��5�����壬�ܹ�ֱ�ӻص�TestlogicReset״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_TestlogicReset(JTAG_HandlerType* JTAGx)
{
	UINT8_T i=0;
	JTAG_GPIO_1(JTAGx->msgTMS);
	for (i=0;i<5;i++)
	{
		JTAG_TCK_PULSE(JTAGx);
	}
	JTAGx->msgTapState=TEST_LOGIC_RESET;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ڿ���״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunTestIdle(JTAG_HandlerType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			break;
		case SELECT_DR_SCAN:
			//---capture dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_DR:
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_DR:
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_DR:
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);	
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_IR:
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_IR:
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_IR:
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_TestlogicReset(JTAGx);
			break;
	}
	//---run_test_idle
	JTAG_GPIO_0(JTAGx->msgTMS);
	JTAG_TCK_PULSE(JTAGx);
	JTAGx->msgTapState=RUN_TEST_IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������SelectDRScan״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunSelectDRScan(JTAG_HandlerType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			break;
		case SELECT_DR_SCAN:
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_DR:
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_DR:
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_DR:
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_IR:
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_IR:
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_IR:
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_TestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
	}
	//---select_dr_scan
	JTAG_GPIO_1(JTAGx->msgTMS);
	//---У���Ƿ񱣳�ʱ�Ӳ���
	if (JTAGx->msgTapState == SELECT_DR_SCAN)
	{
		JTAG_GPIO_0(JTAGx->msgTCK);
	}
	else
	{
		JTAG_TCK_PULSE(JTAGx);
	}
	JTAGx->msgTapState = SELECT_DR_SCAN;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������Capture DR
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunCaptureDR(JTAG_HandlerType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_DR_SCAN:
			break;
		case CAPTURE_DR:
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_DR:
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_DR:
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_IR:
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_IR:
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_TestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
	}
	if (JTAGx->msgTapState!=CAPTURE_DR)
	{
		//---capture_dr
		JTAG_GPIO_0(JTAGx->msgTMS);
		JTAG_TCK_PULSE(JTAGx);
	}
	JTAGx->msgTapState = CAPTURE_DR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������ShiftDR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunShiftDR(JTAG_HandlerType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_DR:
			break;
		case SHIFT_DR:
			//---shift_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_DR:
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit2_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_DR:
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_IR:
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_IR:
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_TestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
	}
	JTAGx->msgTapState = SHIFT_DR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������Exit1DR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunExit1DR(JTAG_HandlerType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_DR:
			break;
		case SHIFT_DR:
			break;
		case EXIT1_DR:
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_DR:
			//---shift_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_IR:
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_IR:
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_TestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
	}
	if (JTAGx->msgTapState!=EXIT1_DR)
	{
		//---exit1_dr
		JTAG_GPIO_1(JTAGx->msgTMS);
		JTAG_TCK_PULSE(JTAGx);
	}
	JTAGx->msgTapState = EXIT1_DR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������PauseDR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunPauseDR(JTAG_HandlerType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_DR:
			//---shift_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_DR:
			break;
		case PAUSE_DR:
			break;
		case EXIT2_DR:
			//---shift_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_IR:
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_IR:
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_TestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
	}
	if (JTAGx->msgTapState!=PAUSE_DR)
	{
		//---pause_dr
		JTAG_GPIO_0(JTAGx->msgTMS);
		JTAG_TCK_PULSE(JTAGx);
	}
	JTAGx->msgTapState = PAUSE_DR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������Exit2DR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunExit2DR(JTAG_HandlerType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_DR:
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_DR:
			break;
		case EXIT2_DR:
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_IR:
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_IR:
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_TestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);			
			break;
	}
	if (JTAGx->msgTapState!EXIT2_DR)
	{
		//---exit2_dr
		JTAG_GPIO_1(JTAGx->msgTMS);
		JTAG_TCK_PULSE(JTAGx);
	}
	JTAGx->msgTapState = EXIT2_DR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������UpdateDR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunUpdateDR(JTAG_HandlerType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_DR:
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_DR:
			break;
		case UPDATE_DR:
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_IR:
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_IR:
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_TestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
	}
	if (JTAGx->msgTapState!=UPDATE_DR)
	{
		//---update_dr
		JTAG_GPIO_1(JTAGx->msgTMS);
		JTAG_TCK_PULSE(JTAGx);
	}
	JTAGx->msgTapState = UPDATE_DR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������SelectiRScan״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunSelectIRScan(JTAG_HandlerType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			break;
		case SELECT_DR_SCAN:
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_DR:
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_DR:
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_DR:
			break;
		case SELECT_IR_SCAN:
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_IR:
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_IR:
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_IR:
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_TestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
	}
	//---select_dr_scan
	JTAG_GPIO_1(JTAGx->msgTMS);
	JTAG_TCK_PULSE(JTAGx);
	//---select_ir_scan
	JTAG_GPIO_1(JTAGx->msgTMS);
	//---У���Ƿ񱣳�ʱ�Ӳ���
	if (JTAGx->msgTapState == SELECT_IR_SCAN)
	{
		JTAG_GPIO_0(JTAGx->msgTCK);
	}
	else
	{
		JTAG_TCK_PULSE(JTAGx);
	}
	JTAGx->msgTapState = SELECT_IR_SCAN;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������CaptureIR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunCaptureIR(JTAG_HandlerType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_DR:
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_DR:
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_IR_SCAN:
			break;
		case CAPTURE_IR:
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_IR:
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_IR:
			//---update_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_TestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
	}
	if (JTAGx->msgTapState != CAPTURE_IR)
	{
		//---capture_ir
		JTAG_GPIO_0(JTAGx->msgTMS);
		JTAG_TCK_PULSE(JTAGx);
	}
	JTAGx->msgTapState = CAPTURE_IR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������ShiftDR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunShiftIR(JTAG_HandlerType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_DR:
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_DR:
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_IR:
			break;
		case SHIFT_IR:
			//---shift_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_IR:
			//---pasuse_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit2_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_IR:
			//---shift_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_TestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
	}
	JTAGx->msgTapState = SHIFT_IR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������PauseDR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunExit1IR(JTAG_HandlerType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_DR:
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_DR:
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_IR:
			break;
		case SHIFT_IR:
			break;
		case EXIT1_IR:
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_IR:
			//---shift_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_TestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
	}
	if (JTAGx->msgTapState!=EXIT1_IR)
	{
		//---exit1_ir
		JTAG_GPIO_1(JTAGx->msgTMS);
		JTAG_TCK_PULSE(JTAGx);
	}
	JTAGx->msgTapState = EXIT1_IR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������PauseDR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunPauseIR(JTAG_HandlerType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_DR:
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_DR:
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_IR:
			//---shift_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_IR:
			break;
		case PAUSE_IR:
			break;
		case EXIT2_IR:
			//---shift_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_TestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---shift_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
	}
	//---pause_ir
	JTAG_GPIO_0(JTAGx->msgTMS);
	JTAG_TCK_PULSE(JTAGx);
	JTAGx->msgTapState = PAUSE_IR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������PauseDR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunExit2IR(JTAG_HandlerType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_DR:
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_DR:
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_IR:
			//---pasuse_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_IR:
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_TestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---pause_dr
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
	}
	if (JTAGx->msgTapState!=EXIT2_IR)
	{
		//---exit2_ir
		JTAG_GPIO_1(JTAGx->msgTMS);
		JTAG_TCK_PULSE(JTAGx);
	}
	JTAGx->msgTapState = EXIT2_IR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������PauseDR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunUpdateIR(JTAG_HandlerType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_DR:
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_DR:
			//---update_dr
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_IR:
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_IR:
			break;
		case UPDATE_IR:
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_TestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---select_ir_scan
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_ir
			JTAG_GPIO_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_GPIO_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
	}
	if (JTAGx->msgTapState!=UPDATE_IR)
	{
		//---update_ir
		JTAG_GPIO_1(JTAGx->msgTMS);
		JTAG_TCK_PULSE(JTAGx);
	}
	JTAGx->msgTapState = UPDATE_IR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����IR����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_ShiftIR_Bit(JTAG_HandlerType* JTAGx,UINT8_T irCmd, UINT8_T bitCount, UINT8_T isRunTestIdle)
{
	UINT8_T i = 0;
	UINT8_T _return = OK_0;
	//---capture_ir
	JTAG_RunCaptureIR(JTAGx);
	//---��������
	for (i = 0; i < bitCount; i++)
	{
		JTAG_TCK_PULSE(JTAGx);
		if ((irCmd&0x01)!=0x00)
		{
			JTAG_GPIO_1(JTAGx->msgTDI);
		}
		else
		{
			JTAG_GPIO_0(JTAGx->msgTDI);
		}
		//---��λ����
		irCmd>>=1;
		if (JTAG_GPIO_STATE(JTAGx->msgTDO)!=0)
		{
			_return|=(1<<i);
		}
	}
	JTAGx->msgTapState = SHIFT_IR;
	//---У���Ƿ������ڿ���״̬
	if (isRunTestIdle)
	{
		//---run_test_idle
		JTAG_RunTestIdle(JTAGx);
	}
	//---select_dr_scan
	JTAG_RunSelectDRScan(JTAGx);
	return ((_return==0x01)?OK_0:ERROR_1);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT32_T JTAG_ShiftDR_Bit(JTAG_HandlerType* JTAGx, UINT32_T drCmd, UINT8_T bitCount, UINT8_T isRunTestIdle)
{
	UINT32_T i = 0;
	UINT32_T _return=0;
	//---capture_dr�������ݼĴ���״̬
	JTAG_RunCaptureDR(JTAGx);
	for (i=0;i<bitCount;i++)
	{
		JTAG_TCK_PULSE(JTAGx);
		//---������������
		if ((drCmd & 0x01) != 0x00)
		{
			JTAG_GPIO_1(JTAGx->msgTDI);
		}
		else
		{
			JTAG_GPIO_0(JTAGx->msgTDI);
		}
		//---��λ����
		drCmd >>= 1;
		if (JTAG_GPIO_STATE(JTAGx->msgTDO) != 0)
		{
			_return |= (1 << i);
		}
	}
	JTAGx->msgTapState=SHIFT_DR;
	//---У���Ƿ������ڿ���״̬
	if (isRunTestIdle!=0)
	{
		//---run_test_idle
		JTAG_RunTestIdle(JTAGx);
	}
	//---select_dr_scan
	JTAG_RunSelectDRScan(JTAGx);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡJTAGID��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_ReadIDChip(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T isRunAvrReset)
{
	JTAG_ShiftIR_Bit(JTAGx,IDCODE,4,0);
	JTAG_RunCaptureDR(JTAGx);
	UINT32_T i=0;
	UINT32_T _return=0;
	for (i = 0; i < 32; i++)
	{
		JTAG_TCK_PULSE(JTAGx);
		JTAG_GPIO_0(JTAGx->msgTDI);
		//---��ȡ���
		if (JTAG_GPIO_STATE(JTAGx->msgTDO) != 0)
		{
			_return |= (1 << i);
		}
	}
	if (isRunAvrReset!=0)
	{
		JTAG_ShiftIR_Bit(JTAGx, AVR_RESET, 4, 1);
	}
	else
	{
		JTAG_RunTestIdle(JTAGx);
	}
	_return&=0x0FFFFFFF;
	return OK_0;
}