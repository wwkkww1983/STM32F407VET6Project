#include "ads8688_cfg.h"

//===全局变量定义
ADS8688_HandlerType  g_ADS8688Device0 = { 0 };
pADS8688_HandlerType  pADS8688Device0 = &g_ADS8688Device0;

//===统一发送命令
UINT8_T(*ADS8688_SPI_SEND_CMD)(ADS8688_HandlerType *, UINT8_T, UINT8_T *);

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void ADS8688_SPI_Device0_Init(ADS8688_HandlerType *ADS8688x)
{

	//---复位信号
	ADS8688x->msgHWRST.msgGPIOPort = NULL;
	ADS8688x->msgHWRST.msgGPIOBit = LL_GPIO_PIN_0;

	//---GPIO时钟使能
	if (ADS8688x->msgHWRST.msgGPIOPort != NULL)
	{
		GPIOTask_Clock(ADS8688x->msgHWRST.msgGPIOPort, 1);
	}

	//---CS
	ADS8688x->msgSPI.msgCS.msgGPIOPort = GPIOA;
	ADS8688x->msgSPI.msgCS.msgGPIOBit = LL_GPIO_PIN_4;

	//---SCK
	ADS8688x->msgSPI.msgSCK.msgGPIOPort = GPIOA;
	ADS8688x->msgSPI.msgSCK.msgGPIOBit = LL_GPIO_PIN_5;

	//---MISO
	ADS8688x->msgSPI.msgMISO.msgGPIOPort = GPIOA;
	ADS8688x->msgSPI.msgMISO.msgGPIOBit = LL_GPIO_PIN_6;

	//---MOSI
	ADS8688x->msgSPI.msgMOSI.msgGPIOPort = GPIOA;
	ADS8688x->msgSPI.msgMOSI.msgGPIOBit = LL_GPIO_PIN_7;

	//---GPIO的配置
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---GPIO的初始化
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;					//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;			//---GPIO的速度
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;		//---输出模式---推挽输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;						//---上拉使能

	//---初始化RST
	if (ADS8688x->msgHWRST.msgGPIOPort != NULL)
	{
		GPIO_InitStruct.Pin = ADS8688x->msgHWRST.msgGPIOBit;
		GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
		LL_GPIO_Init(ADS8688x->msgHWRST.msgGPIOPort, &GPIO_InitStruct);
		GPIO_OUT_1(ADS8688x->msgHWRST.msgGPIOPort, ADS8688x->msgHWRST.msgGPIOBit);
	}

	//---复用模式
#ifndef USE_MCU_STM32F1

	//---端口复用模式
	ADS8688x->msgSPI.msgGPIOAlternate = LL_GPIO_AF_5;
#endif

	//---SPI序号
	ADS8688x->msgSPI.msgSPIx = SPI1;
#ifndef USE_MCU_STM32F1

	//---SPI的协议
	ADS8688x->msgSPI.msgStandard = LL_SPI_PROTOCOL_MOTOROLA;
#endif

	UINT8_T i = 0;
	for (i = 0; i < ADS8688_CHANNEL_MAX; i++)
	{
		ADS8688x->msgChannelRange[i] = 0;
		ADS8688x->msgIsPositive[i] = 0;
		ADS8688x->msgChannelADCResult[i] = 0;
		ADS8688x->msgChannelPowerResult[i] = 0;
	}

	ADS8688x->msgChipID = 0x28;
	//---默认是0xFF
	ADS8688x->msgAutoSeqEn = 0xFF;
	//---定义脉冲宽度
	ADS8688x->msgSPI.msgPluseWidth = 2;
	//---时钟空闲为低电平
	ADS8688x->msgSPI.msgCPOL = 0;
	//---数据采样在第二个时钟边沿
	ADS8688x->msgSPI.msgCPOH = 1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void ADS8688_SPI_Device1_Init(ADS8688_HandlerType *ADS8688x)
{
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void ADS8688_SPI_Device2_Init(ADS8688_HandlerType *ADS8688x)
{
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS8688_SPI_HW_Init(ADS8688_HandlerType *ADS8688x)
{
	//---注销当前的所有配置
	SPITask_DeInit(&(ADS8688x->msgSPI));

	//---硬件端口的配置---硬件实现
	SPITask_MHW_GPIO_Init(&(ADS8688x->msgSPI));

	//---硬件SPI的初始化
	LL_SPI_InitTypeDef SPI_InitStruct = {0};

	//---SPI的模式配置
	SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
	SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;						//---主机模式
	SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;				//---8位数据
																	//---时钟极性的设置
	if (ADS8688x->msgSPI.msgCPOL == 0)
	{
		//---CLK空闲时为低电平 (CLK空闲是只能是低电平)
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
		GPIO_OUT_0(ADS8688x->msgSPI.msgSCK.msgGPIOPort, ADS8688x->msgSPI.msgSCK.msgGPIOBit);
	}
	else
	{
		//---CLK空闲时为高电平 (CLK空闲是只能是低电平)
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_HIGH;
	}

	//---数据采样的时钟边沿位置
	if (ADS8688x->msgSPI.msgCPOH ==0)
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
	}
	else
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_2EDGE;
	}
	SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;							//---软件控制
	SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV2;		//---系统时钟256分频
	SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;						//---高位在前
	SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;	//---硬件CRC不使能
	SPI_InitStruct.CRCPoly = 7;

	//---初始化查询方式的SPI
	SPITask_MHW_PollMode_Init(&(ADS8688x->msgSPI), SPI_InitStruct);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS8688_SPI_SW_Init(ADS8688_HandlerType *ADS8688x)
{
	SPITask_DeInit(&(ADS8688x->msgSPI));

	//---硬件端口的配置---软件实现
	SPITask_MSW_GPIO_Init(&(ADS8688x->msgSPI));

	//---时钟线的极性
	if (ADS8688x->msgSPI.msgCPOL == 0)
	{
		GPIO_OUT_0(ADS8688x->msgSPI.msgSCK.msgGPIOPort, ADS8688x->msgSPI.msgSCK.msgGPIOBit);
	}
	else
	{
		GPIO_OUT_1(ADS8688x->msgSPI.msgSCK.msgGPIOPort, ADS8688x->msgSPI.msgSCK.msgGPIOBit);
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
UINT8_T ADS8688_SPI_SW_SendCmd(ADS8688_HandlerType *ADS8688x, UINT8_T cmd, UINT8_T *pRVal)
{
	//---数据发送
	return SPITask_MSW_WriteAndReadByteMSB(&(ADS8688x->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS8688_SPI_HW_SendCmd(ADS8688_HandlerType *ADS8688x, UINT8_T cmd, UINT8_T *pRVal)
{
	//---数据发送
	return SPITask_MHW_PollMode_WriteReadByte(&(ADS8688x->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS8688_SPI_Init(ADS8688_HandlerType *ADS8688x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHW)
{
	//---使用的DHT11的端口
	if ((ADS8688x != NULL) && (ADS8688x == ADS8688_TASK_ONE))
	{
		ADS8688_SPI_Device0_Init(ADS8688x);
	}
	else if ((ADS8688x != NULL) && (ADS8688x == ADS8688_TASK_TWO))
	{
		ADS8688_SPI_Device1_Init(ADS8688x);
	}
	else if ((ADS8688x != NULL) && (ADS8688x == ADS8688_TASK_THREE))
	{
		ADS8688_SPI_Device2_Init(ADS8688x);
	}
	else
	{
		return ERROR_1;
	}

	//---判断初始化的方式
	if (isHW != 0)
	{
		ADS8688x->msgSPI.msgModelIsHW = 1;
		ADS8688_SPI_HW_Init(ADS8688x);
		ADS8688_SPI_SEND_CMD = ADS8688_SPI_HW_SendCmd;
	}
	else
	{
		ADS8688x->msgSPI.msgModelIsHW = 0;
		ADS8688_SPI_SW_Init(ADS8688x);
		ADS8688_SPI_SEND_CMD = ADS8688_SPI_SW_SendCmd;
	}

	//---注册ms延时时间
	if (pFuncDelayms != NULL)
	{
		ADS8688x->msgFuncDelayms = pFuncDelayms;
	}
	else
	{
		ADS8688x->msgFuncDelayms = DelayTask_ms;
	}

	//---注册us延时函数
	if (pFuncDelayus != NULL)
	{
		ADS8688x->msgSPI.msgFuncDelayus = pFuncDelayus;
	}
	else
	{
		ADS8688x->msgSPI.msgFuncDelayus = DelayTask_us;
	}

	//---注册滴答函数
	ADS8688x->msgSPI.msgFuncTimeTick = pFuncTimerTick;

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：写ADS8688命令寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS8688_SPI_WriteCommandReg(ADS8688_HandlerType *ADS8688x, UINT32_T cmd)
{
	UINT8_T _return = OK_0;
	if (ADS8688x->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_0(ADS8688x->msgSPI.msgCS.msgGPIOPort, ADS8688x->msgSPI.msgCS.msgGPIOBit);
	}
	//---写高位
	_return = ADS8688_SPI_SEND_CMD(ADS8688x, (UINT8_T)(cmd >> 8), NULL);
	//---写低位
	_return += ADS8688_SPI_SEND_CMD(ADS8688x, (UINT8_T)(cmd & 0xFF), NULL);
	if (ADS8688x->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_1(ADS8688x->msgSPI.msgCS.msgGPIOPort, ADS8688x->msgSPI.msgCS.msgGPIOBit);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：Program Register写操作
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS8688_SPI_WriteProgramReg(ADS8688_HandlerType *ADS8688x, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	if (ADS8688x->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_0(ADS8688x->msgSPI.msgCS.msgGPIOPort, ADS8688x->msgSPI.msgCS.msgGPIOBit);
	}
	//---写地址
	_return = ADS8688_SPI_SEND_CMD(ADS8688x, (addr << 1) | 0x01, NULL);
	//---写数据
	_return += ADS8688_SPI_SEND_CMD(ADS8688x, val, NULL);
	if (ADS8688x->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_1(ADS8688x->msgSPI.msgCS.msgGPIOPort, ADS8688x->msgSPI.msgCS.msgGPIOBit);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：Program Register读操作
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS8688_SPI_ReadProgramReg(ADS8688_HandlerType *ADS8688x, UINT8_T addr, UINT8_T *pVal)
{
	UINT8_T _return = OK_0;
	if (ADS8688x->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_0(ADS8688x->msgSPI.msgCS.msgGPIOPort, ADS8688x->msgSPI.msgCS.msgGPIOBit);
	}
	//---写地址
	_return = ADS8688_SPI_SEND_CMD(ADS8688x, (addr << 1) & 0xFE, NULL);
	//---读高位数据
	_return += ADS8688_SPI_SEND_CMD(ADS8688x, 0x00, pVal);
	pVal++;
	//---读低位数据
	_return += ADS8688_SPI_SEND_CMD(ADS8688x, 0x00, pVal);
	if (ADS8688x->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_1(ADS8688x->msgSPI.msgCS.msgGPIOPort, ADS8688x->msgSPI.msgCS.msgGPIOBit);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读命令返回
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS8688_SPI_ReadCommandBack(ADS8688_HandlerType* ADS8688x, UINT8_T* pVal)
{
	return ADS8688_SPI_ReadProgramReg(ADS8688x, ADS8688_CMD_READ_BACK, pVal);
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：进入自动扫描模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS8688_SPI_AutoRSTMode(ADS8688_HandlerType* ADS8688x)
{
	return ADS8688_SPI_WriteCommandReg(ADS8688x, ADS8688_CMD_REG_AUTO_RST);
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置自动扫描序列通道
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS8688_SPI_SetAutoScanSequence(ADS8688_HandlerType *ADS8688x, UINT8_T seq)
{
	ADS8688x->msgAutoSeqEn = seq;
	return ADS8688_SPI_WriteProgramReg(ADS8688x, ADS8688_PROG_REG_AUTO_SEQ_EN, seq);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置通道的量程范围
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS8688_SPI_SetCHannelRangeSelect(ADS8688_HandlerType *ADS8688x, UINT8_T chReg, UINT8_T range)
{
	switch (chReg)
	{
		case ADS8688_PROG_REG_CH0_SET_RANGE:
			ADS8688x->msgChannelRange[0] = range;
			break;
		case ADS8688_PROG_REG_CH1_SET_RANGE:
			ADS8688x->msgChannelRange[1] = range;
			break;
		case ADS8688_PROG_REG_CH2_SET_RANGE:
			ADS8688x->msgChannelRange[2] = range;
			break;
		case ADS8688_PROG_REG_CH3_SET_RANGE:
			ADS8688x->msgChannelRange[3] = range;
			break;
		case ADS8688_PROG_REG_CH4_SET_RANGE:
			ADS8688x->msgChannelRange[4] = range;
			break;
		case ADS8688_PROG_REG_CH5_SET_RANGE:
			ADS8688x->msgChannelRange[5] = range;
			break;
		case ADS8688_PROG_REG_CH6_SET_RANGE:
			ADS8688x->msgChannelRange[6] = range;
			break;
		case ADS8688_PROG_REG_CH7_SET_RANGE:
			ADS8688x->msgChannelRange[7] = range;
			break;
		default:
			return ERROR_1;
	}
	return ADS8688_SPI_WriteProgramReg(ADS8688x, chReg, range);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：硬件复位设备
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  ADS8688_SPI_HardReset(ADS8688_HandlerType *ADS8688x)
{
	if (ADS8688x->msgHWRST.msgGPIOPort!=NULL)
	{
		GPIO_OUT_0(ADS8688x->msgHWRST.msgGPIOPort, ADS8688x->msgHWRST.msgGPIOBit);
		ADS8688x->msgFuncDelayms(1);
		GPIO_OUT_1(ADS8688x->msgHWRST.msgGPIOPort, ADS8688x->msgHWRST.msgGPIOBit);
		ADS8688x->msgFuncDelayms(1);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：软件复位设备
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  ADS8688_SPI_SoftReset(ADS8688_HandlerType *ADS8688x)
{
	return ADS8688_SPI_WriteCommandReg(ADS8688x, ADS8688_CMD_REG_RST);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：设备复位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS8688_SPI_Reset(ADS8688_HandlerType* ADS8688x)
{
	UINT8_T _return = OK_0;
	if (ADS8688x->msgHWRST.msgGPIOPort != NULL)
	{
		_return = ADS8688_SPI_HardReset(ADS8688x);
	}
	else
	{
		_return = ADS8688_SPI_SoftReset(ADS8688x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：继续工作在选中的状态
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS8688_SPI_ContinuedOperationInTheSelectedMode(ADS8688_HandlerType* ADS8688x)
{
	return ADS8688_SPI_WriteCommandReg(ADS8688x, ADS8688_CMD_REG_NO_OP);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS8688_SPI_PowerDown(ADS8688_HandlerType* ADS8688x)
{
	return ADS8688_SPI_WriteCommandReg(ADS8688x, ADS8688_CMD_REG_PWR_DN);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS8688_SPI_Standby(ADS8688_HandlerType* ADS8688x)
{
	return ADS8688_SPI_WriteCommandReg(ADS8688x, ADS8688_CMD_REG_STDBY);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：通道选择
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS8688_SPI_ManualChannelSelect(ADS8688_HandlerType* ADS8688x,UINT16_T manualCHCmd)
{
	return ADS8688_SPI_WriteCommandReg(ADS8688x, manualCHCmd);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：设置设备ID
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS8688_SPI_WriteChipID(ADS8688_HandlerType* ADS8688x, UINT8_T devid)
{
	devid <<= 6;
	ADS8688x->msgChipID = (ADS8688x->msgChipID & 0x2F) | (devid & 0xC0);
	return ADS8688_SPI_WriteProgramReg(ADS8688x, ADS8688_PROG_REG_FEATURE_SELECT, ADS8688x->msgChipID);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：读取设备ID
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS8688_SPI_ReadChipID(ADS8688_HandlerType* ADS8688x, UINT8_T *pDevID)
{
	return ADS8688_SPI_ReadProgramReg(ADS8688x, ADS8688_PROG_REG_FEATURE_SELECT, pDevID);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：校验设备ID
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS8688_SPI_CheckChipID(ADS8688_HandlerType* ADS8688x)
{
	UINT8_T tempChipID = 0x00;
	UINT8_T _return = OK_0;
	_return = ADS8688_SPI_ReadChipID(ADS8688x, &tempChipID);
	//---校验读取的ID信息
	if (tempChipID!=ADS8688x->msgChipID)
	{
		_return += ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：探测设备是否存在
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS8688_SPI_DetectionDevice(ADS8688_HandlerType* ADS8688x)
{
	UINT8_T tempAutoSeqEn[2] = { 0 };
	UINT8_T _return = OK_0;
	_return=ADS8688_SPI_ReadProgramReg(pADS8688Device0, ADS8688_PROG_REG_AUTO_SEQ_EN, tempAutoSeqEn);
	//---校验结果是否正确
	if (tempAutoSeqEn[1]!=ADS8688x->msgAutoSeqEn)
	{
		_return += ERROR_1;
	}
	else
	{
		//---校验设备的ID信息
		_return = ADS8688_SPI_CheckChipID(ADS8688x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取自动扫描通道序列的AD转换数据
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  ADS8688_SPI_GetAutoRSTModeChannelResult(ADS8688_HandlerType *ADS8688x, UINT8_T chNum)
{
	UINT8_T i = 0;
	UINT8_T temp = 0;
	UINT8_T _return = 0;
	for (i = 0; i < chNum; i++)
	{
		if (ADS8688x->msgSPI.msgCS.msgGPIOPort!=NULL)
		{
			GPIO_OUT_0(ADS8688x->msgSPI.msgCS.msgGPIOPort, ADS8688x->msgSPI.msgCS.msgGPIOBit);
		}

		//---写高位
		_return += ADS8688_SPI_SEND_CMD(ADS8688x, 0x00, NULL);

		//---写低位
		_return += ADS8688_SPI_SEND_CMD(ADS8688x, 0x00, NULL);

		//---AD转换结果高位在前，低位在后
		_return += ADS8688_SPI_SEND_CMD(ADS8688x, 0x00, &temp);
		ADS8688x->msgChannelADCResult[i] = temp;
		_return += ADS8688_SPI_SEND_CMD(ADS8688x, 0x00, &temp);
		ADS8688x->msgChannelADCResult[i] = (ADS8688x->msgChannelADCResult[i] << 8) + temp;

		if (ADS8688x->msgSPI.msgCS.msgGPIOPort != NULL)
		{
			GPIO_OUT_1(ADS8688x->msgSPI.msgCS.msgGPIOPort, ADS8688x->msgSPI.msgCS.msgGPIOBit);
		}
	}
	return  _return;
}