#include "ADS868X_cfg.h"

//===全局变量定义
ADS868X_HandlerType   g_ADS868XDevice0 = { 0 };
pADS868X_HandlerType  pADS868XDevice0 = &g_ADS868XDevice0;

//===统一发送字节命令
UINT8_T(*ADS868X_SPI_SEND_CMD)(ADS868X_HandlerType *, UINT8_T, UINT8_T *);
//===统一发送数组命令
UINT8_T(*ADS868X_SPI_SEND_ARRAY)(ADS868X_HandlerType*, UINT8_T*, UINT8_T*,UINT16_T);

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void ADS868X_SPI_Device0_Init(ADS868X_HandlerType *ADS868xx)
{

	//---复位信号
	ADS868xx->msgHWRST.msgGPIOPort = NULL;
	ADS868xx->msgHWRST.msgGPIOBit = LL_GPIO_PIN_0;

	//---GPIO时钟使能
	if (ADS868xx->msgHWRST.msgGPIOPort != NULL)
	{
		GPIOTask_Clock(ADS868xx->msgHWRST.msgGPIOPort, 1);
	}

	//---CS
	ADS868xx->msgSPI.msgCS.msgGPIOPort = GPIOA;
	ADS868xx->msgSPI.msgCS.msgGPIOBit = LL_GPIO_PIN_4;

	//---SCK
	ADS868xx->msgSPI.msgSCK.msgGPIOPort = GPIOA;
	ADS868xx->msgSPI.msgSCK.msgGPIOBit = LL_GPIO_PIN_5;

	//---MISO  SD0
	ADS868xx->msgSPI.msgMISO.msgGPIOPort = GPIOA;
	ADS868xx->msgSPI.msgMISO.msgGPIOBit = LL_GPIO_PIN_6;

	//---MOSI SDI
	ADS868xx->msgSPI.msgMOSI.msgGPIOPort = GPIOA;
	ADS868xx->msgSPI.msgMOSI.msgGPIOBit = LL_GPIO_PIN_7;

	//---GPIO的配置
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---GPIO的初始化
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;					//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;		//---GPIO的速度
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;		//---输出模式---推挽输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;						//---上拉使能

	//---初始化RST
	if (ADS868xx->msgHWRST.msgGPIOPort != NULL)
	{
		GPIO_InitStruct.Pin = ADS868xx->msgHWRST.msgGPIOBit;
		GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
		LL_GPIO_Init(ADS868xx->msgHWRST.msgGPIOPort, &GPIO_InitStruct);
		GPIO_OUT_1(ADS868xx->msgHWRST.msgGPIOPort, ADS868xx->msgHWRST.msgGPIOBit);
	}

	//---复用模式
	#ifndef USE_MCU_STM32F1
		//---端口复用模式
		ADS868xx->msgSPI.msgGPIOAlternate = LL_GPIO_AF_5;
	#endif
	//---SPI序号
	ADS868xx->msgSPI.msgSPIx = SPI1;
	#ifndef USE_MCU_STM32F1
		//---SPI的协议
		ADS868xx->msgSPI.msgStandard = LL_SPI_PROTOCOL_MOTOROLA;
	#endif

	UINT8_T i = 0;
	//---参考电压配置
	ADS868xx->msgREFPowerUV = ADS868X_REF_POWER_UV;
	for (i = 0; i < ADS868X_CHANNEL_MAX; i++)
	{
		ADS868xx->msgChannelRange[i] = 0;
		ADS868xx->msgIsPositive[i] = 0;
		ADS868xx->msgChannelNowADCResult[i] = 0;
		ADS868xx->msgChannelOldADCResult[i] = 0;
		ADS868xx->msgChannelPowerResult[i] = 0;
		ADS868X_SPI_ChannelRange(ADS868xx, i);
	}
	ADS868xx->msgDeviceReady = 0;
	ADS868xx->msgInitRetryCount = 3;
	ADS868xx->msgChipID = 0;
	//---默认配置特性
	ADS868xx->msgFeature = 0x28;
	//---默认是0xFF
	ADS868xx->msgAutoSeqEn = 0xFF;
	//---定义脉冲宽度
	ADS868xx->msgSPI.msgPluseWidth = 2;
	//---时钟空闲为低电平
	ADS868xx->msgSPI.msgCPOL = 0;
	//---数据采样在第二个时钟边沿
	ADS868xx->msgSPI.msgCPOH = 1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void ADS868X_SPI_Device1_Init(ADS868X_HandlerType *ADS868xx)
{
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void ADS868X_SPI_Device2_Init(ADS868X_HandlerType *ADS868xx)
{
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_HW_Init(ADS868X_HandlerType *ADS868xx)
{
	//---注销当前的所有配置
	SPITask_DeInit(&(ADS868xx->msgSPI));
	//---硬件端口的配置---硬件实现
	SPITask_MHW_GPIO_Init(&(ADS868xx->msgSPI));
	//---硬件SPI的初始化
	LL_SPI_InitTypeDef SPI_InitStruct = {0};
	//---SPI的模式配置
	SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
	SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;						//---主机模式
	SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;				//---8位数据
	//---时钟极性的设置
	if (ADS868xx->msgSPI.msgCPOL == 0)
	{
		//---CLK空闲时为低电平 (CLK空闲是只能是低电平)
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
		GPIO_OUT_0(ADS868xx->msgSPI.msgSCK.msgGPIOPort, ADS868xx->msgSPI.msgSCK.msgGPIOBit);
	}
	else
	{
		//---CLK空闲时为高电平 (CLK空闲是只能是低电平)
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_HIGH;
	}
	//---数据采样的时钟边沿位置
	if (ADS868xx->msgSPI.msgCPOH ==0)
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
	}
	else
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_2EDGE;
	}
	SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;							//---软件控制
	SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV2;		//---系统时钟4分频
	SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;						//---高位在前
	SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;	//---硬件CRC不使能
	SPI_InitStruct.CRCPoly = 7;
	//---初始化查询方式的SPI
	SPITask_MHW_PollMode_Init(&(ADS868xx->msgSPI), SPI_InitStruct);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_SW_Init(ADS868X_HandlerType *ADS868xx)
{
	SPITask_DeInit(&(ADS868xx->msgSPI));

	//---硬件端口的配置---软件实现
	SPITask_MSW_GPIO_Init(&(ADS868xx->msgSPI));

	//---时钟线的极性
	if (ADS868xx->msgSPI.msgCPOL == 0)
	{
		GPIO_OUT_0(ADS868xx->msgSPI.msgSCK.msgGPIOPort, ADS868xx->msgSPI.msgSCK.msgGPIOBit);
	}
	else
	{
		GPIO_OUT_1(ADS868xx->msgSPI.msgSCK.msgGPIOPort, ADS868xx->msgSPI.msgSCK.msgGPIOBit);
	}

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送字节命令
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_SW_SendCmd(ADS868X_HandlerType *ADS868xx, UINT8_T cmd, UINT8_T *pRVal)
{
	//---数据发送
	return SPITask_MSW_WriteAndReadByteMSB(&(ADS868xx->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送数组命令
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_SW_SendArray(ADS868X_HandlerType* ADS868xx, UINT8_T* pWVal, UINT8_T* pRVal, UINT16_T length)
{
	//---数据发送
	return SPITask_MSW_WriteAndReadDataMSB(&(ADS868xx->msgSPI), pWVal, pRVal, length);
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送字节命令
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_HW_SendCmd(ADS868X_HandlerType *ADS868xx, UINT8_T cmd, UINT8_T *pRVal)
{
	//---数据发送
	return SPITask_MHW_PollMode_WriteAndReadByte(&(ADS868xx->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送数组命令
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_HW_SendArray(ADS868X_HandlerType* ADS868xx, UINT8_T *pWVal, UINT8_T* pRVal,UINT16_T length)
{
	//---数据发送
	return SPITask_MHW_PollMode_WriteAndReadData(&(ADS868xx->msgSPI), pWVal, pRVal,length);
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_Init(ADS868X_HandlerType *ADS868xx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHW)
{
	//---使用的DHT11的端口
	if ((ADS868xx != NULL) && (ADS868xx == ADS868X_TASK_ONE))
	{
		ADS868X_SPI_Device0_Init(ADS868xx);
	}
	else if ((ADS868xx != NULL) && (ADS868xx == ADS868X_TASK_TWO))
	{
		ADS868X_SPI_Device1_Init(ADS868xx);
	}
	else if ((ADS868xx != NULL) && (ADS868xx == ADS868X_TASK_THREE))
	{
		ADS868X_SPI_Device2_Init(ADS868xx);
	}
	else
	{
		return ERROR_1;
	}

	//---判断初始化的方式
	if (isHW != 0)
	{
		ADS868xx->msgSPI.msgModelIsHW = 1;
		ADS868X_SPI_HW_Init(ADS868xx);
		ADS868X_SPI_SEND_CMD = ADS868X_SPI_HW_SendCmd;
		ADS868X_SPI_SEND_ARRAY = ADS868X_SPI_HW_SendArray;
	}
	else
	{
		ADS868xx->msgSPI.msgModelIsHW = 0;
		ADS868X_SPI_SW_Init(ADS868xx);
		ADS868X_SPI_SEND_CMD = ADS868X_SPI_SW_SendCmd;
		ADS868X_SPI_SEND_ARRAY = ADS868X_SPI_SW_SendArray;
	}

	//---注册ms延时时间
	if (pFuncDelayms != NULL)
	{
		ADS868xx->msgFuncDelayms = pFuncDelayms;
	}
	else
	{
		ADS868xx->msgFuncDelayms = DelayTask_ms;
	}

	//---注册us延时函数
	if (pFuncDelayus != NULL)
	{
		ADS868xx->msgSPI.msgFuncDelayus = pFuncDelayus;
	}
	else
	{
		ADS868xx->msgSPI.msgFuncDelayus = DelayTask_us;
	}

	//---注册滴答函数
	ADS868xx->msgSPI.msgFuncTimeTick = pFuncTimerTick;

	//---配置ADS868X
	return ADS868X_SPI_ConfigInit(ADS868xx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：写ADS868X命令寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteCommandReg(ADS868X_HandlerType *ADS868xx, UINT32_T cmd)
{
	UINT8_T _return = OK_0;
	UINT8_T wTemp[2] = { 0 };
	wTemp[0] = (UINT8_T)((cmd >> 8)&0xFF);
	wTemp[1] = (UINT8_T)(cmd & 0xFF);
	if (ADS868xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_0(ADS868xx->msgSPI.msgCS.msgGPIOPort, ADS868xx->msgSPI.msgCS.msgGPIOBit);
	}
	_return = ADS868X_SPI_SEND_ARRAY(ADS868xx, wTemp, NULL, 2);
	if (ADS868xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_1(ADS868xx->msgSPI.msgCS.msgGPIOPort, ADS868xx->msgSPI.msgCS.msgGPIOBit);
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
UINT8_T ADS868X_SPI_WriteProgramReg(ADS868X_HandlerType *ADS868xx, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	UINT8_T wTemp[2] = { 0 };
	wTemp[0] = (addr << 1) | 0x01;
	wTemp[1] = val;
	if (ADS868xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_0(ADS868xx->msgSPI.msgCS.msgGPIOPort, ADS868xx->msgSPI.msgCS.msgGPIOBit);
	}
	_return = ADS868X_SPI_SEND_ARRAY(ADS868xx, wTemp, NULL, 2);
	if (ADS868xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_1(ADS868xx->msgSPI.msgCS.msgGPIOPort, ADS868xx->msgSPI.msgCS.msgGPIOBit);
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
UINT8_T ADS868X_SPI_ReadProgramReg(ADS868X_HandlerType *ADS868xx, UINT8_T addr, UINT8_T *pVal)
{
	UINT8_T _return = OK_0;
	UINT8_T wTemp[3] = { 0 };
	UINT8_T rTemp[3] = { 0 };
	wTemp[0] = (addr << 1) & 0xFE;
	if (ADS868xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_0(ADS868xx->msgSPI.msgCS.msgGPIOPort, ADS868xx->msgSPI.msgCS.msgGPIOBit);
	}
	_return = ADS868X_SPI_SEND_ARRAY(ADS868xx, wTemp, rTemp, 3);
	if (ADS868xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_1(ADS868xx->msgSPI.msgCS.msgGPIOPort, ADS868xx->msgSPI.msgCS.msgGPIOBit);
	}

	//---数据拷贝
	pVal[0] = rTemp[1];
	pVal[1] = rTemp[2];

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读命令返回
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ReadCommandBack(ADS868X_HandlerType* ADS868xx, UINT8_T* pVal)
{
	return ADS868X_SPI_ReadProgramReg(ADS868xx, ADS868X_CMD_READ_BACK, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：继续工作在选中的状态
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_NO_OP(ADS868X_HandlerType* ADS868xx)
{
	return ADS868X_SPI_WriteCommandReg(ADS868xx, ADS868X_CMD_REG_NO_OP);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_STDBY(ADS868X_HandlerType* ADS868xx)
{
	return ADS868X_SPI_WriteCommandReg(ADS868xx, ADS868X_CMD_REG_STDBY);
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：
//////输入参数:
//////输出参数:
//////说		明：退出此模式需执行AUTO_RST或者MAN_CH_n命令，且需要等待至少20us以保证正常数据的AD转换
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_PWRDN(ADS868X_HandlerType* ADS868xx)
{
	return ADS868X_SPI_WriteCommandReg(ADS868xx, ADS868X_CMD_REG_PWR_DN);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：硬件复位设备
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  ADS868X_SPI_HardReset(ADS868X_HandlerType *ADS868xx)
{
	if (ADS868xx->msgHWRST.msgGPIOPort!=NULL)
	{
		GPIO_OUT_0(ADS868xx->msgHWRST.msgGPIOPort, ADS868xx->msgHWRST.msgGPIOBit);
		ADS868xx->msgFuncDelayms(1);
		GPIO_OUT_1(ADS868xx->msgHWRST.msgGPIOPort, ADS868xx->msgHWRST.msgGPIOBit);
		ADS868xx->msgFuncDelayms(1);
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
UINT8_T  ADS868X_SPI_SoftReset(ADS868X_HandlerType *ADS868xx)
{
	return ADS868X_SPI_WriteCommandReg(ADS868xx, ADS868X_CMD_REG_RST);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：设备复位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_Reset(ADS868X_HandlerType* ADS868xx)
{
	UINT8_T _return = OK_0;
	if (ADS868xx->msgHWRST.msgGPIOPort != NULL)
	{
		_return = ADS868X_SPI_HardReset(ADS868xx);
	}
	else
	{
		_return = ADS868X_SPI_SoftReset(ADS868xx);
	}
	ADS868xx->msgDeviceReady = 0;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：进入自动扫描模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_AUTORST(ADS868X_HandlerType* ADS868xx)
{
	return ADS868X_SPI_WriteCommandReg(ADS868xx, ADS868X_CMD_REG_AUTO_RST);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：设置手动扫描通道
//////输入参数:
//////输出参数:
//////说		明：退出此模式需执行AUTO_RST或者MAN_CH_n命令，且需要等待至少20us以保证正常数据的AD转换
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ManualChannel(ADS868X_HandlerType* ADS868xx,UINT16_T manualCHCmd)
{
	return ADS868X_SPI_WriteCommandReg(ADS868xx, manualCHCmd);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：设置设备ID
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteChipID(ADS868X_HandlerType* ADS868xx, UINT8_T devid)
{
	devid <<= 6;
	ADS868xx->msgChipID = (devid & 0xC0) | ADS868xx->msgFeature;
	return ADS868X_SPI_WriteProgramReg(ADS868xx, ADS868X_PROG_REG_FEATURE_SELECT, ADS868xx->msgChipID);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：读取设备ID
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ReadChipID(ADS868X_HandlerType* ADS868xx, UINT8_T *pDevID)
{
	UINT8_T _return= ADS868X_SPI_ReadProgramReg(ADS868xx, ADS868X_PROG_REG_FEATURE_SELECT, pDevID);
	*pDevID &= 0xC0;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：校验设备ID
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_CheckChipID(ADS868X_HandlerType* ADS868xx)
{
	UINT8_T tempChipID = 0x00;
	UINT8_T _return = OK_0;
	_return = ADS868X_SPI_ReadChipID(ADS868xx, &tempChipID);
	//---校验读取的ID信息
	if (tempChipID!=ADS868xx->msgChipID)
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
UINT8_T ADS868X_SPI_DetectionDevice(ADS868X_HandlerType* ADS868xx)
{
	UINT8_T tempAutoSeqEn[2] = { 0 };
	UINT8_T _return = OK_0;
	_return=ADS868X_SPI_ReadProgramReg(pADS868XDevice0, ADS868X_PROG_REG_AUTO_SEQ_EN, tempAutoSeqEn);
	//---校验结果是否正确
	if (tempAutoSeqEn[1]!=ADS868xx->msgAutoSeqEn)
	{
		_return += ERROR_1;
	}
	else
	{
		//---校验设备的ID信息
		_return = ADS868X_SPI_CheckChipID(ADS868xx);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置自动扫描序列通道
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteAUTOSEQEN(ADS868X_HandlerType* ADS868xx, UINT8_T seq)
{
	ADS868xx->msgAutoSeqEn = seq;
	return ADS868X_SPI_WriteProgramReg(ADS868xx, ADS868X_PROG_REG_AUTO_SEQ_EN, seq);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取自动扫描序列通道
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ReadAUTOSEQEN(ADS868X_HandlerType* ADS868xx, UINT8_T *pAutoSeqEn)
{
	UINT8_T tempAutoSeqEn[2] = { 0 };
	UINT8_T _return= ADS868X_SPI_ReadProgramReg(ADS868xx, ADS868X_PROG_REG_AUTO_SEQ_EN, tempAutoSeqEn);
	if (_return==OK_0)
	{
		if (tempAutoSeqEn[1]==ADS868xx->msgAutoSeqEn)
		{
			*pAutoSeqEn = tempAutoSeqEn[1];
		}
		else
		{
			_return = ERROR_2;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：通道掉电模式设置
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteChannelPWRDN(ADS868X_HandlerType* ADS868xx, UINT8_T ch)
{
	ADS868xx->msgChannelPWRDN = ch;
	return ADS868X_SPI_WriteProgramReg(ADS868xx, ADS868X_PROG_REG_CH_PWR_DN, ch);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：通道掉电模式读取
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ReadChannelPWRDN(ADS868X_HandlerType* ADS868xx, UINT8_T *pPWRDN)
{
	UINT8_T tempPWRDN[2] = { 0 };
	UINT8_T _return = ADS868X_SPI_ReadProgramReg(ADS868xx, ADS868X_PROG_REG_CH_PWR_DN, tempPWRDN);
	if (_return == OK_0)
	{
		if (tempPWRDN[1] == ADS868xx->msgChannelPWRDN)
		{
			*pPWRDN = tempPWRDN[1];
		}
		else
		{
			_return = ERROR_2;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：通道掉电模式设置
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteFeature(ADS868X_HandlerType* ADS868xx, UINT8_T feature)
{
	ADS868xx->msgFeature = (feature&0x3F)|ADS868xx->msgChipID;
	return ADS868X_SPI_WriteProgramReg(ADS868xx, ADS868X_PROG_REG_FEATURE_SELECT, feature);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：通道掉电模式读取
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ReadFeature(ADS868X_HandlerType* ADS868xx, UINT8_T *pFeature)
{
	UINT8_T tempFeature[2] = { 0 };
	UINT8_T _return = ADS868X_SPI_ReadProgramReg(ADS868xx, ADS868X_PROG_REG_FEATURE_SELECT, tempFeature);
	if (_return == OK_0)
	{
		if (tempFeature[1] == ADS868xx->msgFeature)
		{
			*pFeature = tempFeature[1];
		}
		else
		{
			_return = ERROR_2;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置通道的量程范围
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteChannelRange(ADS868X_HandlerType* ADS868xx, UINT8_T chReg, UINT8_T range)
{
	UINT8_T ch = ADS868X_CHANNEL_MAX;
	switch (chReg)
	{
		case ADS868X_PROG_REG_CH0_SET_RANGE:
			ADS868xx->msgChannelRange[0] = range;
			ch = 0;
			break;
		case ADS868X_PROG_REG_CH1_SET_RANGE:
			ADS868xx->msgChannelRange[1] = range;
			ch = 1;
			break;
		case ADS868X_PROG_REG_CH2_SET_RANGE:
			ADS868xx->msgChannelRange[2] = range;
			ch = 2;
			break;
		case ADS868X_PROG_REG_CH3_SET_RANGE:
			ADS868xx->msgChannelRange[3] = range;
			ch = 3;
			break;
		case ADS868X_PROG_REG_CH4_SET_RANGE:
			ADS868xx->msgChannelRange[4] = range;
			ch = 4;
			break;
		case ADS868X_PROG_REG_CH5_SET_RANGE:
			ADS868xx->msgChannelRange[5] = range;
			ch = 5;
			break;
		case ADS868X_PROG_REG_CH6_SET_RANGE:
			ADS868xx->msgChannelRange[6] = range;
			ch = 6;
			break;
		case ADS868X_PROG_REG_CH7_SET_RANGE:
			ADS868xx->msgChannelRange[7] = range;
			ch = 7;
			break;
		default:
			return ERROR_1;
	}

	//---每个通道的量程的配置
	ADS868X_SPI_ChannelRange(ADS868xx, ch);
	//---设置通道的量程
	return ADS868X_SPI_WriteProgramReg(ADS868xx, chReg, range);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置通道的量程范围
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ReadChannelRange(ADS868X_HandlerType* ADS868xx, UINT8_T chReg, UINT8_T *pRange)
{
	UINT8_T ch = ADS868X_CHANNEL_MAX;
	UINT8_T tempChannelRange[2] = { 0 };
	UINT8_T _return = OK_0;
	switch (chReg)
	{
		case ADS868X_PROG_REG_CH0_SET_RANGE:
			ch = 0;
			break;
		case ADS868X_PROG_REG_CH1_SET_RANGE:
			ch = 1;
			break;
		case ADS868X_PROG_REG_CH2_SET_RANGE:
			ch = 2;
			break;
		case ADS868X_PROG_REG_CH3_SET_RANGE:
			ch = 3;
			break;
		case ADS868X_PROG_REG_CH4_SET_RANGE:
			ch = 4;
			break;
		case ADS868X_PROG_REG_CH5_SET_RANGE:
			ch = 5;
			break;
		case ADS868X_PROG_REG_CH6_SET_RANGE:
			ch = 6;
			break;
		case ADS868X_PROG_REG_CH7_SET_RANGE:
			ch = 7;
			break;
		default:
			return ERROR_1;
	}
	//---读取通道的量程
	_return=ADS868X_SPI_ReadProgramReg(ADS868xx, chReg, tempChannelRange);
	//---判断读取结果
	if (_return == OK_0)
	{
		if (tempChannelRange[1] == ADS868xx->msgChannelRange[ch])
		{
			*pRange = tempChannelRange[1];
		}
		else
		{
			_return = ERROR_2;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置参考电压uv
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteREFPowerUV(ADS868X_HandlerType* ADS868xx, UINT32_T refUV)
{
	ADS868xx->msgREFPowerUV = refUV;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取参考电压
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT32_T ADS868X_SPI_ReadREFPowerUV(ADS868X_HandlerType* ADS868xx, UINT32_T refUV)
{
	return ADS868xx->msgREFPowerUV;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置参考电压mv
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteREFPowerMV(ADS868X_HandlerType* ADS868xx, UINT32_T refMV)
{
	ADS868xx->msgREFPowerUV = refMV*1000;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置每通道的量程和量程最大值
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ChannelRange(ADS868X_HandlerType* ADS868xx, UINT8_T chIndex)
{
	UINT8_T _return = OK_0;
	if (chIndex==ADS868X_CHANNEL_MAX)
	{
		_return = ERROR_1;
	}
	else
	{
		switch (ADS868xx->msgChannelRange[chIndex])
		{
			//---正负1.25倍的VREF
			case ADS868X_RANGE_5120MV_5120MV:
				ADS868xx->msgChannelRangeIsPositive[chIndex] = 0;
				ADS868xx->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS868xx->msgREFPowerUV * 1250);//5120000000;
				ADS868xx->msgChannelRangeBaseUVX1000[chIndex] = (ADS868xx->msgChannelRangeFullUVX1000[chIndex] * 2) / 65536; //156250;
				break;
			//---正负0.625倍的VREF
			case ADS868X_RANGE_2560MV_2560MV:
				ADS868xx->msgChannelRangeIsPositive[chIndex] = 0;
				ADS868xx->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS868xx->msgREFPowerUV * 625); //2560000000;
				ADS868xx->msgChannelRangeBaseUVX1000[chIndex] = (ADS868xx->msgChannelRangeFullUVX1000[chIndex] * 2) / 65536; //78125;
				break;
			//---正2.5倍的VREF
			case ADS868X_RANGE_0MV_10240MV:
				ADS868xx->msgChannelRangeIsPositive[chIndex] = 1;
				ADS868xx->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS868xx->msgREFPowerUV * 2500);//10240000000;
				ADS868xx->msgChannelRangeBaseUVX1000[chIndex] = ADS868xx->msgChannelRangeFullUVX1000[chIndex] / 65536; //156250;
				break;
			//---正1.25倍的VREF
			case ADS868X_RANGE_0MV_5120MV:
				ADS868xx->msgChannelRangeIsPositive[chIndex] = 1;
				ADS868xx->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS868xx->msgREFPowerUV* 1250);//5120000000;
				ADS868xx->msgChannelRangeBaseUVX1000[chIndex] = ADS868xx->msgChannelRangeFullUVX1000[chIndex] / 65536; //78125;
				break;
			//---正负2.5倍的VREF
			case ADS868X_RANGE_10240MV_10240MV:
			default:
				ADS868xx->msgChannelRangeIsPositive[chIndex] = 0;
				ADS868xx->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS868xx->msgREFPowerUV * 2500);//10240000000;
				ADS868xx->msgChannelRangeBaseUVX1000[chIndex] = (ADS868xx->msgChannelRangeFullUVX1000[chIndex] * 2) / 65536; //312500;
				break;
		}
	}
	return _return;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：通过ADC的采集结果计算ADC通道的电压值
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_CalcChannelPower(ADS868X_HandlerType* ADS868xx, UINT8_T chIndex,UINT8_T isCalcDelta)
{
	//---设置无数据
	ADS868xx->msgIsPositive[chIndex] = 0;
	UINT32_T adcDelta = 0;
	UINT64_T calcPower = 0;
	//---判断是否需要计算差值
	if (isCalcDelta != 0)
	{
		//---获取上次和本次的采样结果的绝对差值
		adcDelta = ABS_SUB(ADS868xx->msgChannelNowADCResult[chIndex], ADS868xx->msgChannelOldADCResult[chIndex]);
		//---软件数据补偿拟合开始
		if (adcDelta < 15)
		{
			if (adcDelta>5)
			{
				ADS868xx->msgChannelOldADCResult[chIndex] = MAX(ADS868xx->msgChannelNowADCResult[chIndex], ADS868xx->msgChannelOldADCResult[chIndex])-2;
			}
			else if (ADS868xx->msgChannelNowADCResult[chIndex] > ADS868xx->msgChannelOldADCResult[chIndex])
			{
				ADS868xx->msgChannelOldADCResult[chIndex] = ADS868xx->msgChannelNowADCResult[chIndex];
				if(adcDelta>2)
				{
					ADS868xx->msgChannelOldADCResult[chIndex] -=2;
				}
			}
			else
			{
				ADS868xx->msgChannelOldADCResult[chIndex] = MAX(ADS868xx->msgChannelNowADCResult[chIndex], ADS868xx->msgChannelOldADCResult[chIndex]);
			}
			calcPower = ADS868xx->msgChannelOldADCResult[chIndex];
		}
		else
		{
			calcPower = ADS868xx->msgChannelNowADCResult[chIndex];
			ADS868xx->msgChannelOldADCResult[chIndex] = ADS868xx->msgChannelNowADCResult[chIndex];
		}
	}
	else
	{
		calcPower = ADS868xx->msgChannelNowADCResult[chIndex];
	}
	calcPower &= 0xFFFC;
	//---软件数据补偿拟合结束
	//---将数字量转换为模拟量
	calcPower *= ADS868xx->msgChannelRangeBaseUVX1000[chIndex];
	double adcPower = 0;
	//---判断ADC采样的量程是双极性还是单极性
	if (ADS868xx->msgChannelRangeIsPositive[chIndex] == 0)
	{
		if ((ADS868xx->msgChannelNowADCResult[chIndex] & 0x8000) != 0)
		{
			ADS868xx->msgIsPositive[chIndex] = 2;
			ADS868xx->msgChannelPowerResult[chIndex] = (UINT32_T)((calcPower - ADS868xx->msgChannelRangeFullUVX1000[chIndex]) / 1000);
		}
		else
		{
			ADS868xx->msgIsPositive[chIndex] = 1;
			ADS868xx->msgChannelPowerResult[chIndex] = (UINT32_T)((ADS868xx->msgChannelRangeFullUVX1000[chIndex] - calcPower) / 1000);
		}
	}
	else
	{
		ADS868xx->msgIsPositive[chIndex] = 2;
		ADS868xx->msgChannelPowerResult[chIndex] = (UINT32_T)(calcPower / 1000);
	}
	//---误差消除计算
	if (ADS868xx->msgADCKP[chIndex] != 0)
	{
		adcPower = ADS868xx->msgChannelPowerResult[chIndex];
		adcPower *= ADS868xx->msgADCKP[chIndex];
		if (adcPower< ADS868xx->msgADCDelta[chIndex])
		{
			ADS868xx->msgIsPositive[chIndex] = 1;
			adcPower = (ADS868xx->msgADCDelta[chIndex] - adcPower);
		}
		else
		{
			adcPower -= ADS868xx->msgADCDelta[chIndex];
		}
		ADS868xx->msgChannelPowerResult[chIndex] = (UINT32_T)adcPower;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取自动扫描通道序列的AD转换数据
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_GetAutoRSTResult(ADS868X_HandlerType *ADS868xx, UINT8_T chNum)
{
	UINT8_T i = 0;
	UINT8_T adcRTemp[4] = {0};
	UINT8_T adcWTemp[4] = { 0 };
	UINT8_T _return = 0;
	UINT8_T rstMode = ADS868xx->msgAutoSeqEn;
	//---判断设备是否初始化成功
	if (ADS868xx->msgDeviceReady == 1)
	{
		_return = ADS868X_SPI_ConfigInit(ADS868xx);
		if (_return != OK_0)
		{
			goto GoToExit;
		}
	}

	//---进入自动扫描模式
	_return =ADS868X_SPI_AUTORST(ADS868xx);

	//---扫描通道的结果
	for (i = 0; i < chNum; i++)
	{
		//---判断是否使能自动RST扫描功能
		if (rstMode & 0x01)
		{
			adcWTemp[3] = i;
			//---准备读取数据
			if (ADS868xx->msgSPI.msgCS.msgGPIOPort != NULL)
			{
				GPIO_OUT_0(ADS868xx->msgSPI.msgCS.msgGPIOPort, ADS868xx->msgSPI.msgCS.msgGPIOBit);
			}
			_return=ADS868X_SPI_SEND_ARRAY(ADS868xx, adcWTemp, adcRTemp, 4);
			//---结束数据的读取
			if (ADS868xx->msgSPI.msgCS.msgGPIOPort != NULL)
			{
				GPIO_OUT_1(ADS868xx->msgSPI.msgCS.msgGPIOPort, ADS868xx->msgSPI.msgCS.msgGPIOBit);
			}
			//---保存读取的数据
			ADS868xx->msgChannelNowADCResult[i] = adcRTemp[2];
			ADS868xx->msgChannelNowADCResult[i] = (ADS868xx->msgChannelNowADCResult[i] << 8) + adcRTemp[3];
			//---计算采样结果
			ADS868X_SPI_CalcChannelPower(ADS868xx, i,0);
		}
		rstMode >>= 1;
	}
	GoToExit:
	return  _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_GetAutoRSTNSampleResult(ADS868X_HandlerType* ADS868xx, UINT8_T chNum)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	UINT8_T j = 0;
	UINT8_T rstMode = ADS868xx->msgAutoSeqEn;
	//---保存采样结果
	UINT16_T adcSampleTemp[ADS868X_CHANNEL_MAX][ADS868X_N_SAMPLE_COUNT] = { 0 };
	//---获取采样结果
	for (i = 0; i < ADS868X_N_SAMPLE_COUNT; i++)
	{
		//---获取采样结果
		_return = ADS868X_SPI_GetAutoRSTResult(ADS868xx, chNum);
		//---采样数据搬移
		for (j=0;j< ADS868X_CHANNEL_MAX;j++)
		{
			adcSampleTemp[j][i] = ADS868xx->msgChannelNowADCResult[j];
		}
		//---校验数据
		if (_return != OK_0)
		{
			break;
		}
	}
	if (_return == OK_0)
	{
		//---采样数据搬移
		for (j = 0; j < ADS868X_CHANNEL_MAX; j++)
		{
			//---判断是否使能自动RST扫描功能
			if (rstMode & 0x01)
			{
				//---升序排列数据
				AscSortFun2(adcSampleTemp[j], ADS868X_N_SAMPLE_COUNT);
				//---计算均值
				ADS868xx->msgChannelNowADCResult[j] = CalcAvgFun1(adcSampleTemp[j], (ADS868X_N_SAMPLE_COUNT - 2), 2);
				//---计算采样的电压值
				ADS868X_SPI_CalcChannelPower(ADS868xx, j,1);
			}
			rstMode >>= 1;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：获取收到扫描通道的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  ADS868X_SPI_GetManualChannelResult(ADS868X_HandlerType* ADS868xx, UINT16_T manualChannel)
{
	UINT8_T _return = OK_0;
	UINT8_T adcRTemp[4] = { 0 };
	UINT8_T adcWTemp[4] = { 0 };
	UINT8_T adcChannel = 0;
	//---判断设备是否初始化成功
	if (ADS868xx->msgDeviceReady==1)
	{
		_return=ADS868X_SPI_ConfigInit(ADS868xx);
		if (_return!=OK_0)
		{
			goto GoToExit;
		}
	}
	//---设置手动扫描通道
	_return = ADS868X_SPI_ManualChannel(ADS868xx, manualChannel);
	//---准备读取设置的扫描通道的值
	if (ADS868xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_0(ADS868xx->msgSPI.msgCS.msgGPIOPort, ADS868xx->msgSPI.msgCS.msgGPIOBit);
	}
	//---读取ADC采样的结果
	_return = ADS868X_SPI_SEND_ARRAY(ADS868xx, adcWTemp, adcRTemp, 4);
	//---结束读取设置的扫描通道的值
	if (ADS868xx->msgSPI.msgCS.msgGPIOPort != NULL)
	{
		GPIO_OUT_1(ADS868xx->msgSPI.msgCS.msgGPIOPort, ADS868xx->msgSPI.msgCS.msgGPIOBit);
	}
	//---通道的转换
	adcChannel = (UINT8_T)(manualChannel >> 10) & 0x0F;
	//---判断是否是AUX通道配置
	if (adcChannel<8)
	{
		ADS868xx->msgChannelNowADCResult[adcChannel] = adcRTemp[2];
		ADS868xx->msgChannelNowADCResult[adcChannel] = (ADS868xx->msgChannelNowADCResult[adcChannel] << 8) + adcRTemp[3];
		//---计算采样结果
		ADS868X_SPI_CalcChannelPower(ADS868xx, adcChannel,0);
	}
	GoToExit:
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：手动通道采样N次的测试结果
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_GetManualChannelNSampleResult(ADS868X_HandlerType* ADS868xx, UINT16_T manualChannel)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---保存采样结果
	UINT16_T adcSampleTemp[ADS868X_N_SAMPLE_COUNT] = { 0 };
	//---获取ADC采样通道的序号
	UINT8_T adcChannelIndex = (UINT8_T)(manualChannel >> 10) & 0x0F;
	//---获取采样结果
	for ( i = 0; i < ADS868X_N_SAMPLE_COUNT; i++)
	{
		_return = ADS868X_SPI_GetManualChannelResult(ADS868xx, manualChannel);
		adcSampleTemp[i] = ADS868xx->msgChannelNowADCResult[adcChannelIndex];
		if (_return!=OK_0)
		{
			break;
		}
	}
	if (_return==OK_0)
	{
		//---升序排列数据
		AscSortFun2(adcSampleTemp, ADS868X_N_SAMPLE_COUNT);
		//---计算均值
		ADS868xx->msgChannelNowADCResult[adcChannelIndex] = CalcAvgFun1(adcSampleTemp, (ADS868X_N_SAMPLE_COUNT - 2), 2);
		//---计算采样的电压值
		ADS868X_SPI_CalcChannelPower(ADS868xx, adcChannelIndex,1);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：校准通道的误差
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_CalibrationChannelErr(ADS868X_HandlerType* ADS868xx)
{
	UINT8_T i = 0;
	UINT8_T rstMode = ADS868xx->msgAutoSeqEn;
	for (i = 0; i < ADS868X_CHANNEL_MAX; i++)
	{
		if ((rstMode&0x01)==0)
		{
			if (i==0)
			{
				////---1号板参数
				//ADS868xx->msgADCKP[i] = 1.013216;
				//ADS868xx->msgADCDelta[i] = 27130;

				//---2号板参数
				ADS868xx->msgADCKP[i] = 1.013216;
				ADS868xx->msgADCDelta[i] = 26430;
			}
			else
			{
				////---1号板参数
				//ADS868xx->msgADCKP[i] = 1.0129;
				//ADS868xx->msgADCDelta[i] = 25870;

				//---2号板参数
				ADS868xx->msgADCKP[i] = 1.0129;
				ADS868xx->msgADCDelta[i] = 27070;
			}
			
		}
		rstMode >>= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：初始化配置
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ConfigInit(ADS868X_HandlerType* ADS868xx)
{
	UINT8_T _return = OK_0;
	UINT8_T tempBuffer[3] = { 0 };
	UINT8_T i = 0;
	if (ADS868xx->msgInitRetryCount==0)
	{
		ADS868xx->msgInitRetryCount = 1;
	}

	//---循环多次初始化设备
	for (i=0;i< ADS868xx->msgInitRetryCount;i++)
	{
		//---复位芯片
		_return = ADS868X_SPI_Reset(ADS868xx);
		//---校验
		if (_return == OK_0)
		{
			//---设备特征配置
			_return = ADS868X_SPI_WriteFeature(ADS868xx, 0x28);
			//---校验
			if (_return == OK_0)
			{
				//---读取设备的特征
				_return = ADS868X_SPI_ReadFeature(ADS868xx, tempBuffer);
				//---校验
				if (_return == OK_0)
				{
					break;
				}
			}
		}
	}

	//---设置扫描方式
	_return = ADS868X_SPI_WriteAUTOSEQEN(ADS868xx, 0xF0);
	//---读取设置的值
	_return = ADS868X_SPI_ReadProgramReg(ADS868xx, ADS868X_PROG_REG_AUTO_SEQ_EN, tempBuffer);

	//---判断校验
	if (ADS868xx->msgAutoSeqEn != tempBuffer[1])
	{
		_return = ERROR_1;
		ADS868xx->msgDeviceReady = 1;
	}
	else
	{
		//---设置通道的量程
		ADS868X_SPI_WriteChannelRange(ADS868xx, ADS868X_PROG_REG_CH0_SET_RANGE, ADS868X_RANGE_0MV_5120MV);
		ADS868X_SPI_WriteChannelRange(ADS868xx, ADS868X_PROG_REG_CH1_SET_RANGE, ADS868X_RANGE_0MV_5120MV);
		ADS868X_SPI_WriteChannelRange(ADS868xx, ADS868X_PROG_REG_CH2_SET_RANGE, ADS868X_RANGE_0MV_5120MV);
		//---设置工作模式
		ADS868X_SPI_AUTORST(ADS868xx);
	}
	ADS868X_SPI_CalibrationChannelErr(ADS868xx);
	return _return;
}