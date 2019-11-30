#include "isp_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_Init(ISP_HandlerType *ISPx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	return ISP_Init(ISPx, pFuncDelayus, pFuncDelayms, pFuncTimerTick);
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：注销初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_DeInit(ISP_HandlerType *ISPx)
{
	return ISP_DeInit(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置编程时钟
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_SetProgClock(ISP_HandlerType* ISPx, UINT8_T clok)
{
	return ISP_SetProgClock(ISPx, clok);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：进入编程
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_EnterProg(ISP_HandlerType *ISPx, UINT8_T isPollReady)
{
	return ISP_EnterProg(ISPx,isPollReady);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：退出编程
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ExitProg(ISP_HandlerType *ISPx)
{
	return ISP_ExitProg(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：添加监控
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_AddWatch(ISP_HandlerType* ISPx)
{
	return ISP_AddWatch( ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：移除监控
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_RemoveWatch(ISP_HandlerType* ISPx)
{
	return ISP_RemoveWatch(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：刷新监控
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_RefreshWatch(ISP_HandlerType* ISPx)
{
	return ISP_RefreshWatch(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取Ready信号
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadReady(ISP_HandlerType *ISPx)
{
	return ISP_ReadReady(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：擦除设备
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_EraseChip(ISP_HandlerType *ISPx)
{
	UINT8_T	_return = 0;
	//---检查当前编程模式
	if (ISPx->msgState == 0)
	{
		//---进入编程模式
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		_return = ISP_EraseChip(ISPx);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取ChipID
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipID(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	UINT8_T	_return = 0;
	//---检查当前编程模式
	if (ISPx->msgState == 0)
	{
		//---进入编程模式
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		_return = ISP_ReadChipID(ISPx, pVal);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取校准字
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipCalibration(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T length)
{
	UINT8_T	_return = 0;
	//---检查当前编程模式
	if (ISPx->msgState == 0)
	{
		//---进入编程模式
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		_return = ISP_ReadChipCalibration(ISPx, pVal, length);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取熔丝位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
{
	UINT8_T	_return = 0;
	//---检查当前编程模式
	if (ISPx->msgState == 0)
	{
		//---进入编程模式
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		_return = ISP_ReadChipFuse(ISPx, pVal, isNeedExternFuse);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取加密位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipLock(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	UINT8_T	_return = 0;
	//---检查当前编程模式
	if (ISPx->msgState == 0)
	{
		//---进入编程模式
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		_return = ISP_ReadChipLock(ISPx, pVal);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取ROM信息
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipRom(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T addr, UINT16_T length)
{
	UINT8_T	_return = 0;
	//---检查当前编程模式
	if (ISPx->msgState == 0)
	{
		//---进入编程模式
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		_return = ISP_ReadChipRom(ISPx, pVal, addr, length);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：编程熔丝位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
{
	UINT8_T	_return = 0;
	//---检查当前编程模式
	if (ISPx->msgState == 0)
	{
		//---进入编程模式
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		_return = ISP_WriteChipFuse(ISPx, pVal, isNeedExternFuse);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：编程加密位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipLock(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	UINT8_T	_return = 0;
	//---检查当前编程模式
	if (ISPx->msgState == 0)
	{
		//---进入编程模式
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		_return = ISP_WriteChipLock(ISPx, pVal);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取EEPROM
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T	_return = 0;
	//---检查当前编程模式
	if (ISPx->msgState == 0)
	{
		//---进入编程模式
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		_return = ISP_ReadChipEepromAddr(ISPx, pVal, highAddr, lowAddr, length);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取EEPROM
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	UINT8_T	_return = 0;
	//---检查当前编程模式
	if (ISPx->msgState == 0)
	{
		//---进入编程模式
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		_return = ISP_ReadChipEepromLongAddr(ISPx, pVal, addr, length);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：编程EEPROM
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISP_WriteChipEepromAddr(ISPx, pVal, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：编程EEPROM
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return ISP_WriteChipEepromLongAddr(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：编程EEPROM
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipEepromAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISP_WriteChipEepromAddrWithJumpEmpty(ISPx, pVal, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：编程EEPROM
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipEepromLongAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return ISP_WriteChipEepromLongAddrWithJumpEmpty(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取Flash
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T	_return = 0;
	//---检查当前编程模式
	if (ISPx->msgState == 0)
	{
		//---进入编程模式
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		_return = ISP_ReadChipFlashAddr(ISPx, pVal, externAddr, highAddr, lowAddr, length);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取Flash
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipFlashLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT32_T addr, UINT16_T length)
{
	UINT8_T	_return = 0;
	//---检查当前编程模式
	if (ISPx->msgState == 0)
	{
		//---进入编程模式
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		_return = ISP_ReadChipFlashLongAddr(ISPx, pVal, addr, length);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：更新拓展位地址
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_UpdateExternAddr(ISP_HandlerType* ISPx, UINT8_T addr)
{
	return ISP_UpdateExternAddr(ISPx, addr);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：更新拓展位地址
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_UpdateExternLongAddr(ISP_HandlerType* ISPx, UINT32_T addr)
{
	return  ISP_UpdateExternLongAddr(ISPx, addr);
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：更新数据到数据缓存区
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_UpdateChipFlashBuffer(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T index, UINT16_T length)
{
	return ISP_UpdateChipFlashBuffer(ISPx, pVal, index, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：更新数据到指定的数据存储区
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_UpdateChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr)
{
	return ISP_UpdateChipFlashAddr(ISPx, externAddr, highAddr, lowAddr);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：更新数据到指定的数据存储区
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_UpdateChipFlashLongAddr(ISP_HandlerType *ISPx, UINT32_T addr)
{
	return ISP_UpdateChipFlashLongAddr(ISPx, addr);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：页模式向指定的数据写入Flash
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipFlashPage(ISP_HandlerType* ISPx,UINT8_T *pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr,UINT16_T length)
{
	UINT8_T _return=OK_0;
	UINT32_T pageAddr = 0;
	//---计算字节地址，之后需要换算成字地址
	pageAddr=externAddr;
	pageAddr=(pageAddr<<8)+highAddr;
	pageAddr+=lowAddr;
	//---计算地址的偏移
	pageAddr+=length;
	//---填充数据缓存
	_return= ISP_UpdateChipFlashBuffer(ISPx,pVal,(UINT8_T)ISPx->msgPageWordIndex,length);
	//---换算返回结果
	_return = (_return == OK_0 ? OK_0 : ERROR_1);
	//---缓存区填满，执行数据写入操作
	if ((_return==OK_0)&&(ISPx->msgPageWordIndex==ISPx->msgFlashPageWordSize))
	{
		//---将字节地址换算成字地址
		pageAddr >>= 1;
		//---更新数据到指定的页地址
		_return= ISP_UpdateChipFlashLongAddr(ISPx,pageAddr);
		//---数据缓存区的
		ISPx->msgPageWordIndex=0;
		//---换算返回结果
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
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
UINT8_T ISPLib_CheckChipFlashEmpty(ISP_HandlerType* ISPx, UINT8_T pageByteSizeH, UINT8_T pageByteSizeL, UINT8_T pageNumH, UINT8_T pageNumL)
{
	return ISP_CheckChipFlashEmpty(ISPx, pageByteSizeH, pageByteSizeL, pageNumH, pageNumL);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_CheckChipFlashEmptyLong(ISP_HandlerType* ISPx, UINT16_T pageByteSize, UINT16_T pageNum)
{
	return ISP_CheckChipFlashEmptyLong(ISPx, pageByteSize, pageNum);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_CheckChipEepromEmpty(ISP_HandlerType* ISPx, UINT8_T byteSize, UINT8_T num)
{
	return ISP_CheckChipEepromEmpty(ISPx, byteSize, num);
}