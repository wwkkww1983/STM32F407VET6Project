#include "usart_task.h"

//===ȫ�ֱ����Ķ���
UINT8_T USART1_RX_BUFFER[USART1_RX_MAX_SIZE] = { 0 };
UINT8_T USART1_TX_BUFFER[USART1_RX_MAX_SIZE] = { 0 };

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTTask_Init(USART_HandlerType*  USARTx, UINT16_T rxSize, UINT8_T* pRxVal, UINT8_T rxCRCFlag, UINT16_T txSize, UINT8_T* pTxVal, UINT8_T txCRCFlag, UINT32_T(*pTimerTick)(void))
{
	UINT8_T _return = OK_0;
	//_return = USARTLib_ParamInit(USARTx, USART1_DEVICE_ID, USART1_ID_INDEX, USART1_CMD_INDEX, USART1_DATA1_INDEX, USART1_DATA2_INDEX);
	_return = USARTLib_Init(USARTx, rxSize, pRxVal, rxCRCFlag, txSize, pTxVal, txCRCFlag, pTimerTick);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTTask_DeInit(USART_HandlerType*  USARTx)
{
	return USARTLib_DeInit(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTTask_ParamInit(USART_HandlerType *USARTx, UINT8_T id, UINT8_T idIndex, UINT8_T cmdIndex, UINT8_T d1Index, UINT8_T d2Index)
{
	return USARTLib_ParamInit(USARTx, id, idIndex, cmdIndex, d1Index, d2Index);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTTask_Read_Init(USART_HandlerType*  USARTx)
{
	return USARTLib_Read_Init(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTTask_GetState(USART_HandlerDef* USARTDefx)
{
	return USARTLib_GetState(USARTDefx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTTask_ClearState(USART_HandlerDef* USARTDefx)
{
	return USARTLib_ClearState(USARTDefx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTTask_TimeTask_OverFlow(USART_HandlerType*USARTx)
{
	//---����
	//USARTLib_TimeTask_OverFlow(USARTx, 0);
	//---����
	return  USARTLib_TimeTask_OverFlow(USARTx, 1);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTTask_ITRead_8BitsTask(USART_HandlerType*USARTx, UINT8_T val)
{
	return USARTLib_ITRead_8BitsTask(USARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTTask_ITRead_16BitsTask(USART_HandlerType*USARTx, UINT8_T val)
{
	return USARTLib_ITRead_16BitsTask(USARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTTask_ITRead_Task(USART_HandlerType*USARTx, UINT8_T val)
{
	return USARTLib_ITRead_Task(USARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTTask_Write_Init(USART_HandlerType*USARTx)
{
	return USARTLib_Write_Init(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTTask_ITWrite_TXETask(USART_HandlerType*USARTx)
{
	return USARTLib_ITWrite_TXETask(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTTask_ITWrite_TCTask(USART_HandlerType*USARTx)
{
	return USARTLib_ITWrite_TCTask(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTTask_RealTime_AddByte(USART_HandlerType*USARTx, UINT8_T val)
{
	return USARTLib_RealTime_AddByte(USARTx, val);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTTask_RealTime_AddSize(USART_HandlerType*USARTx, UINT16_T val)
{
	return USARTLib_RealTime_AddSize(USARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTTask_RealTime_AddCRC(USART_HandlerType*USARTx)
{
	return USARTLib_RealTime_AddCRC(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T	 USARTTask_FillMode_Init( USART_HandlerType*USARTx, UINT8_T isChildCmd)
{
	return USARTLib_FillMode_Init(USARTx,isChildCmd);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTTask_FillMode_AddByte(USART_HandlerType*USARTx, UINT8_T val)
{
	return  USARTLib_FillMode_AddByte(USARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTTask_FillMode_AddData(USART_HandlerType*USARTx, UINT8_T *pVal, UINT16_T length)
{
	return  USARTLib_FillMode_AddData(USARTx, pVal, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T	 USARTTask_FillMode_SetResultFlag(USART_HandlerType* USARTx, UINT8_T val)
{
	return USARTLib_FillMode_SetResultFlag(USARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTTask_FillMode_AddIndexW(USART_HandlerType* USARTx, UINT16_T val)
{
	return USARTLib_FillMode_AddIndexW(USARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTTask_CRCTask_Read(USART_HandlerType*USARTx)
{
	return USARTLib_CRCTask_Read(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTTask_CRCTask_Write(USART_HandlerType*USARTx)
{
	return USARTLib_CRCTask_Write(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��ֽ�ģʽ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTTask_FillMode_WriteByteSTART(USART_HandlerType*USARTx, UINT8_T isNeedID)
{
	return USARTLib_FillMode_WriteByteSTART(USARTx, isNeedID);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ģʽ��������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTTask_FillMode_WriteArraySTART(USART_HandlerType* USARTx, UINT8_T* pArrayVal, UINT16_T length)
{
	return USARTLib_FillMode_WriteArraySTART(USARTx, pArrayVal, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTTask_PollMode_WriteByte(USART_HandlerType*USARTx, UINT8_T  val)
{
	return USARTLib_PollMode_WriteByte(USARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTTask_PollMode_WriteData(USART_HandlerType*USARTx, char *pVal)
{
	return  USARTLib_PollMode_WriteData(USARTx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void USARTTask_PrintfClockFreq(USART_HandlerType*USARTx)
{
	USARTLib_PrintfClockFreq(USARTx);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTTask_IT_TCTask(USART_HandlerType* USARTx)
{
	return USARTLib_IT_TCTask(USARTx);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� У���豸��ID��Ϣ
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTTask_DeviceID(USART_HandlerType*USARTx)
{
	return USARTLib_DeviceID(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��жϴ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void USARTTask_IRQTask(USART_HandlerType* USARTx)
{
	USARTLib_IRQTask(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void USARTTask_Read_DMA_IRQTask(USART_HandlerType* USARTx)
{
	USARTLib_Read_DMA_IRQTask(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void USARTTask_Write_DMA_IRQTask(USART_HandlerType* USARTx)
{
	USARTLib_Write_DMA_IRQTask(USARTx);
}

UINT16_T usartDebugCount=0;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTTask_FuncTask(USART_HandlerType*USARTx, UINT8_T(*pFuncTask)(UINT8_T *, UINT8_T *))
{
	UINT16_T length = 0;
	if (USARTx != NULL)
	{
		//---�жϽ����Ƿ����
		if (USARTTask_GetState(&(USARTx->msgRxdHandler)) == 1)
		{
			//---CRC��У��
			if ((USARTTask_CRCTask_Read(USARTx) == OK_0) && (USARTTask_DeviceID(USARTx) == OK_0))
			{
				//---���ݽ������
				if (pFuncTask != NULL)
				{
					pFuncTask(USARTx->msgRxdHandler.pMsgVal, USARTx->msgTxdHandler.pMsgVal);
				}
				else
				{
					USARTTask_FillMode_AddData(USARTx, USARTx->msgRxdHandler.pMsgVal, USARTx->msgRxdHandler.msgCount);
					//---�������ݷ���
					USARTTask_FillMode_WriteByteSTART(USARTx, 0);
					usartDebugCount++;
					USART_Printf(pUsart1, "TEST Count:%d\r\n", usartDebugCount);
				}
			}
			else
			{
				//---����CRCУ�����
				USART_Printf(USARTx, (void*)"=>>SP%d:CRC Check Error<<=\r\n", (USARTx->msgIndex - 1));
			}
			return USARTTask_Read_Init(USARTx);
		}
		return USARTTask_TimeTask_OverFlow(USARTx);
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
UINT8_T USARTTask_DebugPollFuncTask(USART_HandlerType*USARTx, UINT8_T(*pFuncTask)(UINT8_T *, UINT8_T *))
{
	//UINT16_T length = 0;
	UINT32_T freqVal = 0;
	if (USARTx != NULL)
	{
		//---�жϽ����Ƿ����
		if (USARTTask_GetState(&(USARTx->msgRxdHandler)) == 1)
		{
			//---CRC��У��
			if ((USARTTask_CRCTask_Read(USARTx) == OK_0) && (USARTTask_DeviceID(USARTx) == OK_0))
			{
				if (USARTx->msgRxdHandler.pMsgVal[USART1_CMD_INDEX]==0xA4)
				{
					//---��ȡʱ��Ƶ��
					TimerTask_CalcFreq_Task(0);
					//---����Ƶ��
					freqVal = (UINT32_T)(pCalcFreq->msgFreqKHz[pCalcFreq->msgChannel] * 100);
				}

				USARTTask_FillMode_Init(USARTx,0);
				//USARTTask_FillMode_AddByte(USARTx, 0xA4);
				USARTTask_FillMode_AddByte(USARTx, 0x00);
				USARTTask_FillMode_AddByte(USARTx, (UINT8_T)(freqVal >> 24));
				USARTTask_FillMode_AddByte(USARTx, (UINT8_T)(freqVal >> 16));
				USARTTask_FillMode_AddByte(USARTx, (UINT8_T)(freqVal >> 8));
				USARTTask_FillMode_AddByte(USARTx, (UINT8_T)(freqVal ));

				USARTTask_FillMode_WriteByteSTART(USARTx, 0);
			}
			else
			{
				//---����CRCУ�����
				USART_Printf(USARTx, "=>>SP%d:CRC Check Error<<=\r\n", (USARTx->msgIndex - 1));
			}
			return USARTTask_Read_Init(USARTx);
		}
		return USARTTask_TimeTask_OverFlow(USARTx);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Ƶ�ʲ��Ժ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTTask_DebugFreqTask(USART_HandlerType* USARTx, UINT8_T(*pFuncTask)(UINT8_T*, UINT8_T*))
{
	//UINT16_T length = 0;
	UINT32_T freqVal = 0;
	UINT8_T _return=0;
	if (USARTx != NULL)
	{
		//---�жϽ����Ƿ����
		if (USARTTask_GetState(&(USARTx->msgRxdHandler)) == 1)
		{
			//---CRC��У��
			if ((USARTTask_CRCTask_Read(USARTx) == OK_0) && (USARTTask_DeviceID(USARTx) == OK_0))
			{
				if (USARTx->msgRxdHandler.pMsgVal[USART1_CMD_INDEX] == 0xA4)
				{
					//---�Ƿ������ϵ�
					if (USARTx->msgRxdHandler.pMsgVal[USART1_CMD_INDEX + 1] != 0)
					{
						LM317_POWER_OFF;
						freqVal= USARTx->msgRxdHandler.pMsgVal[USART1_CMD_INDEX + 2];
						freqVal = (freqVal<<8)+USARTx->msgRxdHandler.pMsgVal[USART1_CMD_INDEX + 3];
						//---��ʼ��LM317���Ŀɵ���Դ
						LM317Task_Init(0, freqVal);
						LM317_POWER_ON;
					}
					#ifdef STM32_USE_F407VET6
						//---���������ź�
						GPIO_OUT_0(TRIG_PULSE_PORT, TRIG_PULSE_BIT);
						DelayTask_us(500);
						GPIO_OUT_1(TRIG_PULSE_PORT, TRIG_PULSE_BIT);
						DelayTask_us(500);
						//---��ʱ100ms����ȡƵ��ֵ
						DelayTask_ms(100);
						//---��ȡУ׼��
						_return=DataBus_Read();
					#endif
					//---��ȡʱ��Ƶ��
					TimerTask_CalcFreq_Task(0);
					//---����Ƶ��
					freqVal = (UINT32_T)(pCalcFreq->msgFreqKHz[pCalcFreq->msgChannel] * 100);
				}
				//USARTTask_FillMode_AddByte(USARTx, 0xA4);
				USARTTask_FillMode_Init(USARTx, 0);
				USARTTask_FillMode_AddByte(USARTx, 0x00);
				//---��ȡУ׼��
				USARTTask_FillMode_AddByte(USARTx, _return);
				USARTTask_FillMode_AddByte(USARTx, (UINT8_T)(freqVal >> 24));
				USARTTask_FillMode_AddByte(USARTx, (UINT8_T)(freqVal >> 16));
				USARTTask_FillMode_AddByte(USARTx, (UINT8_T)(freqVal >> 8));
				USARTTask_FillMode_AddByte(USARTx, (UINT8_T)(freqVal));
				//---�������ݷ���
				USARTTask_FillMode_WriteByteSTART(USARTx, 0);
			}
			else
			{
				//---����CRCУ�����
				USART_Printf(USARTx, "=>>SP%d:CRC Check Error<<=\r\n", (USARTx->msgIndex - 1));
			}
			return USARTTask_Read_Init(USARTx);
		}
		return USARTTask_TimeTask_OverFlow(USARTx);
	}
	return ERROR_2;
}
