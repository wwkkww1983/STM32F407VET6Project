#include "w25qxx_cfg.h"

//===全局变量的定义
W25QXX_HandlerType  g_W25QXXDevice0 = { 0 };
pW25QXX_HandlerType pW25QXXDevice0 = &g_W25QXXDevice0;

//===统一发送函数
UINT8_T(*W25QXX_SEND_CMD)(W25QXX_HandlerType *, UINT8_T, UINT8_T *);

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_Device0_Init(W25QXX_HandlerType *W25Qx)
{
	//---SPI1接口
	//---PA4------ > SPI1_NSS
	//---PA5------ > SPI1_SCK
	//---PA6------ > SPI1_MISO
	//---PA7------ > SPI1_MOSI

	//---SPI2接口
	//---PB12------ > SPI2_NSS
	//---PB13------ > SPI2_SCK
	//---PB14------ > SPI2_MISO
	//---PB15------ > SPI2_MOSI

	//---CS
	W25Qx->msgSPI.msgCS.msgGPIOPort = GPIOA;
	W25Qx->msgSPI.msgCS.msgGPIOBit = LL_GPIO_PIN_4;

	//---SCK
	W25Qx->msgSPI.msgSCK.msgGPIOPort = GPIOA;
	W25Qx->msgSPI.msgSCK.msgGPIOBit = LL_GPIO_PIN_5;

	//---MISO  
	W25Qx->msgSPI.msgMISO.msgGPIOPort = GPIOA;
	W25Qx->msgSPI.msgMISO.msgGPIOBit = LL_GPIO_PIN_6;

	//---MOSI
	W25Qx->msgSPI.msgMOSI.msgGPIOPort = GPIOA;
	W25Qx->msgSPI.msgMOSI.msgGPIOBit = LL_GPIO_PIN_7;

	//---复用模式
#ifndef USE_MCU_STM32F1
	W25Qx->msgSPI.msgGPIOAlternate = LL_GPIO_AF_5;
#endif

	//---SPI序号
	W25Qx->msgSPI.msgSPIx = SPI1;
#ifndef USE_MCU_STM32F1

	//---SPI的协议
	W25Qx->msgSPI.msgStandard = LL_SPI_PROTOCOL_MOTOROLA;
#endif

	//---定义脉冲宽度
	W25Qx->msgSPI.msgPluseWidth = 0;

	//---时钟空闲为低电平
	W25Qx->msgSPI.msgCPOL = 0;
	//---数据采样在第一个时钟边沿
	W25Qx->msgSPI.msgCPOH = 0;

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_Device1_Init(W25QXX_HandlerType *W25Qx)
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
UINT8_T W25QXX_SPI_Device2_Init(W25QXX_HandlerType *W25Qx)
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
UINT8_T W25QXX_SPI_HW_Init(W25QXX_HandlerType *W25Qx)
{
	//---注销当前的所有配置
	SPITask_DeInit(&(W25Qx->msgSPI));

	//---硬件端口的配置---硬件实现
	SPITask_MHW_GPIO_Init(&(W25Qx->msgSPI));

	//---硬件SPI的初始化
	LL_SPI_InitTypeDef SPI_InitStruct = { 0 };

	//---SPI的模式配置
	SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
	SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;						//---主机模式
	SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;				//---8位数据
																	//---时钟空闲时的极性
	if (W25Qx->msgSPI.msgCPOL == 0)
	{
		//---CLK空闲时为低电平 (CLK空闲是只能是低电平)
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;				
		GPIO_OUT_0(W25Qx->msgSPI.msgSCK.msgGPIOPort, W25Qx->msgSPI.msgSCK.msgGPIOBit);
	}
	else
	{
		//---CLK空闲时为高电平 (CLK空闲是只能是低电平)
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_HIGH;				
	}

	//---数据采样的时钟边沿位置
	if (W25Qx->msgSPI.msgCPOL == 0)
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
	}
	else
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_2EDGE;
	}
	
	SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;							//---软件控制
	SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV4;		//---系统时钟256分频
	SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;						//---高位在前
	SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;	//---硬件CRC不使能
	SPI_InitStruct.CRCPoly = 7;

	//---初始化查询方式的SPI
	SPITask_MHW_PollMode_Init(&(W25Qx->msgSPI), SPI_InitStruct);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_SW_Init(W25QXX_HandlerType *W25Qx)
{
	SPITask_DeInit(&(W25Qx->msgSPI));

	//---硬件端口的配置---软件实现
	SPITask_MSW_GPIO_Init(&(W25Qx->msgSPI));

	//---时钟空闲时的极性
	if (W25Qx->msgSPI.msgCPOL == 0)
	{
		GPIO_OUT_0(W25Qx->msgSPI.msgSCK.msgGPIOPort, W25Qx->msgSPI.msgSCK.msgGPIOBit);
	}
	else
	{
		GPIO_OUT_1(W25Qx->msgSPI.msgSCK.msgGPIOPort, W25Qx->msgSPI.msgSCK.msgGPIOBit);
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
UINT8_T W25QXX_SPI_HW_SendCmd(W25QXX_HandlerType *W25Qx, UINT8_T cmd, UINT8_T *pRVal)
{
	//---数据发送
	return SPITask_MHW_PollMode_WriteAndReadByte(&(W25Qx->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_SW_SendCmd(W25QXX_HandlerType *W25Qx, UINT8_T cmd, UINT8_T *pRVal)
{
	//---数据发送
	return SPITask_MSW_WriteAndReadByteMSB(&(W25Qx->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_Init(W25QXX_HandlerType *W25Qx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHW)
{
	//---使用的DHT11的端口
	if ((W25Qx != NULL) && (W25Qx == W25QXX_TASK_ONE))
	{
		W25QXX_SPI_Device0_Init(W25Qx);
	}
	else if ((W25Qx != NULL) && (W25Qx == W25QXX_TASK_TWO))
	{
		W25QXX_SPI_Device1_Init(W25Qx);
	}
	else if ((W25Qx != NULL) && (W25Qx == W25QXX_TASK_THREE))
	{
		W25QXX_SPI_Device2_Init(W25Qx);
	}
	else
	{
		return ERROR_1;
	}

	//---判断初始化的方式
	if (isHW != 0)
	{
		W25Qx->msgSPI.msgModelIsHW = 1;
		W25QXX_SPI_HW_Init(W25Qx);

		//---命令读写
		W25QXX_SEND_CMD = W25QXX_SPI_HW_SendCmd;
	}
	else
	{
		W25Qx->msgSPI.msgModelIsHW = 0;
		W25QXX_SPI_SW_Init(W25Qx);

		//---命令读写
		W25QXX_SEND_CMD = W25QXX_SPI_SW_SendCmd;
	}

	//---注册ms延时时间
	if (pFuncDelayms != NULL)
	{
		W25Qx->msgFuncDelayms = pFuncDelayms;
	}
	else
	{
		W25Qx->msgFuncDelayms = DelayTask_ms;
	}

	//---注册us延时函数
	if (pFuncDelayus != NULL)
	{
		W25Qx->msgSPI.msgFuncDelayus = pFuncDelayus;
	}
	else
	{
		W25Qx->msgSPI.msgFuncDelayus = DelayTask_us;
	}

	//---注册滴答函数
	W25Qx->msgSPI.msgFuncTimeTick = pFuncTimerTick;
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：自动初始化，避免同一个SPI端口挂载多个设备，速度不一致的问题
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_AutoInit(W25QXX_HandlerType* W25Qx)
{
	if (W25Qx->msgSPI.msgModelIsHW != 0)
	{
		//---软件初始化
		W25QXX_SPI_HW_Init(W25Qx);
	}
	else
	{
		//---硬件初始化
		W25QXX_SPI_SW_Init(W25Qx);
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：自动注销
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_AutoDeInit(W25QXX_HandlerType* W25Qx)
{
	//---注销当前的所有配置
	return	SPITask_DeInit(&(W25Qx->msgSPI));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 读取状态寄存器1
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_ReadRegSR1(W25QXX_HandlerType *W25Qx)
{
	UINT8_T _return = 0;
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//--发送读取状态寄存器的命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_READ_REG_SR1, NULL);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &_return);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 读取状态寄存器2
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_ReadRegSR2(W25QXX_HandlerType *W25Qx)
{
	UINT8_T _return = 0;
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//--发送读取状态寄存器的命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_READ_REG_SR2, NULL);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &_return);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 写入状态寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_WriteRegSR1(W25QXX_HandlerType *W25Qx, UINT8_T cmd)
{
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//--发送读取状态寄存器的命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_WRITE_REG_SR, NULL);
	W25QXX_SEND_CMD(W25Qx, cmd, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 写入状态寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_WriteRegSR2(W25QXX_HandlerType *W25Qx, UINT8_T cmd)
{
	//---读取SR1的值
	UINT8_T _return = W25QXX_SPI_ReadRegSR1(W25Qx);
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//--发送读取状态寄存器的命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_WRITE_REG_SR, NULL);

	//---写SR1
	W25QXX_SEND_CMD(W25Qx, _return, NULL);

	//---写SR2
	W25QXX_SEND_CMD(W25Qx, cmd, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 写使能
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EnableWrite(W25QXX_HandlerType *W25Qx)
{
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//--发送读取状态寄存器的命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_ENABLE_WRITE, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 写使能
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_DisableWrite(W25QXX_HandlerType *W25Qx)
{
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//---发送读取状态寄存器的命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_DISABLE_WRITE, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：  读取芯片ID
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT16_T W25QXX_SPI_ReadID(W25QXX_HandlerType *W25Qx)
{
	UINT8_T temp = 0;
	UINT16_T  _return = 0;
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//--发送读取ID命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_MANUFACT_DEVICE_ID, NULL);
	W25QXX_SEND_CMD(W25Qx, 0x00, NULL);
	W25QXX_SEND_CMD(W25Qx, 0x00, NULL);
	W25QXX_SEND_CMD(W25Qx, 0x00, NULL);

	//---读取设备的ID信息高位值
	W25QXX_SEND_CMD(W25Qx, 0xFF, &temp);
	_return = temp;

	//---读取设备的ID信息低位值
	W25QXX_SEND_CMD(W25Qx, 0xFF, &temp);
	_return = (_return << 8) + temp;
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);
	W25Qx->msgChipID = _return;
	switch (W25Qx->msgChipID)
	{
		case 0xEF13:
			W25Qx->msgEraseDelayMS = 25000;
			W25Qx->msgEraseSectorDelayMS = 200;
			W25Qx->msgErase32KbBlockDelayMS = 1000;
			W25Qx->msgErase64KbBlockDelayMS = 1500;
			break;
		case 0xEF14:
			W25Qx->msgEraseDelayMS = 40000;
			W25Qx->msgEraseSectorDelayMS = 200;
			W25Qx->msgErase32KbBlockDelayMS = 1000;
			W25Qx->msgErase64KbBlockDelayMS = 1500;
			break;
		case 0xEF15:
			W25Qx->msgEraseDelayMS = 80000;
			W25Qx->msgEraseSectorDelayMS = 200;
			W25Qx->msgErase32KbBlockDelayMS = 1000;
			W25Qx->msgErase64KbBlockDelayMS = 1500;
			break;
		case 0xEF16:
			W25Qx->msgEraseDelayMS = 30000;
			W25Qx->msgEraseSectorDelayMS = 400;
			W25Qx->msgErase32KbBlockDelayMS = 800;
			W25Qx->msgErase64KbBlockDelayMS = 1000;
			break;
		default:
			break;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_WaitBusy(W25QXX_HandlerType *W25Qx,UINT32_T timeOut)
{
	//---读取状态寄存器
	UINT8_T _return = W25QXX_SPI_ReadRegSR1(W25Qx);

	//---获取时间标签
	UINT32_T nowTime = 0;
	UINT32_T oldTime = 0;
	UINT64_T cnt = 0;

	//---获取当前时间节拍
	if (W25Qx->msgSPI.msgFuncTimeTick != NULL)
	{
		oldTime = W25Qx->msgSPI.msgFuncTimeTick();
	}

	//---等待BUSY位清空
	while ((_return & 0x01) == 0x01)
	{
		_return = W25QXX_SPI_ReadRegSR1(W25Qx);
		if (W25Qx->msgSPI.msgFuncTimeTick != NULL)
		{
			//---当前时间
			nowTime = W25Qx->msgSPI.msgFuncTimeTick();

			//---判断滴答定时是否发生溢出操作
			if (nowTime < oldTime)
			{
				cnt = (0xFFFFFFFF - oldTime + nowTime);
			}
			else
			{
				cnt = nowTime - oldTime;
			}

			//---判断是否超时
			if (cnt > timeOut)
			{
				//---发送发生超时错误
				return ERROR_1;
			}
		}
		else
		{
			nowTime++;
			if (nowTime > timeOut*100000)
			{
				//---发送发生超时错误
				return ERROR_2;
			}
		}
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
void W25QXX_SPI_ReadData(W25QXX_HandlerType *W25Qx, UINT32_T addr, UINT8_T *pVal, UINT16_T length)
{
	UINT16_T i = 0;

	//--使能片选
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//----发送读取命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_READ_DATA, NULL);

	//----发送24bit地址
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(addr >> 16), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(addr >> 8), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(addr), NULL);

	//---循环读取数据
	for (i = 0; i < length; i++)
	{
		W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[i]);
	}

	//---取消片选
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_ReadFast(W25QXX_HandlerType *W25Qx, UINT32_T addr, UINT8_T *pVal, UINT16_T length)
{
	UINT16_T i = 0;

	//--使能片选
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//----发送读取命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_READ_FAST, NULL);

	//----发送24bit地址
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(addr >> 16), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(addr >> 8), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(addr), NULL);

	//---发送伪字节
	W25QXX_SEND_CMD(W25Qx, 0xFF, NULL);

	//---循环读取数据
	for (i = 0; i < length; i++)
	{
		W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[i]);
	}

	//---取消片选
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 写页数据
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_WritePage(W25QXX_HandlerType *W25Qx, UINT32_T addr, UINT8_T *pVal, UINT16_T length)
{
	UINT8_T pageIndex = 0;
	UINT16_T i = 0;
	UINT32_T pageAdddr = 0;

	//---判断也数据的个数，最大是256个字节
	if (length > W25QXX_PAGE_BYTE_SIZE)
	{
		length = W25QXX_PAGE_BYTE_SIZE;
	}

	//---校验页地址
	pageAdddr = (addr & W25QXX_PAGE_NUM_MASK);

	//---校验页序号
	pageIndex = (UINT8_T)(addr & W25QXX_PAGE_BYTE_MASK);

	//---设置WEL
	W25QXX_SPI_EnableWrite(W25Qx);

	//--使能片选
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//----发送写页命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_PAGE_PROGRAM, NULL);

	//----发送24bit地址
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(pageAdddr >> 16), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(pageAdddr >> 8), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(pageAdddr), NULL);

	//---循环写入数据
	for (i = pageIndex; i < length; i++)
	{
		W25QXX_SEND_CMD(W25Qx, pVal[i - pageIndex], NULL);
	}

	//---取消片选
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//---等待写入结束
	W25QXX_SPI_WaitBusy(W25Qx,100);
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 擦除整个芯片
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseChip(W25QXX_HandlerType *W25Qx)
{
	//---设置WEL
	W25QXX_SPI_EnableWrite(W25Qx);

	//---等待忙结束
	W25QXX_SPI_WaitBusy(W25Qx,100);
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//---发送片擦除命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_ERASE_CHIP, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);
	
	//---等待擦除结束
	W25QXX_SPI_WaitBusy(W25Qx,W25Qx->msgEraseDelayMS);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 擦除挂起
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseSuspend(W25QXX_HandlerType* W25Qx)
{
	//---设置WEL
	W25QXX_SPI_EnableWrite(W25Qx);

	//---等待忙结束
	W25QXX_SPI_WaitBusy(W25Qx, 100);
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//---发送片擦除命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_ERASE_SUSPEND, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//---等待擦除结束
	W25QXX_SPI_WaitBusy(W25Qx, 100);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 擦除恢复
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseResume(W25QXX_HandlerType* W25Qx)
{
	//---设置WEL
	W25QXX_SPI_EnableWrite(W25Qx);

	//---等待忙结束
	W25QXX_SPI_WaitBusy(W25Qx, 100);
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//---发送片擦除命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_ERASE_RESUME, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//---等待擦除结束
	W25QXX_SPI_WaitBusy(W25Qx, 100);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 擦除指定扇区
//////输入参数: sectorNum---扇区的序号，比如0到511，不同器件扇区的个数不同
//////输出参数:
//////说		明：扇区的地址，0到511（）
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseSector(W25QXX_HandlerType *W25Qx, UINT32_T sectorNum)
{
	//---计算扇区地址
	sectorNum *= W25QXX_SECTOR_BYTE_SIZE;

	//---设置WEL
	W25QXX_SPI_EnableWrite(W25Qx);

	//---等待忙结束
	W25QXX_SPI_WaitBusy(W25Qx,100);
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//--发送读取状态寄存器的命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_ERASE_SECTOR, NULL);

	//----发送24bit地址
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(sectorNum >> 16), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(sectorNum >> 8), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(sectorNum), NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//---等待擦除结束
	W25QXX_SPI_WaitBusy(W25Qx, W25Qx->msgEraseSectorDelayMS);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 擦除指定扇区
//////输入参数: sectorNum---扇区的序号，比如0到511，不同器件扇区的个数不同
//////输出参数:
//////说		明：扇区的地址，0到511（）
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseAddrSector(W25QXX_HandlerType* W25Qx, UINT32_T sectorAddr)
{
	//---计算扇区序号
	sectorAddr /= W25QXX_SECTOR_BYTE_SIZE;
	W25QXX_SPI_EraseSector(W25Qx, sectorAddr);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：擦除块，32KB
//////输入参数: block32KbNum---块区域的序号，比如0到63
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseBlock32KB(W25QXX_HandlerType *W25Qx, UINT32_T block32KbNum)
{
	//---计算32Kb大小块的地址
	block32KbNum *= W25QXX_BLOCK_32KB_BYTE_SIZE;

	//---设置WEL
	W25QXX_SPI_EnableWrite(W25Qx);

	//---等待忙结束
	W25QXX_SPI_WaitBusy(W25Qx,100);
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//--发送读取状态寄存器的命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_ERASE_BLOCK_32KB, NULL);

	//----发送24bit地址
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(block32KbNum >> 16), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(block32KbNum >> 8), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(block32KbNum), NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//---等待擦除结束
	W25QXX_SPI_WaitBusy(W25Qx, W25Qx->msgErase32KbBlockDelayMS);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：擦除块，32KB
//////输入参数: block32KbNum---块区域的序号，比如0到63
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseAddrBlock32KB(W25QXX_HandlerType* W25Qx, UINT32_T block32KbAddr)
{
	//---计算32Kb大小块的序号
	block32KbAddr /= W25QXX_BLOCK_32KB_BYTE_SIZE;
	W25QXX_SPI_EraseBlock32KB(W25Qx, block32KbAddr);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：擦除块，64KB
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseBlock64KB(W25QXX_HandlerType *W25Qx, UINT32_T blockNum)
{
	//---计算64Kb大小块的地址
	blockNum *= W25QXX_BLOCK_64KB_BYTE_SIZE;

	//---设置WEL
	W25QXX_SPI_EnableWrite(W25Qx);

	//---等待忙结束
	W25QXX_SPI_WaitBusy(W25Qx,100);
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//--发送读取状态寄存器的命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_ERASE_BLOCK_64KB, NULL);

	//----发送24bit地址
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(blockNum >> 16), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(blockNum >> 8), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(blockNum), NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//---等待擦除结束
	W25QXX_SPI_WaitBusy(W25Qx, W25Qx->msgErase64KbBlockDelayMS);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：擦除块，64KB
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseAddrBlock64KB(W25QXX_HandlerType* W25Qx, UINT32_T blockAddr)
{
	//---计算64Kb大小块的序号
	blockAddr /= W25QXX_BLOCK_64KB_BYTE_SIZE;
	W25QXX_SPI_EraseBlock64KB( W25Qx, blockAddr);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 进入掉电模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_PowerDown(W25QXX_HandlerType *W25Qx)
{
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//---发送掉电命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_POWER_DOWN, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//---TDP
	W25Qx->msgSPI.msgFuncDelayus(3);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 唤醒
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_WakeUp(W25QXX_HandlerType *W25Qx)
{
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//---发送唤醒命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_RELEASE_POWER_DOWN, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//---TRES1
	Delay_us(3);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取序列号
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_ReadUniqueIDNumber(W25QXX_HandlerType *W25Qx, UINT8_T *pVal)
{
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//--发送读取ID命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_READ_UNIQUE_ID, NULL);
	W25QXX_SEND_CMD(W25Qx, 0x00, NULL);
	W25QXX_SEND_CMD(W25Qx, 0x00, NULL);
	W25QXX_SEND_CMD(W25Qx, 0x00, NULL);
	W25QXX_SEND_CMD(W25Qx, 0x00, NULL);

	//---读取64Bit的UniqueSerialNumber
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[0]);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[1]);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[2]);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[3]);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[4]);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[5]);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[6]);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[8]);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_ReadJEDECID(W25QXX_HandlerType *W25Qx, UINT8_T *pVal)
{
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//--发送读取ID命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_JEDEC_ID, NULL);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[0]);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[1]);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[2]);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：擦除加密寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseSecurityReg(W25QXX_HandlerType *W25Qx, UINT32_T regAddr)
{
	//---设置WEL
	W25QXX_SPI_EnableWrite(W25Qx);

	//---等待忙结束
	W25QXX_SPI_WaitBusy(W25Qx,100);
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//--发送读取状态寄存器的命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_ERASE_SECURITY_REG, NULL);

	//----发送24bit地址
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(regAddr >> 16), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(regAddr >> 8), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(regAddr), NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//---等待擦除结束
	W25QXX_SPI_WaitBusy(W25Qx,100);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：编程加密寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_ProgramSecurityReg(W25QXX_HandlerType *W25Qx, UINT32_T regAddr, UINT8_T *pVal, UINT16_T length)
{
	UINT16_T i = 0;

	//---判断也数据的个数，最大是256个字节
	if (length > W25QXX_PAGE_BYTE_SIZE)
	{
		length = W25QXX_PAGE_BYTE_SIZE;
	}

	//---设置WEL
	W25QXX_SPI_EnableWrite(W25Qx);

	//--使能片选
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//----发送写页命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_PROGRAM_SECURITY_REG, NULL);

	//----发送24bit地址
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(regAddr >> 16), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(regAddr >> 8), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(regAddr), NULL);

	//---循环写入数据
	for (i = 0; i < length; i++)
	{
		W25QXX_SEND_CMD(W25Qx, pVal[i], NULL);
	}

	//---取消片选
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//---等待写入结束
	W25QXX_SPI_WaitBusy(W25Qx,100);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取加密寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_ReadSecurityReg(W25QXX_HandlerType *W25Qx, UINT32_T regAddr, UINT8_T *pVal, UINT16_T length)
{
	UINT16_T i = 0;

	//--使能片选
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//----发送读取命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_READ_SECURITY_REG, NULL);

	//----发送24bit地址
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(regAddr >> 16), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(regAddr >> 8), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(regAddr), NULL);

	//---循环读取数据
	for (i = 0; i < length; i++)
	{
		W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[i]);
	}

	//---取消片选
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 唤醒
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EnableReset(W25QXX_HandlerType *W25Qx)
{
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//---发送使能复位命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_ENABLE_RESET, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 唤醒
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_Reset(W25QXX_HandlerType *W25Qx)
{
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);

	//---发送师恩能够复位命令
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_RESET, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgGPIOPort, W25Qx->msgSPI.msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：只写入不校验数据是否可以写入Flash
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_OnlyWrite(W25QXX_HandlerType *W25Qx, UINT32_T addr, UINT8_T* pVal, UINT16_T length)
{
	//---单页剩余的字节数
	UINT16_T pageByteNum = W25QXX_PAGE_BYTE_SIZE - (UINT8_T)(addr&W25QXX_PAGE_BYTE_MASK);
	if (length < pageByteNum)
	{
		//---不大于256个字节
		pageByteNum = length;
	}

	//---循环写入数据
	while (1)
	{
		W25QXX_SPI_WritePage(W25Qx, addr, pVal, pageByteNum);
		if (length == pageByteNum)
		{
			//---写入结束了
			break;
		}
		else
		{
			pVal += pageByteNum;
			addr += pageByteNum;

			//---减去已经写入了的字节数
			length -= pageByteNum;
			if (length > W25QXX_PAGE_BYTE_SIZE)
			{
				//---一次可以写入256个字节
				pageByteNum = W25QXX_PAGE_BYTE_SIZE;
			}
			else
			{
				//---不够256个字节了
				pageByteNum = length;
			}
		}
	};
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_CheckWrite(W25QXX_HandlerType *W25Qx, UINT32_T addr, UINT8_T* pVal, UINT16_T length)
{
	UINT32_T secpos = 0;
	UINT16_T secoff = 0;
	UINT16_T secremain = 0;
	UINT16_T i = 0;

	//---扇区地址
	secpos = addr & W25QXX_SECTOR_NUM_MASK;

	//---在扇区内的偏移
	secoff = addr & W25QXX_SECTOR_BYTE_MASK;

	//---扇区剩余空间大小
	secremain = W25QXX_SECTOR_BYTE_SIZE - secoff;

	if (length <= secremain)
	{
		//---不大于4096个字节
		secremain = length;
	}

	//---循环写入数据
	while (1)
	{
		//---读出整个扇区的内容
		W25QXX_SPI_ReadData(W25Qx, secpos * W25QXX_SECTOR_BYTE_SIZE, W25Qx->msgBuffer, W25QXX_SECTOR_BYTE_SIZE);

		//---校验数据
		for (i = 0; i < secremain; i++)
		{
			if (W25Qx->msgBuffer[secoff + i] != 0XFF)
			{
				//---需要擦除
				break;
			}
		}

		//---判断是否需要擦除
		if (i < secremain)
		{
			//---擦除这个扇区
			W25QXX_SPI_EraseSector(W25Qx, secpos);

			//---复制
			for (i = 0; i < secremain; i++)
			{
				W25Qx->msgBuffer[i + secoff] = pVal[i];
			}

			//---写入整个扇区
			W25QXX_SPI_OnlyWrite(W25Qx, secpos * W25QXX_SECTOR_BYTE_SIZE, W25Qx->msgBuffer, W25QXX_SECTOR_BYTE_SIZE);
		}
		else
		{
			//---写已经擦除了的,直接写入扇区剩余区间.
			W25QXX_SPI_OnlyWrite(W25Qx, addr, pVal, secremain);
		}

		//---判断是否写入完成
		if (length == secremain)
		{
			//---写入结束了
			break;
		}
		else
		{
			//---写入未结束
			//---扇区地址增1
			secpos++;

			//---偏移位置为0
			secoff = 0;

			//---指针偏移
			pVal += secremain;

			//---写地址偏移
			addr += secremain;

			//---字节数递减
			length -= secremain;

			//---判断下一个扇区是否能够写完
			if (length > W25QXX_SECTOR_BYTE_SIZE)
			{
				//---下一个扇区还是写不完
				secremain = 4096;
			}
			else
			{
				//---下一个扇区可以写完了
				secremain = length;
			}
		}
	};
}