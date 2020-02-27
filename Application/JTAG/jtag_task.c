#include "jtag_task.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_Init(JTAG_HandlerType* JTAGx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	return JTAGLib_Init(JTAGx, pFuncDelayus, pFuncDelayms, pFuncTimerTick);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ù̶����ʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_SetProgClock(JTAG_HandlerType* JTAGx, UINT8_T clok)
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
UINT8_T JTAGTask_ExitProg(JTAG_HandlerType* JTAGx)
{
	return JTAGLib_ExitProg(JTAGx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_EnterProg(JTAG_HandlerType* JTAGx)
{
	return JTAGLib_EnterProg(JTAGx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_EnterProgAndConfigInfo(JTAG_HandlerType* JTAGx, UINT8_T isPollReady, UINT8_T* pVal)
{
	return JTAGLib_EnterProgAndConfigInfo(JTAGx, isPollReady, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_EraseChip(JTAG_HandlerType* JTAGx)
{
	return JTAGLib_EraseChip(JTAGx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadIDChip(JTAG_HandlerType* JTAGx, UINT8_T* pVal)
{
	return JTAGLib_ReadIDChip(JTAGx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChipID(JTAG_HandlerType* JTAGx, UINT8_T* pVal)
{
	return JTAGLib_ReadChipID(JTAGx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChip(JTAG_HandlerType* JTAGx, UINT8_T* pVal)
{
	return JTAGLib_ReadChip(JTAGx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChipCalibration(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T length)
{
	return JTAGLib_ReadChipCalibration(JTAGx, pVal, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChipFuse(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T isNeedExternFuse)
{
	return JTAGLib_ReadChipFuse(JTAGx, pVal, isNeedExternFuse);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChipLock(JTAG_HandlerType* JTAGx, UINT8_T* pVal)
{
	return JTAGLib_ReadChipLock(JTAGx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChipRom(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T addr, UINT16_T length)
{
	return JTAGLib_ReadChipRom(JTAGx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_WriteChipFuse(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T isNeedExternFuse)
{
	return JTAGLib_WriteChipFuse(JTAGx, pVal, isNeedExternFuse);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_WriteChipLock(JTAG_HandlerType* JTAGx, UINT8_T lockVal)
{
	return JTAGLib_WriteChipLock(JTAGx, lockVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChipEepromAddr(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return JTAGLib_ReadChipEepromAddr(JTAGx, pVal, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChipEepromLongAddr(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT16_T addr, UINT16_T length)
{
	return JTAGLib_ReadChipEepromLongAddr(JTAGx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_WriteChipEeprom(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum)
{
	return JTAGLib_WriteChipEeprom(JTAGx, pVal, highAddr, lowAddr, pageNum);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChipFlashAddr(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return JTAGLib_ReadChipFlashAddr(JTAGx, pVal, externAddr, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChipFlashLongAddr(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT32_T addr, UINT16_T length)
{
	return JTAGLib_ReadChipFlashLongAddr(JTAGx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_WriteChipFlashPage(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return JTAGLib_WriteChipFlashPage(JTAGx, pVal, externAddr, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_CheckChipFlashEmpty(JTAG_HandlerType* JTAGx, UINT8_T pageByteSizeH, UINT8_T pageByteSizeL, UINT8_T pageNumH, UINT8_T pageNumL)
{
	return JTAGLib_CheckChipFlashEmpty(JTAGx, pageByteSizeH, pageByteSizeL, pageNumH, pageNumL);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_CheckChipFlashEmptyLong(JTAG_HandlerType* JTAGx, UINT16_T pageByteSize, UINT16_T pageNum)
{
	return JTAGLib_CheckChipFlashEmptyLong(JTAGx, pageByteSize, pageNum);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_CheckChipEepromEmpty(JTAG_HandlerType* JTAGx, UINT8_T byteSize, UINT8_T num)
{
	return JTAGLib_CheckChipEepromEmpty(JTAGx, byteSize, num);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_SetConfigInfo(JTAG_HandlerType* JTAGx, UINT8_T* pVal)
{
	return JTAGLib_SetConfigInfo(JTAGx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChipPower(JTAG_HandlerType* JTAGx, UINT8_T* pVal)
{
	//---��ȡоƬ�Ĺ����ѹ
	UINT16_T tempPower = ADCTask_GetChipPower();
	//---��ȡ��ѹֵ
	//---�������
	*(pVal++) = (UINT8_T)(tempPower >> 8);
	*pVal = (UINT8_T)(tempPower);
	return  OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_WriteChipPower(JTAG_HandlerType* JTAGx, UINT8_T* pVal)
{
	UINT16_T tempPower = *(pVal++);
	tempPower = (tempPower << 8) + *(pVal++);
	//---ͨ��DAC���ÿɵ���ԴLM317�����ֵ
	LM317Task_Init(0, tempPower);
	//---У���Դ�Ƿ���
	if (*pVal > 0)
	{
		LM317_POWER_ON;
	}
	else
	{
		LM317_POWER_HZ;
	}
	return  OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��˳����߽�����ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_UARTCmd_OpenAndClose(JTAG_HandlerType* JTAGx, UART_HandlerType* UARTx)
{
	UINT8_T	_return = 0;
	//---����λ��
	if (UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 1)
	{
		//---������ģʽ�������û�������
		_return = JTAGTask_EnterProgAndConfigInfo(JTAGx, UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset], UARTx->msgRxdHandler.pMsgVal + UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1);
	}
	else if (UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 2)
	{
		//---���û�������,��Ҫ��ʹ��ʹ��EEPROM��ҳ���ģʽ
		_return = JTAGTask_SetConfigInfo(JTAGx, UARTx->msgRxdHandler.pMsgVal + UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1);
	}
	else
	{
		_return = JTAGTask_ExitProg(JTAGx);
	}
	//---ִ�н��
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����Chip
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_UARTCmd_EraseChip(JTAG_HandlerType* JTAGx, UART_HandlerType* UARTx)
{
	UINT8_T _return = OK_0;
	if (UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 0)
	{
		//---�豸����
		_return = JTAGTask_EraseChip(JTAGx);
	}
	else if (UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 1)
	{
		//---���FlashΪ��
		_return = JTAGTask_CheckChipFlashEmpty(JTAGx,
			UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 1], UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 2],
			UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 3], UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 4]
		);
	}
	else if (UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 2)
	{
		//---���EepromΪ��
		_return = JTAGTask_CheckChipEepromEmpty(JTAGx,
			UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 1], UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 2]
		);
	}
	else
	{
		_return = 0xFF;
	}
	//---�����ǲ��ǲ�ղ���
	if (UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] != 0)
	{
		//---����ղ�����ֵ
		UARTTask_FillMode_AddByte(UARTx, _return);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡоƬID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_UARTCmd_ReadChipID(JTAG_HandlerType* JTAGx, UART_HandlerType* UARTx)
{
	UINT8_T	_return = 0;
	//---��ȡ�豸ID��Ϣ
	_return = JTAGTask_ReadChipID(JTAGx, UARTx->msgTxdHandler.pMsgVal + UARTx->msgTxdHandler.msgWIndex);
	//---���ݳ���ƫ��
	UARTx->msgTxdHandler.msgWIndex += 3;
	//---ִ�н��
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡоƬ��У׼��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_UARTCmd_ReadChipCalibration(JTAG_HandlerType* JTAGx, UART_HandlerType* UARTx)
{
	UINT8_T	_return = 0;
	//---��ȡ�豸��У׼��
	_return = JTAGTask_ReadChipCalibration(JTAGx, UARTx->msgTxdHandler.pMsgVal + UARTx->msgTxdHandler.msgWIndex, UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset]);
	//---���ݵ�ַƫ��
	UARTx->msgTxdHandler.msgWIndex += UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset];
	//---ִ�н��
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡоƬ����˿λ��У׼��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_UARTCmd_ReadChipFuseAndLock(JTAG_HandlerType* JTAGx, UART_HandlerType* UARTx)
{
	UINT8_T	_return = 0;
	//---�ж��Ƕ�ȡ��˿λ���Ǽ���λ
	if (UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 0)
	{
		//---��ȡ��˿λ
		_return = JTAGTask_ReadChipFuse(JTAGx, UARTx->msgTxdHandler.pMsgVal + UARTx->msgTxdHandler.msgWIndex, UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset]);
		//---У���Ƿ��ȡ��չ��˿λ
		if (UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset] != 0)
		{
			UARTx->msgTxdHandler.msgWIndex += 1;
		}
		UARTx->msgTxdHandler.msgWIndex += 2;
	}
	else
	{
		//---��ȡ����λ
		_return = JTAGTask_ReadChipLock(JTAGx, UARTx->msgTxdHandler.pMsgVal + UARTx->msgTxdHandler.msgWIndex);
		UARTx->msgTxdHandler.msgWIndex += 1;
	}
	//---ִ�н��
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������˿λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_UARTCmd_WriteChipFuse(JTAG_HandlerType* JTAGx, UART_HandlerType* UARTx)
{
	return JTAGTask_WriteChipFuse(JTAGx, UARTx->msgRxdHandler.pMsgVal + UARTx->msgDataTwoIndex + UARTx->msgIndexOffset, UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset]);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���̼���λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_UARTCmd_WriteChipLock(JTAG_HandlerType* JTAGx, UART_HandlerType* UARTx)
{
	return JTAGTask_WriteChipLock(JTAGx, UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset]);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡоƬ��ROM��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_UARTCmd_ReadChipRom(JTAG_HandlerType* JTAGx, UART_HandlerType* UARTx)
{
	UINT8_T	_return = 0;
	UINT16_T length = 0;
	//---�����ȡ���ݵĴ�С
	if (UARTx->msgRxdHandler.msgMaxSize < 0xFF)
	{
		length = UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset];
	}
	else
	{
		length = UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset];
		length = (length << 8) + UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1];
	}
	//---��ȡROMҳ��Ϣ
	_return = JTAGTask_ReadChipRom(JTAGx, UARTx->msgTxdHandler.pMsgVal + UARTx->msgTxdHandler.msgWIndex, UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset], length);
	//---���ݵ�ƫ��
	UARTx->msgTxdHandler.msgWIndex += length;
	//---ִ�н��
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ñ��ʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_UARTCmd_SetProgClok(JTAG_HandlerType* JTAGx, UART_HandlerType* UARTx)
{
	UINT8_T _return = OK_0;
	//---��ȡ��ѹ
	if (UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 1)
	{
		_return = JTAGTask_ReadChipPower(JTAGx, UARTx->msgTxdHandler.pMsgVal + UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 1);
		UARTx->msgTxdHandler.msgWIndex += 2;
	}
	//---���õ�ѹ
	else if (UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 2)
	{
		_return = JTAGTask_WriteChipPower(JTAGx, UARTx->msgRxdHandler.pMsgVal + UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 1);
	}
	else
	{
		//---���ñ��ʱ��
		_return = JTAGTask_SetProgClock(JTAGx, UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 1]);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ�����������ȡFlash����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_UARTCmd_ReadChipFlash(JTAG_HandlerType* JTAGx, UART_HandlerType* UARTx)
{
	UINT8_T	_return = 0;
	UINT16_T length = 0;
	//---�����ȡ���ݵĴ�С
	if (UARTx->msgRxdHandler.msgMaxSize < 0xFF)
	{
		length = UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 2];
	}
	else
	{
		length = UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 2];
		length = (length << 8) + UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 3];
	}
	//---��ȡָ��λ�õ�Flash����
	_return = JTAGTask_ReadChipFlashAddr(JTAGx, UARTx->msgTxdHandler.pMsgVal + UARTx->msgTxdHandler.msgWIndex,
		UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset],
		UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset],
		UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1],
		length);
	//---���ݵ�ƫ��
	UARTx->msgTxdHandler.msgWIndex += length;
	//---ִ�н��
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ������������Flash����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_UARTCmd_WriteChipFlashPage(JTAG_HandlerType* JTAGx, UART_HandlerType* UARTx)
{
	UINT8_T dataOffset = 0;
	UINT16_T length = 0;
	//---����д�����ݵĴ�С
	if (UARTx->msgRxdHandler.msgMaxSize < 0xFF)
	{
		length = UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 2];
		dataOffset = 3;
	}
	else
	{
		length = UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 2];
		length = (length << 8) + UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 3];
		dataOffset = 4;
	}
	//---��ָ��λ�ñ������
	return JTAGTask_WriteChipFlashPage(JTAGx, UARTx->msgRxdHandler.pMsgVal + UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + dataOffset,
		UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset],
		UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset],
		UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1],
		length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ�����������ȡeeprom����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_UARTCmd_ReadChipEeprom(JTAG_HandlerType* JTAGx, UART_HandlerType* UARTx)
{
	UINT8_T	_return = 0;
	UINT16_T length = 0;
	//---�����ȡ���ݵĴ�С
	if (UARTx->msgRxdHandler.msgMaxSize < 0xFF)
	{
		length = UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1];
	}
	else
	{
		length = UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1];
		length = (length << 8) + UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 2];
	}
	//---��ȡָ��λ�õ�Eeprom����
	_return = JTAGTask_ReadChipEepromAddr(JTAGx, UARTx->msgTxdHandler.pMsgVal + UARTx->msgTxdHandler.msgWIndex,
		UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset],
		UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset],
		length);
	//---���ݵ�ƫ��
	UARTx->msgTxdHandler.msgWIndex += length;
	//---ִ�н��
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ������������eeprom����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_UARTCmd_WriteChipEeprom(JTAG_HandlerType* JTAGx, UART_HandlerType* UARTx)
{
	UINT8_T dataOffset = 0;
	UINT16_T length = 0;
	//---�����ȡ���ݵĴ�С
	if (UARTx->msgRxdHandler.msgMaxSize < 0xFF)
	{
		length = UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1];
		dataOffset = 2;
	}
	else
	{
		length = UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1];
		length = (length << 8) + UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 2];
		dataOffset = 3;
	}
	//---���ָ��λ�õ�Eeprom����
	return JTAGTask_WriteChipEeprom(JTAGx, UARTx->msgRxdHandler.pMsgVal + UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + dataOffset,
		UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset],
		UARTx->msgRxdHandler.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset],
		length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_UARTCmd_ChildTask(JTAG_HandlerType* JTAGx, UART_HandlerType* UARTx, UINT8_T isChildCmd)
{
	UINT8_T _return = 0;
	//---������ִ�н��
	UARTTask_FillMode_AddByte(UARTx, 0x00);
	UARTx->msgIndexOffset = (isChildCmd == 0 ? 0 : 1);
	//---���������������
	switch (UARTx->msgRxdHandler.pMsgVal[UARTx->msgCmdIndex + UARTx->msgIndexOffset])
	{
		case CMD_JTAG_OPEN_CLOSE:
			//---����֮�󣬵�1�ֽ�0---����رգ�1---����򿪣���2�ֽ�����йأ���ر��޹�
			_return = JTAGTask_UARTCmd_OpenAndClose(JTAGx, UARTx);
			break;
		case CMD_JTAG_ERASE:
			//---�����豸����1�ֽ�0---���������1---������Flash��2---������Eeprom
			_return = JTAGTask_UARTCmd_EraseChip(JTAGx, UARTx);
			break;
		case CMD_JTAG_FLASH_PAGE_READ:
			//---��ȡFlash
			_return = JTAGTask_UARTCmd_ReadChipFlash(JTAGx, UARTx);
			break;
		case CMD_JTAG_FLASH_PAGE_WRITE:
			//---���Flash
			_return = JTAGTask_UARTCmd_WriteChipFlashPage(JTAGx, UARTx);
			break;
		case CMD_JTAG_EEPROM_PAGE_READ:
			//---��ȡEeprom
			_return = JTAGTask_UARTCmd_ReadChipEeprom(JTAGx, UARTx);
			break;
		case CMD_JTAG_EEPROM_PAGE_WRITE:
			//---���Eeprom
			_return = JTAGTask_UARTCmd_WriteChipEeprom(JTAGx, UARTx);
			break;
		case CMD_JTAG_FUSE_LOCK_READ:
			//---��ȡ��˿λ����У��λ
			_return = JTAGTask_UARTCmd_ReadChipFuseAndLock(JTAGx, UARTx);
			break;
		case CMD_JTAG_FUSE_WRITE:
			//---�����˿λ
			_return = JTAGTask_UARTCmd_WriteChipFuse(JTAGx, UARTx);
			break;
		case CMD_JTAG_LOCK_WRITE:
			//---��̼���λ
			_return = JTAGTask_UARTCmd_WriteChipLock(JTAGx, UARTx);
			break;
		case CMD_JTAG_ID_READ:
			//---��ȡ�豸��ID
			_return = JTAGTask_UARTCmd_ReadChipID(JTAGx, UARTx);
			break;
		case CMD_JTAG_CALIBRATIONBYTE_READ:
			//---��ȡУ׼��
			_return = JTAGTask_UARTCmd_ReadChipCalibration(JTAGx, UARTx);
			break;
		case CMD_JTAG_ROM_PAGE_READ:
			//---��ȡROMҳ��Ϣ
			_return = JTAGTask_UARTCmd_ReadChipRom(JTAGx, UARTx);
			break;
		case CMD_JTAG_PROG_CLOCK_SET:
			//---���ñ��ʱ�ӣ��༶������������Ҫ�е�Դ�����úͶ�ȡ
			_return = JTAGTask_UARTCmd_SetProgClok(JTAGx, UARTx);
			break;
		default:
			//---��ʶ�������
			_return = ERROR_1;
			break;
	}
	//---�����Խ��
	UARTTask_FillMode_SetResultFlag(UARTx, _return);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_UARTCmd_ParentTask(JTAG_HandlerType* JTAGx, UART_HandlerType* UARTx, UINT8_T isChildCmd)
{
	if ((UARTx != NULL) && (JTAGx != NULL))
	{
		//---�жϽ����Ƿ����
		if (UARTTask_GetState(&(UARTx->msgRxdHandler)) == 1)
		{
			//---CRC��У����豸IDУ��
			if ((UARTTask_CRCTask_Read(UARTx) == OK_0) && (UARTTask_DeviceID(UARTx) == OK_0))
			{
				//---����������������ݱ�ͷ�����ȣ���ַID,����Ĵ���
				UARTTask_FillMode_Init(UARTx, isChildCmd);
				//---��������
				JTAGTask_UARTCmd_ChildTask(JTAGx, UARTx, isChildCmd);
				//---�������ݷ���
				UARTTask_FillMode_WriteByteSTART(UARTx, 0);
			}
			else
			{
				//---����CRCУ�����
				UARTTask_Printf(UARTx, "=>>SP%d:CRC Check Error<<=\r\n", (UARTx->msgIndex - 1));
			}
			return UARTTask_Read_Init(UARTx);
		}
		return UARTTask_TimeTask_OverFlow(UARTx);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_UARTCmd_ParentTask_New(JTAG_HandlerType* JTAGx, UART_HandlerType* UARTx, UINT8_T isChildCmd)
{
	UINT8_T _return = OK_0;
	//---����������������ݱ�ͷ�����ȣ���ַID,����Ĵ���
	UARTTask_FillMode_Init(UARTx, isChildCmd);
	//---��������
	_return = JTAGTask_UARTCmd_ChildTask(JTAGx, UARTx, isChildCmd);
	//---�Ƿ���Ҫ���ӻ��з�
	if (UARTx->msgTxdHandler.msgAddNewLine == 1)
	{
		UARTTask_FillMode_AddByte(UARTx, 0x0D);
		UARTTask_FillMode_AddByte(UARTx, 0x0A);
	}
	//---�������ݷ���
	UARTTask_FillMode_WriteByteSTART(UARTx, 0);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_UARTCmd_Task(JTAG_HandlerType* JTAGx, UART_HandlerType* UARTx)
{
	UINT8_T _return = OK_0;
	//_return = JTAGTask_UARTCmd_ParentTask(JTAGx, UARTx, 0);
	_return = JTAGTask_UARTCmd_ParentTask_New(JTAGx, UARTx, 0);
	return _return;
}