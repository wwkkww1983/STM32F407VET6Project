#include"jtag_cfg.h"

//===全局变量定义
JTAG_HandlerType	g_JtagDevice0={0};
//===全局指针变量
pJTAG_HandlerType	pJtagDevice0=&g_JtagDevice0;

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
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
	//---OE使用的端口
#ifdef JTAG_USE_lEVEL_SHIFT
	//---OE->PD13---控制电平装换的使能
	JTAGx->msgOE.msgGPIOPort = GPIOD;
	JTAGx->msgOE.msgGPIOBit = LL_GPIO_PIN_13;
#endif

	JTAGx->msgPluseWidth = 20;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_Device1_Init(JTAG_HandlerType* JTAGx)
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
UINT8_T JTAG_Device2_Init(JTAG_HandlerType* JTAGx)
{
	JTAGx->msgTapState = TEST_LOGIC_RESET;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_GPIO_Init(JTAG_HandlerType* JTAGx)
{
	//---使能GPIO的时钟
	GPIOTask_Clock(JTAGx->msgTDI.msgGPIOPort, 1);
	GPIOTask_Clock(JTAGx->msgTDO.msgGPIOPort, 1);
	GPIOTask_Clock(JTAGx->msgTMS.msgGPIOPort, 1);
	GPIOTask_Clock(JTAGx->msgTCK.msgGPIOPort, 1);
	GPIOTask_Clock(JTAGx->msgRST.msgGPIOPort, 1);
	//---JTAG的OE使能端
#ifdef JTAG_USE_lEVEL_SHIFT
	GPIOTask_Clock(JTAGx->msgOE.msgGPIOPort, 1);
#endif

	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;														//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;												//---GPIO的速度---低速设备
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;											//---输出模式---推挽输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;															//---上拉
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;														//---端口复用模式
#endif
	//---TDI---输出为低
	GPIO_InitStruct.Pin = JTAGx->msgTDI.msgGPIOBit;
	LL_GPIO_Init(JTAGx->msgTDI.msgGPIOPort, &GPIO_InitStruct);
	JTAG_GPIO_0(JTAGx->msgTDI);
	//---TCK---输出为低
	GPIO_InitStruct.Pin = JTAGx->msgTCK.msgGPIOBit;
	LL_GPIO_Init(JTAGx->msgTCK.msgGPIOPort, &GPIO_InitStruct);
	JTAG_GPIO_0(JTAGx->msgTCK);
	//---TMS---输出为高
	GPIO_InitStruct.Pin = JTAGx->msgTMS.msgGPIOBit;
	LL_GPIO_Init(JTAGx->msgTMS.msgGPIOPort, &GPIO_InitStruct);
	JTAG_GPIO_1(JTAGx->msgTMS);
	//---RST---输出为高
	GPIO_InitStruct.Pin = JTAGx->msgRST.msgGPIOBit;
	LL_GPIO_Init(JTAGx->msgRST.msgGPIOPort, &GPIO_InitStruct);
	JTAG_GPIO_1(JTAGx->msgRST);
#ifdef JTAG_USE_lEVEL_SHIFT
	//---OE---输出为低，低有效
	GPIO_InitStruct.Pin = JTAGx->msgOE.msgGPIOBit;
	LL_GPIO_Init(JTAGx->msgOE.msgGPIOPort, &GPIO_InitStruct);
	JTAG_GPIO_0(JTAGx->msgOE);
#endif 
	//---TDO---输入，上拉使能
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;														//---配置状态为输入模式
	GPIO_InitStruct.Pin = JTAGx->msgTDO.msgGPIOBit;
	LL_GPIO_Init(JTAGx->msgTDO.msgGPIOPort, &GPIO_InitStruct);
	JTAG_GPIO_1(JTAGx->msgTDO);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_Init(JTAG_HandlerType* JTAGx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	//---使用的资源
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
	//---注册ms的延时函数
	if (pFuncDelayms != NULL)
	{
		JTAGx->msgDelayms = pFuncDelayms;
	}
	else
	{
		JTAGx->msgDelayms = DelayTask_us;
	}
	//---注册us延时函数
	if (pFuncDelayus != NULL)
	{
		JTAGx->msgDelayus = pFuncDelayus;
	}
	else
	{
		JTAGx->msgDelayus = DelayTask_us;
	}
	////---注册滴答函数
	//JTAGx->msgSPI.msgFuncTimeTick = pFuncTimerTick;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：TMS为高，TCK给5个脉冲，能够直接回到TestlogicReset状态
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：运行在空闲状态
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：运行在SelectDRScan状态
//////输入参数:
//////输出参数:
//////说		明：
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
	//---校验是否保持时钟不变
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
//////函		数：
//////功		能：运行在Capture DR
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：运行在ShiftDR状态
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：运行在Exit1DR状态
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：运行在PauseDR状态
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：运行在Exit2DR状态
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：运行在UpdateDR状态
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：运行在SelectiRScan状态
//////输入参数:
//////输出参数:
//////说		明：
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
	//---校验是否保持时钟不变
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
//////函		数：
//////功		能：运行在CaptureIR状态
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：运行在ShiftDR状态
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：运行在PauseDR状态
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：运行在PauseDR状态
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：运行在PauseDR状态
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：运行在PauseDR状态
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：发送IR命令
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_ShiftIR_Bit(JTAG_HandlerType* JTAGx,UINT8_T irCmd, UINT8_T bitCount, UINT8_T isRunTestIdle)
{
	UINT8_T i = 0;
	UINT8_T _return = OK_0;
	//---capture_ir
	JTAG_RunCaptureIR(JTAGx);
	//---发送命令
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
		//---移位数据
		irCmd>>=1;
		if (JTAG_GPIO_STATE(JTAGx->msgTDO)!=0)
		{
			_return|=(1<<i);
		}
	}
	JTAGx->msgTapState = SHIFT_IR;
	//---校验是否运行在空闲状态
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT32_T JTAG_ShiftDR_Bit(JTAG_HandlerType* JTAGx, UINT32_T drCmd, UINT8_T bitCount, UINT8_T isRunTestIdle)
{
	UINT32_T i = 0;
	UINT32_T _return=0;
	//---capture_dr捕获数据寄存器状态
	JTAG_RunCaptureDR(JTAGx);
	for (i=0;i<bitCount;i++)
	{
		JTAG_TCK_PULSE(JTAGx);
		//---发送数据命令
		if ((drCmd & 0x01) != 0x00)
		{
			JTAG_GPIO_1(JTAGx->msgTDI);
		}
		else
		{
			JTAG_GPIO_0(JTAGx->msgTDI);
		}
		//---移位数据
		drCmd >>= 1;
		if (JTAG_GPIO_STATE(JTAGx->msgTDO) != 0)
		{
			_return |= (1 << i);
		}
	}
	JTAGx->msgTapState=SHIFT_DR;
	//---校验是否运行在空闲状态
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
//////函		数：
//////功		能：读取JTAGID信息
//////输入参数:
//////输出参数:
//////说		明：
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
		//---读取结果
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