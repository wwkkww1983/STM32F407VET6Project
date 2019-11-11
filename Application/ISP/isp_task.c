#include "isp_task.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_Init(ISP_HandlerType *ISPx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	return ISPLib_Init(ISPx, pFuncDelayus, pFuncDelayms, pFuncTimerTick);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_DeInit(ISP_HandlerType *ISPx)
{
	return ISPLib_DeInit(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_EnterProg(ISP_HandlerType *ISPx, UINT8_T isPollReady)
{
	return ISPLib_EnterProg(ISPx,isPollReady);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ExitProg(ISP_HandlerType *ISPx)
{
	return ISPLib_ExitProg(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_AddWatch(ISP_HandlerType* ISPx)
{
	return ISPLib_AddWatch(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_RemoveWatch(ISP_HandlerType* ISPx)
{
	return ISPLib_RemoveWatch(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_RefreshWatch(ISP_HandlerType* ISPx)
{
	return ISPLib_RefreshWatch(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadReady(ISP_HandlerType *ISPx)
{
	return ISPLib_ReadReady(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_EraseChip(ISP_HandlerType *ISPx)
{
	return ISPLib_EraseChip(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipID(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	return ISPLib_ReadChipID(ISPx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipCalibration(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T length)
{
	return ISPLib_ReadChipCalibration(ISPx, pVal, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
{
	return ISPLib_ReadChipFuse(ISPx, pVal, isNeedExternFuse);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipLock(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	return ISPLib_ReadChipLock(ISPx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipRom(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T addr, UINT16_T length)
{
	return ISPLib_ReadChipRom(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
{
	return ISPLib_WriteChipFuse(ISPx, pVal, isNeedExternFuse);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipLock(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	return ISPLib_WriteChipLock(ISPx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISPLib_ReadChipEepromAddr(ISPx, pVal, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return ISPLib_ReadChipEepromLongAddr(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISPLib_WriteChipEepromAddr(ISPx, pVal, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return ISPLib_WriteChipEepromLongAddr(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipEepromAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISPLib_WriteChipEepromAddrWithJumpEmpty(ISPx, pVal, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipEepromLongAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return  ISPLib_WriteChipEepromLongAddrWithJumpEmpty(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateExternAddr(ISP_HandlerType *ISPx, UINT8_T addr)
{
	return ISPLib_UpdateExternAddr(ISPx, addr);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateExternLongAddr(ISP_HandlerType *ISPx, UINT32_T addr)
{
	return ISPLib_UpdateExternLongAddr(ISPx, addr);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISPLib_ReadChipFlashAddr(ISPx, pVal, externAddr, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipFlashLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT32_T addr, UINT16_T length)
{
	return ISPLib_ReadChipFlashLongAddr(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateChipFlashBuffer(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T index, UINT16_T length)
{
	return ISPLib_UpdateChipFlashBuffer(ISPx, pVal, index, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr)
{
	return ISPLib_UpdateChipFlashAddr(ISPx, externAddr, highAddr, lowAddr);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateChipFlashLongAddr(ISP_HandlerType *ISPx, UINT32_T addr)
{
	return ISPLib_UpdateChipFlashLongAddr(ISPx, addr);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��˳����߽�����ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_USARTCmd_OpenAndClose(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T	_return=0;
	//---����λ��
	if (USARTx->msgRxHandler.pMsgVal[USARTx->msgDataOneIndex]==1)
	{
		_return=ISPTask_EnterProg(ISPx, USARTx->msgRxHandler.pMsgVal[USARTx->msgDataTwoIndex]);
	}
	else
	{
		_return = ISPTask_ExitProg(ISPx);
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
UINT8_T ISPTask_USARTCmd_EraseChip(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState==0)
	{
		//---������ģʽ
		_return = ISPTask_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	//---���ģʽ��֤
	if (_return==OK_0)
	{
		//---�豸����
		_return = ISPTask_EraseChip(ISPx);
	}
	//---ִ�н��
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡоƬID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_USARTCmd_ReadChipID(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISPTask_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	//---���ģʽ��֤
	if (_return==OK_0)
	{
		//---��ȡ�豸ID��Ϣ
		_return = ISPTask_ReadChipID(ISPx, USARTx->msgTxHandler.pMsgVal + USARTx->msgTxHandler.msgIndexW);
		//---���ݳ���ƫ��
		USARTx->msgTxHandler.msgIndexW += 3;
	}
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
UINT8_T ISPTask_USARTCmd_ReadChipCalibration(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISPTask_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	//---���ģʽ��֤
	if (_return==OK_0)
	{
		//---��ȡ�豸��У׼��
		_return = ISPTask_ReadChipCalibration(ISPx, USARTx->msgTxHandler.pMsgVal + USARTx->msgTxHandler.msgIndexW, USARTx->msgRxHandler.pMsgVal[USARTx->msgDataOneIndex]);
		//---���ݵ�ַƫ��
		USARTx->msgTxHandler.msgIndexW += USARTx->msgRxHandler.pMsgVal[USARTx->msgDataOneIndex];
	}
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
UINT8_T ISPTask_USARTCmd_ReadChipFuseAndLock(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISPTask_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	//---���ģʽ��֤
	if (_return == OK_0)
	{
		//---�ж��Ƕ�ȡ��˿λ���Ǽ���λ
		if (USARTx->msgRxHandler.pMsgVal[USARTx->msgDataOneIndex]==0)
		{
			//---��ȡ��˿λ
			_return=ISPTask_ReadChipFuse(ISPx, USARTx->msgTxHandler.pMsgVal + USARTx->msgTxHandler.msgIndexW, USARTx->msgRxHandler.pMsgVal[USARTx->msgDataTwoIndex]);
			//---У���Ƿ��ȡ��չ��˿λ
			if (USARTx->msgRxHandler.pMsgVal[USARTx->msgDataTwoIndex] != 0)
			{
				USARTx->msgTxHandler.msgIndexW +=1;
			}
			USARTx->msgTxHandler.msgIndexW +=2;
		}
		else 
		{
			//---��ȡ����λ
			_return = ISPTask_ReadChipLock(ISPx, USARTx->msgTxHandler.pMsgVal + USARTx->msgTxHandler.msgIndexW);
			USARTx->msgTxHandler.msgIndexW += 1;
		}
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
UINT8_T ISPTask_USARTCmd_WriteChipFuse(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISPTask_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	//---���ģʽ��֤
	if (_return == OK_0)
	{
		//---�����˿λ
		_return=ISPTask_WriteChipFuse(ISPx, USARTx->msgRxHandler.pMsgVal+USARTx->msgDataTwoIndex, USARTx->msgRxHandler.pMsgVal[USARTx->msgDataOneIndex]);
	}
	//---ִ�н��
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���̼���λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_USARTCmd_WriteChipLock(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISPTask_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	//---���ģʽ��֤
	if (_return == OK_0)
	{
		//---��̼���λ
		_return = ISPTask_WriteChipLock(ISPx, USARTx->msgRxHandler.pMsgVal + USARTx->msgDataTwoIndex);
	}
	//---ִ�н��
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡоƬ��ROM��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_USARTCmd_ReadChipRom(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	UINT16_T length=0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISPTask_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	//---���ģʽ��֤
	if (_return == OK_0)
	{
		//---����Ҫ��ȡ���ݵĳ���
		length= USARTx->msgRxHandler.pMsgVal[USARTx->msgDataTwoIndex];
		length=(length<<8)+ USARTx->msgRxHandler.pMsgVal[USARTx->msgDataOneIndex+1];
		//---��ȡROMҳ��Ϣ
		_return=ISPTask_ReadChipRom(ISPx, USARTx->msgTxHandler.pMsgVal + USARTx->msgTxHandler.msgIndexW, USARTx->msgRxHandler.pMsgVal[USARTx->msgDataOneIndex],length);
	}
	//---ִ�н��
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_USARTCmd_ChildTask(ISP_HandlerType* ISPx, USART_HandlerType* USARTx,UINT8_T isChildCmd)
{
	UINT8_T _return = 0;
	//---������ִ�н��
	USARTTask_FillMode_AddByte(USARTx, 0x00);
	//---���������������
	switch (USARTx->msgRxHandler.pMsgVal[USARTx->msgCmdIndex+ (isChildCmd == 0 ? 0 : 1)])
	{
		case CMD_ISP_OPEN_CLOSE:
			//---����֮�󣬵�1�ֽ�0---����رգ�1---����򿪣���2�ֽ�����йأ���ر��޹�
			_return= ISPTask_USARTCmd_OpenAndClose(ISPx,USARTx);
			break;
		case CMD_ISP_ERASE:
			//---�����豸
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
		default:
			//---��ʶ�������
			_return = ERROR_1;
			break;
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
UINT8_T ISPTask_USARTCmd_ParentTask(ISP_HandlerType* ISPx, USART_HandlerType* USARTx, UINT8_T isChildCmd)
{
	UINT8_T _return = 0;
	if ((USARTx != NULL) && (ISPx != NULL))
	{
		//---�жϽ����Ƿ����
		if (USARTTask_GetReadState(USARTx) == 1)
		{
			//---CRC��У����豸IDУ��
			if ((USARTTask_CRCTask_Read(USARTx) == OK_0) && (USARTTask_DeviceID(USARTx) == OK_0))
			{
				//---����������������ݱ�ͷ�����ȣ���ַID�Ĵ���
				USARTTask_FillMode_Init(USARTx,isChildCmd);
				//---����������
				_return=ISPTask_USARTCmd_ChildTask(ISPx, USARTx, isChildCmd);
				//---���ؽ�����������������
				//USARTTask_FillMode_AddByte(USARTx, 0x00);
				//---�Ƿ���Ҫ���ӻ��з�
				if (USARTx->msgTxHandler.msgAddNewLine == 1)
				{
					USARTTask_FillMode_AddByte(USARTx, 0x0D);
					USARTTask_FillMode_AddByte(USARTx, 0x0A);
				}
				//---�������ݷ���
				USARTTask_FillMode_WriteSTART(USARTx, 0);
			}
			else
			{
				//---����CRCУ�����
				USART_Printf(USARTx, "=>>����%d:����CRCУ�����<<=\r\n", (USARTx->msgIndex - 1));
			}
			return USARTTask_ReadInit(USARTx);
		}
		return USARTTask_TimeOVFTask(USARTx);
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
UINT8_T ISPTask_USARTCmd_Task(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T _return = OK_0;
	_return= ISPTask_USARTCmd_ParentTask(ISPx, USARTx, 0);
	return _return;
}