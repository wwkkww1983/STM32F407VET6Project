#include "isp_task.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_Init(ISP_HandlerType *ISPx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	return ISPLib_Init(ISPx, pFuncDelayus, pFuncDelayms, pFuncTimerTick);
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：注销初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_DeInit(ISP_HandlerType *ISPx)
{
	return ISPLib_DeInit(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置固定编程时钟
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_SetProgClock(ISP_HandlerType* ISPx, UINT8_T clok)
{
	return ISPLib_SetProgClock(ISPx,clok);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：进入编程
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_EnterProg(ISP_HandlerType *ISPx, UINT8_T isPollReady)
{
	return ISPLib_EnterProg(ISPx,isPollReady);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：退出编程
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ExitProg(ISP_HandlerType *ISPx)
{
	return ISPLib_ExitProg(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：添加监控
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_AddWatch(ISP_HandlerType* ISPx)
{
	return ISPLib_AddWatch(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：注销监控
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_RemoveWatch(ISP_HandlerType* ISPx)
{
	return ISPLib_RemoveWatch(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：刷新监控
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_RefreshWatch(ISP_HandlerType* ISPx)
{
	return ISPLib_RefreshWatch(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取Ready信号
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadReady(ISP_HandlerType *ISPx)
{
	return ISPLib_ReadReady(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：擦除设备
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_EraseChip(ISP_HandlerType *ISPx)
{
	return ISPLib_EraseChip(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取ChipID
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipID(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	return ISPLib_ReadChipID(ISPx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取校准字
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipCalibration(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T length)
{
	return ISPLib_ReadChipCalibration(ISPx, pVal, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取熔丝位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
{
	return ISPLib_ReadChipFuse(ISPx, pVal, isNeedExternFuse);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取加密位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipLock(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	return ISPLib_ReadChipLock(ISPx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取ROM信息
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipRom(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T addr, UINT16_T length)
{
	return ISPLib_ReadChipRom(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：编程熔丝位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
{
	return ISPLib_WriteChipFuse(ISPx, pVal, isNeedExternFuse);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：编程加密位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipLock(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	return ISPLib_WriteChipLock(ISPx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取EEPROM
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISPLib_ReadChipEepromAddr(ISPx, pVal, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取EEPROM
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return ISPLib_ReadChipEepromLongAddr(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：编程EEPROM
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISPLib_WriteChipEepromAddr(ISPx, pVal, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return ISPLib_WriteChipEepromLongAddr(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：编程EEPROM
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipEepromAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISPLib_WriteChipEepromAddrWithJumpEmpty(ISPx, pVal, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：编程EEPROM
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipEepromLongAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return  ISPLib_WriteChipEepromLongAddrWithJumpEmpty(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取Flash
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISPLib_ReadChipFlashAddr(ISPx, pVal, externAddr, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取Flash
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipFlashLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT32_T addr, UINT16_T length)
{
	return ISPLib_ReadChipFlashLongAddr(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：更新拓展位地址
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateExternAddr(ISP_HandlerType* ISPx, UINT8_T addr)
{
	return ISPLib_UpdateExternAddr(ISPx, addr);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：更新拓展位地址
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateExternLongAddr(ISP_HandlerType* ISPx, UINT32_T addr)
{
	return ISPLib_UpdateExternLongAddr(ISPx, addr);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：更新数据到数据缓存区
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateChipFlashBuffer(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T index, UINT16_T length)
{
	return ISPLib_UpdateChipFlashBuffer(ISPx, pVal, index, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：更新数据到指定的数据地址
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr)
{
	return ISPLib_UpdateChipFlashAddr(ISPx, externAddr, highAddr, lowAddr);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：更新数据到数据的指定地址
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateChipFlashLongAddr(ISP_HandlerType *ISPx, UINT32_T addr)
{
	return ISPLib_UpdateChipFlashLongAddr(ISPx, addr);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：退出或者进入编程模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_USARTCmd_OpenAndClose(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T	_return=0;
	//---命令位置
	if (USARTx->msgRxHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset]==1)
	{
		_return=ISPTask_EnterProg(ISPx, USARTx->msgRxHandler.pMsgVal[USARTx->msgDataTwoIndex+ USARTx->msgIndexOffset]);
	}
	else
	{
		_return = ISPTask_ExitProg(ISPx);
	}
	//---执行结果
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：擦除Chip
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_USARTCmd_EraseChip(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	//---设备擦除
	return ISPTask_EraseChip(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取芯片ID
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_USARTCmd_ReadChipID(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	//---读取设备ID信息
	_return = ISPTask_ReadChipID(ISPx, USARTx->msgTxHandler.pMsgVal + USARTx->msgTxHandler.msgIndexW);
	//---数据长度偏移
	USARTx->msgTxHandler.msgIndexW += 3;
	//---执行结果
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取芯片的校准字
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_USARTCmd_ReadChipCalibration(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	//---读取设备的校准字
	_return = ISPTask_ReadChipCalibration(ISPx, USARTx->msgTxHandler.pMsgVal + USARTx->msgTxHandler.msgIndexW, USARTx->msgRxHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset]);
	//---数据地址偏移
	USARTx->msgTxHandler.msgIndexW += USARTx->msgRxHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset];
	//---执行结果
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取芯片的熔丝位和校准字
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_USARTCmd_ReadChipFuseAndLock(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	//---判断是读取熔丝位还是加密位
	if (USARTx->msgRxHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset] == 0)
	{
		//---读取熔丝位
		_return = ISPTask_ReadChipFuse(ISPx, USARTx->msgTxHandler.pMsgVal + USARTx->msgTxHandler.msgIndexW, USARTx->msgRxHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset]);
		//---校验是否读取拓展熔丝位
		if (USARTx->msgRxHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset] != 0)
		{
			USARTx->msgTxHandler.msgIndexW += 1;
		}
		USARTx->msgTxHandler.msgIndexW += 2;
	}
	else
	{
		//---读取加密位
		_return = ISPTask_ReadChipLock(ISPx, USARTx->msgTxHandler.pMsgVal + USARTx->msgTxHandler.msgIndexW);
		USARTx->msgTxHandler.msgIndexW += 1;
	}
	//---执行结果
	return _return;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：编程熔丝位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_USARTCmd_WriteChipFuse(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	return ISPTask_WriteChipFuse(ISPx, USARTx->msgRxHandler.pMsgVal + USARTx->msgDataTwoIndex + USARTx->msgIndexOffset, USARTx->msgRxHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset]);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：编程加密位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_USARTCmd_WriteChipLock(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	return ISPTask_WriteChipLock(ISPx, USARTx->msgRxHandler.pMsgVal + USARTx->msgDataTwoIndex + USARTx->msgIndexOffset);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取芯片的ROM信息
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_USARTCmd_ReadChipRom(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	UINT16_T length=0;
	//---计算要读取数据的长度。
	length = USARTx->msgRxHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset];
	length = (length << 8) + USARTx->msgRxHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset + 1];
	//---读取ROM页信息
	_return = ISPTask_ReadChipRom(ISPx, USARTx->msgTxHandler.pMsgVal + USARTx->msgTxHandler.msgIndexW, USARTx->msgRxHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset], length);
	//---执行结果
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置编程时钟
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_USARTCmd_ReadProgClok(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	ISPTask_SetProgClock(ISPx, USARTx->msgRxHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset]);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_USARTCmd_ChildTask(ISP_HandlerType* ISPx, USART_HandlerType* USARTx,UINT8_T isChildCmd)
{
	UINT8_T _return = 0;
	//---填充测试执行结果
	USARTTask_FillMode_AddByte(USARTx, 0x00);
	USARTx->msgIndexOffset= (isChildCmd == 0 ? 0 : 1);
	//---依据命令解析数据
	switch (USARTx->msgRxHandler.pMsgVal[USARTx->msgCmdIndex+ USARTx->msgIndexOffset])
	{
		case CMD_ISP_OPEN_CLOSE:
			//---命令之后，第1字节0---代表关闭，1---代表打开；第2字节与打开有关，与关闭无关
			_return= ISPTask_USARTCmd_OpenAndClose(ISPx,USARTx);
			break;
		case CMD_ISP_ERASE:
			//---擦除设备
			_return= ISPTask_USARTCmd_EraseChip(ISPx, USARTx);
			break;
		case CMD_ISP_FLASH_PAGE_READ:
			break;
		case CMD_ISP_FLASH_PAGE_WRITE:
			break;
		case CMD_ISP_EEPROM_PAGE_READ:
			break;
		case CMD_ISP_EEPROM_PAGE_WRITE:
			break;
		case CMD_ISP_FUSE_LOCK_READ:
			_return= ISPTask_USARTCmd_ReadChipFuseAndLock(ISPx,USARTx);
			break;
		case CMD_ISP_FUSE_WRITE	:
			_return= ISPTask_USARTCmd_WriteChipFuse(ISPx, USARTx);
			break;
		case CMD_ISP_LOCK_WRITE	:
			_return= ISPTask_USARTCmd_WriteChipLock(ISPx, USARTx);
			break;
		case CMD_ISP_ID_READ:
			_return= ISPTask_USARTCmd_ReadChipID(ISPx,USARTx);
			break;
		case CMD_ISP_CALIBRATIONBYTE_READ:
			_return= ISPTask_USARTCmd_ReadChipCalibration(ISPx, USARTx);
			break;
		case CMD_ISP_ROM_PAGE_READ:
			_return= ISPTask_USARTCmd_ReadChipRom(ISPx,USARTx);
			break;
		case CMD_ISP_PROG_CLOCK_SET:
			_return= ISPTask_USARTCmd_ReadProgClok(ISPx, USARTx);
			break;
		default:
			//---不识别的命令
			_return = ERROR_1;
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
UINT8_T ISPTask_USARTCmd_ParentTask(ISP_HandlerType* ISPx, USART_HandlerType* USARTx, UINT8_T isChildCmd)
{
	if ((USARTx != NULL) && (ISPx != NULL))
	{
		//---判断接收是否完成
		if (USARTTask_GetReadState(USARTx) == 1)
		{
			//---CRC的校验和设备ID校验
			if ((USARTTask_CRCTask_Read(USARTx) == OK_0) && (USARTTask_DeviceID(USARTx) == OK_0))
			{
				//---任务命令处理函数，数据报头，长度，地址ID,命令的处理
				USARTTask_FillMode_Init(USARTx,isChildCmd);
				//---处理子命令
				ISPTask_USARTCmd_ChildTask(ISPx, USARTx, isChildCmd);
				//---是否需要增加换行符
				if (USARTx->msgTxHandler.msgAddNewLine == 1)
				{
					USARTTask_FillMode_AddByte(USARTx, 0x0D);
					USARTTask_FillMode_AddByte(USARTx, 0x0A);
				}
				//---启动数据发送
				USARTTask_FillMode_WriteSTART(USARTx, 0);
			}
			else
			{
				//---发生CRC校验错误
				USART_Printf(USARTx, "=>>串口%d:发生CRC校验错误<<=\r\n", (USARTx->msgIndex - 1));
			}
			return USARTTask_ReadInit(USARTx);
		}
		return USARTTask_TimeOVFTask(USARTx);
	}
	return ERROR_2;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_USARTCmd_Task(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T _return = OK_0;
	_return= ISPTask_USARTCmd_ParentTask(ISPx, USARTx, 0);
	return _return;
}