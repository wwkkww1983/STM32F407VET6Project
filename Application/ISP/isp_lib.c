#include "isp_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_Init(ISP_HandlerType *ISPx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	return ISP_Init(ISPx, pFuncDelayus, pFuncDelayms, pFuncTimerTick);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ע����ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_DeInit(ISP_HandlerType *ISPx)
{
	return ISP_DeInit(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ñ��ʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_SetProgClock(ISP_HandlerType* ISPx, UINT8_T clok)
{
	return ISP_SetProgClock(ISPx, clok);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_EnterProg(ISP_HandlerType *ISPx, UINT8_T isPollReady)
{
	return ISP_EnterProg(ISPx,isPollReady);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��˳����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ExitProg(ISP_HandlerType *ISPx)
{
	return ISP_ExitProg(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���Ӽ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_AddWatch(ISP_HandlerType* ISPx)
{
	return ISP_AddWatch( ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��Ƴ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_RemoveWatch(ISP_HandlerType* ISPx)
{
	return ISP_RemoveWatch(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ˢ�¼��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_RefreshWatch(ISP_HandlerType* ISPx)
{
	return ISP_RefreshWatch(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡReady�ź�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadReady(ISP_HandlerType *ISPx)
{
	return ISP_ReadReady(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������豸
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_EraseChip(ISP_HandlerType *ISPx)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
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
//////��		����
//////��		�ܣ���ȡChipID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipID(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
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
//////��		����
//////��		�ܣ���ȡУ׼��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipCalibration(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T length)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
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
//////��		����
//////��		�ܣ���ȡ��˿λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
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
//////��		����
//////��		�ܣ���ȡ����λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipLock(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
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
//////��		����
//////��		�ܣ���ȡROM��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipRom(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T addr, UINT16_T length)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
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
//////��		����
//////��		�ܣ������˿λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
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
//////��		����
//////��		�ܣ���̼���λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipLock(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
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
//////��		����
//////��		�ܣ���ȡEEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
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
//////��		����
//////��		�ܣ���ȡEEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
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
//////��		����
//////��		�ܣ����EEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISP_WriteChipEepromAddr(ISPx, pVal, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����EEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return ISP_WriteChipEepromLongAddr(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����EEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipEepromAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISP_WriteChipEepromAddrWithJumpEmpty(ISPx, pVal, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����EEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipEepromLongAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return ISP_WriteChipEepromLongAddrWithJumpEmpty(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡFlash
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
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
//////��		����
//////��		�ܣ���ȡFlash
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipFlashLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT32_T addr, UINT16_T length)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
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
//////��		����
//////��		�ܣ�������չλ��ַ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_UpdateExternAddr(ISP_HandlerType* ISPx, UINT8_T addr)
{
	return ISP_UpdateExternAddr(ISPx, addr);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������չλ��ַ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_UpdateExternLongAddr(ISP_HandlerType* ISPx, UINT32_T addr)
{
	return  ISP_UpdateExternLongAddr(ISPx, addr);
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������ݵ����ݻ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_UpdateChipFlashBuffer(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T index, UINT16_T length)
{
	return ISP_UpdateChipFlashBuffer(ISPx, pVal, index, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������ݵ�ָ�������ݴ洢��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_UpdateChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr)
{
	return ISP_UpdateChipFlashAddr(ISPx, externAddr, highAddr, lowAddr);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������ݵ�ָ�������ݴ洢��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_UpdateChipFlashLongAddr(ISP_HandlerType *ISPx, UINT32_T addr)
{
	return ISP_UpdateChipFlashLongAddr(ISPx, addr);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ҳģʽ��ָ��������д��Flash
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipFlashPage(ISP_HandlerType* ISPx,UINT8_T *pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr,UINT16_T length)
{
	UINT8_T _return=OK_0;
	UINT32_T pageAddr = 0;
	//---�����ֽڵ�ַ��֮����Ҫ������ֵ�ַ
	pageAddr=externAddr;
	pageAddr=(pageAddr<<8)+highAddr;
	pageAddr+=lowAddr;
	//---�����ַ��ƫ��
	pageAddr+=length;
	//---������ݻ���
	_return= ISP_UpdateChipFlashBuffer(ISPx,pVal,(UINT8_T)ISPx->msgPageWordIndex,length);
	//---���㷵�ؽ��
	_return = (_return == OK_0 ? OK_0 : ERROR_1);
	//---������������ִ������д�����
	if ((_return==OK_0)&&(ISPx->msgPageWordIndex==ISPx->msgFlashPageWordSize))
	{
		//---���ֽڵ�ַ������ֵ�ַ
		pageAddr >>= 1;
		//---�������ݵ�ָ����ҳ��ַ
		_return= ISP_UpdateChipFlashLongAddr(ISPx,pageAddr);
		//---���ݻ�������
		ISPx->msgPageWordIndex=0;
		//---���㷵�ؽ��
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_CheckChipFlashEmpty(ISP_HandlerType* ISPx, UINT8_T pageByteSizeH, UINT8_T pageByteSizeL, UINT8_T pageNumH, UINT8_T pageNumL)
{
	return ISP_CheckChipFlashEmpty(ISPx, pageByteSizeH, pageByteSizeL, pageNumH, pageNumL);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_CheckChipFlashEmptyLong(ISP_HandlerType* ISPx, UINT16_T pageByteSize, UINT16_T pageNum)
{
	return ISP_CheckChipFlashEmptyLong(ISPx, pageByteSize, pageNum);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_CheckChipEepromEmpty(ISP_HandlerType* ISPx, UINT8_T byteSize, UINT8_T num)
{
	return ISP_CheckChipEepromEmpty(ISPx, byteSize, num);
}